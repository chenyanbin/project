//
//  MarketAuctionSellLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
// 出售

#ifndef __FightPass__MarketAuctionSellLayer__
#define __FightPass__MarketAuctionSellLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../marketData/auctionData/AuctionSellData.h"
#include "../../../userWealth/UserEquipLayer.h"
class MarketAuctionSellLayer:public BaseLayer,TableViewDataSource,TableViewDelegate,public cocos2d::extension::EditBoxDelegate
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 100,
        TAG_MINUS
    };

    MarketAuctionSellLayer();
    ~MarketAuctionSellLayer();
    static MarketAuctionSellLayer* create();
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
    
    //输入伪托
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
private:
    void createTableView();
    void setBackGround();
    UserEquipLayer* singleList(ssize_t idx);
    void setrightBg();
    void setcount(Ref* psender);
    void setPrice(int nowCount);
    void setSellEquip(Ref* psender);
    void onHeroHeadClick(Node* psender);
    
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestAuctionSellListMsg(int lastMarketGoodsId);//请求出售列表信息
    void onAuctionSellMsg(EventCustom* msg);
    
    void requestSureAuctionSellListMsg(int itemType, int itemId, int sellCount,int price);//请求卖出
    void onAuctionSureSell(EventCustom* msg);
    void setTableViewDelegate();
    void setrightLabel(int idx);
    void updateSellLabel(int idx);
    void onitemHeadClick(Node* psender);
private:
    Sprite* listBg;
    int now_count;//商店物品数量
    TableView* _tableView;
    int m_nowcount;//上架数量
    int TAG_COUNT;//数量
    EditBox* editbox;
    int TAG_SELL;
    int TAG_HEAD;
    int TAG_COUNTSELL;
    Size cellSize;
    int m_selectedIndex;//当前选择的道具小标
    Vector<AuctionSellData*> *m_sellList;

};

#endif /* defined(__FightPass__MarketAuctionSellLayer__) */
