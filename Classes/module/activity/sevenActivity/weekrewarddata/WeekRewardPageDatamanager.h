//
//  WeekRewardPageDatamanager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#ifndef __FightPass__WeekRewardPageDatamanager__
#define __FightPass__WeekRewardPageDatamanager__

#include "cocos2d.h"
USING_NS_CC;
#include "WeekRewardData.h"
class WeekRewardPageDatamanager
{
public:
    WeekRewardPageDatamanager();
    
    ~ WeekRewardPageDatamanager();
    
    static void destroyInstance();
    
    static WeekRewardPageDatamanager* getInstance();
    
    void addData(WeekRewardData* data);
    
    Vector<WeekRewardData*>* rewardlList;
    
    void clearMailList();
    
    
    
    
    void adddescData(WeekDescData* data);
    Vector<WeekDescData*>* desclList;

    
    
private:
    static WeekRewardPageDatamanager* _instance;
};


#endif /* defined(__FightPass__WeekRewardPageDatamanager__) */
