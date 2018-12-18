//
//  ChooseCardMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#include "ChooseCardMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
ChooseCardMsg::ChooseCardMsg(int cardId)
:_cardId(cardId)
{
    
}
ChooseCardMsg::~ChooseCardMsg()
{
    
}
ByteStream *ChooseCardMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroMaterialSelPageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}