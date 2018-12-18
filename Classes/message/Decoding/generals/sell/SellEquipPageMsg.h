//
//  SellEquipPageMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#ifndef __FightPass__SellEquipPageMsg__
#define __FightPass__SellEquipPageMsg__

#include "../../MessageSendI.h"
class SellEquipPageMsg:public MessageSendI
{
public:
    SellEquipPageMsg();
    ~SellEquipPageMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__SellEquipPageMsg__) */
