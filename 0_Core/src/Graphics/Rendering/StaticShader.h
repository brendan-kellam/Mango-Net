#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "Platform.h"
#include "ShaderProgram.h"
#include "System/Entity/Camera.h"
#include "Util/Math.h"

#define VERTEX_FILE   "C:\\Users\\poptart\\Documents\\c++\\Mango\\Resources\\Shaders\\VertexShader.glsl"
#define FRAGMENT_FILE "C:\\Users\\poptart\\Documents\\c++\\Mango\\Resources\\Shaders\\FragmentShader.glsl"

class MANGO_API CStaticShader 
	: public CShaderProgram
{
public:

	virtual void Init() override;

	void LoadTransformationMatrix(glm::mat4 matrix);

	void LoadViewMatrix(CCamera& camera);

	void LoadProjectionMatrix(glm::mat4 projection);
	

protected:

	virtual void GetAllUniformLocations() override;
	virtual void BindAttributes() override;

private:
	GLint m_transMatrixLocation;
	GLint m_projectionMatrixLocation;
	GLint m_viewMatrixLocation;

};


#endif 