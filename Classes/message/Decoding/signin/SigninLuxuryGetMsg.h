//
//  SigninLuxuryGetMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/11/9.
//
//

#ifndef __FightPass__SigninLuxuryGetMsg__
#define __FightPass__SigninLuxuryGetMsg__

#include "../MessageSendI.h"
class SigninLuxuryGetMsg:public MessageSendI
{
public:
    SigninLuxuryGetMsg();
    ~SigninLuxuryGetMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SigninLuxuryGetMsg__) */
