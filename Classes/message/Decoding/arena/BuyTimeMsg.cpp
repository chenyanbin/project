//
//  BuyTimeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//

#include "BuyTimeMsg.hpp"
BuyTimeMsg::BuyTimeMsg(int status)
:m_status(status)
{
    
}
BuyTimeMsg::~BuyTimeMsg()
{
    
}
ByteStream *BuyTimeMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaBuyReq);
    headBufferee->put(m_status);
    SetMessageLength();
}