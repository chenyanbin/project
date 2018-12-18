//
//  MarketShopLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/27.
//
//  商店

#ifndef __FightPass__MarketShopLayer__
#define __FightPass__MarketShopLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../marketData/ShopPageListData.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
class MarketShopLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MarketShopLayer();
    ~MarketShopLayer();
    static MarketShopLayer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void createTableView();
    void setBackGround();
    Sprite* singleList(ssize_t idx);
    void onClick(Ref* psender);//购买
    void onshopitemClick(Node* pSender);//查看物品属性
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg();//请求列表信息
    void onUpdataCell(EventCustom* msg);

private:
    Sprite* listBg;
    TableView* _tableView;
    int TAG_TABLEVIEW;
    int m_todayBuyCount;//今日购买次数
    int m_maxBuyCount;//一天最大购买次数
    int m_selectedIndex;//当前选择的道具小标
    bool isMoveing;
};


#endif /* defined(__FightPass__MarketShopLayer__) */
