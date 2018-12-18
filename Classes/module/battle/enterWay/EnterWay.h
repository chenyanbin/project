//
//  EnterWay.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/27.
//出场方式
//

#ifndef __FightPass__EnterWay__
#define __FightPass__EnterWay__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/Avatar.h"
class EnterWay
{
public:
    EnterWay();
    ~EnterWay();
public:
    static void jumpIn(Avatar* avatar);//跳入
    static void flashInt(Avatar* avatar);//闪入
    
};

#endif /* defined(__FightPass__EnterWay__) */
