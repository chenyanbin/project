//
//  RequestStageMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#ifndef __FightPass__RequestStageMsg__
#define __FightPass__RequestStageMsg__

#include "../MessageSendI.h"
class RequestStageMsg:public MessageSendI
{
public:
    RequestStageMsg(int stageID);
    ~RequestStageMsg();
    ByteStream *encodingData();
private:
    int m_stageID;
    
};

#endif /* defined(__FightPass__RequestStageMsg__) */
