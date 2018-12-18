//
//  MailCellDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailCellDataManager.h"
MailCellDataManager* MailCellDataManager::_instance = NULL;

MailCellDataManager::MailCellDataManager()
:mailCellList(NULL)
{
    mailCellList=new Vector<MailCellData*>();
    
}
MailCellDataManager::~MailCellDataManager()
{
    mailCellList->clear();
    CC_SAFE_DELETE(mailCellList);
    mailCellList = NULL;
}
MailCellDataManager* MailCellDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new MailCellDataManager();
    }
    return _instance;
}
void MailCellDataManager::addData(MailCellData* data)
{
    mailCellList->pushBack(data);
}
void MailCellDataManager::clearMailCellList()
{
    this->mailCellList->clear();
}
void MailCellDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}