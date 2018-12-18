//
//  LineupDownMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/14.
//
//下阵

#ifndef __FightPass__LineupDownMsg__
#define __FightPass__LineupDownMsg__


#include "../../MessageSendI.h"
class LineupDownMsg:public MessageSendI
{
public:
    LineupDownMsg(int lineupNo,int heroId);
    ~LineupDownMsg();
    ByteStream *encodingData();
private:
    int m_lineupNo;
    int m_heroId;
};

#endif /* defined(__FightPass__LineupDownMsg__) */
