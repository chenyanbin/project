//
//  AuctionShangjiaMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__AuctionShangjiaMsg__
#define __FightPass__AuctionShangjiaMsg__

#include "../../../MessageSendI.h"
class AuctionShangjiaMsg:public MessageSendI
{
public:
    AuctionShangjiaMsg(int lastMarketGoodsId);
    ~ AuctionShangjiaMsg();
    ByteStream *encodingData();
private:
    int m_lastMarketGoodsId;
    
};


#endif /* defined(__FightPass__AuctionShangjiaMsg__) */
