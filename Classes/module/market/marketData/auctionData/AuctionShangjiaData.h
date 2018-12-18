
//
//  AuctionShangjiaData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef FightPass_AuctionShangjiaData_h
#define FightPass_AuctionShangjiaData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class AuctionShangjiaData:public Ref
{
public:
    AuctionShangjiaData()
    :sellId(0)
    ,itemId(0)
    ,itemType(0)
    ,itemName("")
    ,quality(0)
    ,price(0)
    ,sellCount(0)
    ,remainingTimes(0)
    {
        
    }
    ~ AuctionShangjiaData()
    {
        
    }
    int sellId;//我的售卖
    int itemId ;//物品ID
    int itemType;//物品类型
    string itemName;//物品名称
    int quality;//物品质量
    int price;//价格
    int sellCount;//数量
    int remainingTimes;//剩余时间
};



#endif
