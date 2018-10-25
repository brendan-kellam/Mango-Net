#include "StaticShader.h"

void CStaticShader::Init()
{
	InitInternal(VERTEX_FILE, FRAGMENT_FILE);
}

void CStaticShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	LoadMatrix(m_transMatrixLocation, matrix);
}

void CStaticShader::LoadViewMatrix(CCamera& camera)
{
	glm::mat4 viewMatrix = CreateViewMatrix(camera);
	LoadMatrix(m_viewMatrixLocation, viewMatrix);
}

void CStaticShader::LoadProjectionMatrix(glm::mat4 projection)
{
	LoadMatrix(m_projectionMatrixLocation, projection);
}

void CStaticShader::GetAllUniformLocations()
{
	m_transMatrixLocation = GetUniformLocation("transformationMatrix");
	m_projectionMatrixLocation = GetUniformLocation("projectionMatrix");
	m_viewMatrixLocation = GetUniformLocation("viewMatrix");
}

void CStaticShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCords");
}
