//
//  WeekRewardPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#include "WeekRewardPageMsg.h"
WeekRewardPageMsg::WeekRewardPageMsg(int day)
:m_day(day)
{
    
}
WeekRewardPageMsg::~ WeekRewardPageMsg()
{
    
}
ByteStream* WeekRewardPageMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekRewardPageReq);
    headBufferee->put(m_day);
    
    SetMessageLength();
}