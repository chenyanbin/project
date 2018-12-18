//
//  WeekHalfGiftData.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef FightPass_WeekHalfGiftData_h
#define FightPass_WeekHalfGiftData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class WeekHalfGiftData:public Ref
{
public:
    WeekHalfGiftData()
    :itemType(1)
    ,itemId(0)
    ,itemCount(0)
    ,itemName("")
    ,itemDesc("")
    ,itemQuality()
    ,status(0)
    ,priceOri(0)
    ,price(0)
    ,sellCount(0)
    ,selledCount(0)
    {
        
    }
    ~ WeekHalfGiftData()
    {
        
    }
    int itemType;//物品类型
    int itemId ;//ID
    int itemCount;//物品数量
    string itemName;//物品名称
    string itemDesc;//物品描述
    int itemQuality;//物品品质
    int status;//状态
    int priceOri;//原价
    int price;//现价
    int sellCount;//可购买数量
    int selledCount;//已购买数量
};



#endif
