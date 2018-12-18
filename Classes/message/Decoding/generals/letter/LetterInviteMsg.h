//
//  LetterInviteMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/28.
//
//

#ifndef __FightPass__LetterInviteMsg__
#define __FightPass__LetterInviteMsg__

#include "../../MessageSendI.h"
class LetterInviteMsg:public MessageSendI
{
public:
    LetterInviteMsg(int letterId);
    ~LetterInviteMsg();
    ByteStream *encodingData();
private:
    int _id;
};

#endif /* defined(__FightPass__LetterInviteMsg__) */
