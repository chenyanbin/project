//
//  LetterGiftMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#ifndef __FightPass__LetterGiftMsg__
#define __FightPass__LetterGiftMsg__

#include "../../MessageSendI.h"
class LetterGiftMsg:public MessageSendI
{
public:
    LetterGiftMsg(int letterId);
    ~LetterGiftMsg();
    ByteStream *encodingData();
private:
    int _id;
};

#endif /* defined(__FightPass__LetterGiftMsg__) */
