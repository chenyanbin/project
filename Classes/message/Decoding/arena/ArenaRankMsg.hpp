//
//  ArenaRankMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
// 竞技场排行榜

#ifndef ArenaRankMsg_hpp
#define ArenaRankMsg_hpp

#include "../MessageSendI.h"
class ArenaRankMsg:public MessageSendI
{
public:
    ArenaRankMsg();
    ~ ArenaRankMsg();
    ByteStream *encodingData();
};

#endif /* ArenaRankMsg_hpp */
