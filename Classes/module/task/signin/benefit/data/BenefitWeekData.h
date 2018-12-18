//
//  BenefitWeekData.h
//  FightPass
//
//  Created by chenyanbin on 15/12/11.
//
//

#ifndef BenefitWeekData_h
#define BenefitWeekData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class BenefitWeekData:public Ref
{
public:
    BenefitWeekData()
    :status(1)
    ,itemType(0)
    ,itemId(1)
    ,itemCount(0)
    ,itemQuality(0)
    ,itemName("")
    {
        
    }
    ~BenefitWeekData()
    {
        
    }
    int status;
    int itemType;//
    int itemId ;//
    int itemCount;//
    int itemQuality;//
    string itemName;//
    int privceOri;//原价
    int price;//现价
};


#endif /* BenefitWeekData_h */
