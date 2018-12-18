//
//  RoleMessageDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/28.
//
//

#include "RoleMessageDataManager.hpp"
RoleMessageDataManager* RoleMessageDataManager::_instance = NULL;

RoleMessageDataManager::RoleMessageDataManager()
:roleList(NULL)
{
    roleList=new Vector<RoleMessageData*>();
    
}
RoleMessageDataManager::~ RoleMessageDataManager()
{
    roleList->clear();
    CC_SAFE_DELETE(roleList);
    roleList = NULL;
}
RoleMessageDataManager* RoleMessageDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new RoleMessageDataManager();
    }
    return _instance;
}
void RoleMessageDataManager::addData(RoleMessageData* data)
{
    roleList->pushBack(data);
}
void RoleMessageDataManager::clearMailList()
{
    this->roleList->clear();
}
void RoleMessageDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}