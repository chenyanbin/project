//
//  RequestMusouBattleListMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#include "RequestMusouBattleListMsg.h"
RequestMusouBattleListMsg::RequestMusouBattleListMsg(int stageID)
:m_stageID(stageID)
{
    
}
RequestMusouBattleListMsg::~RequestMusouBattleListMsg()
{
    
}
ByteStream* RequestMusouBattleListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MUSOU_MusouBattlePageReq);
    headBufferee->putInt(m_stageID);
    SetMessageLength();
}