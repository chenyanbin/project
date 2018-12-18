//
//  RaidsLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/25.
//
//

#ifndef __FightPass__RaidsLayer__
#define __FightPass__RaidsLayer__

#include "../BaseLayer.h"
#include "../../net/bytestream.h"
#include "../battle/settleLayer/BattleWin.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
class RaidsData:public Ref
{
public:
    RaidsData():expAdd(0),coinAdd(0),itemList(NULL),commonLen(0),prestigeLen(0)
    {
        itemList = new Vector<PrizeData*>();
    }
    ~RaidsData()
    {
        itemList->clear();
        CC_SAFE_DELETE(itemList);
        itemList = NULL;
    }
    int expAdd;
    int coinAdd;
    int commonLen;//普通掉落数量
    int prestigeLen;//声望掉落数量
    Vector<PrizeData*>* itemList;//根据普通掉落数量和声望数量分辨是普通掉落还是声望掉落
};
class RaidsLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    RaidsLayer();
    ~RaidsLayer();
    virtual bool init(ByteStream* byteStream);
    static RaidsLayer* create(ByteStream* byteStream);
    static void show(ByteStream* byteStream);
private:
    void parseMsg(ByteStream* byteStream);
    void setTableView();
    void setBg();
    Node* getNode(int index);
    void setTitle();
    void onUpdate(float dt);
    void setContentOffSet();
    void onContentBack();
    void onCompleted();
    void onSetCloseState();
    void onCompletedBtnClick(Ref* pSender);
    void onItemClick(Node* psender);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    
    
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
     Vector<RaidsData*>* prizeList;//物品奖励
    int m_nowIndex;
    Point initPoint;
    bool isAbleClick;
    Size cellSize;
    int TAG_TABLEVIEW;
};

#endif /* defined(__FightPass__RaidsLayer__) */
