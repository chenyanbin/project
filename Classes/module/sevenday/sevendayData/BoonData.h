//
//  BoonData.h
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#ifndef BoonData_h
#define BoonData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class BoonData:public Ref
{
public:
    BoonData()
    :rewardType(0)
    ,itemType(1)
    ,itemId(0)
    ,itemCount(0)
    ,itemName("")
    ,itemDesc("")
    ,itemQuality()
    
    {
        
    }
    ~ BoonData()
    {
        
    }
    int rewardType;//奖励类型
    int itemType ;//物品类型
    int itemId;//物品id
    int itemCount;//物品数量
    string itemName;//物品名称
    string itemDesc;//物品描述
    int itemQuality;//物品品质
};

class WeekDescData:public Ref
{
public:
    WeekDescData()
    :desc("")
    ,rewardType(1)
    ,status(0)
    ,targetValue(0)
    {
        
    }
    ~ WeekDescData()
    {
        
    }
    string desc;//物品描述
    int rewardType;
    int status;//状态
    int targetValue;//达到的目标值
    int finishValue;//完成值
};





#endif /* BoonData_h */
