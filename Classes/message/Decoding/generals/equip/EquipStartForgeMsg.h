//
//  EquipStartForgeMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/8.
//
//

#ifndef __FightPass__EquipStartForgeMsg__
#define __FightPass__EquipStartForgeMsg__
#include "../../MessageSendI.h"

class EquipStartForgeMsg:public MessageSendI
{
public:
    EquipStartForgeMsg(int cardId);
    ~EquipStartForgeMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__EquipStartForgeMsg__) */
