//
//  FriendRefuseMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/24.
//
//

#ifndef FriendRefuseMsg_h
#define FriendRefuseMsg_h

#include "../MessageSendI.h"
class FriendRefuseMsg:public MessageSendI
{
public:
    FriendRefuseMsg(long id);
    ~FriendRefuseMsg();
    ByteStream *encodingData();
private:
    long userId;
};

#endif /* FriendRefuseMsg_h */
