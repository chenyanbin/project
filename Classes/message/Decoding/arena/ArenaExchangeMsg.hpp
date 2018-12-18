//
//  ArenaExchangeMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/21.
//
// 荣誉商店

#ifndef ArenaExchangeMsg_hpp
#define ArenaExchangeMsg_hpp


#include "../MessageSendI.h"
class ArenaExchangeMsg:public MessageSendI
{
public:
    ArenaExchangeMsg(int _refresh);
    ~ ArenaExchangeMsg();
    ByteStream *encodingData();
private:
    int m_refresh;
};


#endif /* ArenaExchangeMsg_hpp */
