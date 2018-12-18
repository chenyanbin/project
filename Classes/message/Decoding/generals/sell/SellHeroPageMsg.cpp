//
//  SellHeroPageMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#include "SellHeroPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
SellHeroPageMsg::SellHeroPageMsg()
{
    
}
SellHeroPageMsg::~SellHeroPageMsg()
{
    
}
ByteStream *SellHeroPageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroSellPageReq);
    SetMessageLength();
}