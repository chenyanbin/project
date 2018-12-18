//
//  HeroPutOnMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/17.
//
//

#ifndef __FightPass__HeroPutOnMsg__
#define __FightPass__HeroPutOnMsg__

#include "../../MessageSendI.h"
class HeroPutOnMsg:public MessageSendI
{
public:
    HeroPutOnMsg(int herId,int slot,int equitId);
    ~HeroPutOnMsg();
    ByteStream *encodingData();
private:
    int _herId;
    int _slot;
    int _equitId;
};

#endif /* defined(__FightPass__HeroPutOnMsg__) */
