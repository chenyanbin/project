//
//  FirstRechargeDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#ifndef __FightPass__FirstRechargeDataManager__
#define __FightPass__FirstRechargeDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "FirstRechargeData.h"
class FirstRechargeDataManager
{
public:
    FirstRechargeDataManager();
    
    ~ FirstRechargeDataManager();
    
    static void destroyInstance();
    
    static FirstRechargeDataManager* getInstance();
    
    void addData(FirstRechargeData* data);
    
    Vector<FirstRechargeData*>* firstList;
    
    void clearFirstList();
    
private:
    static FirstRechargeDataManager* _instance;
};

#endif /* defined(__FightPass__FirstRechargeDataManager__) */
