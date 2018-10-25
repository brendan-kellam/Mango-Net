#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H


//
// Notes:
//	- When using GLEW, ensure all #include-s are done before opengl #include-s
//	
//

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Platform.h"
#include "Util/Singleton.h"
#include "Util/Interfaces/Manager.h"
#include "Util/Interfaces/Updatable.h"
#include "Graphics/Rendering/LoadShader.h"
#include "Graphics/Rendering/Loader.h"
#include "Graphics/Rendering/Renderer.h"
#include "Graphics/Rendering/StaticShader.h"
#include "System/Entity/Entity.h"
#include "System/Entity/Camera.h"

class MANGO_API CWindowManager
	: public CSingleton<CWindowManager>, public IManager, public IUpdateable
{ 

public:
	

	void StartUp() override;
	void ShutDown() override;

	void Update() override;

	GLFWwindow* GetWindow() const { return m_window; }
	CCamera& GetCamera() { return m_camera; }

	void SetWindowPos(int x, int y);

	bool m_mouseEnabled;

private:
	
	bool CreateNewWindow();


	GLFWwindow* m_window;
	int m_height;
	int m_width;

	CLoader m_loader;
	CStaticShader m_shader;
	CCamera m_camera;

	CRenderer* m_renderer;
	CEntity* m_entity;

};

#endif /* WINDOWMANAGER_H */