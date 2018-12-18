//
//  FirstRechargeMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/11/19.
//
//

#ifndef __FightPass__FirstRechargeMsg__
#define __FightPass__FirstRechargeMsg__

#include "../MessageSendI.h"
class FirstRechargeMsg:public MessageSendI
{
public:
    FirstRechargeMsg();
    ~FirstRechargeMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__FirstRechargeMsg__) */
