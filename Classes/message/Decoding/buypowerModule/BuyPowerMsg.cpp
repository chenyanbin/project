//
//  BuyPowerMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
//

#include "BuyPowerMsg.hpp"
BuyPowerMsg::BuyPowerMsg()
{
    
}
BuyPowerMsg::~ BuyPowerMsg()
{
    
}
ByteStream *BuyPowerMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_BuyPowerReq);
    SetMessageLength();
}