//
//  Generals_layer.h
//  FightPass
//
//  Created by 超 顾 on 15/7/27.
//
//

#ifndef __FightPass__Generals_layer__
#define __FightPass__Generals_layer__
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "data/CardDataManager.h"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/TouchSprite/Button.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class Generals_Layer:public BaseLayer
{
public:
    enum PageTurn
    {
        PAGE_TAG_ITEM = 0,//道具
        PAGE_TAG_MATERIAL = 1,//材料
        PAGE_TAG_EQUIP = 2,//装备
        PAGE_TAG_LETTER = 3,//书信
        PAGE_TAG_GENERAL = 4,//武将
        PAGE_TAG_RISEQUALIGY = 5//升品
    };
    Generals_Layer();
    ~Generals_Layer();
    static Generals_Layer* create(int value,int _cardId);
    virtual bool init(int value,int _cardId);
    virtual void onEnter();
    virtual void onExit();
    static void show(int fromeScene = -1,int value = PAGE_TAG_GENERAL,int _cardId=0);
protected:
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void rightListVertical();
    void topLayer();
    void setBackBg();    
    void onRightBtnClick(Ref* psender);
    void onRight2BtnClick(Ref* psender);
    void onRight3BtnClick(Ref* psender);
    void onBtnListClick(Ref* psender);    
    void onRefreshDot(EventCustom* msg);
private:
    float sx;
    float sy;
    int TAG_TABLEVIEW;
    int TAG_LISTBG;
    int TAG_TOP;
    int rightSelected;
    int cardId;
    UserWealthLayer* topsLayer;
    
};
#endif /* defined(__FightPass__Generals_layer__) */
