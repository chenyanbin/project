
#include "ODSocket.h"
#include <signal.h>
#ifdef WIN32

 #pragma comment(lib, "pthreadVC2.lib")
	#pragma comment(lib, "wsock32")
#else
    #include <errno.h>
#endif


ODSocket::ODSocket(SOCKET sock){m_sock = sock;}

ODSocket::~ODSocket(){}

int ODSocket::Init()
{
#ifdef WIN32
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
//		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	return 0;
}
ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}

bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET ) {
        Close();
		return false;
	}
	return true;
}
bool ODSocket::Connect(const string ip, unsigned short port)
{
    //检测ip是否为空或者长度不符或者ip不合法
    unsigned long serveraddr = inet_addr(ip.c_str());
    if(ip.c_str() == NULL || strlen(ip.c_str()) > 15||serveraddr == INADDR_NONE){
        Close();
        return false;
    }
    
	int optval=1;
    //设置套接口选项SOL_SOCKET:通用套接字选项SO_KEEPALIVE:保持连接
	if(setsockopt(m_sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval))){
        Close();
        return false;
    }
    //设置网络连接基本属性
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip.c_str());
	svraddr.sin_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}else
    {
        timeval timeout;
        timeout.tv_sec  = 10;
        timeout.tv_usec = 0;
        fd_set readset, writeset, exceptset;
        FD_ZERO(&readset);//清空readset与所有文件句柄的联系
        FD_ZERO(&writeset);
        FD_ZERO(&exceptset);
        FD_SET(m_sock, &readset);   //建立文件句柄m_sock与readset的联系。
        FD_SET(m_sock, &writeset);
        FD_SET(m_sock, &exceptset);
        
        int ret = select(m_sock+1, &readset, &writeset, &exceptset, &timeout);
        if (ret == 0 || ret < 0){
            Close();
            return false;
        }else{
            //检查exceptset联系的文件句柄m_sock是否异常，当>0表示异常
            if(FD_ISSET(m_sock, &exceptset)){
                Close();
                return false;  
            }  
        }  

    }
    struct linger so_linger;
    so_linger.l_onoff = 1;
    so_linger.l_linger = 500;
    
    //设置套接口选项SOL_SOCKET:通用套接字选项SO_LINGER:延迟关闭连接
    setsockopt(m_sock, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));
    
	return true;
}
bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}
	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

ssize_t ODSocket::Send(uint8_t* buf, int len, int flags)
{
//    if (m_sock==0) {
//        return false;
//    }
//    ssize_t bytes = 0;
//    bytes = send(m_sock, (const char*)buf, len, flags);
//    return bytes;
    
    ssize_t bytes = 0;
	ssize_t count = 0;
    
	while ( count < len ) {
        
		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	}
    
	return count;
    
	
}

int ODSocket::Recv(uint8_t* buf, int len, int flags)
{
   
    long i = recv(m_sock, ( char*)buf, len, flags);
    if (i==SOCKET_ERROR) {
        return false;
    }
	return (int)i;
}

int ODSocket::Close()
{

    if(m_sock>=0)
    {
        #ifdef WIN32
            return (closesocket(m_sock));
        #else
        
            return (close(m_sock));
        #endif
        m_sock = -1;
    }
    else
    {
       
        return m_sock;
    }
   
    return 0;
}
int ODSocket::GetError()
{


#ifdef WIN32
	return (WSAGetLastError());
#else
//	return (m_sock);
    return errno;
    
#endif
    
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
