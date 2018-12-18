

//
//  BenefitWeekDataManager_h
//  FightPass
//
//  Created by chenyanbin on 15/12/11.
//
//

#ifndef BenefitWeekDataManager_h
#define BenefitWeekDataManager_h

#include "cocos2d.h"
USING_NS_CC;
#include "BenefitWeekData.h"
class BenefitWeekDataManager
{
public:
    BenefitWeekDataManager();
    
    ~BenefitWeekDataManager();
    
    static void destroyInstance();
    
    static BenefitWeekDataManager* getInstance();
    
    void addData(BenefitWeekData* data);
    
    Vector<BenefitWeekData*>* benefitweekList;
    
    void clearweekList();
    
private:
    static BenefitWeekDataManager* _instance;
};

#endif /* BenefitWeekDataManager_h */