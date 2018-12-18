//
//  NetworkDataProcessing.h
//  IpGame
//
//  Created by 孙宏利 on 14-4-4.
//
//

#ifndef __IpGame__NetworkDataProcessing__
#define __IpGame__NetworkDataProcessing__

#include "cocos2d.h"
#include "ODSocket.h"
#include "bytestream.h"
#include "../message/Decoding/MessageSendI.h"
#include "../message/Encoding/MessageReceiveI.h"
#include "../message/Encoding/MessageReceive.h"
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>
#include "../common/CommonMsgProcesser.h"
#define BUFHEADSIZE 8
USING_NS_CC;
#ifdef WIN32
 #pragma comment(lib, "pthreadVC2.lib")
#endif

class NetworkDataProcessing:public Ref  {
    
public:
    NetworkDataProcessing();
    ~NetworkDataProcessing();
public:
    
    bool connectThread();// 连接服务器线程
    
    void connectServer();
    bool connectNet();                         //连接
    void reConnectNet();                       //断线重连
 
    bool writeData(MessageSendI *decoing);     //堵塞入写数据
    bool asyncReadData();                      //异步读取数据
    bool asyncWriteData(MessageSendI *decoing);//异步入写数据
    bool closeNet();                           //关闭连接
    int getSOCKET();
    static void * getMessage(void *);
    static void * sendMessage(void *);
    static void * connectServer(void *);
    void clearMsgQueue();
    void showKickOffLineMsg(float dt = 0);
    void reLogin(Node* pTarget = NULL);

public:
    bool isReconnect;//是否是断线重连
    static bool socketConnected;
    static bool socketIsOk;//socket是否正常状态 目的是检查如果socket断开了。则继续发协议出现崩溃的问题
    static NetworkDataProcessing* sharedNet(void);
    static NetworkDataProcessing* getInstance(void);
    static ODSocket * sockeyClient;
    static NetworkDataProcessing* network;
    static std::queue<MessageReceive*>* s_pReceiveQueue;
   
    static Map<int,__Double*>* messageRecord;//消息发送记录
private:
    void onUpdate(float dt);
    void TimerConnectListen(float dt);//侦听连接服务器状态

   
    
private:
    

//    uint8_t* _buf;
};

#endif
