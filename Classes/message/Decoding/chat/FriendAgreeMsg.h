//
//  FriendAgreeMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/24.
//
//

#ifndef FriendAgreeMsg_h
#define FriendAgreeMsg_h

#include "../MessageSendI.h"
class FriendAgreeMsg:public MessageSendI
{
public:
    FriendAgreeMsg(long id);
    ~FriendAgreeMsg();
    ByteStream *encodingData();
private:
    long userId;
};


#endif /* FriendAgreeMsg_h */
