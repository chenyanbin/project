//
//  AuctionHomeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionHomeMsg.h"
AuctionHomeMsg:: AuctionHomeMsg(const char* _itemName,int lastSellId)
:itemName(_itemName)
,m_lastSellId(lastSellId)
{
    
}
AuctionHomeMsg::~ AuctionHomeMsg()
{
    
}
ByteStream * AuctionHomeMsg::encodingData()
{
   
    MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketSellPageReq);
    headBufferee->putUTF8(itemName);
    headBufferee->putInt(m_lastSellId);
    SetMessageLength();
}