#include "Graphics/Rendering/Loader.h"

GLuint CLoader::LoadTexture(const char* imagepath)
{
	int width, height;
	unsigned char* image = SOIL_load_image(imagepath, &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
	{
		printf("Error loading image!\n");
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	m_textures.push_back(textureID);

	glActiveTexture(GL_TEXTURE0);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(image);

	return textureID;
}

CRawModel CLoader::LoadToVAO(std::vector<float>& vertices, std::vector<float>& textureCords, std::vector<int>& indices)
{

	// Create VAO
	GLuint vaoID = CreateVAO();

	// Create & bind IBO
	BindIndicesBuffer(indices);

	// Create & bind vertices
	StoreDataInAttributeList(0, 3, vertices);
	StoreDataInAttributeList(1, 2, textureCords);

	// Unbind the VAO
	UnbindVAO();

	return CRawModel(vaoID, indices.size());
}

void CLoader::CleanUp()
{

	for (GLuint vaoId : m_vaos)
	{
		glDeleteVertexArrays(1, &vaoId);
	}

	for (GLuint vboId : m_vbos)
	{
		glDeleteBuffers(1, &vboId);
	}

	for (GLuint textureId : m_textures)
	{
		glDeleteTextures(1, &textureId);
	}
}

GLuint CLoader::CreateVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	m_vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void CLoader::StoreDataInAttributeList(int attributeNumber, int cordSize, std::vector<float>& data)
{
	GLuint vboID;

	// Generate 1 VBO. Put ID in vboID
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);

	// Make the new VBO active (Array buffer VBO)
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Create and initialize VBOs data store
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	// Input assembly
	glVertexAttribPointer(
		attributeNumber,	 // Attribute number
		cordSize,			 // Length of the vector
		GL_FLOAT,			 // type
		GL_FALSE,			 // normalized?
		0,					 // stride
		(void*)0		 // array buffer offset
	);


	// Unbind the current VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CLoader::BindIndicesBuffer(std::vector<int>& indices)
{
	GLuint iboID;
	glGenBuffers(1, &iboID);
	m_vbos.push_back(iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void CLoader::UnbindVAO()
{
	glBindVertexArray(0);
}
