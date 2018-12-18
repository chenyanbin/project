//
//  DartPageMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
// 运镖页

#ifndef DartPageMsg_hpp
#define DartPageMsg_hpp

#include "../MessageSendI.h"
class DartPageMsg:public MessageSendI
{
public:
    DartPageMsg();
    ~ DartPageMsg();
    ByteStream *encodingData();
};

#endif /* DartPageMsg_hpp */
