//
//  ArenaRewardMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/5.
//
//

#include "ArenaRewardMsg.hpp"
ArenaRewardMsg::ArenaRewardMsg()
{
    
}
ArenaRewardMsg::~ArenaRewardMsg()
{
    
}
ByteStream *ArenaRewardMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaRewardReq);
    SetMessageLength();

}