//
//  ShopBuyMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__ShopBuyMsg__
#define __FightPass__ShopBuyMsg__

#include "../../../MessageSendI.h"
class ShopBuyMsg:public MessageSendI
{
public:
    ShopBuyMsg(int shopId, int buyCount);
    ~ShopBuyMsg();
    ByteStream *encodingData();
private:
    int m_shopId;
    int m_buyCount;
};

#endif /* defined(__FightPass__ShopBuyMsg__) */
