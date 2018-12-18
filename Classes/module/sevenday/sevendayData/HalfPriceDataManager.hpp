//
//  HalfPriceDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#ifndef HalfPriceDataManager_hpp
#define HalfPriceDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "HalfPriceData.h"
class HalfPriceDataManager
{
public:
    HalfPriceDataManager();
    
    ~ HalfPriceDataManager();
    
    static void destroyInstance();
    
    static HalfPriceDataManager* getInstance();
    
    void addData(HalfPriceData* data);
    
    Vector<HalfPriceData*>* halfpriceList;
    
    void clearhalfpriceList();
    
private:
    static HalfPriceDataManager* _instance;
};


#endif /* HalfPriceDataManager_hpp */
