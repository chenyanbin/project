//
//  VipBlackShopLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/8.
//
//

#ifndef __FightPass__VipBlackShopLayer__
#define __FightPass__VipBlackShopLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class VipBlackShopLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    VipBlackShopLayer();
    ~VipBlackShopLayer();
    static VipBlackShopLayer* create();
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
    
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg(int refresh, int free );//请求列表信息
    void onUpdataBtn(Ref* psender);
    void update(float delta);
    void setlasttime();
    void onShuaxinProcess(EventCustom* msg);
    void onbuyProgress(EventCustom* msg);
    void onitemClick(Node* pSender);
private:
    Sprite* listBg;
    TableView* _tableView;
    int TAG_TABLEVIEW;
    int m_todayBuyCount;//今日购买次数
    int m_maxBuyCount;//一天最大购买次数
    int m_selectedIndex;//当前选择的道具小标
    
    long m_refreshRemainingTimes;//刷新时间
    int m_manualFrfreshGold;//花费元宝
    Label* label;
    bool m_isshuaxin;//是否刷新
    int TAG_LABELTIME;
    bool isMoveing;
};


#endif /* defined(__FightPass__VipBlackShopLayer__) */
