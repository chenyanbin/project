//
//  TeskDexPriceDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#ifndef TeskDexPriceDataManager_hpp
#define TeskDexPriceDataManager_hpp


#include "cocos2d.h"
USING_NS_CC;
#include "TaskData.h"
class TeskDexPriceDataManager
{
public:
    TeskDexPriceDataManager();
    
    ~ TeskDexPriceDataManager();
    
    static void destroyInstance();
    
    static TeskDexPriceDataManager* getInstance();
    
    void addData(TeskDesData* data);
    
    Vector<TeskDesData*>* lineupList;
    
    void clearMailList();
    
private:
    static TeskDexPriceDataManager* _instance;
};


#endif /* TeskDexPriceDataManager_hpp */
