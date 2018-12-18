//
//  AuctionHomeData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef FightPass_AuctionHomeData_h
#define FightPass_AuctionHomeData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class AuctionHomeData:public Ref
{
public:
    AuctionHomeData()
    :sellId(0)
    ,itemId(0)
    ,itemType(0)
    ,itemName("")
    ,quality(0)
    ,price(0)
    ,sellCount(0)
    ,sellRoleName("")
    ,remainingTimes(0)
    {
        
    }
    ~ AuctionHomeData()
    {
        
    }
    int sellId;//全局售卖Id
    int itemId ;//物品ID
    int itemType;//物品类型
    string itemName;//物品名称
    int quality;//品质
    int price;//价格
    int sellCount;//数量
    string sellRoleName;//卖出人名字
    int remainingTimes;//剩余时间
};

#endif
