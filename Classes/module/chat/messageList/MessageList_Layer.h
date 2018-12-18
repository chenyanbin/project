//
//  MessageList_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/11/23.
//
//

#ifndef __FightPass__MessageList_Layer__
#define __FightPass__MessageList_Layer__
#include "../data/MessageData.h"
#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../../YVSDK/YVPlatform.h"
using namespace YVSDK;
class MessageList_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MessageList_Layer();
    ~MessageList_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static MessageList_Layer* create(int cardId);
private:
    void createLayer();
    void initTableView();
    void tableTouched(Ref* psender);
    
    void addEventListener();
    void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setWorldMsg();//设置世界聊天
    void onMsgItemClick(Ref* item);
private:
    vector<YVMessagePtr>* messageList;
    Size cellSize;
    bool isMoveing;
private:
    int TAG_TABLEVIEW;
};

#endif /* defined(__FightPass__MessageList_Layer__) */
