//
//  HeroOneKeyPutOnMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/27.
//
//

#ifndef __FightPass__HeroOneKeyPutOnMsg__
#define __FightPass__HeroOneKeyPutOnMsg__

#include "../../MessageSendI.h"
class HeroOneKeyPutOnMsg:public MessageSendI
{
public:
    HeroOneKeyPutOnMsg(int cardId);
    ~HeroOneKeyPutOnMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};
#endif /* defined(__FightPass__HeroOneKeyPutOnMsg__) */
