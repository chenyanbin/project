//
//  DartMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
// 劫镖

#ifndef DartMsg_hpp
#define DartMsg_hpp

#include "../MessageSendI.h"
class DartMsg:public MessageSendI
{
public:
    DartMsg();
    ~ DartMsg();
    ByteStream *encodingData();
};
#endif /* DartMsg_hpp */
