//
//  RequestSubmitTask.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//领取任务奖励
//

#ifndef RequestSubmitTask_hpp
#define RequestSubmitTask_hpp

#include "../MessageSendI.h"
class RequestSubmitTask:public MessageSendI
{
public:
    RequestSubmitTask(int taskID);
    ~RequestSubmitTask();
    ByteStream *encodingData();
private:
    int m_taskID;
};

#endif /* RequestSubmitTask_hpp */
