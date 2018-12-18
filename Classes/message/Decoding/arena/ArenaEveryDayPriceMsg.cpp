//
//  ArenaEveryDayPriceMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//

#include "ArenaEveryDayPriceMsg.hpp"
ArenaEveryDayPriceMsg::ArenaEveryDayPriceMsg()

{
    
}
ArenaEveryDayPriceMsg::~ ArenaEveryDayPriceMsg()
{
    
}
ByteStream *ArenaEveryDayPriceMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaDayRewardCountDownReq);
    SetMessageLength();
}