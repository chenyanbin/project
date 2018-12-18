//
//  WeekBenefit_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/16.
//
//

#ifndef __FightPass__WeekBenefit_Layer__
#define __FightPass__WeekBenefit_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../../../common/TouchSprite/Button.h"
#include "../../../data/BaseTypeData.h"
class WeekBenefit_Layer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    WeekBenefit_Layer();
    ~WeekBenefit_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static WeekBenefit_Layer* create();
private:
    void createLayer();
    void onComboBoxBtnClick(Ref* psender);
    void onClickBtn(Ref* psender);
    void removeEventListener();
    Node* singleList(ssize_t idx);
    void onVipClick(Ref* pSender);
    void onSelected(Ref* pSender);
    void initTableView();
    void setSelectedByIndex(int index);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
  
    void setItem(int viplevel);
    void onHeroHeadClick(Node* pSender);
    void UpdataTime(float dt);
    
    void requestWeekbenefitMsg();
    void onWeekBenefitMsgProcess(EventCustom* msg);
    void requestWeeklingquMsg(int viplevel);
    void onWeeklingquProcess(EventCustom* msg);//领取
    void addEventListener();
    
private:
    float sx;
    int selectVip;
    int TAG_TABLEVIEW;
    Button* _itemImage;
    int TAG_NODE;
    int m_viplevel;
    int TAG_RESETTIME;//倒计时时间
    long m_resettimess;//倒计时的时间
    Label* m_resettimeLabel;
    
};

#endif /* defined(__FightPass__WeekBenefit_Layer__) */
