//
//  LetterDataManager.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/19.
//
//

#include "LetterDataManager.h"
LetterDataManager* LetterDataManager::_instance = NULL;

LetterDataManager::LetterDataManager()
:letterList(NULL)
{
    letterList=new Vector<LetterData*>();
    
}
LetterDataManager::~LetterDataManager()
{
    letterList->clear();
    CC_SAFE_DELETE(letterList);
    letterList = NULL;
}
LetterDataManager* LetterDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new LetterDataManager();
    }
    return _instance;
}
void LetterDataManager::addData(LetterData* data)
{
    letterList->pushBack(data);
}
void LetterDataManager::removeData(int _heroId)
{
    int index = this->getIndexByCardID(_heroId);
    if(index >= 0)
    {
        letterList->erase(index);
    }
}
int LetterDataManager::getIndexByCardID(int _heroId)
{
    int len = (int)letterList->size();
    for(int i = 0; i < len; i++)
    {
        if(letterList->at(i)->bookId == _heroId)
        {
            return i;
        }
    }
    return -1;
}
LetterData* LetterDataManager::getCardDataByIndex(int index)
{
    if(index < 0 || index > this->letterList->size())
    {
        return NULL;
    }
    return this->letterList->at(index);
}
Vector<LetterData*>* LetterDataManager::getDataList()
{
    return this->letterList;
}
void LetterDataManager::clearCardList()
{
    this->letterList->clear();
}
