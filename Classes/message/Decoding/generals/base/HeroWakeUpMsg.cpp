//
//  HeroWakeUpMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/27.
//
//

#include "HeroWakeUpMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

HeroWakeUpMsg::HeroWakeUpMsg(int cardId)
:_cardId(cardId)
{
    
}
HeroWakeUpMsg::~HeroWakeUpMsg()
{
    
}
ByteStream *HeroWakeUpMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroOneKeyPutOnReq);

    headBufferee->putInt(_cardId);
    SetMessageLength();
}