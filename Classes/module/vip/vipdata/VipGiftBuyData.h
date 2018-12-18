//
//  VipGiftBuyData.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#ifndef FightPass_VipGiftBuyData_h
#define FightPass_VipGiftBuyData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class VipGiftBuyData:public Ref
{
public:
    VipGiftBuyData()
    :itemType(0)
    ,itemDictId(0)
    ,itemName("")
    ,itemQuality(0)
    ,itemDesc("")
    ,itemCount(0)
    {
        
    }
    ~VipGiftBuyData()
    {
        
    }
    int itemType;//物品类型
    int itemDictId;//物品ID
    string itemName;//物品名称
    int itemQuality;//物品品质
    string itemDesc;//描述
    int itemCount;//数量
};


#endif
