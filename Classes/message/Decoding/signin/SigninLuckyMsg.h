//
//  SigninLuckyMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/30.
//
//

#ifndef __FightPass__SigninLuckyMsg__
#define __FightPass__SigninLuckyMsg__

#include "../MessageSendI.h"
class SigninLuckyMsg:public MessageSendI
{
public:
    SigninLuckyMsg();
    ~ SigninLuckyMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SigninLuckyMsg__) */
