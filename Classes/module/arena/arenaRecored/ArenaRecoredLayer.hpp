//
//  ArenaRecoredLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/14.
//
//

#ifndef ArenaRecoredLayer_hpp
#define ArenaRecoredLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class ArenaRecoredLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ArenaRecoredLayer();
    ~ ArenaRecoredLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static ArenaRecoredLayer* create();
    static void show();
private:
    void createLayer();
    Sprite* singleList(int idx);
    void createTable();
    
    void requestRecoredMsg();//
    void onRecoredMsgProcess(EventCustom* msg);
protected:
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    virtual void addEventListener();
    virtual void removeEventListener();
    
private:
    float sx;
    float TAG_TABLEBG;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    int TAG_PERDETAILBG;
    bool isMoveing;
    Point isDownPoint;
};

#endif /* ArenaRecoredLayer_hpp */
