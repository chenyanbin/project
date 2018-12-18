//
//  ExchangeOneMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//

#include "ExchangeOneMsg.hpp"
ExchangeOneMsg::ExchangeOneMsg(int itenId)
:m_itemid(itenId)
{
    
}
ExchangeOneMsg::~ ExchangeOneMsg()
{
    
}
ByteStream *ExchangeOneMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaExchangeReq);
    headBufferee->putInt(m_itemid);
    SetMessageLength();
}