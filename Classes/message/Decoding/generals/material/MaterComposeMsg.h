//
//  MaterComposeMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/9.
//
//

#ifndef __FightPass__MaterComposeMsg__
#define __FightPass__MaterComposeMsg__

#include "../../MessageSendI.h"
class MaterComposeMsg:public MessageSendI
{
public:
    MaterComposeMsg(int cardId);
    ~MaterComposeMsg();
    ByteStream *encodingData();
private:
    int _materId;
};

#endif /* defined(__FightPass__MaterComposeMsg__) */
