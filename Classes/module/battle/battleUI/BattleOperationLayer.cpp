//
//  BattleOperationLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/11.
//
//

#include "BattleOperationLayer.hpp"
#include "../../../protocol/UserCustomEvent.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
BattleOperationLayer::BattleOperationLayer()
{
    
}
BattleOperationLayer::~BattleOperationLayer()
{
    
}
bool BattleOperationLayer::init()
{
    this->setClickEnabled(true);
    this->setBackground(IMG_NEWGUIDE_FIRSTGAME);
    
    return true;
}

bool BattleOperationLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void BattleOperationLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void BattleOperationLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    broadMsg(CUSTOM_MONSTER_TALK_END);
    NewPlayerGuild::getInstance()->start();
    this->removeFromParent();
}