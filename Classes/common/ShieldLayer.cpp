//
//  ShieldLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-8-21.
//
//

#include "ShieldLayer.h"
ShieldLayer::ShieldLayer()
{
    
}
ShieldLayer::~ShieldLayer()
{
//    log("~ShieldLayer ~ShieldLayer ~ShieldLayer");
}
bool ShieldLayer::init()
{
    bool bref = false;
    do
    {
        CC_BREAK_IF(!BaseLayer::init());
        this->setClickEnabled(true);
        this->isAbleGuiding = false;
        bref = true;
    } while (false);
    return bref;
}

void ShieldLayer::onEnter()
{
    BaseLayer::onEnter();
    this->unschedule(schedule_selector(ShieldLayer::onDelay));
    this->schedule(schedule_selector(ShieldLayer::onDelay), .5);
}
void ShieldLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
    
}
void ShieldLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->unschedule(schedule_selector(ShieldLayer::onDelay));
}
void ShieldLayer::onDelay(float dt)
{
    this->unschedule(schedule_selector(ShieldLayer::onDelay));
    if(this->getParent())
    {
        this->removeFromParent();
    }
}