//
//  SigninPowerMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/23.
//
//

#ifndef SigninPowerMsg_hpp
#define SigninPowerMsg_hpp

#include "../MessageSendI.h"
class SigninPowerMsg:public MessageSendI
{
public:
    SigninPowerMsg();
    ~ SigninPowerMsg();
    ByteStream *encodingData();
};

#endif /* SigninPowerMsg_hpp */
