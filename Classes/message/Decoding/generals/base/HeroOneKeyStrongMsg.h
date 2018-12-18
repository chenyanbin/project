//
//  HeroOneKeyStrongMsg.hpp
//  FightPass
//
//  Created by 超 顾 on 16/1/4.
//
//

#ifndef HeroOneKeyStrongMsg_h
#define HeroOneKeyStrongMsg_h

#include "../../MessageSendI.h"
class HeroOneKeyStrongMsg:public MessageSendI
{
public:
    HeroOneKeyStrongMsg(int cardId);
    ~HeroOneKeyStrongMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* HeroOneKeyStrongMsg_h */
