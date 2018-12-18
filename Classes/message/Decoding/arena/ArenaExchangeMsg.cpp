//
//  ArenaExchangeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/21.
//
//

#include "ArenaExchangeMsg.hpp"
ArenaExchangeMsg::ArenaExchangeMsg(int _refresh)
:m_refresh(_refresh)
{
    
}
ArenaExchangeMsg::~ ArenaExchangeMsg()
{
    
}
ByteStream *ArenaExchangeMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaGloryShopReq);
    headBufferee->put(m_refresh);
    SetMessageLength();
}