//
//  ArenaTeamMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//

#include "ArenaTeamMsg.hpp"
ArenaTeamMsg::ArenaTeamMsg()
{
    
}
ArenaTeamMsg::~ ArenaTeamMsg()
{
    
}
ByteStream *ArenaTeamMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaLineupHeroPageReq);
    SetMessageLength();
}