#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdlib> 
#include <ctime> 

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include "Graphics/Window/WindowManager.h"
#include "System/Debug/LogManager.h"
#include "Net/Connection.h"
#include "Net/Address.h"
#include "Net/Socket.h"
#include "Net/Message/Message.h"
#include "Net/Message/SimpleMessage/SimpleMessage.h"
#include "Net/Message/SimpleMessage/SimpleMessageFactory.h"
#include <conio.h>

#include "Client.h"

#define PORT 4002

int main()
{
	std::cout << "Client running..." << std::endl;

	CLogManager::Instance().StartUp();
	CWindowManager::Instance().StartUp();
	//CWindowManager::Instance().SetWindowPos(1500, 100);
	GLFWwindow* window = CWindowManager::Instance().GetWindow();

	// Create client
	CAddress serverAddr(127, 0, 0, 1, 2000);
	CClient client(serverAddr, PORT);

	CSimpleMsgFactory facSend;
	std::vector<CMessage*> recvMessages;
	
	auto last = std::chrono::steady_clock::now();
	int count = 0;
	std::srand((unsigned)time(0));
	int dur = 10;

	while (!_kbhit()
		&& glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		CWindowManager::Instance().Update();

		auto now = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (now - last).count();


		// 4 ups/s
		if (duration > dur)
		{

			if (client.Receive(facSend, recvMessages))
			{
				std::cout << "Messages: " << recvMessages.size() << std::endl;

				CMessage* msg = recvMessages[1];
				if (msg->GetType() == CSimpleMsgFactory::ETypes::SIMPLE_MESSAGE)
				{
					CSimpleMessage* msgRecv = (CSimpleMessage*)msg; 
					std::cout << "Server: " << msgRecv->ToString() << std::endl;
				}
				facSend.ReleaseMessages(recvMessages);
			}

			CSimpleMessage* sendMessage = (CSimpleMessage*)facSend.CreateMessage(CSimpleMsgFactory::ETypes::SIMPLE_MESSAGE);
			sendMessage->SetMessage(count);

			CCameraMessage* camPosMsg = (CCameraMessage*)facSend.CreateMessage(CSimpleMsgFactory::ETypes::CAMERA_POSITION_MESSAGE);
			CCamera& cam = CWindowManager::Instance().GetCamera();
			camPosMsg->SetMessage(cam.GetHorizontalAngle(),
				cam.GetVerticalAngle(),
				cam.GetPosition().x,
				cam.GetPosition().y,
				cam.GetPosition().z);

			std::vector<CMessage*> messages = { sendMessage, camPosMsg };
	
			client.Send(facSend, messages);

			facSend.ReleaseMessage(sendMessage);

			last = now;
			count++;

		}
	}

	CWindowManager::Instance().ShutDown();
	CLogManager::Instance().ShutDown();

	return 0;
}
