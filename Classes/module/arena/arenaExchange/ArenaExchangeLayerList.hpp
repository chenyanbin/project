//
//  ArenaExchangeLayerList.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/10.
//
//

#ifndef ArenaExchangeLayerList_hpp
#define ArenaExchangeLayerList_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../../data/BaseTypeData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class ArenaExchangeLayerList : public BaseLayer, TableViewDataSource,TableViewDelegate
{
public:
    ArenaExchangeLayerList();
    ~ArenaExchangeLayerList();
    virtual bool init();
    static ArenaExchangeLayerList* create();
    
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void createLayer();
    Sprite* singleList(int idx);
    void createTable();
    void onExchangeClick(Ref* pSender);
    void setTopData(int _rank,int _fightPowe,int _honer);
    Node* getTopNode(const char* titlePath,int value);
    void onitemClick(Node* pSender);
    void onUpdataBtn(Ref* pSender);
    void requestExchangeMsg(int refresh);
    void onExchangeMsgProcess(EventCustom* msg);
    void requestOneExchangeMsg(int itemid);
private:
    TableView* _tableView;
    int TAG_TABLEVIEW;
    int m_ownGloy;//个人荣誉值
    int m_index;
    Vector<BaseTypeData*>* m_baselist;
    int m_custHonnor;
    bool m_isUpdata;//shifoushuaxin
    int TAG_TOPNODE;//
    int m_combatPower;//战斗力
    int m_currentRank;//当前排名
};

#endif /* ArenaExchangeLayerList_hpp */
