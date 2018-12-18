//
//  GeneralsEquipStrong_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/25.
//
//

#ifndef __FightPass__GeneralsEquipStrong_Layer__
#define __FightPass__GeneralsEquipStrong_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../data/EquipDataManager.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsEquipStrong_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsEquipStrong_Layer();
    ~GeneralsEquipStrong_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static GeneralsEquipStrong_Layer* create(int cardId);
private:
    void createLayer();
    void initTableView();
    void onUserClick(Node* pSender);
    int countLeastLocation();
    
    void addEventListener();
    void removeEventListener();
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    void onStartExperience(Ref* psender);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    float sx;
    int TAG_LISTBG;
    int TAG_TABLEVIEW;
    int TAG_EXPERIENCELABEL;//当前获得经验
    int TAG_EXPUPDATALABEL;//升级所需经验
    int TAG_CURRENTLV;//当前等级
    int TAG_UPLEVEL;//升级后等级
    
    int TAG_ADDPRESTIGE;//加声望
    int TAG_CONSUME;//花费
    
    int cardId;
    int cardExperience;//
    int cardLeve;//当前卡牌等级；
    int getExperience;//当前获得经验；
    int upgradeExperience;//升级所需经验；
    Point isDownPoint;
    bool isMoveing;
    bool isClose;
    Vector<BaseEquipData*>* equipList;
};

#endif /* defined(__FightPass__GeneralsEquipStrong_Layer__) */
