//
//  SigninLuckyMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/30.
//
//

#include "SigninLuckyMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SigninLuckyMsg::SigninLuckyMsg()
{
    
}
SigninLuckyMsg::~ SigninLuckyMsg()
{
    
}
ByteStream *SigninLuckyMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LUCKY_LuckyPageReq);
    SetMessageLength();
}