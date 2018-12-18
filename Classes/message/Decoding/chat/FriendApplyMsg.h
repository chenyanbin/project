//
//  FriendApplyMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#ifndef FriendApplyMsg_h
#define FriendApplyMsg_h

#include "../MessageSendI.h"
class FriendApplyMsg:public MessageSendI
{
public:
    FriendApplyMsg();
    ~FriendApplyMsg();
    ByteStream *encodingData();
};

#endif /* FriendApplyMsg_h */
