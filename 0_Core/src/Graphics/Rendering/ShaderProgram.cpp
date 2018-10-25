#include "ShaderProgram.h"

void CShaderProgram::InitInternal(std::string vertexFile, std::string fragmentFile)
{
	m_vertexShaderID = LoadShader(vertexFile, GL_VERTEX_SHADER);
	m_fragmentShaderID = LoadShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	// Link inputs to VAO
	BindAttributes();

	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	int infoLogLength;
	GLint result = GL_FALSE;

	// Check the program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}

	// Get all uniform locations
	GetAllUniformLocations();
}

void CShaderProgram::Start()
{
	glUseProgram(m_programID);
}

void CShaderProgram::Stop()
{
	glUseProgram(0);
}

void CShaderProgram::CleanUp()
{
	Stop();
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_programID);
}

GLint CShaderProgram::GetUniformLocation(const GLchar* uniformName)
{
	return glGetUniformLocation(m_programID, uniformName);
}

void CShaderProgram::LoadFloat(GLint location, const GLfloat value)
{
	glUniform1f(location, value);
}

void CShaderProgram::LoadVector(GLint location, const glm::vec3& vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void CShaderProgram::LoadBoolean(GLint location, const bool value)
{
	glUniform1f(location, value);
}

void CShaderProgram::LoadMatrix(GLint location, const glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void CShaderProgram::BindAttribute(int attribute, const GLchar* variableName)
{
	glBindAttribLocation(m_programID, attribute, variableName);
}