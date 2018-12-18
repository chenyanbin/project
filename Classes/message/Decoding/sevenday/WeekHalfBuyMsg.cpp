//
//  WeekHalfBuyMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#include "WeekHalfBuyMsg.h"
WeekHalfBuyMsg::WeekHalfBuyMsg(int day)
:m_day(day)
{
    
}
WeekHalfBuyMsg::~ WeekHalfBuyMsg()
{
    
}
ByteStream* WeekHalfBuyMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekHalfBuyReq);
    headBufferee->put(m_day);
    
    SetMessageLength();
}