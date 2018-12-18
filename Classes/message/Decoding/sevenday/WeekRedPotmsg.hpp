//
//  WeekRedPotmsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/29.
//
//

#ifndef WeekRedPotmsg_hpp
#define WeekRedPotmsg_hpp

#include "../MessageSendI.h"
class WeekRedPotmsg:public MessageSendI
{
public:
    WeekRedPotmsg();
    ~ WeekRedPotmsg();
    ByteStream *encodingData();
    
};

#endif /* WeekRedPotmsg_hpp */
