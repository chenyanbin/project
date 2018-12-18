//
//  PropertyMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/10.
//
//

#ifndef __FightPass__PropertyMsg__
#define __FightPass__PropertyMsg__

#include "../../MessageSendI.h"
class PropertyMsg:public MessageSendI
{
public:
    PropertyMsg(int cardId);
    ~PropertyMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};


#endif /* defined(__FightPass__PropertyMsg__) */
