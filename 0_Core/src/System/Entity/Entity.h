#ifndef ENTITY_H
#define ENTITY_H

#include "Graphics/Rendering/TexturedModel.h"
#include <glm/glm.hpp>

class MANGO_API CEntity
{

public:
	CEntity(CTexturedModel& model, glm::vec3& position, float rotX, float rotY, float rotZ,float scale)
		: m_model(model),
		m_position(position),
		m_rotX(rotX), 
		m_rotY(rotY), 
		m_rotZ(rotZ),
		m_scale(scale)
	{

	}

	void IncreasePosition(float dx, float dy, float dz)
	{
		m_position.x += dx;
		m_position.y += dy;
		m_position.z += dz;
	}

	void IncreaseRotation(float dx, float dy, float dz)
	{
		m_rotX += dx;
		m_rotY += dy;
		m_rotZ += dz;
	}

	void SetRotX(float rotX) { m_rotX = rotX; }
	void SetRotY(float rotY) { m_rotY = rotY; }
	void SetRotZ(float rotZ) { m_rotZ = rotZ; }

	float GetRotX() { return m_rotX; }
	float GetRotY() { return m_rotY; }
	float GetRotZ() { return m_rotZ; }

	void SetModel(CTexturedModel& model) { m_model = model; }
	CTexturedModel& GetModel() { return m_model; }

	void SetPosition(glm::vec3& position) { m_position = position; }
	glm::vec3 GetPosition() { return m_position; }

	void SetScale(float scale) { m_scale = scale; }
	float GetScale() { return m_scale; }

private:
	CTexturedModel m_model;
	glm::vec3 m_position;
	float m_rotX, m_rotY, m_rotZ;
	float m_scale;

};



#endif