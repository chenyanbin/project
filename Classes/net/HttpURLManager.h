//
//  HttpURLManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/16.
//
//

#ifndef __FightPass__HttpURLManager__
#define __FightPass__HttpURLManager__

#include "cocos2d.h"
USING_NS_CC;
#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>

#define CLIENT_ACCESS_KEY "ddcca99b729f592c71ad13e4106ef788"
#define CLIENT_SECRET_KEY "ceffaf03d3680824fb14a5260b6ffeb4"
#define CLIENT_SUB_CHANNEL "SANGUO_CLIENT_SUB_CHANNEL"

class HttpURLManager:public Ref
{
public:
    static HttpURLManager* getInstance();
    static void destoryInstance();
    
    void login();//登录
    void requestServerList();//请求服务器列表
    
    void subChannelActive();//激活子账号
    
    void requestNoticeData();//请求公告数据
    
private:
    void onLoginCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onServerListCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    void onReLogin(Node* pSender);
    
    void onSubWayActiveBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    
    std::string getReleaseVersionURL();
    std::string getDebugVersionURL();
    
    void onNoticeCallBack(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
private:
    HttpURLManager();
    ~HttpURLManager();
    static HttpURLManager* _instance;
    int m_loginIndex;
    

};

#endif /* defined(__FightPass__HttpURLManager__) */
