#ifndef LOADSHADER_H
#define LOADSHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// Load shaders function
GLuint LoadShader(std::string path, GLenum type);
bool ReadFromShader(std::ifstream& stream, std::string& output);
void CompileShader(GLuint shaderID, std::string& shaderCode);

#endif /* LOADSHADER_H */
