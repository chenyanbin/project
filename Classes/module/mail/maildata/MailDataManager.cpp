//
//  MailDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/11.
//
//

#include "MailDataManager.h"

MailDataManager* MailDataManager::_instance = NULL;

MailDataManager::MailDataManager()
:mailList(NULL)
{
    mailList=new Vector<MailData*>();
    
}
MailDataManager::~MailDataManager()
{
    mailList->clear();
    CC_SAFE_DELETE(mailList);
    mailList = NULL;
}
MailDataManager* MailDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new MailDataManager();
    }
    return _instance;
}
void MailDataManager::addData(MailData* data)
{
    mailList->pushBack(data);
}
void MailDataManager::clearMailList()
{
    this->mailList->clear();
}
void MailDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}