//
//  LuckyReceiveAllMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/12/3.
//
//

#ifndef __FightPass__LuckyReceiveAllMsg__
#define __FightPass__LuckyReceiveAllMsg__

#include "../MessageSendI.h"
class LuckyReceiveAllMsg:public MessageSendI
{
public:
    LuckyReceiveAllMsg();
    ~ LuckyReceiveAllMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__LuckyReceiveAllMsg__) */
