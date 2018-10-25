#ifndef SIMPLEMSGFACTORY_H
#define SIMPLEMSGFACTORY_H

#include "Net/Message/MessageFactory.h"
#include "SimpleMessage.h"

class MANGO_API CSimpleMsgFactory
	: public CMessageFactory
{

public:
	enum ETypes
	{
		SIMPLE_MESSAGE,
		CAMERA_POSITION_MESSAGE,
		LENGTH
	};

	CSimpleMsgFactory() : CMessageFactory(ETypes::LENGTH) { }

protected:
	virtual CMessage* CreateMessageInternal(int type) override
	{
		CMessage* message;

		switch (type)
		{
		case ETypes::SIMPLE_MESSAGE:

			message = new CSimpleMessage();
			if (!message)
			{
				return NULL;
			}
			SetMessageType(message, ETypes::SIMPLE_MESSAGE);
			return message;

		case ETypes::CAMERA_POSITION_MESSAGE:

			message = new CCameraMessage();
			if (!message)
			{
				return NULL;
			}
			SetMessageType(message, ETypes::CAMERA_POSITION_MESSAGE);
			return message;

		default:
			return NULL;

		}
	}
};

#endif