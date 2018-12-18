//
//  ExchangeOneMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//  兑换

#ifndef ExchangeOneMsg_hpp
#define ExchangeOneMsg_hpp

#include "../MessageSendI.h"
class ExchangeOneMsg:public MessageSendI
{
public:
    ExchangeOneMsg(int itemId);
    ~ ExchangeOneMsg();
    ByteStream *encodingData();
private:
    int m_itemid;
};

#endif /* ExchangeOneMsg_hpp */
