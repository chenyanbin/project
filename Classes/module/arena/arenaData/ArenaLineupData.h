//
//  ArenaLineupData.h
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//  阵容

#ifndef ArenaLineupData_h
#define ArenaLineupData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct heroDesc
{
    int heroDictId;//武将原型
    int heroLevel;//武将等级
    int prestige;//声望
    int heroQuality;//品质
};

class ArenaLineupData:public Ref
{
public:
    ArenaLineupData()
    :lineupPower(0)
    ,isdefault(0)
    {
        
    }
    ~ ArenaLineupData()
    {
        
    }
    int lineupPower;//阵容战斗力
    int isdefault;//是否上阵页
    vector<heroDesc> herolist;
    
    
};

#endif /* ArenaLineupData_h */
