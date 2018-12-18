//
//  LineupSetLocationMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/14.
//
//调整武将位置

#ifndef __FightPass__LineupSetLocationMsg__
#define __FightPass__LineupSetLocationMsg__

#include "../../MessageSendI.h"
class LineupSetLocationMsg:public MessageSendI
{
public:
    LineupSetLocationMsg(int lineupNo, int heroId1, int heroId2,int heroId3);
    ~LineupSetLocationMsg();
    ByteStream *encodingData();
private:
    int m_lineupNo;
    int m_heroId1;
    int m_heroId2;
    int m_heroId3;
};

#endif /* defined(__FightPass__LineupSetLocationMsg__) */
