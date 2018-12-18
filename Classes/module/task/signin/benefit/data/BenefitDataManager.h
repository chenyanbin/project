//
//  BenefitDataManager_h
//  FightPass
//
//  Created by chenyanbin on 15/12/10.
//
//

#ifndef BenefitDataManager_h
#define BenefitDataManager_h

#include "cocos2d.h"
USING_NS_CC;
#include "BenefitDayData.h"
class BenefitDataManager
{
public:
    BenefitDataManager();
    
    ~BenefitDataManager();
    
    static void destroyInstance();
    
    static BenefitDataManager* getInstance();
    
    void addData(BenefitDayData* data);
    
    Vector<BenefitDayData*>* benefitDayList;
    
    void clearbenefitList();
    
private:
    static BenefitDataManager* _instance;
};

#endif /* BenefitDataManager_h */