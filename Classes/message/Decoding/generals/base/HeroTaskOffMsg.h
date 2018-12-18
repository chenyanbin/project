//
//  HeroTaskOffMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#ifndef __FightPass__HeroTaskOffMsg__
#define __FightPass__HeroTaskOffMsg__

#include "../../MessageSendI.h"
class HeroTaskOffMsg:public MessageSendI
{
public:
    HeroTaskOffMsg(int herId,int slot);
    ~HeroTaskOffMsg();
    ByteStream *encodingData();
private:
    int _herId;
    int _slot;
};

#endif /* defined(__FightPass__HeroTaskOffMsg__) */
