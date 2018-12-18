//
//  generalsHeroList_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/9/17.
//
//

#ifndef __FightPass__generalsHeroList_Layer__
#define __FightPass__generalsHeroList_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
#include "../../../common/TouchSprite/Button.h"
#include <Vector>

USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsHeroList_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    GeneralsHeroList_Layer();
    ~GeneralsHeroList_Layer();
    static GeneralsHeroList_Layer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void createLayer();
    void initTableView();
    Button* singleList(ssize_t idx);
    void onSellBtnClick(Ref* psender);
    void onHeadClick(Ref* pSender);
    void onTopComboBoxClick(Ref* psender);
    void updataCreat();
    
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
    virtual void scrollViewDidZoom(ScrollView* view) ;
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    float sx;
    int TAG_TABLEVIEW;
    int TAG_LATTERNUM;
    int TAG_LISTBG;//
    
    int titleCount;
//    vector<CardPropertyData*> *heroList;
    string sortMode;
    short maxHero;
    bool isMoveing;
    Label* equipNumLabel;
    Point isDownPoint;
    bool isTouchHero;
};



#endif /* defined(__FightPass__generalsHeroList_Layer__) */
