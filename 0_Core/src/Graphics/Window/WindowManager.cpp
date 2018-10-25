
#include "WindowManager.h"

#include "Graphics/Rendering/RawModel.h"
#include "Graphics/Rendering/ModelTexture.h"
#include "Graphics/Rendering/TexturedModel.h"


#include <glm/gtc/matrix_transform.hpp>


/* Create window */
void CWindowManager::StartUp()
{
	m_width = 1024;
	m_height = 768;
	m_mouseEnabled = true;

	// Create a new GLFW window
	CreateNewWindow();

	m_renderer = new CRenderer(m_shader);

	std::vector<float> vertices = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f

	};

	std::vector<float> textureCords = {
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
	};

	std::vector<int> indices = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22
	};
	
	CRawModel model = m_loader.LoadToVAO(vertices, textureCords, indices);
	CModelTexture texture(m_loader.LoadTexture("C:\\Users\\poptart\\Documents\\c++\\Mango\\Resources\\Textures\\fish.png"));
	
	CTexturedModel texturedModel(model, texture);

	m_entity = new CEntity(texturedModel, glm::vec3(0, 0, -5.0f), 0, 0, 0, 1);
}

void CWindowManager::Update()
{
	m_entity->IncreaseRotation(0.2f, 0.0f, 0.0f);

	m_camera.Move(m_window, m_mouseEnabled);

	m_renderer->Prepare();
	m_shader.Start();

	// Move shader
	m_shader.LoadViewMatrix(m_camera);

	m_renderer->Render(*m_entity, m_shader);

	m_shader.Stop();

	// swap buffers
	glfwSwapBuffers(m_window);	// Swap front and back buffers for specified window
	glfwPollEvents();			// Process all pending events

}

bool CWindowManager::CreateNewWindow()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // make osx happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Gives us new OpenGL


																   /// Open a window and create it's OpenGL context
	m_window = glfwCreateWindow(m_width, m_height, "Mango Engine", NULL, NULL);
	if (m_window == nullptr)
	{
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Opengl Context creation
	glfwMakeContextCurrent(m_window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return false;
	}

	return true;
}

void CWindowManager::SetWindowPos(int x, int y)
{
	glfwSetWindowPos(m_window, x, y);
}

void CWindowManager::ShutDown()
{
	delete m_renderer;
	delete m_entity;
	m_loader.CleanUp();
	m_shader.CleanUp();
}




