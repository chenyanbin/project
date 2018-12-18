//
//  RequestTaskList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#include "RequestTaskList.h"
RequestTaskList::RequestTaskList()
{
    
}
RequestTaskList::~RequestTaskList()
{
    
}
ByteStream* RequestTaskList::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_TASK_TaskCommonPageReq);
    SetMessageLength();
}