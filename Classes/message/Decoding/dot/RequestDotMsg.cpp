//
//  RequestDotMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 16/3/3.
//
//

#include "RequestDotMsg.h"
#include "../../../common/Dialog/Dialog.h"
RequestDotMsg::RequestDotMsg()
{
    
}
RequestDotMsg::~RequestDotMsg()
{
    
}
ByteStream* RequestDotMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_RedPointReq);
    SetMessageLength();
}