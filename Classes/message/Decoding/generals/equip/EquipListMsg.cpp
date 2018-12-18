//
//  EquipListMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/1.
//
//

#include "EquipListMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
EquipListMsg::EquipListMsg()
{
    
}
EquipListMsg::~EquipListMsg()
{
    
}
ByteStream *EquipListMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipListPageReq);
    SetMessageLength();
}