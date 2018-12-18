//
//  FriendSetIcon.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#ifndef FriendSetIcon_h
#define FriendSetIcon_h

#include "../MessageSendI.h"
class FriendSetIcon:public MessageSendI
{
public:
    FriendSetIcon(int id);
    ~FriendSetIcon();
    ByteStream *encodingData();
private:
    int heroDictId;
};

#endif /* FriendSetIcon_h */
