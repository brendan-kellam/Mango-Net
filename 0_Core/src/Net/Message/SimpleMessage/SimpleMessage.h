#ifndef SIMPLEMESSAGE_H
#define SIMPLEMESSAGE_H

#include "Platform.h"
#include "Net/Message/Message.h"
#include <stdio.h>

class MANGO_API CSimpleMessage
	: public CMessage
{
private:

	int m_message; // min = 0, max = 1000  

	template <typename Stream>
	bool SerializeInternal(Stream& stream)
	{
		serialize_int(stream, m_message, 0, 100000);

		return true;
	}

public:
	virtual bool Serialize(CWriteStream& stream) override
	{
		return SerializeInternal(stream);
	}

	virtual bool Serialize(CReadStream& stream) override
	{
		return SerializeInternal(stream);
	}

	virtual std::string ToString() override
	{
		return std::to_string(GetMessage());
	}

	void SetMessage(const int m)
	{
		m_message = m;
	}

	int GetMessage() const
	{
		return m_message;
	}
};

class MANGO_API CCameraMessage
	: public CMessage
{
private:

	float m_horizontalAngle;
	float m_verticalAngle;
	float m_x, m_y, m_z;

	template <typename Stream>
	bool SerializeInternal(Stream& stream)
	{

		serialize_float(stream, m_horizontalAngle);
		serialize_float(stream, m_verticalAngle);
		serialize_float(stream, m_x);
		serialize_float(stream, m_y);
		serialize_float(stream, m_z);

		return true;
	}

public:
	virtual bool Serialize(CWriteStream& stream) override
	{
		return SerializeInternal(stream);
	}

	virtual bool Serialize(CReadStream& stream) override
	{
		return SerializeInternal(stream);
	}

	void SetMessage(float horizontalAngle, float verticalAngle, float x, float y, float z)
	{
		m_horizontalAngle = horizontalAngle;
		m_verticalAngle = verticalAngle;
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void SetCamera(float& horizontalAngle, float& verticalAngle, float& x, float& y, float& z)
	{
		horizontalAngle = m_horizontalAngle;
		verticalAngle = m_verticalAngle;
		x = m_x;
		y = m_y;
		z = m_z;
	}

	virtual std::string ToString() override
	{
		std::ostringstream out;
		out << "[" << m_horizontalAngle << ", " << m_verticalAngle << "]  ("
			<< m_x << ", " << m_y << ", " << m_z << ")";

		return out.str();
	}

};


#endif // 

