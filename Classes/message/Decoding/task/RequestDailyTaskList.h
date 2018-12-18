//
//  RequestDailyTaskList.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//
//

#ifndef RequestDailyTaskList_hpp
#define RequestDailyTaskList_hpp

#include "../MessageSendI.h"
class RequestDailyTaskList:public MessageSendI
{
public:
    RequestDailyTaskList();
    ~RequestDailyTaskList();
    ByteStream *encodingData();
};

#endif /* RequestDailyTaskList_hpp */
