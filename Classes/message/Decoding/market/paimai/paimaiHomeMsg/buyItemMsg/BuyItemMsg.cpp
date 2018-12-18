//
//  BuyItemMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "BuyItemMsg.h"
BuyItemMsg:: BuyItemMsg(int SellId)
:m_SellId(SellId)
{
    
}
BuyItemMsg::~ BuyItemMsg()
{
    
}
ByteStream * BuyItemMsg::encodingData()
{

    MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketBuyReq);
    headBufferee->putInt(m_SellId);
    SetMessageLength();
}