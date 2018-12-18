//
//  RankSynLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//  综合排名

#ifndef RankSynLayer_hpp
#define RankSynLayer_hpp

#include "extensions/cocos-ext.h"
#include "../BaseLayer.h"
USING_NS_CC_EXT;
class RankSynLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    RankSynLayer();
    ~ RankSynLayer();
    virtual bool init();
    static RankSynLayer* create();
private:
    void setPersonBg();
    void setperdetail();//个人信息
    void onPriceClick(Ref* pSender);
    void setTableView();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
    Sprite* singleList(size_t idx);
    
    void requestSynRankingMsg();
    void onSynRankingProcess(EventCustom* msg);
    
    void onfriendclick(Ref* pSender);

private:
    int TAG_TABLEVIEW;
    Size cellSize;
    int TAG_PERSONBG;
    string m_legendName;//本期名将转名字
    long m_activityStartTimes;//活动开始时间
    long m_activityEndTimes;//活动借宿时间
    int m_scoreTotal;//玩家总分
    int m_rank;//玩家排名
    int m_combatPower;//我的战斗力
    int m_roleLevel;//我的角色等级
};

#endif /* RankSynLayer_hpp */
