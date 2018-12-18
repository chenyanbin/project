//
//  SigninPowerPageMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/25.
//
//

#ifndef SigninPowerPageMsg_hpp
#define SigninPowerPageMsg_hpp

#include "../MessageSendI.h"
class SigninPowerPageMsg:public MessageSendI
{
public:
    SigninPowerPageMsg();
    ~ SigninPowerPageMsg();
    ByteStream *encodingData();
};

#endif /* SigninPowerPageMsg_hpp */
