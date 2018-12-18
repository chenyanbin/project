//
//  ArenaChageListMsg.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/23.
//
// 换一组

#ifndef ArenaChageListMsg_hpp
#define ArenaChageListMsg_hpp

#include "../MessageSendI.h"
class ArenaChageListMsg:public MessageSendI
{
public:
    ArenaChageListMsg();
    ~ ArenaChageListMsg();
    ByteStream *encodingData();
private:

};

#endif /* ArenaChageListMsg_hpp */
