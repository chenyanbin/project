//
//  MarketFindData.h
//  FightPass
//
//  Created by chenyanbin on 15/8/31.
//
// 寻访页

#ifndef FightPass_MarketFindData_h
#define FightPass_MarketFindData_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MarketFindData:public Ref
{
public:
    MarketFindData()
    :findSize(0)
    ,findId(1)
    ,status(1)
    ,heroId(0)
    ,heroDictId(0)
    ,heroQuality(0)
    ,heroLevel(0)
    ,heroPrestige()
    ,remainingTime(0)
    ,fastGold(0)
    {
        
    }
    ~MarketFindData()
    {
        
    }
    
    int findSize;//寻访数量
    int findId ;//寻访
    int status;//状态
    int heroId;//寻访武将
    int heroDictId;//dict id
    int heroQuality;//英雄品质
    int heroLevel;//武将等级
    int heroPrestige;//武将声望
    int remainingTime;//寻访剩余时间
    int fastGold;//加速寻访需要金币
};


#endif
