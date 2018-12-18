//
//  BenefitData.h
//  FightPass
//
//  Created by chenyanbin on 15/12/10.
//
//

#ifndef BenefitData_h
#define BenefitData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class BenefitData:public Ref
{
public:
    BenefitData()
    :itemType(0)
    ,itemId(1)
    ,itemQuality(0)
    ,itemCount(0)
    ,itemName("")
    {
        
    }
    ~BenefitData()
    {
        
    }
    int itemType;//
    int itemId ;//
    int itemQuality;//
    int itemCount;//
    string itemName;//
};

#endif /* BenefitData_h */
