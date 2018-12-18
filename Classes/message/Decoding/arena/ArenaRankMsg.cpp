//
//  ArenaRankMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//

#include "ArenaRankMsg.hpp"
ArenaRankMsg::ArenaRankMsg()
{
    
}
ArenaRankMsg::~ ArenaRankMsg()
{
    
}
ByteStream *ArenaRankMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaRankPageReq);
    SetMessageLength();
}