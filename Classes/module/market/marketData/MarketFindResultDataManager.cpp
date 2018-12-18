//
//  MarketFindResultDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/6.
//
//

#include "MarketFindResultDataManager.h"
MarketFindResultDataManager* MarketFindResultDataManager::_instance = NULL;

MarketFindResultDataManager::MarketFindResultDataManager()
:dumpList(NULL)
,m_resultType(0)
{
    dumpList=new Vector<MarketFindResultData*>();
    
}
MarketFindResultDataManager::~MarketFindResultDataManager()
{
    dumpList->clear();
    CC_SAFE_DELETE(dumpList);
    dumpList = NULL;
}
MarketFindResultDataManager* MarketFindResultDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new MarketFindResultDataManager();
    }
    return _instance;
}
void MarketFindResultDataManager::addData(MarketFindResultData* data)
{
    dumpList->pushBack(data);
}
void MarketFindResultDataManager::setfindTypeData(int data)
{
    m_resultType = NULL;
    m_resultType = data;
}
int MarketFindResultDataManager::getFindTypeData()
{
    return m_resultType;
}
void MarketFindResultDataManager::clearDumpList()
{
    this->dumpList->clear();
}
void MarketFindResultDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}




