//
//  AuctionShangjiaDataManger.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
// 上架中

#ifndef __FightPass__AuctionShangjiaDataManger__
#define __FightPass__AuctionShangjiaDataManger__

#include "cocos2d.h"
USING_NS_CC;
#include "AuctionShangjiaData.h"
class AuctionShangjiaDataManger
{
public:
    AuctionShangjiaDataManger();
    ~ AuctionShangjiaDataManger();
    static void destroyInstance();
    static AuctionShangjiaDataManger* getInstance();
    void addData(AuctionShangjiaData* data);
    Vector<AuctionShangjiaData*>* shangjiaList;
    void clearshangjiaList();
    
    void setItemCountData(int itemcount);
    int getItemCountData();
    
private:
    int m_itemcount;
    static AuctionShangjiaDataManger* _instance;
};


#endif /* defined(__FightPass__AuctionShangjiaDataManger__) */
