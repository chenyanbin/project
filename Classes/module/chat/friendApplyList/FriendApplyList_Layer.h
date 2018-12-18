//
//  FriendApplyList_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#ifndef __FightPass__FriendApplyList_Layer__
#define __FightPass__FriendApplyList_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/MessageData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class FriendApplyList_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FriendApplyList_Layer();
    ~FriendApplyList_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static FriendApplyList_Layer* create(int cardId);
private:
    void createLayer();
    void initTableView();
    
    void requestApplyListMsg(EventCustom* evt=NULL);
    void onMsgProcess(EventCustom* msg);
    
    void addEventListener();
    void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    int TAG_TABLEVIEW;
    Vector<MessageData*>* m_list;
};

#endif /* defined(__FightPass__FriendApplyList_Layer__) */
