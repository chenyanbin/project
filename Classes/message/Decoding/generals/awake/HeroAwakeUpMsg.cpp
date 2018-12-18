//
//  HeroAwakeUpMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//
//

#include "HeroAwakeUpMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

HeroAwakeUpMsg::HeroAwakeUpMsg(int cardId)
:_cardId(cardId)
{
    
}
HeroAwakeUpMsg::~HeroAwakeUpMsg()
{
    
}
ByteStream *HeroAwakeUpMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroWakeUpReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}