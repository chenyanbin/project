//
//  FirstRechargeData.h
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#ifndef FightPass_FirstRechargeData_h
#define FightPass_FirstRechargeData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class FirstRechargeData:public Ref
{
public:
    FirstRechargeData()
    :itemType(0)
    ,itemId(0)
    ,itemCount(0)
    ,itemQuality(1)
    ,itemName("")
    ,status(0)
    {
        
    }
    ~ FirstRechargeData()
    {
        
    }
    int itemType;//物品类型
    int itemId ;//物品Id
    int itemCount;
    int itemQuality;
    string itemName;//发件人
    int status;//状态
};

#endif
