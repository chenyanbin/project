//
//  FindFriendListMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/22.
//
//

#ifndef FindFriendListMsg_h
#define FindFriendListMsg_h

#include "../MessageSendI.h"
class FindFriendListMsg:public MessageSendI
{
public:
    FindFriendListMsg(string name);
    ~FindFriendListMsg();
    ByteStream *encodingData();
private:
    string userName;
};

#endif /* FindFriendListMsg_h */
