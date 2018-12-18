//
//  WeekOpenDayMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#ifndef __FightPass__WeekOpenDayMsg__
#define __FightPass__WeekOpenDayMsg__

#include "../MessageSendI.h"
class WeekOpenDayMsg:public MessageSendI
{
public:
    WeekOpenDayMsg();
    ~ WeekOpenDayMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__WeekOpenDayMsg__) */
