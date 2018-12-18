//
//  karmaData.h
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//

#ifndef __FightPass__karmaData__
#define __FightPass__karmaData__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class KarmaData:public Ref
{
public:
    KarmaData()
    :karmaDictId(0)
    ,karmaName("")
    ,karmaDesc("")
    ,karmaOwn(false)
    {
        
    }
    virtual void release()
    {
        Ref::release();
    }
    ~KarmaData()
    {
        
    }
    int karmaDictId;//缘分ID
    string karmaName;//缘分名字
    bool karmaOwn;//0:未得到 1:已得到
    string karmaDesc;//缘分描述

};


#endif /* defined(__FightPass__karmaData__) */
