//
//  ArenaDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/14.
//
//

#ifndef ArenaDataManager_hpp
#define ArenaDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "ArenaListData.h"
class ArenaDataManager
{
public:
    ArenaDataManager();
    
    ~ ArenaDataManager();
    
    static void destroyInstance();
    
    static ArenaDataManager* getInstance();
    
    void addData(ArenaListData* data);
    
    Vector<ArenaListData*>* arenaList;
    
    void clearMailList();
    
private:
    static ArenaDataManager* _instance;
};

#endif /* ArenaDataManager_hpp */
