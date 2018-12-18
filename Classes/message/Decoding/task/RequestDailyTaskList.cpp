//
//  RequestDailyTaskList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#include "RequestDailyTaskList.h"
RequestDailyTaskList::RequestDailyTaskList()
{
    
}
RequestDailyTaskList::~RequestDailyTaskList()
{
    
}
ByteStream* RequestDailyTaskList::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_TASK_TaskDayPageReq);
    SetMessageLength();
}