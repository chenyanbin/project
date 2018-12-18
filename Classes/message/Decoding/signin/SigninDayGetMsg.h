//
//  SigninDayGetMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/11/9.
//
//

#ifndef __FightPass__SigninDayGetMsg__
#define __FightPass__SigninDayGetMsg__

#include "../MessageSendI.h"
class SigninDayGetMsg:public MessageSendI
{
public:
    SigninDayGetMsg(int day);
    ~SigninDayGetMsg();
    ByteStream *encodingData();
private:
    int _day;
};

#endif /* defined(__FightPass__SigninDayGetMsg__) */
