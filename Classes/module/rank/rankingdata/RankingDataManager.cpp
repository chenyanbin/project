//
//  RankingDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#include "RankingDataManager.hpp"

RankingDataManager* RankingDataManager::_instance = NULL;

RankingDataManager::RankingDataManager()
:rankingList(NULL)
{
    rankingList = new Vector<RankingData*>();
}
RankingDataManager::~RankingDataManager()
{
    rankingList->clear();
    CC_SAFE_DELETE(rankingList);
    rankingList = NULL;
}
void RankingDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
RankingDataManager* RankingDataManager::getInstance()
{
    if (_instance == NULL) {
        _instance = new RankingDataManager();
    }
    return _instance;
}
void RankingDataManager::add(RankingData* data)
{
    this->rankingList->pushBack(data);
}
void RankingDataManager::clearRankingList()
{
    this->rankingList->clear();
}