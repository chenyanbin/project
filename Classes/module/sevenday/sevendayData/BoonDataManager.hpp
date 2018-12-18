//
//  BoonDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#ifndef BoonDataManager_hpp
#define BoonDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "BoonData.h"
class BoonDataManager
{
public:
    BoonDataManager();
    
    ~ BoonDataManager();
    
    static void destroyInstance();
    
    static BoonDataManager* getInstance();
    
    void addData(BoonData* data);
    
    Vector<BoonData*>* rewardlList;
    
    void clearMailList();
    
    void adddescData(WeekDescData* data);
    Vector<WeekDescData*>* desclList;
    
    
    
private:
    static BoonDataManager* _instance;
};

#endif /* BoonDataManager_hpp */
