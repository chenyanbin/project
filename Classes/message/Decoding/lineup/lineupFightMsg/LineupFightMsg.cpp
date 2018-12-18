//
//  LineupFightMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/22.
//
//

#include "LineupFightMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupFightMsg::LineupFightMsg(int lineupNo)
:m_lineupNo(lineupNo)
{
    
}
LineupFightMsg::~ LineupFightMsg()
{
    
}
ByteStream *LineupFightMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupSetDefaultReq);
    headBufferee->put(m_lineupNo);
    SetMessageLength();
}