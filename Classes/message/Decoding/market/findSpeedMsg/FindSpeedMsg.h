//
//  FindSpeedMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#ifndef __FightPass__FindSpeedMsg__
#define __FightPass__FindSpeedMsg__

#include "../../MessageSendI.h"
class FindSpeedMsg:public MessageSendI
{
public:
    FindSpeedMsg(int findid);
    ~FindSpeedMsg();
    ByteStream *encodingData();
private:
    int m_findId;
};

#endif /* defined(__FightPass__FindSpeedMsg__) */
