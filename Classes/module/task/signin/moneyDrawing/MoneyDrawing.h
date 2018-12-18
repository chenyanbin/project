//
//  MoneyDrawing.h
//  FightPass
//
//  Created by 超 顾 on 15/10/14.
//
//

#ifndef __FightPass__MoneyDrawing__
#define __FightPass__MoneyDrawing__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class MoneyDrawing:public BaseLayer
{
public:
    MoneyDrawing();
    ~MoneyDrawing();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static MoneyDrawing* create();
private:
    void createLayer();
    void removeEventListener();
    void onPersonClick(Ref* pSender);
    
    void requestLuckyMsg();
    void onLuckyMsgProcess(EventCustom* msg);
    void addEventListener();
    
    void requestItemGiftMsg();//请求;
    void onItemGiftMsgProcess(EventCustom* msg);
    
    
    void setLuckytime();
    void update2(float delta);
    void onseeClick(Ref* pSender);
private:
    float sx;
    int m_totalCount;//祈福总次数
    int m_todayCount;//今日一祈福次数
    int m_todayTotalCount;//今日总共可以祈福次数
    int m_status;//状态 1：可祈福 2：倒计时中 3;今日已结束
    long m_remainingTimes;//剩余时间
    Label* label;
    int TAG_TODAYTIME;
    int TAG_ALLTODAY;
    int TAG_DAOJISHI;
    int TAG_RECUITIME;
    
    
};

#endif /* defined(__FightPass__MoneyDrawing__) */
