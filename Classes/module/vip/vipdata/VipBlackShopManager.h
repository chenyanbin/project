//
//  VipBlackShopManager.h
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#ifndef __FightPass__VipBlackShopManager__
#define __FightPass__VipBlackShopManager__

#include "cocos2d.h"
USING_NS_CC;
#include "VipBlackshopData.h"
class VipBlackShopManager
{
public:
    VipBlackShopManager();
   
    ~VipBlackShopManager();
    
    static void destroyInstance();
   
    static VipBlackShopManager* getInstance();
   
    void addData(VipBlackshopData* data);
   
    Vector<VipBlackshopData*>* bsList;
   
    void clearblackshopList();
    
private:
    static VipBlackShopManager* _instance;
};


#endif /* defined(__FightPass__VipBlackShopManager__) */
