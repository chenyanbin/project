//
//  SigninLuxuryGetMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/9.
//
//

#include "SigninLuxuryGetMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SigninLuxuryGetMsg::SigninLuxuryGetMsg()
{
    
}
SigninLuxuryGetMsg::~SigninLuxuryGetMsg()
{
    
}
ByteStream *SigninLuxuryGetMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_SIGNELITE_SignEliteSignReq);
    SetMessageLength();
}