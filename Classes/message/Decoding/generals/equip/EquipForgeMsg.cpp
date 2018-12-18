//
//  EquipForgeMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/7.
//
//

#include "EquipForgeMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
EquipForgeMsg::EquipForgeMsg(int cardId)
:_cardId(cardId)
{
    
}
EquipForgeMsg::~EquipForgeMsg()
{
    
}
ByteStream *EquipForgeMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipForgePageReq);

    headBufferee->putInt(_cardId);
    SetMessageLength();
}