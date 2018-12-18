//
//  FindChoseFinderMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//

#include "FindChoseFinderMsg.h"
FindChoseFinderMsg:: FindChoseFinderMsg(int findId, int heroId)
:m_findId(findId)
,m_heroId(heroId)
{
    
}
FindChoseFinderMsg::~ FindChoseFinderMsg()
{
    
}
ByteStream * FindChoseFinderMsg::encodingData()
{
 
    MessageSendI::encodingData(SCENSE_CLIENT_FIND_FindHeroSelReq);
    headBufferee->putInt(m_findId);
    headBufferee->putInt(m_heroId);
    SetMessageLength();
}