//
//  BenefitDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/10.
//
//

#include "BenefitDataManager.h"
BenefitDataManager* BenefitDataManager::_instance = NULL;

BenefitDataManager::BenefitDataManager()
:benefitDayList(NULL)
{
    benefitDayList=new Vector<BenefitDayData*>();
    
}
BenefitDataManager::~BenefitDataManager()
{
    benefitDayList->clear();
    CC_SAFE_DELETE(benefitDayList);
    benefitDayList = NULL;
}
BenefitDataManager* BenefitDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new BenefitDataManager();
    }
    return _instance;
}
void BenefitDataManager::addData(BenefitDayData* data)
{
    benefitDayList->pushBack(data);
}
void BenefitDataManager::clearbenefitList()
{
    this->benefitDayList->clear();
}
void BenefitDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}