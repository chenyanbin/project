//
//  HeroUpStarMsg.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#include "HeroUpStarMsg.hpp"
HeroUpStarMsg::HeroUpStarMsg(int heroId)
:m_heroID(heroId)
{
    
}
HeroUpStarMsg::~HeroUpStarMsg()
{
    
}
ByteStream *HeroUpStarMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_HERO_HeroStarUpReq);
    headBufferee->putInt(m_heroID);
    SetMessageLength();
}