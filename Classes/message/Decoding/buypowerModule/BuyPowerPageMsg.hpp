//
//  BuyPowerPageMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
// 购买体力页

#ifndef BuyPowerPageMsg_hpp
#define BuyPowerPageMsg_hpp

#include "../MessageSendI.h"
class BuyPowerPageMsg:public MessageSendI
{
public:
    BuyPowerPageMsg();
    ~ BuyPowerPageMsg();
    ByteStream *encodingData();
};

#endif /* BuyPowerPageMsg_hpp */
