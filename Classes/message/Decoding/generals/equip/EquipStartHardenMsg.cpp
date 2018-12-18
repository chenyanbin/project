//
//  EquipStartHardenMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/7.
//
//

#include "EquipStartHardenMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

EquipStartHardenMsg::EquipStartHardenMsg(int cardId,bool bol)
:_cardId(cardId)
,_bol(bol)
{
    
}
EquipStartHardenMsg::~EquipStartHardenMsg()
{
    
}
ByteStream *EquipStartHardenMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipStartHardenReq);

    headBufferee->putInt(_cardId);
    headBufferee->put(int(_bol));
    
    SetMessageLength();
}