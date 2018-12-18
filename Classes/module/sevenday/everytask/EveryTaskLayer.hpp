//
//  EveryTaskLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#ifndef EveryTaskLayer_hpp
#define EveryTaskLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
#include "../sevendayData/TeskDexPriceDataManager.hpp"
class EveryTaskLayer:public BaseLayer, TableViewDataSource, TableViewDelegate
{
public:
    EveryTaskLayer();
    ~ EveryTaskLayer();
    static EveryTaskLayer* create(int day,int type);
    virtual bool init( int day,int type);
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table,ssize_t idx);
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view) {};
private:
    void setBackground();
    void createTableView();
    Sprite* singleList(ssize_t idx);
    void onButtonClick(Ref* pSender);
    void requestWeeTaskPage(int _day,int tasktag);
    void onWeekRewardProcess(EventCustom* msg);
    
    void onHeroHeadClick(Node* pSender );
    
    void requestWeekRewardMsg(int _day, int _type, int _numPrice, int _numHero);//q请求领取奖励
    void onWeekDayRewardMsgProcess(EventCustom* msg);
    
    void onqianwangClick(Ref* psender);
    void onGoFunctionByTaskData(TeskDesData* taskData);
private:
    int m_day;
    float sx;
    Sprite* listBg;
    int TAG_TABLEVIEW;//tableView
    TableView* _tableView;
    int m_type;
    int m_taskTag;
};

#endif /* EveryTaskLayer_hpp */
