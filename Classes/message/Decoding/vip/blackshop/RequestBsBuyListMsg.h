//
//  RequestBsBuyListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
// 黑市购买

#ifndef __FightPass__RequestBsBuyListMsg__
#define __FightPass__RequestBsBuyListMsg__

#include "../../MessageSendI.h"
class RequestBsBuyListMsg:public MessageSendI
{
public:
    RequestBsBuyListMsg(int shopId);
    ~RequestBsBuyListMsg();
    ByteStream *encodingData();
private:
    int m_shopId;//是否刷新
};


#endif /* defined(__FightPass__RequestBsBuyListMsg__) */
