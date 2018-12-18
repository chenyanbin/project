//
//  NoicePageMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 16/2/25.
//
//

#include "NoicePageMsg.h"
#include "../../../common/Dialog/Dialog.h"
NoicePageMsg::NoicePageMsg()
{
    
}
NoicePageMsg::~NoicePageMsg()
{
    
}
ByteStream* NoicePageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_NoticePageReq);
    SetMessageLength();
}