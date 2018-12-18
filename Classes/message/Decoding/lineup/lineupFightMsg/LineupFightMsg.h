//
//  LineupFightMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/22.
//
//

#ifndef __FightPass__LineupFightMsg__
#define __FightPass__LineupFightMsg__

#include "../../MessageSendI.h"
class LineupFightMsg:public MessageSendI
{
public:
    LineupFightMsg(int lineupNo);
    ~LineupFightMsg();
    ByteStream *encodingData();
private:
    int m_lineupNo;
};


#endif /* defined(__FightPass__LineupFightMsg__) */
