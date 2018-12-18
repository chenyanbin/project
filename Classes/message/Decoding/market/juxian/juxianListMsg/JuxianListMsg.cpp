//
//  JuxianListMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "JuxianListMsg.h"
JuxianListMsg:: JuxianListMsg()
{
    
}
JuxianListMsg::~ JuxianListMsg()
{
    
}
ByteStream * JuxianListMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEAD_LeadPageReq);
    SetMessageLength();
}