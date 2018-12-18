//
//  WeekTeskMag.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#include "WeekTeskMag.hpp"
WeekTeskMag::WeekTeskMag(int day,int taskTag)
:m_day(day)
,m_teskTag(taskTag)
{
    
}
WeekTeskMag::~ WeekTeskMag()
{
    
}
ByteStream* WeekTeskMag::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekTaskPageReq);
    headBufferee->put(m_day);
    headBufferee->putInt(m_teskTag);
    
    SetMessageLength();
}