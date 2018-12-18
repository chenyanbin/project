//
//  HeroAddExpMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/7.
//
//

#include "HeroAddExpMsg.hpp"
HeroAddExpMsg::HeroAddExpMsg(int heroID)
:m_heroID(heroID)
{
    
}
HeroAddExpMsg::~HeroAddExpMsg()
{
    
}
ByteStream *HeroAddExpMsg::encodingData()
{
     MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroAddExpReq);
    headBufferee->putInt(m_heroID);
    SetMessageLength();
}