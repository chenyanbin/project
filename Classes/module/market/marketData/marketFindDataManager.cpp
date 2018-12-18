//
//  marketFindDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "marketFindDataManager.h"
marketFindDataManager* marketFindDataManager::_instance = NULL;

marketFindDataManager::marketFindDataManager()
:findList(NULL)
,m_findToken(0)
{
    findList=new Vector<MarketFindData*>();
    
}
marketFindDataManager::~marketFindDataManager()
{
    findList->clear();
    CC_SAFE_DELETE(findList);
    findList = NULL;
}
marketFindDataManager* marketFindDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new marketFindDataManager();
    }
    return _instance;
}
void marketFindDataManager::addData(MarketFindData* data)
{
    findList->pushBack(data);
}
void marketFindDataManager::removeData(int _equipId)
{
    int index = this->getIndexByCardID(_equipId);
    if(index >= 0)
    {
        findList->erase(index);
    }
}
int marketFindDataManager::getIndexByCardID(int _equipId)
{
    int len = (int)findList->size();
    for(int i = 0; i < len; i++)
    {
        if(findList->at(i)->heroId == _equipId)
        {
            return i;
        }
    }
    return -1;
}
void marketFindDataManager::setfindTokenData(int data)
{
    this->m_findToken=NULL;
    this->m_findToken = data;
}
int marketFindDataManager::getFindTokenData()
{
    return this->m_findToken;
}
void marketFindDataManager::clearfindList()
{
    this->findList->clear();
}
void marketFindDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
