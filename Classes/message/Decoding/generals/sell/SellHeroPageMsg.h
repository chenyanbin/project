//
//  SellHeroPageMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#ifndef __FightPass__SellHeroPageMsg__
#define __FightPass__SellHeroPageMsg__

#include "../../MessageSendI.h"
class SellHeroPageMsg:public MessageSendI
{
public:
    SellHeroPageMsg();
    ~SellHeroPageMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SellHeroPageMsg__) */
