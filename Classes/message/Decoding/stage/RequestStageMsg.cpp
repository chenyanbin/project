//
//  RequestStageMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#include "RequestStageMsg.h"
#include "../../../commonData/GlobalInfo.h"
RequestStageMsg::RequestStageMsg(int stageID)
:m_stageID(stageID)
{
    
}
RequestStageMsg::~RequestStageMsg()
{
    
}
ByteStream* RequestStageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_StagePageReq);
    
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_stageID);
    
    
    SetMessageLength();
}