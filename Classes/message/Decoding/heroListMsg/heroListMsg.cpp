//
//  heroListMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/6.
//
//

#include "heroListMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
heroListMsg::heroListMsg()
{
    
}
heroListMsg::~heroListMsg()
{
    
}
ByteStream *heroListMsg::encodingData()
{
    Dialog::showServerLoading();
     MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroListPageReq);
    SetMessageLength();
}