//
//  FamouseFriendMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/29.
//名将传好友列表
//

#ifndef FamouseFriendMsg_hpp
#define FamouseFriendMsg_hpp


#include "../MessageSendI.h"
class FamouseFriendMsg:public MessageSendI
{
public:
    FamouseFriendMsg();
    ~FamouseFriendMsg();
    ByteStream *encodingData();

};

#endif /* FamouseFriendMsg_hpp */
