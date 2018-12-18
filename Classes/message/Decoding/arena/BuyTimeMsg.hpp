//
//  BuyTimeMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//  购买次数

#ifndef BuyTimeMsg_hpp
#define BuyTimeMsg_hpp

#include "../MessageSendI.h"
class BuyTimeMsg:public MessageSendI
{
public:
    BuyTimeMsg(int status);
    ~ BuyTimeMsg();
    ByteStream *encodingData();
private:
    int m_status;
};

#endif /* BuyTimeMsg_hpp */
