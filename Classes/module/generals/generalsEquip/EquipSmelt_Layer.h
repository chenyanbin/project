//
//  EquipSmelt_Layer.h
//  FightPass
//  熔炼改成强化。现在界面为强化页面
//  Created by 超 顾 on 15/9/7.
//
//

#ifndef __FightPass__EquipSmelt_Layer__
#define __FightPass__EquipSmelt_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/EquipDataManager.h"
USING_NS_CC_EXT;
USING_NS_CC;
class EquipSmelt_Layer:public BaseLayer
{
public:
    EquipSmelt_Layer();
    ~EquipSmelt_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static EquipSmelt_Layer* create(int cardId);
private:
    void addEventListener();
    void removeEventListener();
    void onMsgProcess(EventCustom* msg);
    void requestListMsg();
    void onBtnClick(Ref* psender);
    void equipStartHardenMsg();
    void showEquipLvUpSound();
    
    void rightLayer();
    void leftLayer();
private:
    float sx;
    int _cardId;
    int TAG_SMELT;
    
    BaseEquipData* equipData;
    BaseEquipData* newEquipData;
    int costCoin;//强化花费铜钱
    int oneKeyCostCoin;//一键强化花费铜钱
    
    Sprite* leftBg;
    Sprite* rightBg;
    int TAG_RIGHTBG1;
    int TAG_RIGHTBG;
    int TAG_COSTBTN;
    int TAG_ONEKEYCOSBTN;
    int TAG_LEFTBG;
    bool isOneKey;
};

#endif /* defined(__FightPass__EquipSmelt_Layer__) */
