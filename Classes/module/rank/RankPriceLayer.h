//
//  RankPriceLayer.h
//  FightPass
//
//  Created by chenyanbin on 16/1/6.
//
// 查看奖励

#ifndef __FightPass__RankPriceLayer__
#define __FightPass__RankPriceLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class RankPriceLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    RankPriceLayer();
    ~ RankPriceLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static RankPriceLayer* create();
    static void show();
private:
    void createLayer();
    void onHeroHeadClick(Node* pSender);
    void onHeroHeadClick2(Node* pSender);
    void onHeroHeadClick3(Node* pSender);
    void onHeroHeadClick4(Node* pSender);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    Sprite* singleList(int idx);
    void createTable();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    float sx;
    float TAG_TABLEBG;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    int TAG_PERDETAILBG;
    bool isMoveing;
    Point isDownPoint;
};


#endif /* RankPriceLayer_h */
