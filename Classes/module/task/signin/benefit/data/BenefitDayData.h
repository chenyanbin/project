//
//  BenefitDayData.h
//  FightPass
//
//  Created by chenyanbin on 15/12/10.
//
//

#ifndef BenefitDayData_h
#define BenefitDayData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "BenefitData.h"
class BenefitDayData:public Ref
{
public:
    BenefitDayData()
    :vipStatue(0)
    ,ItemSize(0)
    {
        benefitList = new Vector<BenefitData*>();
    }
    ~BenefitDayData()
    {
        benefitList->clear();
        CC_SAFE_DELETE(benefitList);
        benefitList = NULL;
    }
    int vipStatue;//
    int ItemSize ;//
    Vector<BenefitData*>* benefitList;
};


#endif /* BenefitDayData_h */
