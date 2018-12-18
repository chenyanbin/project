//
//  MarketFindExtendMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/31.
//
//

#ifndef __FightPass__MarketFindExtendMsg__
#define __FightPass__MarketFindExtendMsg__

#include "../../MessageSendI.h"
class MarketFindExtendMsg:public MessageSendI
{
public:
    MarketFindExtendMsg();
    ~MarketFindExtendMsg();
    ByteStream *encodingData();

};

#endif /* defined(__FightPass__MarketFindExtendMsg__) */
