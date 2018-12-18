//
//  Generals_Sell_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#ifndef __FightPass__Generals_Sell_Layer__
#define __FightPass__Generals_Sell_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "data/CardDataManager.h"
#include "data/EquipDataManager.h"
#include "../BaseLayer.h"
#include "../../commonData/dictData/DictHeroPrestigeUpCost/DictHeroPrestigeUpCostManager.h"
USING_NS_CC_EXT;
USING_NS_CC;
class Generals_Sell_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    Generals_Sell_Layer();
    ~Generals_Sell_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static Generals_Sell_Layer* create(int isValue);
private:
    void createLayer();
    void initTableView();
    void onUserClick(Node* pSender);
    void updataData();
    void onSellBtn(Ref* psender);
    int getIndexByCardID(int _HeroId);
    int getIndexByEquipID(int _EquipId);
    
    void addEventListener();
    void removeEventListener();
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    //服务器
    void requestListMsg();
    void requestSellMsg();
    void onMsgProcess(EventCustom* msg);
    void onUpData();
    
    void sortList(string name);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    float sx;
    Vector<CardPropertyData*> *cardList;
    Vector<CardPropertyData*> *selectCardList;
    Vector<BaseEquipData*> *equipList;
    Vector<BaseEquipData*> *selectEquipList;
    Point isDownPoint;
    bool isMoveing;
    string thisSort;
    int isEquipOrHero;//0:equip;1:hero;
    int TAG_CONSUME;
    int TAG_TABLEVIEW;
};


#endif /* defined(__FightPass__Generals_Sell_Layer__) */
