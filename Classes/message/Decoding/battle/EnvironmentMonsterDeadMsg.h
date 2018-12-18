//
//  EnvironmentMonsterDeadMsg.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/9.
//环境怪死亡
//

#ifndef EnvironmentMonsterDeadMsg_hpp
#define EnvironmentMonsterDeadMsg_hpp

#include "../MessageSendI.h"
class EnvironmentMonsterDeadMsg:public MessageSendI
{
public:
    EnvironmentMonsterDeadMsg(int monsterid);
    ~EnvironmentMonsterDeadMsg();
    ByteStream *encodingData();
private:
    int m_monsterID;
};


#endif /* EnvironmentMonsterDeadMsg_hpp */
