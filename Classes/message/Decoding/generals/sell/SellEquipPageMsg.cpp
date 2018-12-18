//
//  SellEquipPageMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#include "SellEquipPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
SellEquipPageMsg::SellEquipPageMsg()
{
    
}
SellEquipPageMsg::~SellEquipPageMsg()
{
    
}
ByteStream *SellEquipPageMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipSellPageReq);
    SetMessageLength();
}