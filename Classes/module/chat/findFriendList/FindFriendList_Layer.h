//
//  FindFriendList_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#ifndef __FightPass__FindFriendList_Layer__
#define __FightPass__FindFriendList_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/MessageData.h"
#include <Vector>
USING_NS_CC_EXT;
USING_NS_CC;
class FindFriendList_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FindFriendList_Layer();
    ~FindFriendList_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static FindFriendList_Layer* create();
    
    void requestFindFriendListMsg(string name="");
private:
    void createLayer();
    void initTableView();
    //后台协议部分
    
    void onMsgProcess(EventCustom* msg);
    //监听事件
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
    Vector<MessageData*>* listData;
};

#endif /* defined(__FightPass__FindFriendList_Layer__) */
