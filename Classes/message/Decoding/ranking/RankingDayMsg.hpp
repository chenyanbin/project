//
//  RankingDayMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//  每日排名

#ifndef RankingDayMsg_hpp
#define RankingDayMsg_hpp

#include "../MessageSendI.h"
class RankingDayMsg:public MessageSendI
{
public:
    RankingDayMsg();
    ~ RankingDayMsg();
    ByteStream *encodingData();
};

#endif /* RankingDayMsg_hpp */
