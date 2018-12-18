//
//  HeroWakeUpMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/27.
//
//

#ifndef __FightPass__HeroWakeUpMsg__
#define __FightPass__HeroWakeUpMsg__

#include "../../MessageSendI.h"
class HeroWakeUpMsg:public MessageSendI
{
public:
    HeroWakeUpMsg(int cardId);
    ~HeroWakeUpMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__HeroWakeUpMsg__) */
