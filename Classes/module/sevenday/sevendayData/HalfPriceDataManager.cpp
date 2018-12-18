//
//  HalfPriceDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#include "HalfPriceDataManager.hpp"
HalfPriceDataManager* HalfPriceDataManager::_instance = NULL;

HalfPriceDataManager::HalfPriceDataManager()
:halfpriceList(NULL)
{
    halfpriceList=new Vector<HalfPriceData*>();
    
}
HalfPriceDataManager:: ~ HalfPriceDataManager()
{
    halfpriceList->clear();
    CC_SAFE_DELETE(halfpriceList);
    halfpriceList = NULL;
}
HalfPriceDataManager* HalfPriceDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new HalfPriceDataManager();
    }
    return _instance;
}
void HalfPriceDataManager::addData(HalfPriceData* data)
{
    halfpriceList->pushBack(data);
}
void HalfPriceDataManager::clearhalfpriceList()
{
    this->halfpriceList->clear();
}
void HalfPriceDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}