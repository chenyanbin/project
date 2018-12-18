//
//  RequestEnterStageBattle.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#ifndef __FightPass__RequestEnterStageBattle__
#define __FightPass__RequestEnterStageBattle__

#include "../MessageSendI.h"
class RequestEnterStageBattle:public MessageSendI
{
public:
    RequestEnterStageBattle(int battleID);
    ~RequestEnterStageBattle();
    ByteStream *encodingData();
private:
    int m_battleID;
};

#endif /* defined(__FightPass__RequestEnterStageBattle__) */
