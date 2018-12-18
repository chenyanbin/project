//
//  BuyPowerLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
// 购买体力页

#ifndef BuyPowerLayer_hpp
#define BuyPowerLayer_hpp

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
class BuyPowerLayer:public BaseLayer
{
public:
    
    BuyPowerLayer();
    ~ BuyPowerLayer();
    virtual bool init();
    static BuyPowerLayer* create();
    static void show();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void onSetContent(int gold,int count,int power);
    void onclick(Ref* psender);
    
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
    void requestBuyPowerPageMsg();
    void requestBuyPowerMsg();
    void onBuyPowerMsgProcess(EventCustom* msg);
private:
    int m_gold;
};

#endif /* BuyPowerLayer_hpp */
