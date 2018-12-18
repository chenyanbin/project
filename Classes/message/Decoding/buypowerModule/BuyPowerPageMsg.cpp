//
//  BuyPowerPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
//

#include "BuyPowerPageMsg.hpp"
BuyPowerPageMsg::BuyPowerPageMsg()
{
    
}
BuyPowerPageMsg::~ BuyPowerPageMsg()
{
    
}
ByteStream *BuyPowerPageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_BuyPowerPageReq);
    SetMessageLength();
}