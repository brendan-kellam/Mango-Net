#include "ModelTexture.h"

CModelTexture::CModelTexture(GLuint textureID) : m_textureID(textureID)
{

}

GLuint CModelTexture::GetID() const
{
	return m_textureID;
}
