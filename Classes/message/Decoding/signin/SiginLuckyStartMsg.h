//
//  SiginLuckyStartMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/30.
//
//

#ifndef __FightPass__SiginLuckyStartMsg__
#define __FightPass__SiginLuckyStartMsg__

#include "../MessageSendI.h"
class SiginLuckyStartMsg:public MessageSendI
{
public:
    SiginLuckyStartMsg();
    ~ SiginLuckyStartMsg();
    ByteStream *encodingData();
};
#endif /* defined(__FightPass__SiginLuckyStartMsg__) */
