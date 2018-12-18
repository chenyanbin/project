//
//  RequestMarqueeMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/2.
//
//

#include "RequestMarqueeMsg.hpp"
RequestMarqueeMsg::RequestMarqueeMsg()
{
    
}
RequestMarqueeMsg::~RequestMarqueeMsg()
{
    
}
ByteStream* RequestMarqueeMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_MarqueePageReq);
    SetMessageLength();
}