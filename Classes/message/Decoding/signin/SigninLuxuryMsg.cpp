//
//  SigninLuxuryMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/4.
//
//

#include "SigninLuxuryMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SigninLuxuryMsg::SigninLuxuryMsg()
{
    
}
SigninLuxuryMsg::~SigninLuxuryMsg()
{
    
}
ByteStream *SigninLuxuryMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_SIGNELITE_SignElitePageReq);
    SetMessageLength();
}