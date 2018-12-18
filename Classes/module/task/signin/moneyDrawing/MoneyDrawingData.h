//
//  MoneyDrawingData.h
//  FightPass
//
//  Created by chenyanbin on 15/12/1.
//
//  

#ifndef FightPass_MoneyDrawingData_h
#define FightPass_MoneyDrawingData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MoneyDrawingData:public Ref
{
public:
    MoneyDrawingData()
    :itemType(0)
    ,itemId(0)
    ,itemCount(0)
    ,itemQuality(0)
    ,itemName("")
    {
        
    }
    ~ MoneyDrawingData()
    {
        
    }
    int itemType;//物品类型
    int itemId ;//物品ID
    int itemCount;//物品数量
    int itemQuality;//无品品质
    string itemName;//物品名字
};


#endif
