//
//  StartFinddataManger.h
//  FightPass
//
//  Created by chenyanbin on 15/9/21.
//
//

#ifndef __FightPass__StartFinddataManger__
#define __FightPass__StartFinddataManger__

#include "cocos2d.h"
USING_NS_CC;
class StartFinddataManger
{
public:
    StartFinddataManger();
    ~ StartFinddataManger();
    static void destroyInstance();
    static StartFinddataManger* getInstance();
    void clearshopList();
    
    void setfindIdData(int findId);//寻访ID
    int getfindIdData();
    
    void setRemainingTimesData(int remainingTimes);//正在寻访剩余时间
    int getRemainingTimesData();
    
    void setjiasugoldData(int gold);//加速寻访需要元宝
    int getjiasugoldData();
    
    void setjungongData(int jungong);//剩余军工
    int getjungongData();
    
    void setxunfanglingData(int xunfagnling);//剩余寻访令
    int getxunfanglingData();
    
private:
    static StartFinddataManger* _instance;
    int m_findId;//寻访ID
    int m_remainingTimes;//正在寻访剩余时间
    int m_gold;//加速需要的金币
    int m_jungong;//剩余军工
    int m_xunfangling;//剩余寻访令
    
};


#endif /* defined(__FightPass__StartFinddataManger__) */
