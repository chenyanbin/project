//
//  VipLibaoLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/12.
//
//

#ifndef __FightPass__VipLibaoLayer__
#define __FightPass__VipLibaoLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class VipLibaoLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    VipLibaoLayer();
    ~ VipLibaoLayer();
    static VipLibaoLayer* create();
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
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void createTableView();
    void setBackGround();
    Sprite* singleList(ssize_t idx);
    void onClick(Ref* psender);//购买
    
    void requestGiltListMsg();
    void onGiltMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onHeadClick(Node* pSender);
    void onGiltBuyMsgProcess(EventCustom* msg);
private:
    Sprite* listBg;
    TableView* _tableView;
    int TAG_TABLEVIEW;
    
};

#endif /* defined(__FightPass__VipLibaoLayer__) */
