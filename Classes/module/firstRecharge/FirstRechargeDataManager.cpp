//
//  FirstRechargeDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#include "FirstRechargeDataManager.h"

FirstRechargeDataManager* FirstRechargeDataManager::_instance = NULL;

FirstRechargeDataManager::FirstRechargeDataManager()
:firstList(NULL)
{
    firstList=new Vector<FirstRechargeData*>();
    
}
FirstRechargeDataManager::~FirstRechargeDataManager()
{
    firstList->clear();
    CC_SAFE_DELETE(firstList);
    firstList = NULL;
}
FirstRechargeDataManager* FirstRechargeDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new FirstRechargeDataManager();
    }
    return _instance;
}
void FirstRechargeDataManager::addData(FirstRechargeData* data)
{
    firstList->pushBack(data);
}
void FirstRechargeDataManager::clearFirstList()
{
    this->firstList->clear();
}
void FirstRechargeDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}