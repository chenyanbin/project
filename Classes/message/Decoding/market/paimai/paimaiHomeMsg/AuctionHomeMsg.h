//
//  AuctionHomeMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__AuctionHomeMsg__
#define __FightPass__AuctionHomeMsg__

#include "../../../MessageSendI.h"
class AuctionHomeMsg:public MessageSendI
{
public:
    AuctionHomeMsg(const char* _itemName,int lastSellId);
    ~AuctionHomeMsg();
    ByteStream *encodingData();
private:
    const char* itemName;
    int m_lastSellId;
};

#endif /* defined(__FightPass__AuctionHomeMsg__) */
