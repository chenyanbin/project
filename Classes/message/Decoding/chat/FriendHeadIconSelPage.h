//
//  FriendHeadIconSelPage.hpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#ifndef FriendHeadIconSelPage_h
#define FriendHeadIconSelPage_h

#include "../MessageSendI.h"
class FriendHeadIconSelPage:public MessageSendI
{
public:
    FriendHeadIconSelPage();
    ~FriendHeadIconSelPage();
    ByteStream *encodingData();
};


#endif /* FriendHeadIconSelPage_h */
