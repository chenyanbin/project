//
//  FindStartMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef __FightPass__FindStartMsg__
#define __FightPass__FindStartMsg__

#include "../../MessageSendI.h"
class FindStartMsg:public MessageSendI
{
public:
    FindStartMsg(int findid, int honor);
    ~FindStartMsg();
    ByteStream *encodingData();
private:
    int m_findId;
    int m_honor;//军工
};

#endif /* defined(__FightPass__FindStartMsg__) */
