//
//  GeneralsBaseMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//

#include "GeneralsBaseMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

GeneralsBaseMsg::GeneralsBaseMsg(int cardId)
:_cardId(cardId)
{
    
}
GeneralsBaseMsg::~GeneralsBaseMsg()
{
    
}
ByteStream *GeneralsBaseMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroBasePageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}