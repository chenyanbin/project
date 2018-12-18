//
//  HeroPutOnMsg.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#include "HeroPutOnMsg.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/Dialog/Dialog.h"

HeroPutOnMsg::HeroPutOnMsg(int herId,int slot,int equitId)
:_herId(herId)
,_slot(slot)
,_equitId(equitId)
{
    
}
HeroPutOnMsg::~HeroPutOnMsg()
{
    
}
ByteStream *HeroPutOnMsg::encodingData()
{
    Dialog::showServerLoading();
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroPutOnReq);
    headBufferee->putInt(_herId);
    headBufferee->putInt(_equitId);
    headBufferee->put(_slot);
    SetMessageLength();
}