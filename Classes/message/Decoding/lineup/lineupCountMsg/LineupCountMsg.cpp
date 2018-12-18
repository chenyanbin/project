//
//  LineupCountMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#include "LineupCountMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupCountMsg::LineupCountMsg()
{
    
}
LineupCountMsg::~LineupCountMsg()
{
    
}
ByteStream *LineupCountMsg::encodingData()
{
  
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupListReq);
    SetMessageLength();
}