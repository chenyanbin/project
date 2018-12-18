//
//  AuctionSellDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
// 去出售

#ifndef __FightPass__AuctionSellDataManager__
#define __FightPass__AuctionSellDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "AuctionSellData.h"
class AuctionSellDataManager
{
public:
    AuctionSellDataManager();
    ~ AuctionSellDataManager();
    static void destroyInstance();
    static AuctionSellDataManager* getInstance();
    void addData(AuctionSellData* data);
    Vector<AuctionSellData*>* sellList;
    void clearshopList();
    
    void setItemCountData(int itemcount);
    int getItemCountData();
    
private:
    int m_itemcount;
    static AuctionSellDataManager* _instance;
};


#endif /* defined(__FightPass__AuctionSellDataManager__) */
