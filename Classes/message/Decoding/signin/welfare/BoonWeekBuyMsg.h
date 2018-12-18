//
//  BoonWeekBuyMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/12/4.
//
// 每周福利领取

#ifndef __FightPass__BoonWeekBuyMsg__
#define __FightPass__BoonWeekBuyMsg__

#include "../../MessageSendI.h"
class BoonWeekBuyMsg:public MessageSendI
{
public:
    BoonWeekBuyMsg(int _vip);
    ~BoonWeekBuyMsg();
    ByteStream *encodingData();
private:
    int m_vip;
};


#endif /* defined(__FightPass__BoonWeekBuyMsg__) */
