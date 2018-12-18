//
//  MailMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/9.
//
//

#include "MailMsg.h"
MailMsg::MailMsg()
{
    
}
MailMsg::~MailMsg()
{
    
}
ByteStream* MailMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MAIL_MailPageReq);
//    headBufferee->put(m_function);
    
    SetMessageLength();
}