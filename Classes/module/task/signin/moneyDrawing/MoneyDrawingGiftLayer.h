//
//  MoneyDrawingGiftLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/12/1.
//
//

#ifndef __FightPass__MoneyDrawingGiftLayer__
#define __FightPass__MoneyDrawingGiftLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
#include "../../../../common/TouchSprite/Button.h"
USING_NS_CC_EXT;
USING_NS_CC;
class MoneyDrawingGiftLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MoneyDrawingGiftLayer();
    ~ MoneyDrawingGiftLayer();
    static MoneyDrawingGiftLayer* create(int canReceive);
    static void show(int canReceive);
    virtual bool init(int canReceive);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
private:
    void createTableView();
    void setBg();
    Sprite* singleList(ssize_t idx);
    void onUserClick(Node* pSender);
    void onReceiveClick(Ref* pSender);
    
    void requestLuckyReceiveMsg();
    void onLuckyReceiveProgress(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    bool isMoveing;
    Point isDownPoint;
    int TAG_LISTBG;
    int m_canReceive;//0 ： 不能领取 1： 可以领取
    
};

#endif /* defined(__FightPass__MoneyDrawingGiftLayer__) */
