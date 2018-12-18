//
//  FindUserMessageMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/28.
//
//

#include "FindUserMessageMsg.hpp"
FindUserMessageMsg::FindUserMessageMsg(int idType,long roleId)
:m_idType(idType)
,m_roleid(roleId)
{
    
}
FindUserMessageMsg::~ FindUserMessageMsg()
{
    
}
ByteStream *FindUserMessageMsg::encodingData()
{
    
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaLookUpRoleInfoReq);
    headBufferee->put(m_idType);
    headBufferee->putLong(m_roleid);
    SetMessageLength();
}