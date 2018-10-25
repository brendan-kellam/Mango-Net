#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class MANGO_API CCamera
{

public:

	CCamera()
		: m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_up(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_horizontalAngle(0.0f),
		m_verticalAngle(0.0f),
		m_fov(m_initialFoV),
		m_lastTime(glfwGetTime())
	{
		//glfwSetScrollCallback(CWindowManager::Instance().GetWindow(), ScrollCB);
	}

	void Move(GLFWwindow* window, bool enabled)
	{
		//GLFWwindow* window = CWindowManager::Instance().GetWindow();


		int windowWidth, windowHeight;	// Window dims
		double xpos, ypos;				// Mouse pos

		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - m_lastTime);


		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glfwGetCursorPos(window, &xpos, &ypos);
		
		if (enabled)
		{
			// Reset cursor position
			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

			m_horizontalAngle -= m_mouseSpeed * deltaTime * float(windowWidth / 2 - xpos);
			m_verticalAngle += m_mouseSpeed * deltaTime * float(windowHeight / 2 - ypos);
		}

		m_direction = glm::vec3(
			cos(m_verticalAngle) * sin(m_horizontalAngle),
			sin(m_verticalAngle),
			cos(m_verticalAngle) * cos(m_horizontalAngle)
		);

		glm::vec3 right(
			sin(m_horizontalAngle - 3.14 / 2.0f),
			0,
			cos(m_horizontalAngle - 3.14f / 2.0f)
		);

		m_up = glm::cross(right, m_direction);

		if (enabled)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				m_position += m_direction * deltaTime * m_speed;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				m_position -= m_direction * deltaTime * m_speed;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				m_position += right * deltaTime * m_speed;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				m_position -= right * deltaTime * m_speed;
			}
		}

		m_lastTime = currentTime;
	}
	
	glm::vec3& GetPosition()
	{
		return m_position;
	}

	glm::vec3& GetDirection()
	{
		return m_direction;
	}

	void SetPosition(float x, float y, float z)
	{
		m_position = glm::vec3(x, y, z);
	}

	float& GetHorizontalAngle()
	{
		return m_horizontalAngle;
	}

	float& GetVerticalAngle()
	{
		return m_verticalAngle;
	}

	glm::vec3& GetUp()
	{
		return m_up;
	}

private:

	float m_horizontalAngle;
	float m_verticalAngle;
	float m_fov;
	
	const float m_initialFoV = 45.0f;
	const float m_speed = 3.0f;
	const float m_mouseSpeed = 0.5f;

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	double m_lastTime;

};

#endif