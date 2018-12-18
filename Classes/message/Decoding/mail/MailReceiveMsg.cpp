//
//  MailReceiveMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailReceiveMsg.h"
MailReceiveMsg::MailReceiveMsg(int _mailId)
:m_mailId(_mailId)
{
    
}
MailReceiveMsg::~MailReceiveMsg()
{
    
}
ByteStream* MailReceiveMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MAIL_MailReceiveItemReq);
    headBufferee->putInt(m_mailId);
    
    SetMessageLength();
}