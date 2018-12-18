//
//  BuyPowerMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
//  购买体力

#ifndef BuyPowerMsg_hpp
#define BuyPowerMsg_hpp

#include "../MessageSendI.h"
class BuyPowerMsg:public MessageSendI
{
public:
    BuyPowerMsg();
    ~ BuyPowerMsg();
    ByteStream *encodingData();
};

#endif /* BuyPowerMsg_hpp */
