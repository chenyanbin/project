//
//  ArenaChageListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/23.
//
//

#include "ArenaChageListMsg.hpp"
ArenaChageListMsg::ArenaChageListMsg()

{
    
}
ArenaChageListMsg::~ ArenaChageListMsg()
{
    
}
ByteStream *ArenaChageListMsg::encodingData()
{
    
    // MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaChangeASetReq);
    // SetMessageLength();
    return headBufferee;
}