//
//  PropertyMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/10.
//
//

#include "PropertyMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

PropertyMsg::PropertyMsg(int cardId)
:_cardId(cardId)
{
    
}
PropertyMsg::~PropertyMsg()
{
    
}
ByteStream *PropertyMsg::encodingData()
{
    Dialog::showServerLoading();
     MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroPropertyPageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}