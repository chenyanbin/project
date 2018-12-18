//
//  JuxianTimeMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__JuxianTimeMsg__
#define __FightPass__JuxianTimeMsg__

#include "../../../MessageSendI.h"
class JuxianTimeMsg:public MessageSendI
{
public:
    JuxianTimeMsg(int leadId, int countMode);
    ~JuxianTimeMsg();
    ByteStream *encodingData();
private:
    int m_leadId;
    int m_countMode;
};

#endif /* defined(__FightPass__JuxianTimeMsg__) */
