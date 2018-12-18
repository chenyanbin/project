//
//  ArenaOrderLayerList.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/9.
//竞技排行榜
//

#ifndef ArenaOrderLayerList_hpp
#define ArenaOrderLayerList_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class ArenaOrderLayerList:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    ArenaOrderLayerList();
    ~ ArenaOrderLayerList();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static ArenaOrderLayerList* create();
   
private:
    void createLayer();
    void onSeeMeClick(Ref* pSender);
    void onSeeOtherClick(Ref* pSender);
    void setTopData(int _rank,int _fightPowe,int _honer,long _fightTimes,long _time);
    Node* getTopNode(const char* titlePath,int value);
    Sprite* singleList(int idx);
    void createTable();
    
    void requestRankMsg();//
    void onRankMsgProcess(EventCustom* msg);
protected:
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    
    
    virtual void addEventListener();
    virtual void removeEventListener();
    
    
private:
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    int TAG_PERDETAILBG;
    int m_myRank;//我的排名
    Point  m_tableView;
};


#endif /* ArenaOrderLayerList_hpp */
