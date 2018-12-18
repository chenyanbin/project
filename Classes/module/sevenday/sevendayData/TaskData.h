//
//  TaskData.h
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#ifndef TaskData_h
#define TaskData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct TaskPrice
{
    int itemType ;//物品类型
    int itemId;//物品id
    int itemCount;//物品数量
    string itemName;//物品名称
    string itemDesc;//物品描述
    int itemQuality;//物品品质
};


class TeskDesData:public Ref
{
public:
    TeskDesData()
    :desc("")
    ,taskId(1)
    ,status(0)
    ,function(0)
    ,functionType(0)
    {
        
    }
    ~ TeskDesData()
    {
        
    }
    
    int taskId;
    string desc;//物品描述
    int status;//状态
    int function;//前往功能模块
    int functionType;//模块类型
    vector<TaskPrice> priceList;
};

#endif /* TaskData_h */
