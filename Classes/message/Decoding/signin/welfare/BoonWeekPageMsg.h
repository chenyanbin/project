//
//  BoonWeekPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
// 每周福利页

#ifndef __FightPass__BoonWeekPageMsg__
#define __FightPass__BoonWeekPageMsg__

#include "../../MessageSendI.h"
class BoonWeekPageMsg:public MessageSendI
{
public:
    BoonWeekPageMsg();
    ~BoonWeekPageMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__BoonWeekPageMsg__) */
