//
//  LineupCountMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#ifndef __FightPass__LineupCountMsg__
#define __FightPass__LineupCountMsg__

#include "../../MessageSendI.h"
class LineupCountMsg:public MessageSendI
{
public:
    LineupCountMsg();
    ~LineupCountMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__LineupCountMsg__) */
