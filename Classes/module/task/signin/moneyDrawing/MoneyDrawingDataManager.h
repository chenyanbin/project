//
//  MoneyDrawingDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/12/1.
//
//

#ifndef __FightPass__MoneyDrawingDataManager__
#define __FightPass__MoneyDrawingDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MoneyDrawingData.h"
class MoneyDrawingDataManager
{
public:
    MoneyDrawingDataManager();
    ~ MoneyDrawingDataManager();
    static void destroyInstance();
    static MoneyDrawingDataManager* getInstance();
    void addData(MoneyDrawingData* data);
    Vector<MoneyDrawingData*>* giftList;
    void cleargiftList();
    
private:
    static MoneyDrawingDataManager* _instance;
};


#endif /* defined(__FightPass__MoneyDrawingDataManager__) */
