//
//  WeekReceiveMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#include "WeekReceiveMsg.h"
WeekReceiveMsg::WeekReceiveMsg(int day, int type, int _numPrice, int _numHero)
:m_day(day)
,m_type(type)
,m_numPrice(_numPrice)
,m_numHero(_numHero)
{
    
}
WeekReceiveMsg::~ WeekReceiveMsg()
{
    
}
ByteStream* WeekReceiveMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekReceiveReq);
    headBufferee->put(m_day);
    headBufferee->put(m_type);
    headBufferee->put(m_numPrice);
    headBufferee->put(m_numHero);
    SetMessageLength();
}