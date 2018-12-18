//
//  SigninDayMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/11/4.
//
//

#ifndef __FightPass__SigninDayMsg__
#define __FightPass__SigninDayMsg__

#include "../MessageSendI.h"
class SigninDayMsg:public MessageSendI
{
public:
    SigninDayMsg();
    ~SigninDayMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SigninDayMsg__) */
