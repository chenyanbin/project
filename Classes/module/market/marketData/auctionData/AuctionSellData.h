//
//  AuctionSellData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef FightPass_AuctionSellData_h
#define FightPass_AuctionSellData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class AuctionSellData:public Ref
{
public:
    AuctionSellData()
    :marketGoodsId(0)
    ,itemId(0)
    ,itemType(0)
    ,itemName("")
    ,quality(0)
    ,priceLowest(0)
    ,priceHighest(0)
    ,canSellCount(0)
    {
        
    }
    ~ AuctionSellData()
    {
        
    }
    int marketGoodsId;//商品ID
    int itemId ;//物品ID
    int itemType;//物品类型
    string itemName;//物品名称
    int quality;//品质
    int priceLowest;//最低卖出价格
    int priceHighest;//最高卖出价格
    int canSellCount;//可卖出数量
};


#endif
