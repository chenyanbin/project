//
//  LetterDeliverMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#ifndef __FightPass__LetterDeliverMsg__
#define __FightPass__LetterDeliverMsg__

#include "../../MessageSendI.h"
class LetterDeliverMsg:public MessageSendI
{
public:
    LetterDeliverMsg(int letterId);
    ~LetterDeliverMsg();
    ByteStream *encodingData();
private:
    int _id;
};

#endif /* defined(__FightPass__LetterDeliverMsg__) */
