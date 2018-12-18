//
//  ArenaEveryDayPriceMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//  每日灵江倒计时

#ifndef ArenaEveryDayPriceMsg_hpp
#define ArenaEveryDayPriceMsg_hpp

#include "../MessageSendI.h"
class ArenaEveryDayPriceMsg:public MessageSendI
{
public:
    ArenaEveryDayPriceMsg();
    ~ ArenaEveryDayPriceMsg();
    ByteStream *encodingData();
private:
    
};

#endif /* ArenaEveryDayPriceMsg_hpp */
