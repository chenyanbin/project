//
//  LineupPageMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#ifndef __FightPass__LineupPageMsg__
#define __FightPass__LineupPageMsg__

#include "../../MessageSendI.h"
class LineupPageMsg:public MessageSendI
{
public:
    LineupPageMsg(int page);
    ~LineupPageMsg();
    ByteStream *encodingData();
private:
    int m_page;
};

#endif /* defined(__FightPass__LineupPageMsg__) */
