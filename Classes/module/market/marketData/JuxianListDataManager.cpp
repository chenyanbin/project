//
//  JuxianListDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "JuxianListDataManager.h"
JuxianListDataManager* JuxianListDataManager::_instance = NULL;

JuxianListDataManager::JuxianListDataManager()
:juxianList(NULL)
{
    juxianList=new Vector<JuxianListData*>();
    
}
JuxianListDataManager::~JuxianListDataManager()
{
    juxianList->clear();
    CC_SAFE_DELETE(juxianList);
    juxianList = NULL;
}
JuxianListDataManager* JuxianListDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new JuxianListDataManager();
    }
    return _instance;
}
void JuxianListDataManager::addData(JuxianListData* data)
{
    juxianList->pushBack(data);
}
void JuxianListDataManager::clearjuxianList()
{
    this->juxianList->clear();
}
void JuxianListDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}