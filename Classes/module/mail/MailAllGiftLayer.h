//
//  MailAllGiftLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef __FightPass__MailAllGiftLayer__
#define __FightPass__MailAllGiftLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
USING_NS_CC_EXT;
USING_NS_CC;
class MailAllGiftLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MailAllGiftLayer();
    ~ MailAllGiftLayer();
    static MailAllGiftLayer* create();
    static void show();
    virtual bool init();
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
    
//    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
//    virtual void onTouchMoved(Touch *touch, Event *unused_event);
//    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void createTableView();
    void setBg();
    Sprite* singleList(ssize_t idx);
private:
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    bool isMoveing;
    Point isDownPoint;
    int TAG_LISTBG;
};


#endif /* defined(__FightPass__MailAllGiftLayer__) */
