//
//  RequestMusouFightMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#include "RequestMusouFightMsg.h"
RequestMusouFightMsg::RequestMusouFightMsg(int stageID)
:m_battleID(stageID)
{
    
}
RequestMusouFightMsg::~RequestMusouFightMsg()
{
    
}
ByteStream* RequestMusouFightMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MUSOU_MusouStartBattleReq);
    headBufferee->putInt(m_battleID);
    SetMessageLength();
}