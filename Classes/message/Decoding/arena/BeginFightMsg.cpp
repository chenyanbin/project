//
//  BeginFightMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//

#include "BeginFightMsg.hpp"
BeginFightMsg::BeginFightMsg(int index)
:m_index(index)
{
    
}
BeginFightMsg::~ BeginFightMsg()
{
    
}
ByteStream *BeginFightMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaStartBattleReq);
    headBufferee->put(m_index);
    SetMessageLength();
}