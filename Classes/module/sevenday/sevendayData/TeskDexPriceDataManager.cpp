//
//  TeskDexPriceDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#include "TeskDexPriceDataManager.hpp"
TeskDexPriceDataManager* TeskDexPriceDataManager::_instance = NULL;

TeskDexPriceDataManager::TeskDexPriceDataManager()
:lineupList(NULL)
{
    lineupList=new Vector<TeskDesData*>();
    
}
TeskDexPriceDataManager::~ TeskDexPriceDataManager()
{
    lineupList->clear();
    CC_SAFE_DELETE(lineupList);
    lineupList = NULL;
}
TeskDexPriceDataManager* TeskDexPriceDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new TeskDexPriceDataManager();
    }
    return _instance;
}
void TeskDexPriceDataManager::addData(TeskDesData* data)
{
    lineupList->pushBack(data);
}
void TeskDexPriceDataManager::clearMailList()
{
    this->lineupList->clear();
}
void TeskDexPriceDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}