//
//  MailReceiveMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
// 领取邮件物品

#ifndef __FightPass__MailReceiveMsg__
#define __FightPass__MailReceiveMsg__

#include "../MessageSendI.h"

class MailReceiveMsg:public MessageSendI
{
public:
    MailReceiveMsg(int _mailId);
    ~MailReceiveMsg();
    ByteStream *encodingData();
private:
    int m_mailId;
};


#endif /* defined(__FightPass__MailReceiveMsg__) */
