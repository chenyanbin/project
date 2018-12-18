//
//  BoonDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#include "BoonDataManager.hpp"
BoonDataManager* BoonDataManager::_instance = NULL;

BoonDataManager::BoonDataManager()
:rewardlList(NULL)
,desclList(NULL)
{
    rewardlList=new Vector<BoonData*>();
    desclList = new Vector<WeekDescData*>();
    
}
BoonDataManager:: ~ BoonDataManager()
{
    rewardlList->clear();
    CC_SAFE_DELETE(rewardlList);
    rewardlList = NULL;
    
    desclList->clear();
    CC_SAFE_DELETE(desclList);
    desclList = NULL;
}
BoonDataManager* BoonDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new BoonDataManager();
    }
    return _instance;
}
void BoonDataManager::addData(BoonData* data)
{
    rewardlList->pushBack(data);
}
void BoonDataManager::clearMailList()
{
    this->rewardlList->clear();
    this->desclList->clear();
}
void BoonDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void BoonDataManager::adddescData(WeekDescData* data)
{
    desclList->pushBack(data);
}