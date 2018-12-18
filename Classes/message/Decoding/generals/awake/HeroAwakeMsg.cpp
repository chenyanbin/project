//
//  HeroAwakeMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//
//

#include "HeroAwakeMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

HeroAwakeMsg::HeroAwakeMsg(int cardId)
:_cardId(cardId)
{
    
}
HeroAwakeMsg::~HeroAwakeMsg()
{
    
}
ByteStream *HeroAwakeMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroWakeUpPageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}