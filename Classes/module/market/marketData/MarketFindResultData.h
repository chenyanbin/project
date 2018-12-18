
//
//  MarketFindResultData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/6.
//
//

#ifndef FightPass_MarketFindResultData_h
#define FightPass_MarketFindResultData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MarketFindResultData:public Ref
{
public:
    MarketFindResultData()
    :heroId(0)
    ,dictId(0)
    ,name("")
    ,level(0)
    ,prestige(0)
    ,combatPower(0)
    ,leaderShip(0)
    ,quality(0)
    ,itemId(0)
    ,itemDesc("")
    ,heroForce(0)
    ,itemCount(0)
    {
        
    }
    ~MarketFindResultData()
    {
        
    }
    int itemType;//物品类型
    int heroId;//卡牌ID(顺序ID)
    
    int itemId;//物品ID
    int dictId;//英雄ID
    int itemCount;//卡牌数量
    int heroForce;//当前所属势力   1魏 2吴 3蜀
    string name;//卡牌名字
    int quality; //卡牌品质
    int level;//卡牌等级
    int prestige;//卡牌声望
    int combatPower;//卡牌战斗力
    int leaderShip;//卡牌领导力
    string itemDesc;//描述
};


#endif
