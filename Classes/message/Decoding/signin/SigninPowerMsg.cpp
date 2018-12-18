//
//  SigninPowerMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/23.
//
//

#include "SigninPowerMsg.hpp"
SigninPowerMsg::SigninPowerMsg()
{
    
}
SigninPowerMsg::~ SigninPowerMsg()
{
    
}
ByteStream *SigninPowerMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_ReceivePowerReq);
    SetMessageLength();
}