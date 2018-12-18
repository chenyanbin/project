//
//  ArenaExchangeData.h
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//  兑换

#ifndef ArenaExchangeData_h
#define ArenaExchangeData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class ArenaExchangeData:public Ref
{
public:
    ArenaExchangeData()
    :itemType(0)
    ,itemId(0)
    ,itemCount(0)
    ,itemName("")
    ,gloy(0)
    ,itemDes("")
    ,quality(0)
    ,status(0)
    {
        
    }
    ~ ArenaExchangeData()
    {
        
    }
    int itemType;//	物品类型
    int itemId;//	物品原型id	int
    int itemCount;
    string itemName;//	物品名称	string
    int gloy;//	所需荣誉	int
    string itemDes;//	物品描述
    int quality;
    int status;
    
    
};
#endif /* ArenaExchangeData_h */
