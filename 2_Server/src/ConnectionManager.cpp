#define _WINSOCK_DEPRECATED_NO_WARNINGS // Supress winsock warnings


#include "ConnectionManager.h"
#include "Graphics/Window/WindowManager.h"
#include "System/Debug/LogManager.h"
#include "Net/Packet/Packet.h"
#include "Net/Message/Message.h"
#include "Net/Message/SimpleMessage/SimpleMessage.h"
#include <conio.h>
#include <stdio.h>

CConnectionManager::CConnectionManager()
{

}

bool CConnectionManager::InitializeWinsock()
{
	return WSAStartup(MAKEWORD(2, 2), &m_wsaData) == NO_ERROR; 
}

bool isKeyPressed(unsigned timeout_ms = 0)
{
	return WaitForSingleObject(
		GetStdHandle(STD_INPUT_HANDLE),
		timeout_ms) == WAIT_OBJECT_0;
}

void CConnectionManager::StartUp()
{
	// --- Initialize winsock
	std::cout << "\nInitialising Winsock...";
	if (!InitializeWinsock())
	{
		std::cout << "Failed. Error code : " << WSAGetLastError();
		exit(EXIT_FAILURE);
	}
	std::cout << "Initialized." << std::endl;
	// ----------------------
	
	if (!m_serverSocket.Open(LOCAL_PORT))
	{
		std::cout << "Failed to create socket! Error code : " << WSAGetLastError() << std::endl;
	}
}

void CConnectionManager::Update()
{
	CSimpleMessage* msg1 = (CSimpleMessage*)m_facSend.CreateMessage(CSimpleMsgFactory::ETypes::SIMPLE_MESSAGE);
	CSimpleMessage* msg2 = (CSimpleMessage*)m_facSend.CreateMessage(CSimpleMsgFactory::ETypes::SIMPLE_MESSAGE);

	msg1->SetMessage(15);
	msg2->SetMessage(10);
	std::vector<CMessage*> messages = { msg1, msg2 };
	
	std::vector<CMessage*> recvMessages;

	CAddress from;
	int bytesRead = m_serverSocket.Receive(from, m_recvBuf, PACKET_SIZE);
	
	if (bytesRead > 0)
	{
		CConnection* connection;


		// ---- EXISTING CONNECTION ----
		if (connection = GetConnection(from))
		{
			connection->Receive(m_facSend, recvMessages, m_recvBuf, PACKET_SIZE);
			connection->Send(m_facSend, messages);

		}
		// ---- NEW CONNECTION ----
		else
		{
			// Create new connection and insert into hashmap
			// TODO: Don't allocate new objects for potential packets not addressed to us!!
			connection = new CConnection(from, m_serverSocket);

			// Check if packet can be received without error
			if (!connection->Receive(m_facSend, recvMessages, m_recvBuf, PACKET_SIZE))
			{
				delete connection;

				// Ignore connection
				return;
			}

			m_connections.insert(ConnectionMap::value_type(from, connection));

			connection->Send(m_facSend, messages);
		}

		std::cout << "Messages: " << recvMessages.size() << std::endl;

		CMessage* msg = recvMessages[1];
		if (msg->GetType() == CSimpleMsgFactory::ETypes::CAMERA_POSITION_MESSAGE)
		{
			CCameraMessage* msgRecv = (CCameraMessage*)msg;
			CCamera& cam = CWindowManager::Instance().GetCamera();
			msgRecv->SetCamera(cam.GetHorizontalAngle(), 
				cam.GetVerticalAngle(), 
				cam.GetPosition().x,
				cam.GetPosition().y,
				cam.GetPosition().z);
		}
			
		m_facSend.ReleaseMessages(recvMessages);
		

	}

	memset(m_recvBuf, '\0', PACKET_SIZE);
	UpdateConnections();

	m_facSend.ReleaseMessage(msg1);
	m_facSend.ReleaseMessage(msg2);

}

void CConnectionManager::UpdateConnections()
{
	for (ConnectionMap::iterator it = m_connections.begin(); it != m_connections.end(); ++it)
	{
		// Update all connections in HashMap
		CConnection* connection = it->second; 
		connection->Update();
	}
}

CConnection* CConnectionManager::GetConnection(CAddress& addr)
{
	auto iter = m_connections.find(addr);
	if (iter != m_connections.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

void CConnectionManager::ShutDown()
{

	// Delete all connections
	while (m_connections.begin() != m_connections.end())
	{
		delete m_connections.begin()->second;
		m_connections.erase(m_connections.begin());
	}

	WSACleanup();
}

