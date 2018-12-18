//
//  FriendMyInfoMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 16/1/7.
//
//

#ifndef FriendMyInfoMsg_h
#define FriendMyInfoMsg_h

#include "../MessageSendI.h"
class FriendMyInfoMsg:public MessageSendI
{
public:
    FriendMyInfoMsg();
    ~FriendMyInfoMsg();
    ByteStream *encodingData();
};

#endif /* FriendMyInfoMsg_h */
