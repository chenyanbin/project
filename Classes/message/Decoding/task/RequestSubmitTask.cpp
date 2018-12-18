//
//  RequestSubmitTask.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#include "RequestSubmitTask.h"
RequestSubmitTask::RequestSubmitTask(int taskID)
:m_taskID(taskID)
{
    
}
RequestSubmitTask::~RequestSubmitTask()
{
    
}
ByteStream* RequestSubmitTask::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_TASK_TaskCommonRewardReq);
    headBufferee->putInt(m_taskID);
    SetMessageLength();
}