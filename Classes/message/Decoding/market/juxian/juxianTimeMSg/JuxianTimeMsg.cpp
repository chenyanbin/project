//
//  JuxianTimeMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "JuxianTimeMsg.h"

JuxianTimeMsg:: JuxianTimeMsg(int leadId, int countMode)
:m_leadId(leadId)
,m_countMode(countMode)
{
    
}
JuxianTimeMsg::~ JuxianTimeMsg()
{
    
}
ByteStream * JuxianTimeMsg::encodingData()
{

    MessageSendI::encodingData(SCENSE_CLIENT_LEAD_LeadReq);

    headBufferee->put(m_leadId);
    headBufferee->put(m_countMode);
    SetMessageLength();
}