//
//  ExperienceDetermineMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#ifndef __FightPass__ExperienceDetermineMsg__
#define __FightPass__ExperienceDetermineMsg__

#include "../../MessageSendI.h"
class ExperienceDetermineMsg:public MessageSendI
{
public:
    ExperienceDetermineMsg(int cardId);
    ~ExperienceDetermineMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};


#endif /* defined(__FightPass__ExperienceDetermineMsg__) */
