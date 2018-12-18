//
//  SkillMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/11.
//
//

#ifndef __FightPass__SkillMsg__
#define __FightPass__SkillMsg__

#include "../../MessageSendI.h"
class SkillMsg:public MessageSendI
{
public:
    SkillMsg(int cardId);
    ~SkillMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__SkillMsg__) */
