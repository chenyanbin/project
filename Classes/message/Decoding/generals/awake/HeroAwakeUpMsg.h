//
//  HeroAwakeUpMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//
//

#ifndef __FightPass__HeroAwakeUpMsg__
#define __FightPass__HeroAwakeUpMsg__

#include "../../MessageSendI.h"
class HeroAwakeUpMsg:public MessageSendI
{
public:
    HeroAwakeUpMsg(int cardId);
    ~HeroAwakeUpMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};


#endif /* defined(__FightPass__HeroAwakeUpMsg__) */
