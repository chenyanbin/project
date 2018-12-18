//
//  SigninDayMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/4.
//
//

#include "SigninDayMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SigninDayMsg::SigninDayMsg()
{
    
}
SigninDayMsg::~SigninDayMsg()
{
    
}
ByteStream *SigninDayMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_SIGNDAY_SignDayPageReq);
    SetMessageLength();
}