//
//  heroListMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/6.
//
//

#ifndef __FightPass__heroListMsg__
#define __FightPass__heroListMsg__

#include "../MessageSendI.h"
class heroListMsg:public MessageSendI
{
public:
    heroListMsg();
    ~heroListMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__heroListMsg__) */
