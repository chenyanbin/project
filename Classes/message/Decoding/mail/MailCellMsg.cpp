//
//  MailCellMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailCellMsg.h"
MailCellMsg::MailCellMsg(int _mailId)
:m_mailId(_mailId)
{
    
}
MailCellMsg::~MailCellMsg()
{
    
}
ByteStream* MailCellMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MAIL_MailContentReq);
        headBufferee->putInt(m_mailId);
    
    SetMessageLength();
}