//
//  RequestDotMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 16/3/3.
//
//

#ifndef RequestDotMsg_h
#define RequestDotMsg_h

#include "../MessageSendI.h"
class RequestDotMsg:public MessageSendI
{
public:
    RequestDotMsg();
    ~RequestDotMsg();
    ByteStream *encodingData();
};

#endif /* RequestDotMsg_h */
