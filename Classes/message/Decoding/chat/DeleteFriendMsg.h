//
//  DeleteFriendMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#ifndef DeleteFriendMsg_h
#define DeleteFriendMsg_h

#include "../MessageSendI.h"
class DeleteFriendMsg:public MessageSendI
{
public:
    DeleteFriendMsg(long id);
    ~DeleteFriendMsg();
    ByteStream *encodingData();
private:
    long userId;
};

#endif /* DeleteFriendMsg_h */
