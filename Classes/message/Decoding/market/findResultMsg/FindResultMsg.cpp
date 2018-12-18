//
//  FindResultMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindResultMsg.h"
FindResultMsg:: FindResultMsg(int findId)
:m_findId(findId)
{
    
}
FindResultMsg::~ FindResultMsg()
{
    
}
ByteStream * FindResultMsg::encodingData()
{
   
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindResultReq);
    headBufferee->putInt(m_findId);
    SetMessageLength();
}