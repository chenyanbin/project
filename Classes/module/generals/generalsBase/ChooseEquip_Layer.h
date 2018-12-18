//
//  ChooseEquip_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//

#ifndef __FightPass__ChooseEquip_Layer__
#define __FightPass__ChooseEquip_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/BaseEquipData.h" 
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class ChooseEquip_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ChooseEquip_Layer();
    ~ChooseEquip_Layer();
//    CREATE_FUNC(ChooseEquip_Layer);
    static ChooseEquip_Layer* create(int heroId ,int slot);
    virtual bool init(int heroId ,int slot);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    static void show(int fromeScene,int heroId ,int slot);
    
private:
    void initTableView();
    void createLayer();
    void topLayer();
    void setBackBg();
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void sortList(string name);
    string equipParts(int num);
    void equipPutOnMsg(int equitId);
    void equipTakeOffMsg();
    
    void onTopComboBoxClick(Ref* psender);
    void onRightBtnClick(Ref* psender);
    void onBtnListClick(Ref* psender);
    void onBtnClick(Ref* psender);
    
    Sprite* singleList(ssize_t num);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
private:
    float sx;
    float sy;
    int TAG_TABLEVIEW;
    int TAG_LISTBG;
    int TAG_BOTTOMBG;
    int TAG_TOP;
    int TAG_EQUIPS;
    int TAG_BTN;
    int titleCount;
    int clickIdx;
    short maxHero;
    int _heroId;
    int _slot;
    vector<BaseEquipData*> *equipList;
};


#endif /* defined(__FightPass__ChooseEquip_Layer__) */
