//
//  AuctionSellMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__AuctionSellMsg__
#define __FightPass__AuctionSellMsg__

#include "../../../MessageSendI.h"
class AuctionSellMsg:public MessageSendI
{
public:
    AuctionSellMsg(int lastMarketGoodsId);
    ~AuctionSellMsg();
    ByteStream *encodingData();
    
private:
    int m_lastMarketGoodsId;
};

#endif /* defined(__FightPass__AuctionSellMsg__) */
