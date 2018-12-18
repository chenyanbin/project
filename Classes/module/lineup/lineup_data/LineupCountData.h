//
//  LineupCountData.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//阵容数量

#ifndef FightPass_LineupCountData_h
#define FightPass_LineupCountData_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class LineupCountData:public Ref
{
public:
    LineupCountData()
    :maxCount(0)
    ,nextConsume(0)
    ,lineupSize(0)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~LineupCountData()
    {
        
    }
    int maxCount;//最大阵容数量
    int lineupSize;//当前阵容数量
    int nextConsume;//创建下个阵容需要铜币数
};


#endif
