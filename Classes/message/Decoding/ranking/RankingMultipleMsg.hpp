//
//  RankingMultipleMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//  综合排名

#ifndef RankingMultipleMsg_hpp
#define RankingMultipleMsg_hpp

#include "../MessageSendI.h"
class RankingMultipleMsg:public MessageSendI
{
public:
    RankingMultipleMsg();
    ~ RankingMultipleMsg();
    ByteStream *encodingData();
};

#endif /* RankingMultipleMsg_hpp */
