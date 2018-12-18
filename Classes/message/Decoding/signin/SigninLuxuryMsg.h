//
//  SigninLuxuryMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/11/4.
//
//

#ifndef __FightPass__SigninLuxuryMsg__
#define __FightPass__SigninLuxuryMsg__

#include "../MessageSendI.h"
class SigninLuxuryMsg:public MessageSendI
{
public:
    SigninLuxuryMsg();
    ~SigninLuxuryMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SigninLuxuryMsg__) */
