//
//  SureXiajiaMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "SureXiajiaMsg.h"
SureXiajiaMsg:: SureXiajiaMsg(int sellId)
:m_sellId(sellId)
{
    
}
SureXiajiaMsg::~ SureXiajiaMsg()
{
    
}
ByteStream * SureXiajiaMsg::encodingData()
{

    MessageSendI::encodingData(SCENSE_CLIENT_MARKET_MarketPullOffReq);

    headBufferee->putInt(m_sellId);
    SetMessageLength();
}