//
//  LineupSetRespMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/13.
//
// 上阵

#include "LineupSetRespMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupSetRespMsg::LineupSetRespMsg(int lineupNo, int heroType, int location,int heroId)
:m_lineupNo(lineupNo)
,m_heroType(heroType)
,m_location(location)
,m_heroId(heroId)
{
    
}
LineupSetRespMsg::~LineupSetRespMsg()
{
    
}
ByteStream *LineupSetRespMsg::encodingData()
{
  
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupSetReq);
    headBufferee->put(m_lineupNo);
    headBufferee->put(m_heroType);
    headBufferee->put(m_location);
    headBufferee->putInt(m_heroId);
    SetMessageLength();
}