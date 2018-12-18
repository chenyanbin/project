//
//  BoonDayReceiveMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
//

#include "BoonDayReceiveMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
BoonDayReceiveMsg::BoonDayReceiveMsg()
{
    
}
BoonDayReceiveMsg::~BoonDayReceiveMsg()
{
    
}
ByteStream *BoonDayReceiveMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOON_BoonDayReceiveReq);
    SetMessageLength();
}