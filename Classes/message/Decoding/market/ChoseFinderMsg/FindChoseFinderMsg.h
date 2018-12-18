//
//  FindChoseFinderMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef __FightPass__FindChoseFinderMsg__
#define __FightPass__FindChoseFinderMsg__

#include "../../MessageSendI.h"
class FindChoseFinderMsg:public MessageSendI
{
public:
    FindChoseFinderMsg(int findid, int heroId);
    ~FindChoseFinderMsg();
    ByteStream *encodingData();
private:
    int m_findId;
    int m_heroId;
};

#endif /* defined(__FightPass__FindChoseFinderMsg__) */
