//
//  GeneralsEquip_Scene.h
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#ifndef __FightPass__GeneralsEquip_Scene__
#define __FightPass__GeneralsEquip_Scene__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include <Vector>
#include "../../../common/comboxBtn/ComboBoxBtn.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsEquip_Scene:public BaseLayer
{
public:
    GeneralsEquip_Scene();
    ~GeneralsEquip_Scene();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    
    virtual bool init(int value);
    static GeneralsEquip_Scene* create(int value);
    static void show(int fromeScene,int valueId);
private:
    void createLayer();
    void addRightList();//右列表
    void onComboBoxBtnClick(Ref* psender);
    void smeltLayer();
    
    void onBackClick(Ref* pSender);
    void addEventListener();
    void removeEventListener();
    void onRefreshDot(EventCustom* msg);
private:
    int TAG_TOP;
    int TAG_STRONGLAYER;
    int TAG_SMELTLAYER;
    int TAG_BOBOXCOM;
    float sx;
    int userlayerHeight;
    int chooseId;
    ComboBoxBtn* boxBtn;
};

#endif /* defined(__FightPass__GeneralsEquip_Scene__) */
