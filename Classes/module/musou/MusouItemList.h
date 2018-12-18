//
//  MusouItemList.h
//  FightPass
//无双关卡列表
//  Created by zhangxiaobin on 15/9/17.
//
//

#ifndef __FightPass__MusouItemList__
#define __FightPass__MusouItemList__

#include "cocos2d.h"
USING_NS_CC;
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictMusou/DictMusouManager.h"
#include "../../net/bytestream.h"
#include "data/MusouStageData.h"


class MusouItemList:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MusouItemList();
    ~MusouItemList();
    virtual bool init();
    void setListData(ByteStream* byteStream);
    CREATE_FUNC(MusouItemList);
private:
     void createTableView();
    Node* getNode(int index);
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
    Vector<MusouStageData*>* musouList;
    Point touchBeginPos;
    bool m_isMoved;
    int pageNum;
    int m_nowPage;
    int TAG_TABLEVIEW;
};

#endif /* defined(__FightPass__MusouItemList__) */
