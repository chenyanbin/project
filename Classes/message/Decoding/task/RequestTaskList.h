//
//  RequestTaskList.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/28.
//获取任务列表
//

#ifndef RequestTaskList_hpp
#define RequestTaskList_hpp

#include "../MessageSendI.h"
class RequestTaskList:public MessageSendI
{
public:
    RequestTaskList();
    ~RequestTaskList();
    ByteStream *encodingData();
};

#endif /* RequestTaskList_hpp */
