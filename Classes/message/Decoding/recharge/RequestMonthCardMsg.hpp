//
//  RequestMonthCardMsg.hpp
//  FightPass
//领取月卡奖励
//  Created by zhangxiaobin on 16/1/18.
//
//

#ifndef RequestMonthCardMsg_hpp
#define RequestMonthCardMsg_hpp

#include "../MessageSendI.h"

class RequestMonthCardMsg:public MessageSendI
{
public:
    RequestMonthCardMsg(int cardID);
    ~RequestMonthCardMsg();
    ByteStream *encodingData();
private:
    int m_cardID;
};

#endif /* RequestMonthCardMsg_hpp */
