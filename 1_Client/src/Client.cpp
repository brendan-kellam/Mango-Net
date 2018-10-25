#include "Client.h"

CClient::CClient(CAddress& serverAddr, const unsigned short clientPort)
	: m_serverAddr(serverAddr),
	m_clientPort(clientPort)
{
	// Winsock init
	WSAStartup(MAKEWORD(2, 2), &m_wsaData);

	m_socket.Open(m_clientPort);

	m_connection = new CConnection(m_serverAddr, m_socket);
}

CClient::~CClient()
{
	delete m_connection;
}

void CClient::Update()
{
	m_connection->Update();
}

bool CClient::Receive(CMessageFactory& factory, std::vector<CMessage*>& messages)
{
	CAddress from;
	bool res = false;

	int bytesRead = m_socket.Receive(from, m_recvBuf, PACKET_SIZE);
	if (bytesRead > 0 && from == m_serverAddr)
	{
		res = m_connection->Receive(factory, messages, m_recvBuf, PACKET_SIZE);
	}

	// Clear buffer
	memset(m_recvBuf, '\0', PACKET_SIZE);

	return res;
}

bool CClient::Send(CMessageFactory& factory, std::vector<CMessage*>& messages)
{
	return m_connection->Send(factory, messages);
}
