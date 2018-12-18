//
//  HeroAwakeMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//
//

#ifndef __FightPass__HeroAwakeMsg__
#define __FightPass__HeroAwakeMsg__

#include "../../MessageSendI.h"
class HeroAwakeMsg:public MessageSendI
{
public:
    HeroAwakeMsg(int cardId);
    ~HeroAwakeMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__HeroAwakeMsg__) */
