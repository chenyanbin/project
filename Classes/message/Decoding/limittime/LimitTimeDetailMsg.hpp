//
//  LimitTimeDetailMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/19.
//
//

#ifndef LimitTimeDetailMsg_hpp
#define LimitTimeDetailMsg_hpp

#include "../MessageSendI.h"
class LimitTimeDetailMsg:public MessageSendI
{
public:
    LimitTimeDetailMsg();
    ~ LimitTimeDetailMsg();
    ByteStream *encodingData();
};

#endif /* LimitTimeDetailMsg_hpp */
