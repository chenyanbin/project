//
//  BoonWeekPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
//

#include "BoonWeekPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
BoonWeekPageMsg::BoonWeekPageMsg()
{
    
}
BoonWeekPageMsg::~BoonWeekPageMsg()
{
    
}
ByteStream *BoonWeekPageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_BOON_BoonWeekPageReq);
    SetMessageLength();
}