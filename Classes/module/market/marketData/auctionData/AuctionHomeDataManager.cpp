//
//  AuctionHomeDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionHomeDataManager.h"
AuctionHomeDataManager* AuctionHomeDataManager::_instance = NULL;

AuctionHomeDataManager::AuctionHomeDataManager()
:homeList(NULL)
,m_itemcount(0)
{
    homeList=new Vector<AuctionHomeData*>();
    
}
AuctionHomeDataManager::~AuctionHomeDataManager()
{
    homeList->clear();
    CC_SAFE_DELETE(homeList);
    homeList = NULL;
}
AuctionHomeDataManager* AuctionHomeDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new AuctionHomeDataManager();
    }
    return _instance;
}
void AuctionHomeDataManager::addData(AuctionHomeData* data)
{
    homeList->pushBack(data);
}
void AuctionHomeDataManager::clearAuctionHomeList()
{
    this->homeList->clear();
}
void AuctionHomeDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}

void AuctionHomeDataManager::setItemCountData(int itemcount)
{
    m_itemcount = NULL;
    m_itemcount = itemcount;
}
int AuctionHomeDataManager::getItemCountData()
{
    return m_itemcount;
}