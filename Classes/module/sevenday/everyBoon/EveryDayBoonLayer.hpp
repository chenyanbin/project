//
//  EveryDayBoonLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#ifndef EveryDayBoonLayer_hpp
#define EveryDayBoonLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
class EveryDayBoonLayer:public BaseLayer
{
public:
    EveryDayBoonLayer();
    ~ EveryDayBoonLayer();
    static EveryDayBoonLayer* create(int day);
    virtual bool init( int day);
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setBackground();
    void setItemPrice();
    void onitemClick(Node* pSender);
    void setBg();
    void onClick(Ref* pSender);
    void onGoldClick(Ref* pSender);
    void onChargeClick(Ref* pSender);
    void requestWeekRewardPage(int _day);
    void onWeekRewardProcess(EventCustom* msg);
    void onChoseHeroProcess(EventCustom* msg);
    
    void requestBoonRewardMsg(int _day, int _type, int _numPrice, int _numHero);//q请求领取奖励
    void onBoonDayRewardMsgProcess(EventCustom* msg);
    
    void setMoney();;
private:
    int m_day;
    float sx;
    int TAG_FREEBTN;
    int TAG_GLODBTN;
    int m_freeStatus;//1、可领取  2、不可领取 3、已领取
    int m_glodStatus;//1、可领取  2、不可领取 3、已领取
    int m_numhero;
    int m_type;
    
};


#endif /* EveryDayBoonLayer_hpp */
