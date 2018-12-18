//
//  FindResultMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef __FightPass__FindResultMsg__
#define __FightPass__FindResultMsg__

#include "../../MessageSendI.h"
class FindResultMsg:public MessageSendI
{
public:
    FindResultMsg(int findid);
    ~FindResultMsg();
    ByteStream *encodingData();
private:
    int m_findId;
};

#endif /* defined(__FightPass__FindResultMsg__) */
