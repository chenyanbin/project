//
//  ArenaLineupDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//

#include "ArenaLineupDataManager.hpp"
ArenaLineupDataManager* ArenaLineupDataManager::_instance = NULL;

ArenaLineupDataManager::ArenaLineupDataManager()
:lineupList(NULL)
{
    lineupList=new Vector<ArenaLineupData*>();
    
}
ArenaLineupDataManager::~ ArenaLineupDataManager()
{
    lineupList->clear();
    CC_SAFE_DELETE(lineupList);
    lineupList = NULL;
}
ArenaLineupDataManager* ArenaLineupDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ArenaLineupDataManager();
    }
    return _instance;
}
void ArenaLineupDataManager::addData(ArenaLineupData* data)
{
    lineupList->pushBack(data);
}
void ArenaLineupDataManager::clearMailList()
{
    this->lineupList->clear();
}
void ArenaLineupDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}