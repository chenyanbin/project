//
//  EquipForgeMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/7.
//
//

#ifndef __FightPass__EquipForgeMsg__
#define __FightPass__EquipForgeMsg__

#include "../../MessageSendI.h"
class EquipForgeMsg:public MessageSendI
{
public:
    EquipForgeMsg(int cardId);
    ~EquipForgeMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};
#endif /* defined(__FightPass__EquipForgeMsg__) */
