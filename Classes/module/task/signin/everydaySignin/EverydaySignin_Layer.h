//
//  EverydaySignin_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/9.
//
//

#ifndef __FightPass__EverydaySignin_Layer__
#define __FightPass__EverydaySignin_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
#include "../../../data/BaseTypeData.h"
USING_NS_CC_EXT;
USING_NS_CC;

class SigninData
{
public:
    int itemType;//物品类型
    int itemId;//物品ID
    int itemQuality;//物品品质
    int itemCount;//物品数量
    int vipDouble;//是否双倍签到
    int itemStatus;//领取状态
};

class EverydaySignin_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    EverydaySignin_Layer();
    ~EverydaySignin_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static EverydaySignin_Layer* create();
private:
    void createLayer();
    void onComboBoxBtnClick(Ref* psender);
    
    void requestListMsg();
    void requestListGetMsg();
    void onMsgProcess(EventCustom* msg);
    void onUserTipsClick(Node* pSender);
    void onUserClick(Node* pSender);
    void addEventListener();
    void removeEventListener();
    
    void initTableView();
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
    float sx;
    int TAG_TABLEVIEW;
    vector<SigninData*> *m_list;
    bool isMoveing;
    Point isDownPoint;
    int m_day;
    int m_month;
    Vector<BaseTypeData*> *m_baseList;
};

#endif /* defined(__FightPass__EverydaySignin_Layer__) */
