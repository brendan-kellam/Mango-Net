#ifndef MESSAGE_H
#define MESSAGE_H

#include "Platform.h"
#include "Net/Stream/Serializable.h"

class MANGO_API CMessage
	: public ISerializable
{

public:
	
	CMessage()
		: m_type(0),
		m_refCount(1)
	{ }

	uint32_t GetType() const { return m_type; }
	int GetRefCount() const { return m_refCount; }
	
	virtual bool Serialize(CWriteStream& stream) override = 0;
	virtual bool Serialize(CReadStream& stream) override = 0;

	virtual std::string ToString() = 0;

protected:
	
	void SetType(uint32_t type) { m_type = type; }

	void Acquire()
	{
		MANGO_TRAP(m_refCount > 0);
		m_refCount++;
	}

	void Release()
	{
		MANGO_TRAP(m_refCount > 0);
		m_refCount--;
	}

	virtual ~CMessage()
	{
		MANGO_TRAP(m_refCount == 0);
	}

private:

	friend class CMessageFactory;

	CMessage(const CMessage& other);

	int m_refCount;
	uint32_t m_type;

};

#endif