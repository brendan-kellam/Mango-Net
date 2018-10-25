#ifndef RENDERER_H
#define RENDERER_H

#include "System/Entity/Entity.h"
#include "StaticShader.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class MANGO_API CRenderer
{

public:

	CRenderer(CStaticShader& shader);

	void Prepare();
	void Render(CEntity& entity, CStaticShader& shader);

private:
	glm::mat4 m_projectionMatrix;

	const float FOV = 70.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 100.0f;
	const float ASPECT_RATIO = 4.0f / 3.0f;

};



#endif