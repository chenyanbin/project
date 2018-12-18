//
//  ArenaBattleEndMsg.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//竞技场战斗结束
//

#ifndef ArenaBattleEndMsg_hpp
#define ArenaBattleEndMsg_hpp

#include "../MessageSendI.h"
class ArenaBattleEndMsg:public MessageSendI
{
public:
    ArenaBattleEndMsg(bool isSuc ,int roleID);
    ~ArenaBattleEndMsg();
    ByteStream *encodingData();
private:
    int m_roleID;
    bool m_isSuc;
};

#endif /* ArenaBattleEndMsg_hpp */
