//
//  MailAllGiftDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailAllGiftDataManager.h"
MailAllGiftDataManager* MailAllGiftDataManager::_instance = NULL;

MailAllGiftDataManager::MailAllGiftDataManager()
:giftList(NULL)
,m_size(0)
{
    giftList=new Vector<MailAllGiftData*>();
    
}
MailAllGiftDataManager::~MailAllGiftDataManager()
{
    giftList->clear();
    CC_SAFE_DELETE(giftList);
    giftList = NULL;
}
MailAllGiftDataManager* MailAllGiftDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new MailAllGiftDataManager();
    }
    return _instance;
}
void MailAllGiftDataManager::addData(MailAllGiftData* data)
{
    giftList->pushBack(data);
}
void MailAllGiftDataManager::removeData(int _equipId)
{
    int index = this->getIndexByCardID(_equipId);
    if(index >= 0)
    {
        giftList->erase(index);
    }
}
int MailAllGiftDataManager::getIndexByCardID(int _equipId)
{
    int len = (int)giftList->size();
    for(int i = 0; i < len; i++)
    {
        if(giftList->at(i)->heroId == _equipId)
        {
            return i;
        }
    }
    return -1;
}
void MailAllGiftDataManager::setGiftSizeData(int data)
{
    this->m_size=NULL;
    this->m_size = data;
}
int MailAllGiftDataManager::getGiftSize()
{
    return this->m_size;
}
void MailAllGiftDataManager::clearfindList()
{
    this->giftList->clear();
}
void MailAllGiftDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
