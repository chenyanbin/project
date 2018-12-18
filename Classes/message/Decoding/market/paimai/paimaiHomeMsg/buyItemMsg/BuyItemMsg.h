//
//  BuyItemMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__BuyItemMsg__
#define __FightPass__BuyItemMsg__

#include "../../../../MessageSendI.h"
class BuyItemMsg:public MessageSendI
{
public:
    BuyItemMsg(int SellId);
    ~ BuyItemMsg();
    ByteStream *encodingData();
private:
    int m_SellId;
};

#endif /* defined(__FightPass__BuyItemMsg__) */
