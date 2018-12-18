//
//  ArenaRecoredDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//

#ifndef ArenaRecoredDataManager_hpp
#define ArenaRecoredDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "ArenaRecoredData.h"
class ArenaRecoredDataManager
{
public:
    ArenaRecoredDataManager();
    
    ~ ArenaRecoredDataManager();
    
    static void destroyInstance();
    
    static ArenaRecoredDataManager* getInstance();
    
    void addData(ArenaRecoredData* data);
    
    Vector<ArenaRecoredData*>* recoredList;
    
    void clearMailList();
    
private:
    static ArenaRecoredDataManager* _instance;
};
#endif /* ArenaRecoredDataManager_hpp */
