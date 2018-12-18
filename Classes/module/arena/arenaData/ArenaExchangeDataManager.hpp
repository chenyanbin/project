//
//  ArenaExchangeDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//

#ifndef ArenaExchangeDataManager_hpp
#define ArenaExchangeDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "ArenaExchangeData.h"
class ArenaExchangeDataManager
{
public:
    ArenaExchangeDataManager();
    
    ~ ArenaExchangeDataManager();
    
    static void destroyInstance();
    
    static ArenaExchangeDataManager* getInstance();
    
    void addData(ArenaExchangeData* data);
    
    Vector<ArenaExchangeData*>* exchangeList;
    
    void clearMailList();
    
private:
    static ArenaExchangeDataManager* _instance;
};


#endif /* ArenaExchangeDataManager_hpp */
