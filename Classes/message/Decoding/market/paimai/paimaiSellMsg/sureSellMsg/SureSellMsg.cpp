//
//  SureSellMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "SureSellMsg.h"
SureSellMsg:: SureSellMsg(int itemType, int itemId, int sellCount,int price)
:m_itemType(itemType)
,m_itemId(itemId)
,m_sellCount(sellCount)
,m_price(price)
{
    
}
SureSellMsg::~ SureSellMsg()
{
    
}
ByteStream * SureSellMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketSellReq);
    headBufferee->put(m_itemType);
    headBufferee->putInt(m_itemId);
    headBufferee->putInt(m_sellCount);
    headBufferee->putInt(m_price);

    SetMessageLength();
}