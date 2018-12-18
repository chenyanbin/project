//
//  EquipStrongMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/1.
//
//

#include "EquipStrongMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
EquipStrongMsg::EquipStrongMsg(int cardId)
:_cardId(cardId)
{
    
}
EquipStrongMsg::~EquipStrongMsg()
{
    
}
ByteStream *EquipStrongMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipHardenPageReq);
    
    headBufferee->putInt(_cardId);
    SetMessageLength();
}