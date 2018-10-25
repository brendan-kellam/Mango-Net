#include "Packet.h"

CPacket::CPacket(uint16_t lsn, uint16_t rsn, uint32_t pab, std::vector<CMessage*>& messages)
	: m_protocolID(static_cast<uint32_t>(std::hash<std::string>()("Eros"))),
	m_id(lsn),
	m_ack(rsn),
	m_ackBitfieldInt(pab),
	m_isAcked(false),
	m_messages(messages)
{
	m_remoteProtocolID = m_protocolID;
}

CPacket::CPacket()
	: m_isAcked(false)
{

}

template <typename Stream>
bool CPacket::SerializeInternal(Stream& stream, CMessageFactory& factory)
{
	serialize_bits(stream, m_remoteProtocolID, 32);
	serialize_bits(stream, m_id, 16);
	serialize_bits(stream, m_ack, 16);
	serialize_bits(stream, m_ackBitfieldInt, 32);

	// WRITE
	if (Stream::IsWriting)
	{
		int numMessages = m_messages.size();
		serialize_int(stream, numMessages, 0, MAX_MESSAGE_COUNT);

		for (CMessage* message : m_messages)
		{
			int numTypes = factory.GetNumTypes();
			int msgType = message->GetType();
			serialize_int(stream, msgType, 0, numTypes);
			message->Serialize(stream);
		}
	}

	// READ
	else
	{
		int numMessages;
		serialize_int(stream, numMessages, 0, MAX_MESSAGE_COUNT);

		for (int i = 0; i < numMessages; i++)
		{
			int numTypes = factory.GetNumTypes();
			int msgType;
			serialize_int(stream, msgType, 0, numTypes);

			CMessage* msg = factory.CreateMessage(msgType); 
			msg->Serialize(stream);
			m_messages.push_back(msg);
		}
	}


	return true;
}

bool CPacket::Serialize(CReadStream& stream, CMessageFactory& factory)
{
	return SerializeInternal(stream, factory);
}

bool CPacket::Serialize(CWriteStream& stream, CMessageFactory& factory)
{
	return SerializeInternal(stream, factory);
}
