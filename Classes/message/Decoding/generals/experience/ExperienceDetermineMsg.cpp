//
//  ExperienceDetermineMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#include "ExperienceDetermineMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../module/generals/data/CardDataManager.h"
#include "../../../../common/Dialog/Dialog.h"
ExperienceDetermineMsg::ExperienceDetermineMsg(int cardId)
:_cardId(cardId)
{
    
}
ExperienceDetermineMsg::~ExperienceDetermineMsg()
{
    
}
ByteStream *ExperienceDetermineMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroStartPlacesReq);
    headBufferee->putInt(_cardId);
    int num=(int)CardDataManager::getInstance()->getDataList()->size();
    headBufferee->putShort(num);
    for (int i=0; i<num; i++) {
        headBufferee->putInt(CardDataManager::getInstance()->getCardDataByIndex(i)->heroId);
    }
    SetMessageLength();
}