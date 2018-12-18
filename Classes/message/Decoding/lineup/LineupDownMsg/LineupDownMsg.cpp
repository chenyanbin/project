//
//  LineupDownMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/14.
//
//

#include "LineupDownMsg.h"
LineupDownMsg::LineupDownMsg(int lineupNo, int heroId)
:m_lineupNo(lineupNo)
,m_heroId(heroId)
{
    
}
LineupDownMsg::~LineupDownMsg()
{
    
}
ByteStream *LineupDownMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupDownReq);
    headBufferee->put(m_lineupNo);
    headBufferee->putInt(m_heroId);
    SetMessageLength();
}