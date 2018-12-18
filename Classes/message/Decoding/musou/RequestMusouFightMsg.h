//
//  RequestMusouFightMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#ifndef RequestMusouFightMsg_hpp
#define RequestMusouFightMsg_hpp

#include "../MessageSendI.h"
class RequestMusouFightMsg:public MessageSendI
{
public:
    RequestMusouFightMsg(int battleID);
    ~RequestMusouFightMsg();
    ByteStream *encodingData();
private:
    int m_battleID;
};

#endif /* RequestMusouFightMsg_hpp */
