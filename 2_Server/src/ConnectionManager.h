#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H


#include <iostream>
#include <vector>
#include <map>

#include "Net/Socket.h"
#include "Util/Interfaces/Manager.h"
#include "Util/Singleton.h"
#include "Util/Interfaces/Updatable.h"
#include "Net/Packet/Packet.h"
#include "Net/Connection.h"
#include "Net/Address.h"
#include "Net/Message/SimpleMessage/SimpleMessageFactory.h"


#define ENGINE_NAME		   "Mango"
#define LOCAL_PORT			2000
#define BUFLEN				256


class MANGO_API CConnectionManager final
	: public IManager, public CSingleton<CConnectionManager>, public IUpdateable
{
public: 

	CConnectionManager();
		
	void StartUp() override;
	void ShutDown() override;

	void Update() override;

private:

	CConnection* GetConnection(CAddress& addr);
	void		 UpdateConnections();
	bool		 InitializeWinsock();

	typedef std::map<CAddress, CConnection*, CAddressCompare> ConnectionMap;

	ConnectionMap m_connections;
	WSADATA m_wsaData;
	CSocket m_serverSocket;
	unsigned char m_recvBuf[PACKET_SIZE];

	CSimpleMsgFactory m_facSend;

};

#endif