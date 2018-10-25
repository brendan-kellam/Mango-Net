#include "LoadShader.h"

GLuint LoadShader(std::string path, GLenum type)
{

	// Create the shaders
	GLuint shaderID = glCreateShader(type);

	// Read the Shader code from file
	std::string shaderCode;
	std::ifstream shaderStream(path.c_str(), std::ios::in);


	if (!ReadFromShader(shaderStream, shaderCode))
	{
		std::cout << "ERROR: Unable to open shader. Path: " << path << "." << std::endl;
		return 0;
	}

	// Compile shader
	CompileShader(shaderID, shaderCode);

	return shaderID;
}

void CompileShader(GLuint shaderID, std::string& shaderCode)
{
	char const* pShaderCode = shaderCode.c_str();
	glShaderSource(shaderID, 1, &pShaderCode, NULL);
	
	// Compile shader
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int infoLogLength;

	// Check Shader validity 
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cout << &shaderErrorMessage[0] << std::endl;
	}
}


bool ReadFromShader(std::ifstream& stream, std::string& output)
{
	if (!stream.is_open())
	{
		return false;
	}

	std::string line;
	while (getline(stream, line))
	{
		output += '\n' + line;
	}

	stream.close();
	return true; 
}