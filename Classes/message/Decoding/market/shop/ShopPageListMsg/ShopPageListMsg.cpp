//
//  ShopPageListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "ShopPageListMsg.h"

ShopPageListMsg:: ShopPageListMsg()
{
    
}
ShopPageListMsg::~ ShopPageListMsg()
{
    
}
ByteStream * ShopPageListMsg::encodingData()
{
 
     MessageSendI::encodingData(SCENSE_CLIENT_SHOP_ShopPageReq);
    SetMessageLength();
}