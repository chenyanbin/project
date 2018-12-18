//
//  ArenaRecoredDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//

#include "ArenaRecoredDataManager.hpp"
ArenaRecoredDataManager* ArenaRecoredDataManager::_instance = NULL;

ArenaRecoredDataManager::ArenaRecoredDataManager()
:recoredList(NULL)
{
    recoredList=new Vector<ArenaRecoredData*>();
    
}
ArenaRecoredDataManager::~ ArenaRecoredDataManager()
{
    recoredList->clear();
    CC_SAFE_DELETE(recoredList);
    recoredList = NULL;
}
ArenaRecoredDataManager* ArenaRecoredDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ArenaRecoredDataManager();
    }
    return _instance;
}
void ArenaRecoredDataManager::addData(ArenaRecoredData* data)
{
    recoredList->pushBack(data);
}
void ArenaRecoredDataManager::clearMailList()
{
    this->recoredList->clear();
}
void ArenaRecoredDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}