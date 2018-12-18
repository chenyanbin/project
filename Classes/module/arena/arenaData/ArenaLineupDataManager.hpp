//
//  ArenaLineupDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//

#ifndef ArenaLineupDataManager_hpp
#define ArenaLineupDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "ArenaLineupData.h"
class ArenaLineupDataManager
{
public:
    ArenaLineupDataManager();
    
    ~ ArenaLineupDataManager();
    
    static void destroyInstance();
    
    static ArenaLineupDataManager* getInstance();
    
    void addData(ArenaLineupData* data);
    
    Vector<ArenaLineupData*>* lineupList;
    
    void clearMailList();
    
private:
    static ArenaLineupDataManager* _instance;
};


#endif /* ArenaLineupDataManager_hpp */
