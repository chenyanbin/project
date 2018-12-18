//
//  LineupSetRespMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/13.
//
//

#ifndef __FightPass__LineupSetRespMsg__
#define __FightPass__LineupSetRespMsg__

#include "../../MessageSendI.h"
class LineupSetRespMsg:public MessageSendI
{
public:
    LineupSetRespMsg(int lineupNo, int heroType, int location,int heroId);
    ~LineupSetRespMsg();
    ByteStream *encodingData();
private:
    int m_lineupNo;
    int m_heroType;
    int m_location;
    int m_heroId;
};

#endif /* defined(__FightPass__LineupSetRespMsg__) */
