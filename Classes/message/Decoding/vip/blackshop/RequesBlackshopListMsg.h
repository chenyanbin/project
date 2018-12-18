//
//  RequesBlackshopListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
// 黑市

#ifndef __FightPass__RequesBlackshopListMsg__
#define __FightPass__RequesBlackshopListMsg__

#include "../../MessageSendI.h"
class RequesBlackshopListMsg:public MessageSendI
{
public:
    RequesBlackshopListMsg(int refresh, int free);
    ~RequesBlackshopListMsg();
    ByteStream *encodingData();
private:
    int m_refresh;//是否刷新
    int m_free;//是否免费刷新
};

#endif /* defined(__FightPass__RequesBlackshopListMsg__) */
