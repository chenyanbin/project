//
//  BattleEatBloodMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/22.
//
//

#ifndef BattleEatBloodMsg_hpp
#define BattleEatBloodMsg_hpp

#include "../MessageSendI.h"

class BattleEatBloodMsg:public MessageSendI
{
public:
    BattleEatBloodMsg(int count);
    ~BattleEatBloodMsg();
    ByteStream *encodingData();
private:
    int m_count;
};
#endif /* BattleEatBloodMsg_hpp */
