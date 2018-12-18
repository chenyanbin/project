//
//  ViplibaoBuyLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
// 确认购买礼品

#ifndef __FightPass__ViplibaoBuyLayer__
#define __FightPass__ViplibaoBuyLayer__

#include "../../BaseLayer.h"
#include "../../data/BaseTypeData.h"
class ViplibaoBuyLayer:public BaseLayer
{
public:
    ViplibaoBuyLayer();
    ~ ViplibaoBuyLayer();
    virtual bool init(int _level, int needGold);
    static ViplibaoBuyLayer* create(int _level, int needGold);
    static void show(int _level, int needGold);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
    void onMsggiftProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requesgifttListMsg(int _level );//发送购买信息
    
private:
    int m_level;//vipd等级
    int m_needGold;//刷新消耗元宝
    
    Vector<BaseTypeData*>* m_baselist;
    
};

#endif /* defined(__FightPass__ViplibaoBuyLayer__) */
