//
//  AuctionHomeDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//  拍卖所

#ifndef __FightPass__AuctionHomeDataManager__
#define __FightPass__AuctionHomeDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "AuctionHomeData.h"
class AuctionHomeDataManager
{
public:
    AuctionHomeDataManager();
    ~ AuctionHomeDataManager();
    static void destroyInstance();
    static AuctionHomeDataManager* getInstance();
    void addData(AuctionHomeData* data);
    Vector<AuctionHomeData*>* homeList;
    void clearAuctionHomeList();
    
    void setItemCountData(int itemcount);
    int getItemCountData();
    
private:
    int m_itemcount;
    static AuctionHomeDataManager* _instance;
};


#endif /* defined(__FightPass__AuctionHomeDataManager__) */
