//
//  FirstRechargeLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/11/16.
//
//

#ifndef __FightPass__FirstRechargeLayer__
#define __FightPass__FirstRechargeLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
class FirstRechargeLayer:public BaseLayer
{
public:
    
    FirstRechargeLayer();
    ~ FirstRechargeLayer();
    virtual bool init(int firstCharge);
    static FirstRechargeLayer* create(int firstCharge);
    static void show(int firstCharge = 1);//打开首充
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setButton(int _status);
    void onclick(Ref* psender);
    
    void requestFirstRechargeReceivelMsg();
    void onFirstRechargeMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
    void requestFirstRechargeLingquMsg();
    void onFirstRechargeLingquMsgProcess(EventCustom* msg);
    
    void onHeroHeadClick(Node* pSender);
    void setItemPic();
private:
   Vector<BaseTypeData*>* m_baselist;
    
    
    int TAG_PERSON;
};


#endif /* defined(__FightPass__FirstRechargeLayer__) */
