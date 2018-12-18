//
//  MarketFindPageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/31.
//
//

#include "MarketFindPageMsg.h"
#include "../../../../commonData/GlobalInfo.h"

 MarketFindPageMsg:: MarketFindPageMsg()
{
    
}
 MarketFindPageMsg::~ MarketFindPageMsg()
{
    
}
ByteStream * MarketFindPageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindPageReq);

    SetMessageLength();
}