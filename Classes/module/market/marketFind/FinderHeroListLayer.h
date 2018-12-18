//
//  FinderHeroListLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/25.
//
//

#ifndef __FightPass__FinderHeroListLayer__
#define __FightPass__FinderHeroListLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
#include "../marketData/MarketFinderList.h"
class FinderHeroListLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FinderHeroListLayer();
    ~ FinderHeroListLayer();
    static FinderHeroListLayer* create(int findId);
    static void show(int idx);
    virtual bool init( int findId);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void createTableView();
    void setBg();
    Sprite* singleList(ssize_t idx);
    void sortList(string name);//排序
    void onTopComboBoxClick(Ref* psender);//英雄排序
    void requestListMsg();//武将列表
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void onxunfangnClick(Node* psender);
    void requestChoseHeroMsg(int findId,int heroId);
    void onChoseFinderMsgProcess(EventCustom* msg);
    void onUserClick(Node* pSender);
private:
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    Vector<MarketFinderList*> *heroList;
    int m_findId;
    
};


#endif /* defined(__FightPass__FinderHeroListLayer__) */
