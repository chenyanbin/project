//
//  ShopBuyMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "ShopBuyMsg.h"
ShopBuyMsg:: ShopBuyMsg(int shop, int buyCount)
:m_shopId(shop)
,m_buyCount(buyCount)
{
    
}
ShopBuyMsg::~ ShopBuyMsg()
{
    
}
ByteStream * ShopBuyMsg::encodingData()
{
   
     MessageSendI::encodingData(SCENSE_CLIENT_SHOP_ShopBuyReq);
    headBufferee->putInt(m_shopId);
    headBufferee->putInt(m_buyCount);
    SetMessageLength();
}