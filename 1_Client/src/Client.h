#ifndef CLIENT_H
#define CLIENT_H

#include "Net/Socket.h"
#include "Net/Connection.h"
#include "Net/Address.h"
#include "Net/Message/Message.h"
#include "Net/Message/MessageFactory.h"
#include "Util/Interfaces/Updatable.h"

// Represents a client connection to a given server
class CClient
	: public IUpdateable
{

public:

	CClient(CAddress& serverAddr, const unsigned short clientPort);
	virtual ~CClient();

	void Update() override;

	bool Receive(CMessageFactory& factory, std::vector<CMessage*>& messages);
	bool Send(CMessageFactory& factory, std::vector<CMessage*>& messages);

private:
	WSADATA m_wsaData;
	CSocket m_socket;
	const unsigned short m_clientPort;
	CAddress m_serverAddr;
	CConnection* m_connection;
	unsigned char m_recvBuf[PACKET_SIZE];
};


#endif
