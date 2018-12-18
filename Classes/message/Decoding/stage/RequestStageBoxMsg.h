//
//  RequestStageBoxMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#ifndef __FightPass__RequestStageBoxMsg__
#define __FightPass__RequestStageBoxMsg__
#include "../MessageSendI.h"
class RequestStageBoxMsg:public MessageSendI
{
public:
    RequestStageBoxMsg(int boxID);
    ~RequestStageBoxMsg();
    ByteStream *encodingData();
private:
    int m_boxID;
};

#endif /* defined(__FightPass__RequestStageBoxMsg__) */
