#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "Platform.h"
#include <GL/glew.h>


class MANGO_API CModelTexture
{

public:

	CModelTexture(GLuint textureID);

	GLuint GetID() const;

private:
	GLuint m_textureID;

};

#endif