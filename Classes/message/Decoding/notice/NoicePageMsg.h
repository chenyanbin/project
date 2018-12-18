//
//  NoicePageMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 16/2/25.
//
//

#ifndef NoicePageMsg_h
#define NoicePageMsg_h

#include "../MessageSendI.h"
class NoicePageMsg:public MessageSendI
{
public:
    NoicePageMsg();
    ~NoicePageMsg();
    ByteStream *encodingData();
};

#endif /* NoicePageMsg_h */
