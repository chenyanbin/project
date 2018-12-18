//
//  DetailsLayer.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef DetailsLayer_hpp
#define DetailsLayer_hpp


#include "extensions/cocos-ext.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
class DetailsItemData:public Ref
{
public:
    int itemType;//	物品类型	byte	Y	DictItemTypeEnum
    int itemId;//	物品item id	int	Y	获得新物品的item id
//    武将：DictItemHero.id
//    装备：DictItemEquip.id
//    书信：DictItemBook.id
//    材料：DictItemMater.id
//    道具：DictItem.id
//    角色资源：DictResource.id
    int quality;//	品质	byte	Y	新物品品质
    int count;//	数量	byte	Y	物品数量
    int heroPrestige;//武将声望
};

class DetailsData:public Ref
{
public:
    DetailsData()
    {
        itemList = new Vector<DetailsItemData*>();
    }
    ~DetailsData()
    {
        CC_SAFE_DELETE(itemList);
        itemList = NULL;
    }
   
    string roleName;//	角色名称	string	Y	角色名称
    int iconHeroDictId;//	角色头像	int	Y	角色头像 DictHero.id
    int roleLevel;//	角色等级	int
    int prestige;//声望
    bool isFinder;//	是否为发现者	byte	Y	0否1是
    bool isTop;//	是伤害最高者	;//
    int attackCount	;//攻击次数	byte	Y
    int hurt;
    Vector<DetailsItemData*>* itemList;
};

class DetailsLayer:public BaseLayer,TableViewDataSource,TableViewDelegate
{
public:
    DetailsLayer();
    ~DetailsLayer();
    virtual bool init(int bossID);
    static DetailsLayer* create(int bossID);
    static void show(int bossID);
private:
    void setBossBg();
    void setTableView();
    void onMsgProcess(EventCustom* message);
    void setBoss();
    void setScore();
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
    int bossDictId;//boss原型id	int	Y	DictLegendBattleMonster.id
    string bossName;
    int score;
    float hp;
    float hpMax;
    int status;//	boss状态	byte	Y	1 击杀 2 逃跑
    Vector<DetailsData*>* listData;
private:
    int m_bossID;
    int TAG_TABLEVIEW;
    Size cellSize;
    int TAG_BOSSBG;
    
};

#endif /* DetailsLayer_hpp */
