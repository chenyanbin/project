//
//  MoneyDrawingDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/1.
//
//

#include "MoneyDrawingDataManager.h"
MoneyDrawingDataManager* MoneyDrawingDataManager::_instance = NULL;

MoneyDrawingDataManager::MoneyDrawingDataManager()
:giftList(NULL)

{
    giftList=new Vector<MoneyDrawingData*>();
    
}
MoneyDrawingDataManager::~ MoneyDrawingDataManager()
{
    giftList->clear();
    CC_SAFE_DELETE(giftList);
    giftList = NULL;
}
MoneyDrawingDataManager* MoneyDrawingDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new MoneyDrawingDataManager();
    }
    return _instance;
}
void MoneyDrawingDataManager::addData(MoneyDrawingData* data)
{
    giftList->pushBack(data);
}
void MoneyDrawingDataManager::cleargiftList()
{
    this->giftList->clear();
}
void MoneyDrawingDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
