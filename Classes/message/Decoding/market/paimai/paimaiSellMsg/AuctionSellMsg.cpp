//
//  AuctionSellMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionSellMsg.h"
AuctionSellMsg:: AuctionSellMsg(int lastMarketGoodsId)
:m_lastMarketGoodsId(lastMarketGoodsId)
{
    
}
AuctionSellMsg::~ AuctionSellMsg()
{
    
}
ByteStream * AuctionSellMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketToSellPageReq);

    headBufferee->putInt(m_lastMarketGoodsId);
    SetMessageLength();
}