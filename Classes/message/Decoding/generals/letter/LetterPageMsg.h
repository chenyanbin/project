//
//  LetterPageMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#ifndef __FightPass__LetterPageMsg__
#define __FightPass__LetterPageMsg__

#include "../../MessageSendI.h"
class LetterPageMsg:public MessageSendI
{
public:
    LetterPageMsg();
    ~LetterPageMsg();
    ByteStream *encodingData();

};

#endif /* defined(__FightPass__LetterPageMsg__) */
