//
//  GeneralsEquip_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/21.
//
//

#ifndef __FightPass__GeneralsEquip_Layer__
#define __FightPass__GeneralsEquip_Layer__


#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include <Vector>
#include "../../../common/TouchSprite/Button.h"

USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsEquip_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsEquip_Layer();
    ~GeneralsEquip_Layer();
    static GeneralsEquip_Layer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void initTableView();
    Button* singleList(ssize_t idx);
    void onSellBtnClick(Ref* psender);
    void onHeadClick(Ref* pSender);
    void onTopComboBoxClick(Ref* psender);
    void createLayer();
    void updataCreate();
    
    void requestListMsg(EventCustom* evt=NULL);
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void sortList(string name);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    float sx;
    int TAG_TABLEVIEW;
    int TAG_LATTERNUM;
    int TAG_LISTBG;//
    int titleCount;
    int maxListSize;
    short maxHero;
    
    Label* equipNumLabel;
    bool isMoveing;
    bool isTouchEquip;
    Point isDownPoint;
    
};


#endif /* defined(__FightPass__GeneralsEquip_Layer__) */
