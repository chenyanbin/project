//
//  FamouseEndBattle.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseEndBattle.hpp"
FamouseEndBattle::FamouseEndBattle(int isSuc,int bossID,int damage,int usedBloodBottle)
:m_isSuc(isSuc)
,m_bossID(bossID)
,m_damage(damage)
,m_usedBloodBottle(usedBloodBottle)
{
    
}
FamouseEndBattle::~FamouseEndBattle()
{
    
}
ByteStream *FamouseEndBattle::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_LEGEND_LegendEndBattleReq);

    headBufferee->put(m_isSuc);
    headBufferee->putInt(m_bossID);
    headBufferee->putInt(m_damage);
    headBufferee->putInt(m_usedBloodBottle);
    SetMessageLength();
    
}