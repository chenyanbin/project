//
//  BlockMonster.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/1.
//
//
#include "BlockMonster.h"
BlockMonster::BlockMonster()
{
}
BlockMonster::~BlockMonster()
{
}
bool BlockMonster::init(int monsterID)
{
    bool bref = false;
    do
    {
        CC_BREAK_IF(!Monster::init(monsterID));
        this->_walkSpeed = 0;
        bref = true;
    } while (false);
    return bref;
}
BlockMonster* BlockMonster::create(int monsterID)
{
    BlockMonster* monster = new BlockMonster();
    if(monster && monster->init(monsterID))
    {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    monster = NULL;
    return NULL;
}
void BlockMonster::updatePositon(float dt)
{
//    log("BlockMonsterBlockMonster");
}
void BlockMonster::hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack)
{
    if(this->getActionState() == kActionStateDead)
    {
        return;
    }
    showBloodMinus(damage,isCrit,isBlock,isSkillAttack);
    this->getAvatarProp()->health -= damage;
    if(m_avatar && this->getActionState() != kActionStateDead)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_HURT1))
        {
            m_avatar->getAnimation()->play(AN_HURT1);
            this->setActionState(kActionStateHurt);
        }
        else if(m_avatar->getAnimation()->getAnimationData()->getMovement("Hurt"))
        {
            m_avatar->getAnimation()->play("Hurt");
            this->setActionState(kActionStateHurt);
        }
        
    }
    
    _velocity = Point::ZERO;
    if(this->getAvatarProp()->health <= 0 && _actionState != kActionStateDead)
    {
        this->dead();
    }
}
void BlockMonster::onBuff(int buffID,double damage)
{
//    log("lskdfjk");
}
void BlockMonster::knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击倒
{
    hurtWithDamage(damage,isCrit,isBlock,isSkillAttack);
}
void BlockMonster::knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击飞
{
     hurtWithDamage(damage,isCrit,isBlock,isSkillAttack);
}
void BlockMonster::knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack)//击退
{
     hurtWithDamage(damage,isCrit,isBlock,isSkillAttack);
}
void BlockMonster::idle()
{
    if(this->getAvatarProp()->health != this->_totalHitPoints || this->getAvatarProp()->health <= 0)
    {
        return;
    }
    Monster::idle();
}
void BlockMonster::updateShadow()
{
    //不显示影子
}
