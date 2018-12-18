//
//  RequestAwakePageMsg.hpp
//  FightPass
//武将觉醒页2
//  Created by zhangbin on 16/4/7.
//
//

#ifndef RequestAwakePageMsg_hpp
#define RequestAwakePageMsg_hpp
#include "../../MessageSendI.h"
class RequestAwakePageMsg:public MessageSendI
{
public:
    RequestAwakePageMsg(int heroid);
    ~RequestAwakePageMsg();
    ByteStream *encodingData();
private:
    int m_heroID;
};

#endif /* RequestAwakePageMsg_hpp */
