//
//  SkillEffect.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/16.
//
//

#include "SkillEffect.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/ImagePath.h"
#include "../data/BattleDefine.h"
SkillEffect::SkillEffect()
:_armature(NULL)
,m_name("")
,m_actionAttackCallBack(NULL)
,m_actionMovementCallBack(NULL)
,m_isPlayOver(false)
,m_offPosY(0)
,m_isLoop(false)
{
    
}
SkillEffect::~SkillEffect()
{
    m_isPlayOver = true;
    m_name.clear();
    _armature = NULL;
    m_actionAttackCallBack = NULL;
    m_actionMovementCallBack = NULL;
}
bool SkillEffect::init(const char* _name,float offPosY,bool isLoop )
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        m_name = _name;
        m_offPosY = offPosY;
        this->m_isLoop = isLoop;
        if(!ArmatureDataManager::getInstance()->getAnimationData(m_name))
        {
            const char* path = PublicShowUI::getAvatarPath(IMG_SKILL_EFFECT, _name);
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
            ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        }
              
        setArmature();
        bref = true;
    } while (false);
    return bref;
}
SkillEffect* SkillEffect::create(const char* _name,float offPosY,bool isLoop )
{
    SkillEffect* effect = new SkillEffect();
    if(effect && effect->init(_name,offPosY,isLoop))
    {
        effect->autorelease();
        return effect;
    }
    CC_SAFE_DELETE(effect);
    effect = NULL;
    return effect;
}
void SkillEffect::pauseAnimation()
{
    if(_armature)
    {
        _armature->getAnimation()->pause();
    }
}
void SkillEffect::playAnimation()
{
    if(_armature)
    {
         m_isPlayOver = false;
        _armature->getAnimation()->playWithIndex(0,-1,0);
    }
}
void SkillEffect::setArmature()
{
    if(!ArmatureDataManager::getInstance()->getAnimationData(m_name))
    {
        log("没有这个技能资源＝＝%s",m_name.c_str());
        m_isPlayOver = true;
       
        DelayTime* delay = DelayTime::create(.2);
        RemoveSelf* remove = RemoveSelf::create();
        this->runAction(Sequence::create(delay,remove, NULL));
        return;
    }
    this->_armature = Armature::create(m_name.c_str());
    if(_armature)
    {
        _armature->unscheduleUpdate();
        _armature->setAnchorPoint(Point::ZERO);
        _armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(SkillEffect::onMovementEvent, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        _armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(SkillEffect::onFrameEvent, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        this->addChild(_armature);
        this->setContentSize(_armature->getContentSize());
        _armature->setPositionY(m_offPosY);
    }
    
}
void SkillEffect::onMovementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if(movementType != LOOP_COMPLETE && movementType != COMPLETE)
        return;
    m_isPlayOver = true;

    if(m_actionMovementCallBack)
    {
        m_actionMovementCallBack(this);
    }
    if(m_isLoop)
    {
        this->playAnimation();
    }
    else
    {
        armature->pause();
    }
}
void SkillEffect::onFrameEvent(Bone *bone, const std::string& evt, int origin, int current)
{
    if(evt == SKILL_ATTACK_EVENT)
    {
        if(this->m_actionAttackCallBack)
        {
            this->m_actionAttackCallBack(this);
        }
    }
    
}
bool SkillEffect::isPlayOver()
{
    return m_isPlayOver;
}
void SkillEffect::onEnter()
{
    Node::onEnter();
}
void SkillEffect::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    playAnimation();
}
void SkillEffect::onExit()
{
    Node::onExit();
     m_isPlayOver = true;
}
void SkillEffect::onExitTransitionDidStart()
{
    m_isPlayOver = true;
    Node::onExitTransitionDidStart();
    m_actionAttackCallBack = NULL;
    if(_armature)
    {
         _armature->pause();
    }
   
}