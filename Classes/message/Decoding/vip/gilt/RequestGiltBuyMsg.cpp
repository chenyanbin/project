//
//  RequestGiltBuyMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#include "RequestGiltBuyMsg.h"
RequestGiltBuyMsg::RequestGiltBuyMsg(int _viplevel)
:m_viplevel(_viplevel)
{
    
}
RequestGiltBuyMsg::~RequestGiltBuyMsg()
{
    
}
ByteStream* RequestGiltBuyMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_GIFT_GiftBuyReq);
    headBufferee->put(m_viplevel);
    SetMessageLength();
}