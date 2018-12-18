//
//  ArenaExchangeDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//

#include "ArenaExchangeDataManager.hpp"

ArenaExchangeDataManager* ArenaExchangeDataManager::_instance = NULL;

ArenaExchangeDataManager::ArenaExchangeDataManager()
:exchangeList(NULL)
{
    exchangeList=new Vector<ArenaExchangeData*>();
    
}
ArenaExchangeDataManager::~ ArenaExchangeDataManager()
{
    exchangeList->clear();
    CC_SAFE_DELETE(exchangeList);
    exchangeList = NULL;
}
ArenaExchangeDataManager* ArenaExchangeDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ArenaExchangeDataManager();
    }
    return _instance;
}
void ArenaExchangeDataManager::addData(ArenaExchangeData* data)
{
    exchangeList->pushBack(data);
}
void ArenaExchangeDataManager::clearMailList()
{
    this->exchangeList->clear();
}
void ArenaExchangeDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}