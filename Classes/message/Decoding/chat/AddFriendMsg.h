//
//  AddFriendMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#ifndef AddFriendMsg_h
#define AddFriendMsg_h

#include "../MessageSendI.h"
class AddFriendMsg:public MessageSendI
{
public:
    AddFriendMsg(long id);
    ~AddFriendMsg();
    ByteStream *encodingData();
private:
    long userId;
};

#endif /* AddFriendMsg_h */
