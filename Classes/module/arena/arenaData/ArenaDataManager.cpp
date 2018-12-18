//
//  ArenaDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/14.
//
//

#include "ArenaDataManager.hpp"
ArenaDataManager* ArenaDataManager::_instance = NULL;

ArenaDataManager::ArenaDataManager()
:arenaList(NULL)
{
    arenaList=new Vector<ArenaListData*>();
    
}
ArenaDataManager::~ ArenaDataManager()
{
    arenaList->clear();
    CC_SAFE_DELETE(arenaList);
    arenaList = NULL;
}
ArenaDataManager* ArenaDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ArenaDataManager();
    }
    return _instance;
}
void ArenaDataManager::addData(ArenaListData* data)
{
    arenaList->pushBack(data);
}
void ArenaDataManager::clearMailList()
{
    this->arenaList->clear();
}
void ArenaDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}