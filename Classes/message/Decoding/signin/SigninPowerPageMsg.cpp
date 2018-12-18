//
//  SigninPowerPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//

#include "SigninPowerPageMsg.hpp"
SigninPowerPageMsg::SigninPowerPageMsg()
{
    
}
SigninPowerPageMsg::~ SigninPowerPageMsg()
{
    
}
ByteStream *SigninPowerPageMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_ReceivePowerPageReq);
    SetMessageLength();
}