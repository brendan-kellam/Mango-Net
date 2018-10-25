#include "RawModel.h"

CRawModel::CRawModel(int vaoID, int vertexCount) : m_vaoId(vaoID), m_vertexCount(vertexCount)
{

}

GLuint CRawModel::GetVAOId() const
{
	return m_vaoId;
}

GLuint CRawModel::GetVertexCount() const
{
	return m_vertexCount;
}
