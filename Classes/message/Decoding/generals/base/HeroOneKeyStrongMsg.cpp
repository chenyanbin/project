//
//  HeroOneKeyStrongMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 16/1/4.
//
//

#include "HeroOneKeyStrongMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
HeroOneKeyStrongMsg::HeroOneKeyStrongMsg(int cardId)
:_cardId(cardId)
{
    
}
HeroOneKeyStrongMsg::~HeroOneKeyStrongMsg()
{
    
}
ByteStream *HeroOneKeyStrongMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroOneKeyHardenReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}