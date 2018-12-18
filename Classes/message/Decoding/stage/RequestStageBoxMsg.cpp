//
//  RequestStageBoxMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//扫荡
//

#include "RequestStageBoxMsg.h"
#include "../../../commonData/GlobalInfo.h"
RequestStageBoxMsg::RequestStageBoxMsg(int boxID)
:m_boxID(boxID)
{
    
}
RequestStageBoxMsg::~RequestStageBoxMsg()
{
    
}
ByteStream * RequestStageBoxMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_StageOpenBoxReq);

    
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_boxID);
    
    
    SetMessageLength();
}