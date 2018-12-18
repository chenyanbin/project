//
//  DayBenefit_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/16.
//
//

#ifndef __FightPass__DayBenefit_Layer__
#define __FightPass__DayBenefit_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class DayBenefit_Layer:public BaseLayer, TableViewDataSource, TableViewDelegate
{
public:
    DayBenefit_Layer();
    ~DayBenefit_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static DayBenefit_Layer* create();
    
    
private:
    void createLayer();
    void onComboBoxBtnClick(Ref* psender);
    void onClickBtn(Ref* psender);
    void removeEventListener();
    
    void createTableView();
    Sprite* singleList(ssize_t idx);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view) {};
    
    void requestbenefitMsg();
    void onBenefitMsgProcess(EventCustom* msg);
    
    void addEventListener();
    
    void onClick(Ref* pSender);
    
    void requestlingquMsg();
    void onlingquProcess(EventCustom* msg);//领取
    void onHeroHeadClick(Node* pSender);
    
private:
    float sx;
//    Sprite* thisAward;
//    Sprite* nextVipAward;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    int m_userVipLevel;
    bool isMoveing;
    
};


#endif /* defined(__FightPass__DayBenefit_Layer__) */
