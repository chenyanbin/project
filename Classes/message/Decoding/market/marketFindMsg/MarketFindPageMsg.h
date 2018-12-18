//
//  MarketFindPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/31.
//
//

#ifndef __FightPass__MarketFindPageMsg__
#define __FightPass__MarketFindPageMsg__

#include "../../MessageSendI.h"
class MarketFindPageMsg:public MessageSendI
{
public:
    MarketFindPageMsg();
    ~MarketFindPageMsg();
    ByteStream *encodingData();

};

#endif /* defined(__FightPass__MarketFindPageMsg__) */
