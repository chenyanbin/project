//
//  AuctionSellDataManager.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionSellDataManager.h"
AuctionSellDataManager* AuctionSellDataManager::_instance = NULL;

AuctionSellDataManager::AuctionSellDataManager()
:sellList(NULL)
,m_itemcount(0)
{
    sellList=new Vector<AuctionSellData*>();
    
}
AuctionSellDataManager::~ AuctionSellDataManager()
{
    sellList->clear();
    CC_SAFE_DELETE(sellList);
    sellList = NULL;
}
AuctionSellDataManager* AuctionSellDataManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new AuctionSellDataManager();
    }
    return _instance;
}
void AuctionSellDataManager::addData(AuctionSellData* data)
{
    sellList->pushBack(data);
}
void AuctionSellDataManager::clearshopList()
{
    this->sellList->clear();
}
void AuctionSellDataManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void AuctionSellDataManager::setItemCountData(int itemcount)
{
    m_itemcount = NULL;
    m_itemcount = itemcount;
}
int AuctionSellDataManager::getItemCountData()
{
    return m_itemcount;
}