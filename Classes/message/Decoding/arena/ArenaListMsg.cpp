//
//  ArenaListMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/10.
//
//

#include "ArenaListMsg.hpp"
ArenaListMsg::ArenaListMsg(int isrefresh)
:m_isrefresh(isrefresh)
{
    
}
ArenaListMsg::~ArenaListMsg()
{
    
}
ByteStream *ArenaListMsg::encodingData()
{
  
    MessageSendI::encodingData(SCENSE_CLIENT_ARENA_ArenaPageReq);
    headBufferee->put(m_isrefresh);
    SetMessageLength();
}