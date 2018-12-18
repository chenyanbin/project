//
//  VipGiftManager.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#ifndef __FightPass__VipGiftManager__
#define __FightPass__VipGiftManager__

#include "cocos2d.h"
USING_NS_CC;
#include "VipGiltData.h"
class VipGiftManager
{
public:
    VipGiftManager();
    
    ~VipGiftManager();
    
    static void destroyInstance();
    
    static VipGiftManager* getInstance();
    
    void addData(VipGiltData* data);
    
    Vector<VipGiltData*>* giftList;
    
    void cleargiltList();
    
private:
    static VipGiftManager* _instance;
};


#endif /* defined(__FightPass__VipGiftManager__) */
