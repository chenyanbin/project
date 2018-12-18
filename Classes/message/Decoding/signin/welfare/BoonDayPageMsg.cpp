//
//  BoonDayPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
//

#include "BoonDayPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
BoonDayPageMsg::BoonDayPageMsg()
{
    
}
BoonDayPageMsg::~BoonDayPageMsg()
{
    
}
ByteStream *BoonDayPageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOON_BoonDayPageReq);
    SetMessageLength();
}