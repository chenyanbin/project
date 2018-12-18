//
//  RequestGiltMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//礼包

#ifndef __FightPass__RequestGiltMsg__
#define __FightPass__RequestGiltMsg__

#include "../../MessageSendI.h"
class RequestGiltMsg:public MessageSendI
{
public:
    RequestGiltMsg();
    ~RequestGiltMsg();
    ByteStream *encodingData();
private:
   
};


#endif /* defined(__FightPass__RequestGiltMsg__) */
