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
class ChatMyInfoMsg:public MessageSendI
{
public:
    ChatMyInfoMsg();
    ~ChatMyInfoMsg();
    ByteStream *encodingData();
};

#endif /* ChatMyInfoMsg_hpp */
