//
//  BeginFightMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//

#ifndef BeginFightMsg_hpp
#define BeginFightMsg_hpp

#include "../MessageSendI.h"
class BeginFightMsg:public MessageSendI
{
public:
    BeginFightMsg(int inex);
    ~ BeginFightMsg();
    ByteStream *encodingData();
private:
    int m_index;
};

#endif /* BeginFightMsg_hpp */
