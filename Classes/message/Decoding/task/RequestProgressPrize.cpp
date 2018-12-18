//
//  RequestProgressPrize.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/30.
//
//

#include "RequestProgressPrize.h"
RequestProgressPrize::RequestProgressPrize(int progressID)
:m_progressID(progressID)
{
    
}
RequestProgressPrize::~RequestProgressPrize()
{
    
}
ByteStream *RequestProgressPrize::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_TASK_TaskDayProgressRewardReq);
    headBufferee->putInt(m_progressID);
    SetMessageLength();
}