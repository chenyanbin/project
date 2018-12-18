//
//  WeekHalfGiftDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef __FightPass__WeekHalfGiftDataManager__
#define __FightPass__WeekHalfGiftDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "WeekHalfGiftData.h"
class WeekHalfGiftDataManager
{
public:
    WeekHalfGiftDataManager();
    
    ~ WeekHalfGiftDataManager();
    
    static void destroyInstance();
    
    static WeekHalfGiftDataManager* getInstance();
    
    void addData(WeekHalfGiftData* data);
    
    Vector<WeekHalfGiftData*>* halfpriceList;
    
    void clearhalfpriceList();
    
private:
    static WeekHalfGiftDataManager* _instance;
};


#endif /* defined(__FightPass__WeekHalfGiftDataManager__) */
