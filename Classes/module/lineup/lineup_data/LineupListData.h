//
//  LineupListData.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//阵容英雄列表
//

#ifndef FightPass_LineupListData_h
#define FightPass_LineupListData_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class LineupListData:public Ref
{
public:
    LineupListData()
    :lineupNo(1)
    ,fromHeroType(1)
    ,fromLocation(1)
    ,heroId(0)
    ,heroDictId(0)
    ,heroName("")
    ,force(0)
    ,prestige()
    ,leadership(0)
    ,combatPower(0)
    ,hp(0)
    ,attack(0)
    ,defend(0)
    ,level(0)
    ,quality(0)
    ,op(0)
    ,sort(0)
    {
        
    }
    ~LineupListData()
    {
        
    }
    int lineupNo;//阵容编号
    int fromHeroType;//武将类型 1主阵 2助威
    int fromLocation;//位置，从哪个位置进入此页面的
    //下行
    int heroId;//卡牌ID
    int heroDictId;//卡牌类型ID
    string heroName;//卡牌名字
    int force;
    short prestige;//卡牌声望
    int leadership;//卡牌领导力
    int combatPower;//卡牌战斗力
    int hp;
    int attack;
    int defend;
    int level;//卡牌等级
    int quality; //卡牌品质
    int op;//可上阵/下阵
    int sort;//上阵排序
};


#endif
