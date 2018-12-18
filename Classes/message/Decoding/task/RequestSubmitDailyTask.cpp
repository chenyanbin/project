//
//  RequestSubmitDailyTask.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#include "RequestSubmitDailyTask.h"
RequestSubmitDailyTask::RequestSubmitDailyTask(int taskID)
:m_taskID(taskID)
{
    
}
RequestSubmitDailyTask::~RequestSubmitDailyTask()
{
    
}
ByteStream* RequestSubmitDailyTask::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_TASK_TaskDayRewardReq);
    headBufferee->putInt(m_taskID);
    SetMessageLength();
}