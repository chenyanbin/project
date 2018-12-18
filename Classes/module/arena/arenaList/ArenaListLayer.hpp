//
//  ArenaListLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//竞技场列表
//

#ifndef ArenaListLayer_hpp
#define ArenaListLayer_hpp

#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
class ArenaListLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ArenaListLayer();
    ~ArenaListLayer();
    virtual bool init();
    static ArenaListLayer* create();
    static void show();
private:
    void setTopData(int _rank,int _fightPowe,int _honer,int _allFreeTimes,int _freeTimes);
    Node* getTopNode(const char* titlePath,int value,int freeTime = 100);
    void setChangeBtn();
    void onChangeBtnClick(Ref* pSender);
    void setTableView();
    void setTime();
    
    
    void requestFightListMsg(int refresh);
    void onMsgProcess(EventCustom* message);
    
    void ontFightNumMsgProcess(EventCustom* msg);
    void onSureFightProcess(EventCustom* msg);
    
    void requestBeginFightListMsg(int index);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    int TAG_TABLEVIEW;
    Size cellSize;
    long m_countDown;//倒计时
    int TAG_LEFTTIME;
    int TAG_NODELETTLE;
    int TAG_TOPNODE;
    int m_arenaCount;//挑战底数
    int m_buyCount;//购买次数
    int m_buyCDTimeGold;//冷却时间所需要的元宝
    int m_buyCounyGlod;//买次数所需元宝
    int m_index;//挑战对手角标
    bool m_isRefresh;
};

#endif /* ArenaListLayer_hpp */
