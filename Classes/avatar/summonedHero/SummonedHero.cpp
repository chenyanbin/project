//
//  SummonedHero.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/2.
//
//

#include "SummonedHero.h"
SummonedHero::SummonedHero()
:lifeTime(0)
{
    
}
SummonedHero::~SummonedHero()
{
    
}
bool SummonedHero::init(int heroID,int time)
{
    this->lifeTime = time;
    return Hero::init(heroID);
}
SummonedHero* SummonedHero::create(int heroID,int time)
{
    SummonedHero* hero = new SummonedHero();
    if(hero && hero->init(heroID,time))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    hero = NULL;
    return NULL;
}
void SummonedHero::idle()
{
    Hero::idle();
}
void SummonedHero::dead()
{
    log("ldslfj");
}
void SummonedHero::onEnter()
{
    Hero::onEnter();
    if(this->lifeTime > 0)
    {
        this->runAction(Sequence::create(DelayTime::create(lifeTime),CallFunc::create(CC_CALLBACK_0(SummonedHero::onDelay, this)), NULL));
    }
}
void SummonedHero::onDelay()
{
    PublicShowUI::broadUserMsg(CUSTOM_BATTLE_HERO_LIFETIME, this);
}
void SummonedHero::onExit()
{
     Hero::onExit();
}
bool SummonedHero::skill1()
{
     if(Hero::attack1())
     {
         this->_actionState = kActionStateSkill1;
          return true;
     }
   
     return false;
}
bool SummonedHero::skill2()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateSkill2;
        return true;
    }
    
    return false;
}
bool SummonedHero::skill3()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateSkill3;
        return true;
    }
    
    return false;
}
bool SummonedHero::skill4()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateSkill4;
        return true;
    }
    
    return false;
}
bool SummonedHero::attack1()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateAttack1;
        return true;
    }
    
    return false;
}
bool SummonedHero::attack2()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateAttack2;
        return true;
    }
    
    return false;
}
bool SummonedHero::attack3()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateAttack3;
        return true;
    }
    
    return false;
}
bool SummonedHero::attack4()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateAttack4;
        return true;
    }
    
    return false;
}
bool SummonedHero::attack5()
{
    if(Hero::attack1())
    {
        this->_actionState = kActionStateAttack5;
        return true;
    }
    
    return false;
}
void SummonedHero::onActionCompleted()
{
    switch (this->_actionState) {
        case kActionStateIdle:
            this->idle();
            break;
        case kActionStateWalk:
             this->idle();
            break;
            
        default:
            this->idle();
            break;
    }
}