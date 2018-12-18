//
//  MarketFindExtendMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/31.
//
//

#include "MarketFindExtendMsg.h"
MarketFindExtendMsg:: MarketFindExtendMsg()
{
    
}
MarketFindExtendMsg::~ MarketFindExtendMsg()
{
    
}
ByteStream * MarketFindExtendMsg::encodingData()
{
   
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindExtendReq);
    SetMessageLength();
}