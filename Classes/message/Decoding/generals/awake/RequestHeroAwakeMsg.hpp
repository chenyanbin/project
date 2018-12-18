//
//  RequestHeroAwakeMsg.hpp
//  FightPass
//武将觉醒2
//  Created by zhangbin on 16/4/7.
//
//

#ifndef RequestHeroAwakeMsg_hpp
#define RequestHeroAwakeMsg_hpp
#include "../../MessageSendI.h"
class RequestHeroAwakeMsg:public MessageSendI
{
public:
    RequestHeroAwakeMsg(int heroid);
    ~RequestHeroAwakeMsg();
    ByteStream *encodingData();
private:
    int m_heroID;
};

#endif /* RequestHeroAwakeMsg_hpp */
