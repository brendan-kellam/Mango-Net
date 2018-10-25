#ifndef RAWMODEL_H
#define RAWMODEL_H

#include "Platform.h"
#include <GL/glew.h>
#include <GL/GL.h>

class MANGO_API CRawModel
{

public:
	CRawModel(int vaoID, int vertexCount);

	GLuint GetVAOId() const;
	GLuint GetVertexCount() const;
	
private:
	GLuint m_vaoId;
	GLuint m_vertexCount;
};


#endif