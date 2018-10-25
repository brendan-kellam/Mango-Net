
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <stdio.h>
#include <iostream>
#include "System/Debug/LogManager.h"
#include "Graphics/Window/WindowManager.h"
#include "ConnectionManager.h"
#include <conio.h>

int main()
{
	std::cout << "Server running..." << std::endl;

	CLogManager::Instance().StartUp();
	CConnectionManager::Instance().StartUp();
	CWindowManager::Instance().StartUp();
	CWindowManager::Instance().m_mouseEnabled = false;
	//CWindowManager::Instance().SetWindowPos(100, 100);
	GLFWwindow* window = CWindowManager::Instance().GetWindow();
	

	while (!_kbhit()
		&& glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0)
	{
		CConnectionManager::Instance().Update();
		CWindowManager::Instance().Update();
	}


	CWindowManager::Instance().ShutDown();
	CConnectionManager::Instance().ShutDown();
	CLogManager::Instance().ShutDown();

	return 0;
}