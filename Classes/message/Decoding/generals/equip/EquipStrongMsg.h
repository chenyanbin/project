//
//  EquipStrongMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/1.
//
//

#ifndef __FightPass__EquipStrongMsg__
#define __FightPass__EquipStrongMsg__

#include "../../MessageSendI.h"
class EquipStrongMsg:public MessageSendI
{
public:
    EquipStrongMsg(int cardId);
    ~EquipStrongMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__EquipStrongMsg__) */
