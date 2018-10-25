#include "Renderer.h"
#include "Util/Math.h"
#include "TexturedModel.h"

#include <vector>

CRenderer::CRenderer(CStaticShader& shader)
{
	m_projectionMatrix = glm::perspective(
		glm::radians(FOV),
		ASPECT_RATIO,
		NEAR_PLANE,
		FAR_PLANE
	);

	shader.Init();

	shader.Start();

	// Load projection matrix
	shader.LoadProjectionMatrix(m_projectionMatrix);

	shader.Stop();
}

void CRenderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void CRenderer::Render(CEntity& entity, CStaticShader& shader)
{
	CTexturedModel& texturedModel = entity.GetModel();
	CRawModel& model = texturedModel.GetModel();

	// Bind the VAO
	glBindVertexArray(model.GetVAOId());

	// Activate the attribute list
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 transformationMatrix = CreateTransformation(entity.GetPosition(), entity.GetRotX(), entity.GetRotY(), entity.GetRotZ(), entity.GetScale());
	shader.LoadTransformationMatrix(transformationMatrix);


	//glBindTexture(GL_TEXTURE_2D, texturedModel.GetTexture().GetID());

	glDrawElements(
		GL_TRIANGLES,
		model.GetVertexCount(),
		GL_UNSIGNED_INT,
		(void*)0
	);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}
