//
//  ArenaBattleEndMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#include "ArenaBattleEndMsg.hpp"
ArenaBattleEndMsg::ArenaBattleEndMsg(bool isSuc ,int roleID)
:m_roleID(roleID)
,m_isSuc(isSuc)
{
    
}
ArenaBattleEndMsg::~ArenaBattleEndMsg()
{
    
}
ByteStream *ArenaBattleEndMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaEndBattleReq);
    headBufferee->put(m_isSuc ? 1 : 2);
    headBufferee->put(m_roleID);
    SetMessageLength();
}