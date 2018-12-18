//
//  RequestGiltBuyMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#ifndef __FightPass__RequestGiltBuyMsg__
#define __FightPass__RequestGiltBuyMsg__

#include "../../MessageSendI.h"
class RequestGiltBuyMsg:public MessageSendI
{
public:
    RequestGiltBuyMsg(int _viplevel);
    ~RequestGiltBuyMsg();
    ByteStream *encodingData();
private:
    int m_viplevel;//是否刷新
};

#endif /* defined(__FightPass__RequestGiltBuyMsg__) */
