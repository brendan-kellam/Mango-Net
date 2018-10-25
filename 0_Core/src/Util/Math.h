#ifndef MATH_H
#define MATH_H

#include "Platform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> 
#include "System/Entity/Camera.h"

static glm::mat4 MANGO_API CreateTransformation(glm::vec3 translation, float rx, float ry, float rz, float scale)
{
	
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
	
	glm::mat4 rotationMatrix
		= glm::rotate(glm::radians(rx), glm::vec3(1, 0, 0))
		* glm::rotate(glm::radians(ry), glm::vec3(0, 1, 0))
		* glm::rotate(glm::radians(rz), glm::vec3(0, 0, 1));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

static glm::mat4 MANGO_API CreateViewMatrix(CCamera& camera)
{
	/*
	glm::mat4 rotationMatrix
		= glm::rotate(glm::radians(camera.GetYaw()), glm::vec3(0, 1, 0))
		* glm::rotate(glm::radians(camera.GetPitch()), glm::vec3(1, 0, 0));
		
	
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -camera.GetPosition());

	return  translationMatrix * rotationMatrix;

	*/

	return glm::lookAt(
		camera.GetPosition(),								// Camera Position
		camera.GetPosition() + camera.GetDirection(),		// looks in the directions
		camera.GetUp()										// Head is up 
	);

}


#endif