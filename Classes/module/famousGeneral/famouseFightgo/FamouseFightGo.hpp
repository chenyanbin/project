//
//  FamouseFightGo.hpp
//  FightPass
//奇袭界面
//  Created by zhangxiaobin on 16/1/7.
//
//

#ifndef FamouseFightGo_hpp
#define FamouseFightGo_hpp
#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
//bossId	boss id	int	Y
//bossName	boss名称	string	Y
//bossLevel	boss等级	short	Y
//bossFinderName	boss发现者名称	string	Y
//bossRemainSeconds	倒计时	int	Y	单位：秒
//此时间过后，boss会逃跑
//attackRoleCount	攻击角色数量	short	Y	当前攻击此boss的角色数量
//hurt	伤害	int	Y	我对boss的伤害
//hp	剩余血量	int	Y
//hpMax	最大血量	int	Y
class FamouseBossData:public Ref
{
public:
    int bossId;
    int bossDictId;
    string bossName;
    int bossLevel;
    string bossFinderName;
    int bossRemainSeconds;//单位：秒 此时间过后，boss会逃跑
    long endTime;// 结束时间
    int attackRoleCount;//	攻击角色数量	short	Y	当前攻击此boss的角色数量
    int hurt;//	伤害	int	Y	我对boss的伤害
    int hp;//	剩余血量	int	Y
    int hpMax;//	最大血量	int	Y
};


class FamouseFightGo:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    FamouseFightGo();
    ~FamouseFightGo();
    virtual bool init();
    CREATE_FUNC(FamouseFightGo);
private:
    void setTableView();
    void requestListMsg();
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
    Vector<FamouseBossData*>* dataList;
    Size cellSize;
   
};


#endif /* FamouseFightGo_hpp */
