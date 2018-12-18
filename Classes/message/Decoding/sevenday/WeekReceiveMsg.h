//
//  WeekReceiveMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef __FightPass__WeekReceiveMsg__
#define __FightPass__WeekReceiveMsg__

#include "../MessageSendI.h"
class WeekReceiveMsg:public MessageSendI
{
public:
    WeekReceiveMsg(int day, int type, int _numPrice, int _numHero);
    ~ WeekReceiveMsg();
    ByteStream *encodingData();
private:
    int m_day;
    int m_type;
    int m_numPrice;
    int m_numHero;
    
};

#endif /* defined(__FightPass__WeekReceiveMsg__) */
