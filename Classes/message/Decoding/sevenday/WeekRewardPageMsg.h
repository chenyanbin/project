//
//  WeekRewardPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#ifndef __FightPass__WeekRewardPageMsg__
#define __FightPass__WeekRewardPageMsg__

#include "../MessageSendI.h"
class WeekRewardPageMsg:public MessageSendI
{
public:
    WeekRewardPageMsg(int day);
    ~ WeekRewardPageMsg();
    ByteStream *encodingData();
private:
    int m_day;
    
};

#endif /* defined(__FightPass__WeekRewardPageMsg__) */
