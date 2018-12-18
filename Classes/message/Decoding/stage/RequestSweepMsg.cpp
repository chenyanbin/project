//
//  RequestSweepMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#include "RequestSweepMsg.h"
#include "../../../commonData/GlobalInfo.h"
RequestSweepMsg::RequestSweepMsg(int battleID,int count)
:m_battleID(battleID),m_count(count)
{
    
}
RequestSweepMsg::~RequestSweepMsg()
{
    
}
ByteStream * RequestSweepMsg::encodingData()
{

    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_SweptReq);
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_battleID);
    headBufferee->put(m_count);
    
    SetMessageLength();
}