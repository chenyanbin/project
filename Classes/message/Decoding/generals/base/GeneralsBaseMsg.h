//
//  GeneralsBaseMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/8/7.
//
//

#ifndef __FightPass__GeneralsBaseMsg__
#define __FightPass__GeneralsBaseMsg__

#include "../../MessageSendI.h"
class GeneralsBaseMsg:public MessageSendI
{
public:
    GeneralsBaseMsg(int cardId);
    ~GeneralsBaseMsg();
    ByteStream *encodingData();
private:
    int _cardId;
};

#endif /* defined(__FightPass__GeneralsBaseMsg__) */
