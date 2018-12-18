//
//  RequestSetupMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/22.
//
//

#include "RequestSetupMsg.h"
RequestSetupMsg::RequestSetupMsg(string _name)
:m_name(_name)
{
    
}
RequestSetupMsg::~RequestSetupMsg()
{
    
}
ByteStream* RequestSetupMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ACCOUNT_SetRolenameReq);
    headBufferee->putUTF8(m_name.c_str());
    SetMessageLength();
}