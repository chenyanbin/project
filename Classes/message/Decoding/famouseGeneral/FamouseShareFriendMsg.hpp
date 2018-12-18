//
//  FamouseShareFriendMsg.hpp
//  FightPass
//分享boss
//  Created by zhangxiaobin on 16/1/29.
//
//

#ifndef FamouseShareFriendMsg_hpp
#define FamouseShareFriendMsg_hpp

#include "../MessageSendI.h"
class FamouseShareFriendMsg:public MessageSendI
{
public:
    FamouseShareFriendMsg(int bossID,std::vector<long>* friendList);
    ~FamouseShareFriendMsg();
    ByteStream *encodingData();
private:
    int m_bossID;
    std::vector<long>* m_frindList;
    
};

#endif /* FamouseShareFriendMsg_hpp */
