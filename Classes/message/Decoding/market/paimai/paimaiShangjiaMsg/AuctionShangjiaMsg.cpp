//
//  AuctionShangjiaMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionShangjiaMsg.h"
AuctionShangjiaMsg:: AuctionShangjiaMsg(int lastMarketGoodsId)
:m_lastMarketGoodsId(lastMarketGoodsId)
{
    
}
AuctionShangjiaMsg::~ AuctionShangjiaMsg()
{
    
}
ByteStream * AuctionShangjiaMsg::encodingData()
{

     MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketMySellPageReq);
    headBufferee->putInt(m_lastMarketGoodsId);
    SetMessageLength();
}