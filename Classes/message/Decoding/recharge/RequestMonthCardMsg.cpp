//
//  RequestMonthCardMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/18.
//
//

#include "RequestMonthCardMsg.hpp"
RequestMonthCardMsg::RequestMonthCardMsg(int cardID)
:m_cardID(cardID)
{
    
}
RequestMonthCardMsg::~RequestMonthCardMsg()
{
    
}
ByteStream* RequestMonthCardMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_PAY_PayCardReceiveReq);
    headBufferee->put(m_cardID);
    SetMessageLength();
}