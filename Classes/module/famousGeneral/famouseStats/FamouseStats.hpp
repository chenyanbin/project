//
//  FamouseStats.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//统计界面
//

#ifndef FamouseStats_hpp
#define FamouseStats_hpp


#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
class FamouseStatsData:public Ref
{
public:
    int period;//	期	int	Y	从1开始
    string activityName;//	活动名称	string	Y
    int bossDictId;
    int killBossCount;//	击杀过的boss数量	short	Y	包括自己发现的boss和他人分享给我的boss
    int maxBossLevel;//	最大boss等级	short	Y	我发现的最大boss等级, 我发现的boss每次出现等级都会成长或降级
    long long activityStartTimes;//	活动开始时间	long	Y	单位：毫秒
    long long activityEndTimes;//	活动结束时间	long		单位：毫秒

};

class FamouseStats:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FamouseStats();
    ~FamouseStats();
    virtual bool init();
    CREATE_FUNC(FamouseStats);
private:
    void setTableView();
    void requestInfoList();
    void onMsgProcess(EventCustom* message);
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
private:
    int TAG_TABLEVIEW;
    Size cellSize;
    Vector<FamouseStatsData*>* dataList;
    
};

#endif /* FamouseStats_hpp */
