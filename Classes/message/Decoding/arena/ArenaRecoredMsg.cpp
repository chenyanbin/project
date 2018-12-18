//
//  ArenaRecoredMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//

#include "ArenaRecoredMsg.hpp"
ArenaRecoredMsg::ArenaRecoredMsg()
{
    
}
ArenaRecoredMsg::~ ArenaRecoredMsg()
{
    
}
ByteStream *ArenaRecoredMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaBattleRecordPageReq);
    SetMessageLength();
}