//
//  FirstRechargeLingquMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#ifndef __FightPass__FirstRechargeLingquMsg__
#define __FightPass__FirstRechargeLingquMsg__

#include "../MessageSendI.h"
class FirstRechargeLingquMsg:public MessageSendI
{
public:
    FirstRechargeLingquMsg();
    ~ FirstRechargeLingquMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__FirstRechargeLingquMsg__) */
