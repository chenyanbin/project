//
//  SureXiajiaMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__SureXiajiaMsg__
#define __FightPass__SureXiajiaMsg__

#include <stdio.h>
#include "../../../../MessageSendI.h"
class SureXiajiaMsg:public MessageSendI
{
public:
    SureXiajiaMsg(int sellId);
    ~ SureXiajiaMsg();
    ByteStream *encodingData();
private:
    int m_sellId;
    
};

#endif /* defined(__FightPass__SureXiajiaMsg__) */
