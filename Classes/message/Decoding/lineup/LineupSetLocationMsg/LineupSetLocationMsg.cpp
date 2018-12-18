//
//  LineupSetLocationMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/14.
//
//

#include "LineupSetLocationMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupSetLocationMsg::LineupSetLocationMsg(int lineupNo, int heroId1, int heroId2,int heroId3)
:m_lineupNo(lineupNo)
,m_heroId1(heroId1)
,m_heroId2(heroId2)
,m_heroId3(heroId3)
{
    
}
LineupSetLocationMsg::~LineupSetLocationMsg()
{
    
}
ByteStream *LineupSetLocationMsg::encodingData()
{
   
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupSetLocationReq);
    headBufferee->put(m_lineupNo);
    headBufferee->putInt(m_heroId1);
    headBufferee->putInt((m_heroId2));
    headBufferee->putInt(m_heroId3);
    SetMessageLength();
}