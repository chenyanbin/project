//
//  HeroListBarMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#include "HeroListBarMsg.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/Dialog/Dialog.h"
HeroListBarMsg::HeroListBarMsg()
{
    
}
HeroListBarMsg::~HeroListBarMsg()
{
    
}
ByteStream *HeroListBarMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroListBarReq);
    SetMessageLength();
}