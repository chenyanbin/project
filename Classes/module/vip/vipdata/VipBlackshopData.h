//
//  VipBlackshopData.h
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#ifndef FightPass_VipBlackshopData_h
#define FightPass_VipBlackshopData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class VipBlackshopData:public Ref
{
public:
    VipBlackshopData()
    :shopId(0)
    ,itemType(1)
    
    ,itemId(1)
    ,itemName("")
    ,itemQuality(0)
    ,status()
    ,priceOri(0)
    ,price(0)
    ,openVipLevel(0)
    ,count(0)
    ,conId(0)
    {
        
    }
    ~VipBlackshopData()
    {
        
    }
    int shopId;//商品id
    int itemType ;//物品类型
    int itemId;//物品id
    string itemName;//物品Id
    int itemQuality;//物品品质
    int status;//状态
    int priceOri;//原价
    int price;//现价
    int openVipLevel;//开启vip等级
    int count;//数量
    int conId;//消耗资源类型
    
};

#endif
