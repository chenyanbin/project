//
//  FriendList_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#ifndef __FightPass__FriendList_Layer__
#define __FightPass__FriendList_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/MessageData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class FriendList_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FriendList_Layer();
    ~FriendList_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int cardId);
    static FriendList_Layer* create(int cardId);
private:
    void createLayer();
    void initTableView();
    
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void requestFriendListMsg();//
    void requestDeleteFriendMsg(Node* sp=NULL);//删除好友
    void deleteNotice(EventCustom* msg);
    void removeFriend();
    void addFriend(EventCustom* msg);
    void addFriendMessage();
    void sortList();
    int getIndexByUserId(string id);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    int TAG_TABLEVIEW;
    Vector<MessageData*>* m_list;
    string userId ;
};

#endif /* defined(__FightPass__FriendList_Layer__) */
