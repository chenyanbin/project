//
//  MailReceiveAllMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailReceiveAllMsg.h"
MailReceiveAllMsg::MailReceiveAllMsg()
{
    
}
MailReceiveAllMsg::~MailReceiveAllMsg()
{
    
}
ByteStream* MailReceiveAllMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_MAIL_MailReceiveAllItemReq);
    SetMessageLength();
}