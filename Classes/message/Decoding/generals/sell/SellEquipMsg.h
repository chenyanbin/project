//
//  SellEquipMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#ifndef __FightPass__SellEquipMsg__
#define __FightPass__SellEquipMsg__

#include "../../../../module/generals/data/EquipDataManager.h"
#include "../../MessageSendI.h"
class SellEquipMsg:public MessageSendI
{
public:
    SellEquipMsg(Vector<BaseEquipData*> *list);
    ~SellEquipMsg();
    ByteStream *encodingData();
private:
    Vector<BaseEquipData*> *cardList;
};

#endif /* defined(__FightPass__SellEquipMsg__) */
