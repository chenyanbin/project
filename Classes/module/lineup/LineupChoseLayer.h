//
//  LineupChoseLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#ifndef __FightPass__LineupChoseLayer__
#define __FightPass__LineupChoseLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
class LineupChoseLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    LineupChoseLayer();
    ~LineupChoseLayer();
    virtual bool init();
    static LineupChoseLayer* create();
private:
    void createTableView();
    Node* getCellSizeNode(int index);
    void setBackGround();
    void setDirectBtn();
    void LeftAndRightVisible(float pt);
    
    void leftPage(Ref* pSender);
    void rightPage(Ref* pSender);
    
protected:
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    virtual void onEnter();
    virtual void onExit();
private:
    Size cellSize;
    int pageNum;
    Point touchBeginPos;
    int m_nowPage;
    int m_totalCount;
    Sprite* downBtn;
    Sprite* upBtn;
    bool m_isMoved;
private:
    int TAG_TABLEVIEW;
};


#endif /* defined(__FightPass__LineupChoseLayer__) */
