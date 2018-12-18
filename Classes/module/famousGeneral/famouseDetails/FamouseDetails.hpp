//
//  FamouseDetails.hpp
//  FightPass
//详情界面
//  Created by zhangxiaobin on 16/1/7.
//
//

#ifndef FamouseDetails_hpp
#define FamouseDetails_hpp

#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
//bossName	boss名称	string	Y
//bossLevel	boss等级	short	Y
//bossFinderName	boss发现者名称	string	Y
//attackRoleCount	攻击角色数量	short	Y
//hurt	伤害	int	Y
//hp	剩余血量	int	Y
//hpMax	最大血量	int	Y
//status	boss状态	byte	Y	1 击杀
//2 逃跑
class DetailsListData:public Ref
{
public:
    DetailsListData()
    :isGettedPrize(false)
    {
        
    }
    ~DetailsListData()
    {
        
    }
public:
    int bossID;
    int bossDictID;
    string bossName;//boss名称
    int bossLevel;//boss等级
    string bossFinderName;//boss发现者名称
    int attackRoleCount;//攻击角色数量
    int hurt;//伤害
    float hp;//剩余血量
    float hpMax;//最大血量
    int status;//1 击杀 //2 逃跑
    bool isGettedPrize;//奖励领取状态0 未领取， 1已领取
    long bossRemainSeconds;//剩余时间秒
    
};

class FamouseDetails:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FamouseDetails();
    ~FamouseDetails();
    virtual bool init();
    CREATE_FUNC(FamouseDetails);
private:
    void setTableView();
    void requestList();
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
    Vector<DetailsListData*>* dataList;
    
};

#endif /* FamouseDetails_hpp */
