//
//  FamouseFriendLayer.hpp
//  FightPass
//名将传好友
//  Created by zhangxiaobin on 16/1/29.
//
//

#ifndef FamouseFriendLayer_hpp
#define FamouseFriendLayer_hpp

#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
#include "../../chat/data/MessageData.h"
class FamouseFriendData:public MessageData
{
public:
    FamouseFriendData():isSelected(false)
    {
        
    }
    ~FamouseFriendData()
    {
        
    }
    
    bool isSelected;
};
class FamouseFriendLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FamouseFriendLayer();
    ~FamouseFriendLayer();
    virtual bool init();
    CREATE_FUNC(FamouseFriendLayer);
    static void show();

protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgProcess(EventCustom* message);
    
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
    void setBg();
    void setPageBtn();
    void setTableView();
    Node* getNode(int idx);
    void onTopComboBoxClick(Ref* pSender);
    void onSupportBtnClick(Ref* pSender);
    void onUserClick(Node* pSender);
private:
    int TAG_TABLEVIEW;
    Size cellSize;
    bool isMoveing;
    Vector<FamouseFriendData*>* m_dataList;
    vector<long>* shareList;
};


#endif /* FamouseFriendLayer_hpp */
