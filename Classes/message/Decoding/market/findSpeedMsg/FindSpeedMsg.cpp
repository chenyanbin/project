//
//  FindSpeedMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindSpeedMsg.h"
FindSpeedMsg:: FindSpeedMsg(int findId)
:m_findId(findId)
{
    
}
FindSpeedMsg::~ FindSpeedMsg()
{
    
}
ByteStream * FindSpeedMsg::encodingData()
{
 
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindSpeedUpReq);
    headBufferee->putInt(m_findId);
    SetMessageLength();
}