//
//  BaseData.h
//  FightPass
//
//  Created by 超 顾 on 15/12/7.
//
//

#ifndef __FightPass__BaseTypeData__
#define __FightPass__BaseTypeData__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class BaseTypeData:public Ref
{
public:
    BaseTypeData()
    :dataId(0)
    ,dataName("")
    ,dataType(0)
    ,dataQuality(0)
    ,dataCount(0)
    ,heroPrestige(0)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~BaseTypeData()
    {
        
    }
    int dataId;
    string dataName;
    int dataType;
    int dataQuality;
    int dataCount;
    int heroPrestige;//声望
};
#endif /* defined(__FightPass__BaseData__) */
