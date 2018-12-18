//
//  LuckyReceiveAllMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/3.
//
//

#include "LuckyReceiveAllMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
LuckyReceiveAllMsg::LuckyReceiveAllMsg()
{
    
}
LuckyReceiveAllMsg::~ LuckyReceiveAllMsg()
{
    
}
ByteStream *LuckyReceiveAllMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LUCKY_LuckyReceiveAllReq);
    SetMessageLength();
}