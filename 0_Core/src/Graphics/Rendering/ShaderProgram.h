#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Platform.h"
#include "LoadShader.h"

class MANGO_API CShaderProgram
{
public:
	virtual ~CShaderProgram() {};

	virtual void Init() = 0;

	void Start();
	void Stop();
	void CleanUp();
	GLuint GetProgramID() { return m_programID; }

protected: 

	virtual void GetAllUniformLocations() = 0;
	virtual void BindAttributes() = 0;

	GLint GetUniformLocation(const GLchar* uniformName);

	void LoadFloat(GLint location, const GLfloat value);
	void LoadVector(GLint location, const glm::vec3& vec);
	void LoadBoolean(GLint location, const bool value);
	void LoadMatrix(GLint location, const glm::mat4 matrix);


	// Binds a shader variable to a VAO attribute
	void BindAttribute(int attribute, const GLchar* variableName);

	void InitInternal(std::string vertexFile, std::string fragmentFile);


private:

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};



#endif