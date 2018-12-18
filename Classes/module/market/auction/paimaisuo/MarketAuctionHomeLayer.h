//
//  MarketAuctionHomeLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//  拍卖所

#ifndef __FightPass__MarketAuctionHomeLayer__
#define __FightPass__MarketAuctionHomeLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../marketData/auctionData/AuctionHomeData.h"
class MarketAuctionHomeLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    MarketAuctionHomeLayer();
    ~MarketAuctionHomeLayer();
    static MarketAuctionHomeLayer* create();
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
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void createTableView();
    void setBackGround();
    
    virtual void addEventListener();
    virtual void removeEventListener();
    void onAuctionHomeMsg(EventCustom* msg);
    void requestAuctionHomeListMsg(const char* itemName,int lastSellId);//请求拍卖所列表信息
    void setTableViewDelegate();
    void updataAuctuon(EventCustom* msg);
    void setOnSerch(EventCustom* msg);
private:
    Sprite* listBg;
    int now_count;//商店物品数量
    Size cellSize;
   
    TableView* _tableView;
    Vector<AuctionHomeData*> *m_homeList;
    int TAG_TIME;//倒计时时间
    long timess;//倒计时的时间
    bool isMoveing;
    Point isDownPoint;
    bool m_isrearch;
    bool m_isscroll;
};


#endif /* defined(__FightPass__MarketAuctionHomeLayer__) */
