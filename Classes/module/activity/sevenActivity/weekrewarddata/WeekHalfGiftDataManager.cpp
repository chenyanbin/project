//
//  WeekHalfGiftDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#include "WeekHalfGiftDataManager.h"
WeekHalfGiftDataManager* WeekHalfGiftDataManager::_instance = NULL;

WeekHalfGiftDataManager::WeekHalfGiftDataManager()
:halfpriceList(NULL)
{
    halfpriceList=new Vector<WeekHalfGiftData*>();
    
}
WeekHalfGiftDataManager:: ~ WeekHalfGiftDataManager()
{
    halfpriceList->clear();
    CC_SAFE_DELETE(halfpriceList);
    halfpriceList = NULL;
}
WeekHalfGiftDataManager* WeekHalfGiftDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new WeekHalfGiftDataManager();
    }
    return _instance;
}
void WeekHalfGiftDataManager::addData(WeekHalfGiftData* data)
{
    halfpriceList->pushBack(data);
}
void WeekHalfGiftDataManager::clearhalfpriceList()
{
    this->halfpriceList->clear();
}
void WeekHalfGiftDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}