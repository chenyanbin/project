//
//  WeekHalfPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef __FightPass__WeekHalfPageMsg__
#define __FightPass__WeekHalfPageMsg__

#include "../MessageSendI.h"
class WeekHalfPageMsg:public MessageSendI
{
public:
    WeekHalfPageMsg(int day);
    ~ WeekHalfPageMsg();
    ByteStream *encodingData();
private:
    int m_day;
    
};


#endif /* defined(__FightPass__WeekHalfPageMsg__) */
