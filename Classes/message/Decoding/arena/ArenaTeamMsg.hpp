//
//  ArenaTeamMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
//  上阵英雄页

#ifndef ArenaTeamMsg_hpp
#define ArenaTeamMsg_hpp

#include "../MessageSendI.h"
class ArenaTeamMsg:public MessageSendI
{
public:
    ArenaTeamMsg();
    ~ ArenaTeamMsg();
    ByteStream *encodingData();
};

#endif /* ArenaTeamMsg_hpp */
