//
//  ChooseEuipMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/10.
//
//

#include "ChooseEquipMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

ChooseEquipMsg::ChooseEquipMsg(int herId,int slot)
:_herId(herId)
,_slot(slot)
{
    
}
ChooseEquipMsg::~ChooseEquipMsg()
{
    
}
ByteStream *ChooseEquipMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroEquipSelPageReq);

    headBufferee->putInt(_herId);
    headBufferee->put(_slot);
    SetMessageLength();
}