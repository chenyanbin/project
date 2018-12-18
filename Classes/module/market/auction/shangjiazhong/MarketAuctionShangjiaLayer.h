//
//  MarketAuctionShangjiaLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
// 上架中

#ifndef __FightPass__MarketAuctionShangjiaLayer__
#define __FightPass__MarketAuctionShangjiaLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../marketData/auctionData/AuctionShangjiaData.h"

class MarketAuctionShangjiaLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 10,
        TAG_MINUS
    };
    
    MarketAuctionShangjiaLayer();
    ~MarketAuctionShangjiaLayer();
    static MarketAuctionShangjiaLayer* create();
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
    void setTableViewDelegate();
    void setBackGround();
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestAuctionsahngjiaListMsg(int lastMarketGoodsId);//请求上架中列表信息
    void onAuctionshangjiaMsg(EventCustom* msg);
    void onReceiveXiajiaMsg(EventCustom* msg);
private:
    Sprite* listBg;
    TableView* _tableView;
    int m_nowcount;
    int TAG_COUNT;//数量
    int TAG_ALLCOUNT;//总售价
    bool isCopper;//是否是铜币
    bool isClick;//是否选族了付款方式
    Size cellSize;
    int m_selectedIndex;//当前选择的道具小标
    int TAG_COUNTSELL;
    bool isremove;
};


#endif /* defined(__FightPass__MarketAuctionShangjiaLayer__) */
