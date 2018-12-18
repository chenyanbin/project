//
//  VipGiltData.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#ifndef FightPass_VipGiltData_h
#define FightPass_VipGiltData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class VipGiltData:public Ref
{
public:
    VipGiltData()
    :vipLevel(0)
    ,state(0)
    ,desc("")
    ,cost(0)
    ,costCheap()
    {
        
    }
    ~VipGiltData()
    {
        
    }
    int vipLevel;//VIP等级
    int state;//状态
    string desc;//描述
    int cost;//原价
    int costCheap;//现价
    
};

#endif
