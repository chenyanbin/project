//
//  HearBeatCheck.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-6-30.
//
//

#ifndef __SuiTang__HearBeatCheck__
#define __SuiTang__HearBeatCheck__

#define HEART_DELAY 7
#define HEARTBEAT_CHECK_INTERVAL 10
#include "cocos2d.h"
USING_NS_CC;
class HeartBeatCheck:public Ref
{
public:
    HeartBeatCheck();
    ~HeartBeatCheck();
    //开始心跳检测
    void start();
    //停止心跳
    void stop();
    static HeartBeatCheck* getInstance();
    static void destoryInstance();
private:
    void checkReturn(float dt);
    void addListener();
    void sendMsg(float dt = 0);
    void onMsgProcess(EventCustom* event);
    //断线重连
    void offLineReConnect();
    
 
    static HeartBeatCheck* m_instance;
    
    int lostCount;//协议未返回的次数
};
#endif /* defined(__SuiTang__HearBeatCheck__) */
