#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "Platform.h"
#include "Stream.h"
#include "ReadStream.h"
#include "WriteStream.h"
#include "Net/Message/MessageFactory.h"

class MANGO_API ISerializable
{

public:

	virtual ~ISerializable() { }

	virtual bool Serialize(CReadStream& stream) = 0;
	virtual bool Serialize(CWriteStream& stream) = 0;
	
};

class MANGO_API IMessageFactorySerializable
{

public:

	virtual ~IMessageFactorySerializable() { }

	virtual bool Serialize(CReadStream& stream, CMessageFactory& fac) = 0;
	virtual bool Serialize(CWriteStream& stream, CMessageFactory& fac) = 0;

};

#endif 