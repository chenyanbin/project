//
//  SkillMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/11.
//
//

#include "SkillMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
SkillMsg::SkillMsg(int cardId)
:_cardId(cardId)
{
    
}
SkillMsg::~SkillMsg()
{
    
}
ByteStream *SkillMsg::encodingData()
{
    Dialog::showServerLoading();
     MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroSkillPageReq);
    headBufferee->putInt(_cardId);
    SetMessageLength();
}