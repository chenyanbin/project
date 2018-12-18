//
//  MaterPageMsg.h
//  FightPass
//
//  Created by 超 顾 on 15/9/9.
//
//

#ifndef __FightPass__MaterPageMsg__
#define __FightPass__MaterPageMsg__

#include "../../MessageSendI.h"
class MaterPageMsg:public MessageSendI
{
public:
    MaterPageMsg();
    ~MaterPageMsg();
    ByteStream *encodingData();
    
};

#endif /* defined(__FightPass__MaterPageMsg__) */
