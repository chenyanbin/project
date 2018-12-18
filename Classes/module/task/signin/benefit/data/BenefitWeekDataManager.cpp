//
//  BenefitWeekDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/11.
//
//

#include "BenefitWeekDataManager.h"
BenefitWeekDataManager* BenefitWeekDataManager::_instance = NULL;

BenefitWeekDataManager::BenefitWeekDataManager()
:benefitweekList(NULL)
{
    benefitweekList=new Vector<BenefitWeekData*>();
    
}
BenefitWeekDataManager::~BenefitWeekDataManager()
{
    benefitweekList->clear();
    CC_SAFE_DELETE(benefitweekList);
    benefitweekList = NULL;
}
BenefitWeekDataManager* BenefitWeekDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new BenefitWeekDataManager();
    }
    return _instance;
}
void BenefitWeekDataManager::addData(BenefitWeekData* data)
{
    benefitweekList->pushBack(data);
}
void BenefitWeekDataManager::clearweekList()
{
    this->benefitweekList->clear();
}
void BenefitWeekDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}