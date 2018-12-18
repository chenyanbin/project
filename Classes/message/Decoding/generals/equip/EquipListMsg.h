//
//  EquipListMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/1.
//
//

#ifndef __FightPass__EquipListMsg__
#define __FightPass__EquipListMsg__

#include "../../MessageSendI.h"
class EquipListMsg:public MessageSendI
{
public:
    EquipListMsg();
    ~EquipListMsg();
    ByteStream *encodingData();
    
};
#endif /* defined(__FightPass__EquipListMsg__) */
