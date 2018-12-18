//
//  HeroListBarMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#ifndef __FightPass__HeroListBarMsg__
#define __FightPass__HeroListBarMsg__

#include "../MessageSendI.h"
class HeroListBarMsg:public MessageSendI
{
public:
    HeroListBarMsg();
    ~HeroListBarMsg();
    ByteStream *encodingData();
};


#endif /* defined(__FightPass__HeroListBarMsg__) */
