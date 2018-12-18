//
//  RequestRechargeOrder.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/16.
//
//

#ifndef RequestRechargeOrder_hpp
#define RequestRechargeOrder_hpp

#include "../MessageSendI.h"

class RequestRechargeOrder:public MessageSendI
{
public:
    RequestRechargeOrder(int chargeType,int goldPackID,int cardId,int userMoney);
    ~RequestRechargeOrder();
    ByteStream *encodingData();
private:
    int _chargeType;//RechargeType
    int _goldPackID;//元宝包id
    int _cardID;//月卡id
    int _userMoney;//单位：分
};

#endif /* RequestRechargeOrder_hpp */
