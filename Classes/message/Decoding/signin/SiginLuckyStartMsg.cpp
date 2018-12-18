//
//  SiginLuckyStartMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/30.
//
//

#include "SiginLuckyStartMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
SiginLuckyStartMsg::SiginLuckyStartMsg()
{
    
}
SiginLuckyStartMsg::~ SiginLuckyStartMsg()
{
    
}
ByteStream *SiginLuckyStartMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_LUCKY_LuckyGoReq);
    SetMessageLength();
}