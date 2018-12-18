//
//  WeekHalfBuyMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef __FightPass__WeekHalfBuyMsg__
#define __FightPass__WeekHalfBuyMsg__

#include "../MessageSendI.h"
class WeekHalfBuyMsg:public MessageSendI
{
public:
    WeekHalfBuyMsg(int day);
    ~ WeekHalfBuyMsg();
    ByteStream *encodingData();
private:
    int m_day;
    
};

#endif /* defined(__FightPass__WeekHalfBuyMsg__) */
