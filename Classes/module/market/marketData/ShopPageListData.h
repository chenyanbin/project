//
//  ShopPageListData.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
// 商店

#ifndef FightPass_ShopPageListData_h
#define FightPass_ShopPageListData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class ShopPageListData:public Ref
{
public:
    ShopPageListData()
    :shopId(0)
    ,itemType(0)
    ,itemId(0)
    ,itemName("")
    ,quality(0)
    ,desc("")
    ,gold(0)
    ,goldnow(0)
    ,todayBuyCount(0)
    ,maxBuyCount(0)
    ,ownCount(0)
    {
        
    }
    ~ShopPageListData()
    {
        
    }
    int shopId;//售卖ID
    int itemType ;//物品类型
    int itemId;//物品Id
    string itemName;//物品名称
    int quality;//品质
    string desc;//物品描述
    int gold;//花费元宝原价
    int goldnow;//现价
    int todayBuyCount;//今日购买次数
    int maxBuyCount;//一天最大购买次数
    int ownCount;//拥有数量
};

#endif
