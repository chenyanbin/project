//
//  RequestSweepMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#ifndef __FightPass__RequestSweepMsg__
#define __FightPass__RequestSweepMsg__
#include "../MessageSendI.h"
class RequestSweepMsg:public MessageSendI
{
public:
    RequestSweepMsg(int battleID,int count);
    ~RequestSweepMsg();
    ByteStream *encodingData();
private:
    int m_battleID;
    int m_count;
};

#endif /* defined(__FightPass__RequestSweepMsg__) */
