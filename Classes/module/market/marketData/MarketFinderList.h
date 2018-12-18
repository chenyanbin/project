//
//  MarketFinderList.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef FightPass_MarketFinderList_h
#define FightPass_MarketFinderList_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MarketFinderList:public Ref
{
public:
    MarketFinderList()
    :maxSize(1)
    ,heroSize(1)
    ,heroId(0)
    ,heroDictId(0)
    ,heroName("")
    ,force(0)
    ,prestige()
    ,leadership(0)
    ,combatPower(0)
    ,level(0)
    ,quality(0)
    {
        
    }
    ~MarketFinderList()
    {
        
    }
    int maxSize;//最大武将数量
    int heroSize;//武将数量
    int heroId;//卡牌ID
    int heroDictId;//卡牌类型ID
    string heroName;//卡牌名字
    int force;
    short prestige;//卡牌声望
    int leadership;//卡牌领导力
    int combatPower;//卡牌战斗力
    int level;//卡牌等级
    int quality; //卡牌品质
};

#endif
