//
//  VipgiftBuyManager.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#ifndef __FightPass__VipgiftBuyManager__
#define __FightPass__VipgiftBuyManager__

#include "cocos2d.h"
USING_NS_CC;
#include "VipGiftBuyData.h"
class VipgiftBuyManager
{
public:
    VipgiftBuyManager();
    
    ~VipgiftBuyManager();
    
    static void destroyInstance();
    
    static VipgiftBuyManager* getInstance();
    
    void addData(VipGiftBuyData* data);
    
    Vector<VipGiftBuyData*>* buylist;
    
    void clearbuyList();
    
private:
    static VipgiftBuyManager* _instance;
};


#endif /* defined(__FightPass__VipgiftBuyManager__) */
