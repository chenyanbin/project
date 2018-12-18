//
//  MailReceiveAllMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef __FightPass__MailReceiveAllMsg__
#define __FightPass__MailReceiveAllMsg__

#include "../MessageSendI.h"

class MailReceiveAllMsg:public MessageSendI
{
public:
    MailReceiveAllMsg();
    ~MailReceiveAllMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__MailReceiveAllMsg__) */
