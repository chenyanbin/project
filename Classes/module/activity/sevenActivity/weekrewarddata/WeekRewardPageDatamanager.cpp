//
//  WeekRewardPageDatamanager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#include "WeekRewardPageDatamanager.h"
WeekRewardPageDatamanager* WeekRewardPageDatamanager::_instance = NULL;

WeekRewardPageDatamanager::WeekRewardPageDatamanager()
:rewardlList(NULL)
,desclList(NULL)
{
    rewardlList=new Vector<WeekRewardData*>();
    desclList = new Vector<WeekDescData*>();
    
}
WeekRewardPageDatamanager:: ~ WeekRewardPageDatamanager()
{
    rewardlList->clear();
    CC_SAFE_DELETE(rewardlList);
    rewardlList = NULL;
    
    desclList->clear();
    CC_SAFE_DELETE(desclList);
    desclList = NULL;
}
WeekRewardPageDatamanager* WeekRewardPageDatamanager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new WeekRewardPageDatamanager();
    }
    return _instance;
}
void WeekRewardPageDatamanager::addData(WeekRewardData* data)
{
    rewardlList->pushBack(data);
}
void WeekRewardPageDatamanager::clearMailList()
{
    this->rewardlList->clear();
    this->desclList->clear();
}
void WeekRewardPageDatamanager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void WeekRewardPageDatamanager::adddescData(WeekDescData* data)
{
    desclList->pushBack(data);
}