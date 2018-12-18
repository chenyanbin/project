//
//  ChatMyInfoMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/14.
//
//

#ifndef ChatMyInfoMsg_hpp
#define ChatMyInfoMsg_hpp

#include "../MessageSendI.h"
class ChatFriendsListMsg:public MessageSendI
{
public:
    ChatFriendsListMsg();
    ~ChatFriendsListMsg();
    ByteStream *encodingData();
};

#endif /* ChatMyInfoMsg_hpp */
