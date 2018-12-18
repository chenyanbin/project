//
//  WeekHalfPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#include "WeekHalfPageMsg.h"
WeekHalfPageMsg::WeekHalfPageMsg(int day)
:m_day(day)
{
    
}
WeekHalfPageMsg::~ WeekHalfPageMsg()
{
    
}
ByteStream* WeekHalfPageMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekHalfPageReq);
    headBufferee->put(m_day);
    
    SetMessageLength();
}