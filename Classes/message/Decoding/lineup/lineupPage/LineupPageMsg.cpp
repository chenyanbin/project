//
//  LineupPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#include "LineupPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupPageMsg::LineupPageMsg(int page)
:m_page(page)
{
    
}
LineupPageMsg::~LineupPageMsg()
{
    
}
ByteStream *LineupPageMsg::encodingData()
{

    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupPageReq);
    headBufferee->put(m_page);
    SetMessageLength();
}