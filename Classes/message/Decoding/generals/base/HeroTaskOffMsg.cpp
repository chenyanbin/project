//
//  HeroTaskOffMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#include "HeroTaskOffMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

HeroTaskOffMsg::HeroTaskOffMsg(int herId,int slot)
:_herId(herId)
,_slot(slot)
{
    
}
HeroTaskOffMsg::~HeroTaskOffMsg()
{
    
}
ByteStream *HeroTaskOffMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroTakeOffReq);
    headBufferee->putInt(_herId);
    headBufferee->put(_slot);
    SetMessageLength();
}