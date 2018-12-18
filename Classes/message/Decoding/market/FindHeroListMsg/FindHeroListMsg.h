//
//  FindHeroListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef __FightPass__FindHeroListMsg__
#define __FightPass__FindHeroListMsg__

#include "../../MessageSendI.h"
class FindHeroListMsg:public MessageSendI
{
public:
    FindHeroListMsg();
    ~FindHeroListMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__FindHeroListMsg__) */
