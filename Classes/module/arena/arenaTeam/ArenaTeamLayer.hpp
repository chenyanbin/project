//
//  ArenaTeamLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/10.
//
//

#ifndef ArenaTeamLayer_hpp
#define ArenaTeamLayer_hpp

#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
class ArenaTeamLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ArenaTeamLayer();
    ~ArenaTeamLayer();
    virtual bool init();
    static ArenaTeamLayer* create();
private:
    void setTopData(int _rank,int _fightPowe,int _honer,int _fightTimes,long _time);
    void setChangeBtn();
    void onChangeBtnClick(Ref* pSender);
    void setTableView();
    Node* getTopNode(const char* titlePath,int value);
    Sprite* singleList(size_t idx);
    void onEditBtnClick(Ref* pSender);
    void onSelectedBtnClick(Ref* pSender);

    
    void requestLineupMsg();//请求消息;
    void onLineupMsgProcess(EventCustom* msg);
    
    void requestChoseMsg(int lineupNo);
    void onFightMsgProcess(EventCustom* msg);
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
    int m_index;
    int m_oldIndex;

};

#endif /* ArenaTeamLayer_hpp */
