//
//  GeneralsHeroInfoMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#include "GeneralsHeroInfoMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

GeneralsHeroInfoMsg::GeneralsHeroInfoMsg(int cardId)
:_cardId(cardId)
{
    
}
GeneralsHeroInfoMsg::~GeneralsHeroInfoMsg()
{
    
}
ByteStream *GeneralsHeroInfoMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroInfoPageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}