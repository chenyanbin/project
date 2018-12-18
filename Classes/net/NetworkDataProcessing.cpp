 //
//  NetworkDataProcessing.cpp
//  IpGame
//
//  Created by zxb on 15-7-21
//
//
#include "NetworkDataProcessing.h"
#include<pthread.h>
#include "../common/noticeManager/NoticeManager.h"
#include "../module/login/LoginLayer.h"
#include "../commonData/GlobalInfo.h"
#include "../common/Dialog/Dialog.h"
#include "../common/GameConfig.h"
#include "../common/StringUtil.h"
#include "../module/newPlayerGuide/NewPlayerGuild.h"
#include "../common/TimeUtil.h"
#include "../message/Decoding/loginMsg/ReloginMsg.hpp"
bool NetworkDataProcessing::socketConnected = false;
ODSocket *NetworkDataProcessing::sockeyClient=NULL;
NetworkDataProcessing*NetworkDataProcessing::network = NULL;
std::queue<MessageReceive*>* NetworkDataProcessing::s_pReceiveQueue = NULL;
Map<int, __Double*>* NetworkDataProcessing::messageRecord = NULL;
static unsigned long timer=0;

static pthread_t s_ConnectThread;
static pthread_t s_ReceiveThread;
static pthread_mutex_t sum_mutex;

bool NetworkDataProcessing::socketIsOk = false;
NetworkDataProcessing::NetworkDataProcessing()
{
    pthread_mutex_init( &sum_mutex, NULL ); //对锁进行初始化
    s_pReceiveQueue = new queue<MessageReceive*>();
    messageRecord = new Map<int, __Double*>();
}
NetworkDataProcessing::~NetworkDataProcessing()
{
    if(sockeyClient!=NULL){
        sockeyClient->Close();
    }
    delete s_pReceiveQueue;
    s_pReceiveQueue = NULL;
//    _buf=NULL;
    delete sockeyClient;
    sockeyClient = NULL;
    
    messageRecord->clear();
    CC_SAFE_DELETE(messageRecord);
    messageRecord = NULL;
}

NetworkDataProcessing * NetworkDataProcessing::sharedNet(void)
{
    return getInstance();
}
NetworkDataProcessing* NetworkDataProcessing::getInstance(void)
{
    if (!network)
    {
        network = new NetworkDataProcessing();
    }
    return network;
}
void NetworkDataProcessing::connectServer()
{
  
    NetworkDataProcessing::sharedNet()->isReconnect = false;
    if(socketConnected == false)
    {
      if (NetworkDataProcessing::sharedNet()->connectNet())
      { 
           NetworkDataProcessing::sharedNet()->asyncReadData();
      }
    }
    LoginLayer::requestEnterGameMsg();
}

void NetworkDataProcessing::reLogin(Node* pTarget)
{
  
    GlobalInfo::getInstance()->initIs();
    NewPlayerGuild::destoryInstance();
    NetworkDataProcessing::sharedNet()->closeNet();
    
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    auto scene = LoginLayer::createScene(SCENE_TAG_INIT);
    Director::getInstance()->replaceScene(scene);
   
}
bool NetworkDataProcessing::connectNet()
{
    if(GlobalInfo::getInstance()->addressIP.size() <= 0 || GlobalInfo::getInstance()->port <= 0)
    {
        return false;
    }
    bool res = false;
   socketConnected = false;
    socketIsOk = false;
   if(sockeyClient == NULL)
   {
       sockeyClient = new ODSocket();
       sockeyClient->Init();
       res =  sockeyClient->Create(AF_INET,SOCK_STREAM,0);
     log("创建socket 成功 还是失败＝＝%d sockeyClient.m_socket=%d",res == 1,sockeyClient->m_sock);
   }
    
    res = sockeyClient->Connect(GlobalInfo::getInstance()->addressIP, GlobalInfo::getInstance()->port);
    log("连接服务器connect URL = %s, port = %d res=%d",GlobalInfo::getInstance()->addressIP.c_str(),GlobalInfo::getInstance()->port,res);
      log("连接服务器端 成功 还是失败＝＝%d",res == 1);
    //EBADF		9		/* Bad file descriptor */
    //ETIMEDOUT	60		/* Operation timed out */
    //ECONNREFUSED	61		/* Connection refused */
    //ECONNABORTED	53		/* Software caused connection abort */
    if(res){
        socketConnected = true;
        socketIsOk = true;
        

        
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::onUpdate), this);
        Director::getInstance()->getScheduler()->schedule(schedule_selector(NetworkDataProcessing::onUpdate),this, 0, false);
        GlobalInfo::getInstance()->initIs();
        if(isReconnect)
        {
            log("重新连接成功");
            NetworkDataProcessing::sharedNet()->asyncReadData();
            
            ReloginMsg* msg = new ReloginMsg();
            NetworkDataProcessing::getInstance()->sendMessage(msg);
            msg  = NULL;
            
        }
        
    }
    else
    {
        //允许再次重
        log("err=%d",sockeyClient->GetError());
        socketConnected = false;
        socketIsOk = false;
        string str = "连接不上服务器，请检查您的网络连接或联系客服 errorID=" ;
        str += ERROR_SOCKET_FAILED;
   
        Dialog::show(str.c_str());
        this->closeNet();
    }
    
    return res;
}
void * NetworkDataProcessing::connectServer(void*)
{
    bool res = false;
    if(sockeyClient!=NULL)
    {
        sockeyClient->Close();
        delete sockeyClient;
        sockeyClient = NULL;
    }
    sockeyClient = new ODSocket();
    sockeyClient->Init();
    sockeyClient->Create(AF_INET,SOCK_STREAM,0);
    res = sockeyClient->Connect(GlobalInfo::getInstance()->addressIP, GlobalInfo::getInstance()->port);
    if(res)
    {
        socketConnected = true;
        socketIsOk = true;
    }
    else
    {
        GlobalInfo::getInstance()->odSocketErr= sockeyClient->GetError();
    }

    pthread_exit(NULL);
    return (void*)res;
}
bool NetworkDataProcessing::connectThread()// 连接服务器线程
{
    timer = 0;
    int good= pthread_create(&s_ConnectThread,NULL, NetworkDataProcessing::connectServer, NULL);
    Director::getInstance()->getScheduler()->schedule(schedule_selector(NetworkDataProcessing::TimerConnectListen), this, 0, false);

    cout << "获取消息数据异步线程启动--"<<(good==0?"成功":"失败")<<endl;
    return good == 0;
}
void NetworkDataProcessing::TimerConnectListen(float dt)
{
    if(socketConnected)
    {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::TimerConnectListen), this);
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::onUpdate), this);
        Director::getInstance()->getScheduler()->schedule(schedule_selector(NetworkDataProcessing::onUpdate),this, 0, false);
        
        GlobalInfo::getInstance()->initIs();
        if(isReconnect)
        {
      
            NetworkDataProcessing::sharedNet()->asyncReadData();
        }
    }
    else
    {
        string errMsg="";
        timer++;
        log("timer===%ld",timer);
        if(timer==500)
        {
            //一旦5秒内没有响应，就说明socket服务器没有启动，就取消该定时器
            //测试过大概在timer=4703,差不多47秒的时候，会出现err=60
            errMsg="服务器连接不上,请确认3g或者wifi网络连接正常!";
        }else if(GlobalInfo::getInstance()->odSocketErr==60){
            errMsg="服务器连接超时,请确认3g或者wifi网络连接正常!";
        }else if(GlobalInfo::getInstance()->odSocketErr==61){
            //如果是socketserver刚刚断掉的情况，很大概率直接返回61，不会出现60和timer自增长到500的情况。
            errMsg="服务器连接失败,请确认3g或者wifi网络连接正常!";
        }else if(GlobalInfo::getInstance()->odSocketErr==61){
            errMsg = "err=EBADF		9		 Bad file descriptor";
        }
        else if(GlobalInfo::getInstance()->odSocketErr==53){
            errMsg = "err=ECONNABORTED	53		/* Software caused connection abort */";
        } 
  
        if(!errMsg.empty()){
            //一旦连接失败，就取消该定时器
            Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::TimerConnectListen), this);
            Dialog::show(errMsg.c_str());
        }
        
    }
}
void NetworkDataProcessing::reConnectNet()
{
    
    this->closeNet();
    isReconnect = true;

    connectNet();
   
}

void NetworkDataProcessing::onUpdate(float dt)
{
   
    
   if(socketConnected)
   {
       std::queue<MessageReceive*> *pQueue = s_pReceiveQueue;
       if (pQueue->empty())
       {
//           log("s_pReceiveQueue->empty");
       }
       else
       {
           pthread_mutex_lock( &sum_mutex ); //先加锁，再修改sum的值，锁被占用就阻塞，直到拿到锁再修改sum;
               MessageReceive* msg = pQueue->front();
                pQueue->pop();
           pthread_mutex_unlock( &sum_mutex ); //释放锁，供其他线程使用
           if(msg->state == false)
           {
//                 0	无
//                 -1	系统级错误
//                 -2 未登录，session不存在，要重新登陆
//                 <=-100	业务异常
             if(msg->retCode == -2)
             {
               
                 NetworkDataProcessing::getInstance()->reLogin();
             }
             else
             {
                 if(msg->messageID == SCENE_CLIENT_LOGIN_BACK)
                 {//重连失败 时间太长了，需要重新登陆
                     this->reLogin();
                     return;
                 }
                Dialog::show(msg->errorMsg.c_str());
                
             }
             
       
               //取消蒙层
               Dialog::hideLoading();
               Dialog::hideServerLoading();
           }
       
           CommonMsgProcesser::onMsgProcess(msg);
          
           char str[20] = {0};
           sprintf(str, "%d",msg->messageID);
           EventCustom event(str);
           event.setUserData((void*)msg);
           Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
          
           delete msg;
           msg = NULL;
       }
   }
   else
   {
       Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::onUpdate), this);
   }
}
void NetworkDataProcessing::clearMsgQueue()
{
    while (!s_pReceiveQueue->empty())
    {
        MessageReceive* msg = s_pReceiveQueue->front();
        delete msg;
        s_pReceiveQueue->pop();
    }
}
int NetworkDataProcessing::getSOCKET()
{
    
    return sockeyClient->GetError();
}
bool NetworkDataProcessing::writeData(MessageSendI *decoing)
{
    bool isRes = false;
    do {
        MessageSendI *ms = decoing;
        ByteStream* ss =ms->encodingData();
        sockeyClient->Send(ss->_buf,ss->_count);
        isRes =true;
    } while (0);
    return isRes;
}
bool NetworkDataProcessing::asyncReadData()
{
    int good= pthread_create(&s_ReceiveThread,NULL, NetworkDataProcessing::getMessage, NULL);
	//返回值 0 才算是成功， 其他表示错误
    cout << "获取消息数据异步线程启动--"<<(good==0?"成功":"失败")<<endl;
    return good == 0;
}
bool NetworkDataProcessing::asyncWriteData(MessageSendI *decoing)
{
    pthread_t tid;
    int  good= pthread_create(&tid,NULL, NetworkDataProcessing::sendMessage, decoing);
	
    cout << "发送消息异步线程启动--"<<(good==0?"成功":"失败")<<endl;
    return good == 0;
}
void * NetworkDataProcessing:: getMessage(void *)
{

    bool err=false;
    while (1)
    {
        uint8_t* headBuffer = new uint8_t[BUFHEADSIZE];
        memset(headBuffer,0x0,sizeof(uint8_t)*BUFHEADSIZE);
        int recvLen = sockeyClient->Recv(headBuffer,BUFHEADSIZE);
        log("recvLen===%d",recvLen);
        if (recvLen == BUFHEADSIZE)
        {
            ByteStream *buffer = new ByteStream(headBuffer,BUFHEADSIZE,true);
            int packetLength = buffer->getInt();
            int agreementNumber = buffer->getInt();
            int totalLength = packetLength - 4;
            int readSize = 0;
            int readTotal = 0;
            
            delete buffer;
            uint8_t* buf = new uint8_t[totalLength];
            memset(buf,0x0,sizeof(uint8_t)*totalLength);
            if (totalLength>0)
            {
                while (totalLength!=0)
                {
                    readSize = sockeyClient->Recv(&buf[readTotal],totalLength);
                    readTotal += readSize;
                    totalLength -= readSize;
                    if (readSize==0&&totalLength>0)
                    {
                        break;
                    }
                }
    
            }
            log("接收消息协议号:%d",agreementNumber);

            if (agreementNumber<=-100000000 || agreementNumber > 100000000)
            {
                MessageReceive* msg = new MessageReceive();
                ByteStream* bytestream = new ByteStream(buf,readTotal,true);
              
                msg->sequenceCode = bytestream->getInt();
                msg->messageID = agreementNumber;
                if(agreementNumber < 0)
                {
                   msg->retCode = bytestream->getByte();
                }
                
                msg->state = agreementNumber < 0 ? msg->retCode >= 0 : true;
           
                if(msg->state == false)
                {
                    msg->debugMsg = bytestream->getUTF8();
                    log("debugMsg=============%s",msg->debugMsg.c_str());
                    msg->colorFlag = bytestream->getInt();
                    msg->errorMsg = bytestream->getUTF8();
                    bytestream->setPosition(0);
                }
                msg->byteStream = bytestream;
                pthread_mutex_lock( &sum_mutex );
                 s_pReceiveQueue->push(msg);
                pthread_mutex_unlock( &sum_mutex ); //释放锁，供其他线程使用
            }
            else
            {
                err = true;
                delete [] buf;
                break;
            }
            buf = NULL;
        }
        else
        {
            log("协议长度不于9 .不够一条协议");
            delete [] headBuffer;
            headBuffer = NULL;
            socketIsOk = false;
            err = true;
          
            break;
        }
        

    }
    if(err)
    {
        log("pthread_exitpthread_exitpthread_exit");
        NetworkDataProcessing::getInstance()->socketIsOk =false; 
        NetworkDataProcessing::getInstance()->socketConnected = false;
        pthread_exit(NULL);
        NetworkDataProcessing::getInstance()->reConnectNet();
    }
    return NULL;
}
void NetworkDataProcessing::showKickOffLineMsg(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::showKickOffLineMsg),this);
     Dialog::show("您被踢下线了哟，亲！");
     Dialog::hideLoading();
    Dialog::hideServerLoading();
}


void * NetworkDataProcessing::sendMessage(void *decoing)
{//
    MessageSendI *ms = (MessageSendI*)decoing;

    if(socketIsOk)
    {
        ByteStream* bytestream = ms->encodingData();
        int messageID = ms->getMessageID();
        if(messageID != SCENSE_CLIENT_BATTLE_BattleLootReq)
        {
            double nowTime = TimeUtil::getMilliSecond();
            __Double* lastTime = messageRecord->at(ms->getMessageID());
            if(lastTime)
            {
                if(nowTime - lastTime->getValue() <= .12)
                {//小于.1秒，提示不发送
                    //取消蒙层
                    Dialog::hideServerLoading();
                    if(GlobalInfo::getInstance()->isDebug)
                    {
                         NoticeManager::getInstance()->showNotice("操作太快，戳坏屏幕啦!",4);
                    }
                    return NULL;
                }
            }
            messageRecord->insert(messageID, __Double::create(nowTime));
        }
      
        sockeyClient->Send(bytestream->_buf,bytestream->_count);
    }
    delete ms;
    ms = NULL;
    return NULL;
}
//打印buff的调试函数，
static void printBuff(char * buff,int len)
{
    int i=0;
    printf("协议缓存\n[");
    while(i<len)
    {
        printf("%d ",(unsigned char)buff[i]);
        i++;
    }
    printf("]\n");
}

bool NetworkDataProcessing::closeNet()
{

    
    GlobalInfo::getInstance()->initIs();
    clearMsgQueue();
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkDataProcessing::onUpdate), this);
    socketConnected = false;
    socketIsOk = false;
    if(sockeyClient)
    {
        sockeyClient->Close();
        delete sockeyClient;
        sockeyClient = NULL;
    }
    return true;
}
