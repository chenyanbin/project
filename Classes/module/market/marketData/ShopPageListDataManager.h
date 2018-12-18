//
//  ShopPageListDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/8.
//
//

#ifndef __FightPass__ShopPageListDataManager__
#define __FightPass__ShopPageListDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "ShopPageListData.h"
class ShopPageListDataManager
{
public:
    ShopPageListDataManager();
    ~ShopPageListDataManager();
    static void destroyInstance();
    static ShopPageListDataManager* getInstance();
    void addData(ShopPageListData* data);
    Vector<ShopPageListData*>* shopList;
    void clearshopList();
    
private:
   
    static ShopPageListDataManager* _instance;
};


#endif /* defined(__FightPass__ShopPageListDataManager__) */
