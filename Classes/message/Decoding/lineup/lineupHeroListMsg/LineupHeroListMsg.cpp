//
//  LineupHeroListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#include "LineupHeroListMsg.h"
#include "../../../../commonData/GlobalInfo.h"

LineupHeroListMsg::LineupHeroListMsg(int _lineupId,int _fromHeroType,int _fromLocation)
:lineupId(_lineupId)
,fromHeroType(_fromHeroType)
,fromLocation(_fromLocation)
{
    
}
LineupHeroListMsg::~LineupHeroListMsg()
{
    
}
ByteStream *LineupHeroListMsg::encodingData()
{
   
    MessageSendI::encodingData(SCENSE_CLIENT_LINEUP_LineupHeroSelPageReq);

    headBufferee->put(lineupId);
    headBufferee->put(fromHeroType);
    headBufferee->put(fromLocation);
    SetMessageLength();
}