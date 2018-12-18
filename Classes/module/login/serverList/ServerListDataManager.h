//
//  ServerListDataManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/20.
//
//

#ifndef __FightPass__ServerListDataManager__
#define __FightPass__ServerListDataManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class ServerListData:public Ref
{
public:
    ServerListData()
    :id(""),serverName(""),state(0)
    ,IP(""),port(0),visible(0),canEnter(0),nameColor(0)
    {
        
    }
    
    enum{
        STATE_NORMAL = 1,//正常
        STATE_FIX = 2,//维护
        STATE_NEW = 3,//最新
        STATE_STOP = 4//停服维护
    };
    
    ~ServerListData()
    {
    }
    string id;         //服务器id
    string serverName;  //服务器名称
    string IP;
    int port;
    char state;//1,最新，2，火爆 3,停服维护
    bool visible;
    bool canEnter;
    unsigned long nameColor;
    
};
class ServerListDataManager
{
public:
    static ServerListDataManager* getInstance();
    static void destoryInstance();
public:
    void parseServerList(const char* content);
    Vector<ServerListData*>* getServerList();
    Vector<ServerListData*>* getRecentList();//最近登陆列表
public:
    ServerListData* _nowServerData;
    
private:
    ServerListDataManager();
    ~ServerListDataManager();
    static ServerListDataManager* _instance;
    Vector<ServerListData*>* serverList;
    Vector<ServerListData*>* recentList;//最近登陆
};

#endif /* defined(__FightPass__ServerListDataManager__) */
