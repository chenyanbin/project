//
//  RequestBsBuyListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#include "RequestBsBuyListMsg.h"
RequestBsBuyListMsg::RequestBsBuyListMsg(int shopId)
:m_shopId(shopId)
{
    
}
RequestBsBuyListMsg::~RequestBsBuyListMsg()
{
    
}
ByteStream* RequestBsBuyListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BLACK_BlackBuyReq);
    headBufferee->putInt(m_shopId);
    SetMessageLength();
}