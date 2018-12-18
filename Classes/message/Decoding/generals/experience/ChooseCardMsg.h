//
//  ChooseCardMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/13.
//
//

#ifndef __FightPass__ChooseCardMsg__
#define __FightPass__ChooseCardMsg__

#include "../../MessageSendI.h"
class ChooseCardMsg:public MessageSendI
{
public:
    ChooseCardMsg(int cardId);
    ~ChooseCardMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__ChooseCardMsg__) */
