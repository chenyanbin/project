//
//  JuxianListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__JuxianListMsg__
#define __FightPass__JuxianListMsg__

#include "../../../MessageSendI.h"
class JuxianListMsg:public MessageSendI
{
public:
    JuxianListMsg();
    ~JuxianListMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__JuxianListMsg__) */
