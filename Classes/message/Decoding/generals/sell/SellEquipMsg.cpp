//
//  SellEquipMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#include "SellEquipMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"
SellEquipMsg::SellEquipMsg(Vector<BaseEquipData*> *list)
:cardList(list)
{
    
}
SellEquipMsg::~SellEquipMsg()
{
    CC_SAFE_DELETE(cardList);
    cardList=NULL;
}
ByteStream *SellEquipMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_EQUIP_EquipSellReq);
    int size=(int)cardList->size();
    headBufferee->putShort(size);
    for (int i=0; i<size; i++) {
        headBufferee->putInt(cardList->at(i)->equipId);
    }
    SetMessageLength();
}