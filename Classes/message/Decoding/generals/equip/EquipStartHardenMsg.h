//
//  EquipStartHardenMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/7.
//
//

#ifndef __FightPass__EquipStartHardenMsg__
#define __FightPass__EquipStartHardenMsg__

#include "../../MessageSendI.h"
#include "../../../../module/generals/data/EquipDataManager.h"
class EquipStartHardenMsg:public MessageSendI
{
public:
    EquipStartHardenMsg(int cardId,bool bol);
    ~EquipStartHardenMsg();
    ByteStream *encodingData();
private:
    int _cardId;
    bool _bol;
    
};

#endif /* defined(__FightPass__EquipStartHardenMsg__) */
