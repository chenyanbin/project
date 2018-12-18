//
//  FindStartMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindStartMsg.h"
FindStartMsg:: FindStartMsg(int findId, int honor)
:m_findId(findId)
,m_honor(honor)
{
    
}
FindStartMsg::~ FindStartMsg()
{
    
}
ByteStream * FindStartMsg::encodingData()
{
    
     MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindStartReq);
    headBufferee->putInt(m_findId);
    headBufferee->putInt(m_honor);
     SetMessageLength();
}