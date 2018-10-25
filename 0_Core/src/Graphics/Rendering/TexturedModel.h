#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "ModelTexture.h"
#include "RawModel.h"


// Represents a textured model
class MANGO_API CTexturedModel
{
public: 
	CTexturedModel(CRawModel& model, CModelTexture& texture)
		: m_rawModel(model),
		m_texture(texture)
	{

	}

	CRawModel& GetModel()
	{
		return m_rawModel;
	}

	CModelTexture& GetTexture()
	{
		return m_texture;
	}


private:
	CRawModel m_rawModel;
	CModelTexture m_texture;

};



#endif