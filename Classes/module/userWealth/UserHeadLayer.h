//
//  UserHeadLayer.h
//  FightPass
//
//  Created by 超 顾 on 15/7/31.
//
//

#ifndef __FightPass__UserHeadLayer__
#define __FightPass__UserHeadLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class UserHeadLayer:public Layer
{
public:
    UserHeadLayer();
    ~UserHeadLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(const char* imgPath,int quality,bool isHeroHead = true);
//    CREATE_FUNC(UserHeadLayer);
    static UserHeadLayer* create(string imgPath="",int quality=1,bool isHeroHead = true);
    void addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector);
    void setHeadInfo(int lvInt,short prestInt);
    void setRemoveOther();
    void setHeadNumber(bool bol);
   
    void disableTouchEvent();
    void setFragment();
    void hideHeadInfo();//隐藏等级和声望
    
private:
    void createLayer(const char* imgPath,int quality);
    void onButtonClick(Ref* psender);
    Rect getRect(Node* spr);

private:
    Ref* c_touchBegainTarget;
    SEL_CallFuncN c_touchBegainSelector;
    EventListenerTouchAllAtOnce* touchAllListener;
    bool m_isHeroHead;
    int TAG_LVBG;
    int TAG_PREST;
    int TAG_HEADBOX;
    int TAG_TICK;
    int TAG_HEAD;
    int TAG_BLACKBG;
public:
    float cardId;
};

#endif /* defined(__FightPass__UserHeadLayer__) */
