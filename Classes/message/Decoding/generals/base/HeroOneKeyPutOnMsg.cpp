//
//  HeroOneKeyPutOnMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/27.
//
//

#include "HeroOneKeyPutOnMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
HeroOneKeyPutOnMsg::HeroOneKeyPutOnMsg(int cardId)
:_cardId(cardId)
{
    
}
HeroOneKeyPutOnMsg::~HeroOneKeyPutOnMsg()
{
    
}
ByteStream *HeroOneKeyPutOnMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroOneKeyPutOnReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}