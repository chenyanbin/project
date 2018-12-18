//
//  UserEquipLayer.h
//  FightPass
//
//  Created by 超 顾 on 15/9/2.
//
//

#ifndef __FightPass__UserEquipLayer__
#define __FightPass__UserEquipLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class UserEquipLayer:public Layer
{
public:
    UserEquipLayer();
    ~UserEquipLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(const char* imgPath,int quality,bool _bol,bool _bol2=true);
    //    CREATE_FUNC(UserHeadLayer);
    static UserEquipLayer* create(string imgPath="",int quality=1,bool _bol=true,bool _bol2=true);
    void addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector);
    void setHeadInfo(int lvInt,short prestInt=0);
    void setGray();
    void removeGray();
    void setIsSlect(bool bol);
    void setHeadNumber(int num);
    void setFragment();//加碎片
    void setLetterFragment();//加书信
    
private:
    void createLayer(const char* imgPath,int quality,bool _bol=true,bool _bol2=true);//true 装备图片，false 所有图片
    void onButtonClick(Ref* psender);
    Rect getRect(Node* spr);
    
private:
    Ref* c_touchBegainTarget;
    SEL_CallFuncN c_touchBegainSelector;
    EventListenerTouchAllAtOnce* touchAllListener;
    int TAG_LVBG;
    int TAG_PREST;
    int TAG_HEADBOX;
    int TAG_NUM;
    int TAG_BLACKBG;
    int TAG_TICK;
    int TAG_EQUIPICON;
public:
    float cardId;
    float sx;
    bool isSelect;
};

#endif /* defined(__FightPass__UserEquipLayer__) */
