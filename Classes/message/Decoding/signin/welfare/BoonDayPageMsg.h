//
//  BoonDayPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
// 每日福利

#ifndef __FightPass__BoonDayPageMsg__
#define __FightPass__BoonDayPageMsg__

#include "../../MessageSendI.h"
class BoonDayPageMsg:public MessageSendI
{
public:
    BoonDayPageMsg();
    ~BoonDayPageMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__BoonDayPageMsg__) */
