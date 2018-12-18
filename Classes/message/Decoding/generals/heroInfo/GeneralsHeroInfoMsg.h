//
//  GeneralsHeroInfoMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#ifndef __FightPass__GeneralsHeroInfoMsg__
#define __FightPass__GeneralsHeroInfoMsg__

#include "../../MessageSendI.h"
class GeneralsHeroInfoMsg:public MessageSendI
{
public:
    GeneralsHeroInfoMsg(int cardId);
    ~GeneralsHeroInfoMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__GeneralsHeroInfoMsg__) */
