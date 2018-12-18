//
//  GeneralsStrong_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#ifndef __FightPass__GeneralsStrong_Layer__
#define __FightPass__GeneralsStrong_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../data/BaseEquipData.h"
#include "../../BaseLayer.h"
#include "../../../commonData/dictData/DictHeroPrestigeUpCost/DictHeroPrestigeUpCostManager.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsStrong_Layer:public BaseLayer
{
public:
    GeneralsStrong_Layer();
    ~GeneralsStrong_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static GeneralsStrong_Layer* create(int cardId);
private:
//    void createLayer();
    void rightLayer();//右layer
    int updataProperyt(int equipId,int equipLv,int propertyType,int lv);
    void onBtnClick(Ref* pSender);
    void onEquipClick(Ref* pSender);
    void onUserClick(Node* pSender);
    void leftLayer();
    void tableLayer();
    void updateEquip();
    void requestListMsg();
    void equipStartSmeltMsg();
    void equipListMsg();
    void onMsgProcess(EventCustom* msg);
    void chooseCardOver(EventCustom* msg);
    void showEquipForgeSound();
    void effectOver();
    
    void addEventListener();
    void removeEventListener();
    //武将排序
    void onSort();
private:
    float sx;
    int TAG_LISTBG;
    int TAG_EQUIPMENT;//熔炼
    int TAG_AUTOBTN;//自动添加
    int TAG_CARDBG;
    int TAG_EQUIPBG;
    int TAG_EXPERENCE;
    int TAG_RIGHTBG;
    int TAG_RIGHTBG1;
    int TAG_EQUIPSTRONG;
    int TAG_CURRENTLABEL;//右框当前等级
    int TAG_PROPERTYLABEL;//右框当前属性值
    int TAG_EXPLABLE;
    
    int cardId;
    Vector<BaseEquipData*>* equipList;
    BaseEquipData* oldEquipData;
    BaseEquipData* newEquipData;
    int maxQuality;
        
};



#endif /* defined(__FightPass__GeneralsStrong_Layer__) */
