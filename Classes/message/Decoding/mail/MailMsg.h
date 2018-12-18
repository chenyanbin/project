//
//  MailMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/9.
//
// 邮件列表

#ifndef __FightPass__MailMsg__
#define __FightPass__MailMsg__

#include "../MessageSendI.h"

class MailMsg:public MessageSendI
{
public:
    MailMsg();
    ~MailMsg();
    ByteStream *encodingData();

};


#endif /* defined(__FightPass__MailMsg__) */
