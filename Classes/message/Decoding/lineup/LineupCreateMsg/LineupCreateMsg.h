//
//  LineupCreateMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/15.
//
//

#ifndef __FightPass__LineupCreateMsg__
#define __FightPass__LineupCreateMsg__
#include "../../MessageSendI.h"
class LineupCreateMsg:public MessageSendI
{
public:
    LineupCreateMsg();
    ~LineupCreateMsg();
    ByteStream *encodingData();
};

#endif /* defined(__FightPass__LineupCreateMsg__) */
