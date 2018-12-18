//
//  RequestGiltMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#include "RequestGiltMsg.h"
RequestGiltMsg::RequestGiltMsg()
{
    
}
RequestGiltMsg::~RequestGiltMsg()
{
    
}
ByteStream* RequestGiltMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_GIFT_GiftPageReq);
    SetMessageLength();
}