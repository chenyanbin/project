//
//  ArenaRecoredMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/15.
//
// 对战记录

#ifndef ArenaRecoredMsg_hpp
#define ArenaRecoredMsg_hpp

#include "../MessageSendI.h"
class ArenaRecoredMsg:public MessageSendI
{
public:
    ArenaRecoredMsg();
    ~ ArenaRecoredMsg();
    ByteStream *encodingData();
};

#endif /* ArenaRecoredMsg_hpp */
