//
//  RequestSubmitDailyTask.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#ifndef RequestSubmitDailyTask_hpp
#define RequestSubmitDailyTask_hpp
#include "../MessageSendI.h"
class RequestSubmitDailyTask:public MessageSendI
{
public:
    RequestSubmitDailyTask(int taskID);
    ~RequestSubmitDailyTask();
    ByteStream *encodingData();
private:
    int m_taskID;
};

#endif /* RequestSubmitDailyTask_hpp */
