//
//  StageListLayer.h
//  FightPass
//这个模块已经不有了
//  Created by chenyanbin on 15/6/13.
//
//

#ifndef __FightPass__StageListLayer__
#define __FightPass__StageListLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
class StageListLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    StageListLayer();
    ~StageListLayer();
    virtual bool init();
    static StageListLayer* create();
private:
    void createTableView();
    Node* getCellSizeNode(int index);
    void leftPage(Ref* pSender);
    void rightPage(Ref* pSender);
    
    void setDirectBtn();
    void LeftAndRightVisible();
    void setParticle();
    
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
//    int totalBattle;//总战役数
    vector<BattleType>* battleList;
    int pageNum;
    Point touchBeginPos;
    int m_nowPage;
    Button* leftBtn;
    Button* rightBtn;
    bool m_isMoved;
    
private:
    int TAG_TABLEVIEW;
};

#endif /* defined(__FightPass__StageListLayer__) */
