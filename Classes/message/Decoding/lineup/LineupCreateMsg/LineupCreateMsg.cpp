//
//  LineupCreateMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/15.
//
//

#include "LineupCreateMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupCreateMsg::LineupCreateMsg()
{
    
}
LineupCreateMsg::~LineupCreateMsg()
{
    
}
ByteStream *LineupCreateMsg::encodingData()
{

     MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupCreateReq);
    SetMessageLength();
}