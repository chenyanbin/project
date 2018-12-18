//
//  MailCellMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
// 查看邮件

#ifndef __FightPass__MailCellMsg__
#define __FightPass__MailCellMsg__

#include "../MessageSendI.h"

class MailCellMsg:public MessageSendI
{
public:
    MailCellMsg(int _mailId);
    ~MailCellMsg();
    ByteStream *encodingData();
private:
    int m_mailId;
};

#endif /* defined(__FightPass__MailCellMsg__) */
