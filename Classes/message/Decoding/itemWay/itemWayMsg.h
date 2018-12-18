//
//  itemWayMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/10.
//
//

#ifndef __FightPass__itemWayMsg__
#define __FightPass__itemWayMsg__

#include "../MessageSendI.h"

class itemWayMsg:public MessageSendI
{
public:
    itemWayMsg(int itemType,int itemId,int itemQuality);
    ~itemWayMsg();
    ByteStream *encodingData();
private:
    int _itemType;
    int _itemId;
    int _itemQuality;
    
};

#endif /* defined(__FightPass__itemWayMsg__) */
