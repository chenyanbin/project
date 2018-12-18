//
//  SureSellMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__SureSellMsg__
#define __FightPass__SureSellMsg__

#include "../../../../MessageSendI.h"
class SureSellMsg:public MessageSendI
{
public:
    SureSellMsg(int itemType, int itemId, int sellCount,int price);
    ~SureSellMsg();
    ByteStream *encodingData();
private:
    int m_itemType;//物品类型
    int m_itemId;//物品id
    int m_sellCount;//卖出数量
    int m_price;//卖出价格
};

#endif /* defined(__FightPass__SureSellMsg__) */
