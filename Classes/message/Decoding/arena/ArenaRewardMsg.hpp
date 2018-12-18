//
//  ArenaRewardMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/4/5.
//领取奖励
//

#ifndef ArenaRewardMsg_hpp
#define ArenaRewardMsg_hpp

#include "../MessageSendI.h"
class ArenaRewardMsg:public MessageSendI
{
public:
    ArenaRewardMsg();
    ~ArenaRewardMsg();
    ByteStream *encodingData();

};

#endif /* ArenaRewardMsg_hpp */
