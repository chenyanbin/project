//
//  EquipStartForgeMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/9/8.
//
//

#include "EquipStartForgeMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../module/generals/data/EquipDataManager.h"

EquipStartForgeMsg::EquipStartForgeMsg(int cardId)
:_cardId(cardId)
{
    
}
EquipStartForgeMsg::~EquipStartForgeMsg()
{
    
}
ByteStream *EquipStartForgeMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipForgeReq);

    headBufferee->putInt(_cardId);
    Vector<BaseEquipData*>* chooseList=EquipDataManager::getInstance()->getDataList();
    int _size=(int)chooseList->size();
    headBufferee->put(_size);
    for (int i=0; i<_size; i++) {
        headBufferee->putInt(chooseList->at(i)->equipId);
    }
    
    SetMessageLength();
}