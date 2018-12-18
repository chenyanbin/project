//
//  AuctionShangjiaDataManger.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionShangjiaDataManger.h"
AuctionShangjiaDataManger* AuctionShangjiaDataManger::_instance = NULL;

AuctionShangjiaDataManger::AuctionShangjiaDataManger()
:shangjiaList(NULL)
,m_itemcount(0)
{
    shangjiaList=new Vector<AuctionShangjiaData*>();
    
}
AuctionShangjiaDataManger::~ AuctionShangjiaDataManger()
{
    shangjiaList->clear();
    CC_SAFE_DELETE(shangjiaList);
    shangjiaList = NULL;
}
AuctionShangjiaDataManger* AuctionShangjiaDataManger::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new AuctionShangjiaDataManger();
    }
    return _instance;
}
void AuctionShangjiaDataManger::addData(AuctionShangjiaData* data)
{
    shangjiaList->pushBack(data);
}
void AuctionShangjiaDataManger::clearshangjiaList()
{
    this->shangjiaList->clear();
}
void AuctionShangjiaDataManger::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
void AuctionShangjiaDataManger::setItemCountData(int itemcount)
{
    m_itemcount = NULL;
    m_itemcount = itemcount;
}
int AuctionShangjiaDataManger::getItemCountData()
{
    return m_itemcount;
}