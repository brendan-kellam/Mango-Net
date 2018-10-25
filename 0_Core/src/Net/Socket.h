#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include "Platform.h"
#include "Net/Address.h"


class MANGO_API CSocket
{
public:
	CSocket();
	~CSocket();

	bool Open(unsigned short port);
	void Close();

	bool IsOpen() const; 

	bool Send(const CAddress& destination, const void* data, int size);

	int Receive(CAddress& sender, void* data, int size);

private:
	SOCKET m_handle;

	struct sockaddr_in m_otherAddress;
};

#endif