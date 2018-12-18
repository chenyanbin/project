//
//  ChooseEuipMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/10.
//
//

#ifndef __FightPass__ChooseEuipMsg__
#define __FightPass__ChooseEuipMsg__

#include "../../MessageSendI.h"
class ChooseEquipMsg:public MessageSendI
{
public:
    ChooseEquipMsg(int herId,int slot);
    ~ChooseEquipMsg();
    ByteStream *encodingData();
private:
    int _herId;
    int _slot;
};

#endif /* defined(__FightPass__ChooseEuipMsg__) */
