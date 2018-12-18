//
//  BoonDayReceiveMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
// 每日福利领取

#ifndef __FightPass__BoonDayReceiveMsg__
#define __FightPass__BoonDayReceiveMsg__

#include "../../MessageSendI.h"
class BoonDayReceiveMsg:public MessageSendI
{
public:
    BoonDayReceiveMsg();
    ~BoonDayReceiveMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__BoonDayReceiveMsg__) */
