//
//  BattleRebornMsg.hpp
//  FightPass
//战场复活
//  Created by zhangxiaobin on 15/10/22.
//
//

#ifndef BattleRebornMsg_hpp
#define BattleRebornMsg_hpp

#include "../MessageSendI.h"

class BattleRebornMsg:public MessageSendI
{
public:
    BattleRebornMsg(int count);
    ~BattleRebornMsg();
    ByteStream *encodingData();
private:
    int m_count;
};

#endif /* BattleRebornMsg_hpp */
