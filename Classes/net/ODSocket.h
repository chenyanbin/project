//
//
//  Created by 孙宏利 on 14-3-24.
//
//

#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_

#ifdef WIN32
	#include <Winsock2.h>
	//#include <winsock.h>
   
	typedef int				socklen_t;
	typedef unsigned char	uint8_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	typedef int				SOCKET;
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
#endif
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class ODSocket {

public:
	ODSocket(SOCKET sock = INVALID_SOCKET);
    
	~ODSocket();

	bool Create(int af, int type, int protocol = 0);

	bool Connect(const string ip, unsigned short port);

	bool Accept(ODSocket& s, char* fromip = NULL);
    
    bool isConnected(){return m_sock != -1;}
	
	ssize_t Send(uint8_t* buf, int len, int flags = 0);

	int Recv(uint8_t* buf, int len, int flags = 0);
	
	int Close();

	int GetError();
	
	static int Init();
	
	static bool DnsParse(const char* domain, char* ip);

	ODSocket& operator = (SOCKET s);

	operator SOCKET ();

public:
    
	SOCKET m_sock;

};

#endif
