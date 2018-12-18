//
//  ExperienceMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/12.
//
//

#ifndef __FightPass__ExperienceMsg__
#define __FightPass__ExperienceMsg__

#include "../../MessageSendI.h"
class ExperienceMsg:public MessageSendI
{
public:
    ExperienceMsg(int cardId);
    ~ExperienceMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__ExperienceMsg__) */
