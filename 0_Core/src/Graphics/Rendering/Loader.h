#ifndef LOADER_H
#define LOADER_H

#include "Platform.h"
#include "RawModel.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <SOIL2/SOIL2.h>


class MANGO_API CLoader
{

public: 

	GLuint LoadTexture(const char* imagepath);

	CRawModel LoadToVAO(std::vector<float>& vertices, std::vector<float>& textureCords, std::vector<int>& indices);

	void CleanUp();

private:

	GLuint CreateVAO();

	void StoreDataInAttributeList(int attributeNumber, int cordSize, std::vector<float>& data);

	void BindIndicesBuffer(std::vector<int>& indices);

	void UnbindVAO();

private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;

};

#endif

