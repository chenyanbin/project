//
//  Avatar.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#include "Avatar.h"
#include "../common/ImagePath.h"
#include "../common/StringUtil.h"
#include "../commonData/dictData/DictBuff/DictBuffManager.h"
#include "../module/battle/data/MapDataManager.h"
#include "../module/battle/action/Shake.h"
#include "../common/GameConfig.h"
#include "../commonData/enum/DictBuffPointTypeEnum.h"
#include "../commonData/data/FormulaManager.h"
#include "../module/battleTest/PlayerDataManager.hpp"
Avatar::Avatar()
:m_avatar(NULL)
,_actionState(kActionStateNone)
,_preActionState(kActionStateNone)
,_taskState(kTaskStateNone)
,_delayState(kdelayStateNone)
,_weaponName("")
,_avatarName("")
,_frameEvent("")
,movementType(START)
,_wayNumber(0)
,_baseSpeed(0)
,m_resourceName("")
,_chanedBoneName("")
,m_isHolding(false)
,bloodContainer(NULL)
,isLeft(false)
,isCamreIn(false)
,m_actionFinishedCallBack(NULL)
,m_actionAttackCallBack(NULL)
,m_touchCallBack(NULL)
,m_uid(0)
,m_jumpAttackTime(0.2)
,m_avatarPosY(0)
,m_avatarPosX(0)
,TAG_SHADOWE(1)
,TAG_EFFECT(2)
,TAG_BUFFEFFECT(3)
,TAG_KNOCKBACK_ACTION(4)
,TAG_NAME(5)
,TAG_BLOCKACTION(6)
,TAG_BLOOD(7)
,TAG_BLOCKDELAY(8)
,TAG_SHIELD_BLOOD(9)
,_warningRange(0)
,_isInRoad(true)
,_isPause(false)
,_isDashing(false)
,_jumpHeight(256)
,_avatarProp(NULL)
,_baseAvatarProp(NULL)
,skillCDMap(NULL)
,_dashSkillID(0)
,_frameParam("")
,_avatarType(AVATAR_TYPE_NONE)
,_avatarTeam(AVATAR_TEAM_NONE)
,_enterWay(kEnterWayCommon)
,isBossShadow(false)
,flyAction(NULL)
,m_eventDispatcher(NULL)
,_totalHitPoints(0)
,isNewEnter(true)
,buffContainer(NULL)
,buffListMap(NULL)
,m_bloodPt(NULL)
,_isAbleJumpAttack(false)
,_blockStartTime(0)
,_acitonLoopTime(0)
,_followMainHeroDistance(0)
,_nextDecisionTime(0)
,_shieldBlood(0)
,trunter(NULL)
,_knockFlyCount(0)
,isShowBlood(false)
,aiID(0)
{
    skillCDMap = new map<int,long long>();
    buffListMap = new Map<int,BuffEffectData*>();
    MoveTo* moveby = MoveTo::create(.4, Point(m_avatarPosX,m_avatarPosY + _jumpHeight));
    MoveTo* moveDown = MoveTo::create(.4, Point(m_avatarPosX,m_avatarPosY));
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::onJumpEnded, this));

    flyAction = Sequence::create(moveby,moveDown,callBack, NULL);
    CC_SAFE_RETAIN(flyAction);
    
    auto delay = DelayTime::create(.5);
    auto pBlink = Blink::create(0.2f,2);
    auto deadBack = CallFunc::create(CC_CALLBACK_0(Avatar::onExitScene, this));
    auto remove = RemoveSelf::create();
    this->deadAction = Sequence::create(delay,pBlink, callBack,remove,NULL);
    CC_SAFE_RETAIN(deadAction);
    
//    Scheduler* scheduler = new Scheduler();
//    scheduler->autorelease();
//    this->setScheduler(scheduler);
}
Avatar::~Avatar()
{
    CC_SAFE_RELEASE_NULL(_avatarProp);
    CC_SAFE_RELEASE_NULL(_baseAvatarProp);
    if(m_avatar)
    {
        m_avatar->getAnimation()->setMovementEventCallFunc(NULL);
        m_avatar->getAnimation()->setFrameEventCallFunc(NULL);
        CC_SAFE_RELEASE_NULL(m_avatar);
    }
    m_resourceName.clear();
    _weaponName.clear();
    _frameEvent.clear();
   
    m_actionFinishedCallBack = NULL;
    m_actionAttackCallBack = NULL;
    m_touchCallBack = NULL;
    skillCDMap->clear();
    CC_SAFE_DELETE(skillCDMap);
    skillCDMap = NULL;
    CC_SAFE_RELEASE_NULL(flyAction);
    CC_SAFE_RELEASE_NULL(deadAction);
    clearBuff();
    CC_SAFE_DELETE(buffListMap);
    buffListMap =NULL;
    if(m_eventDispatcher)
    {
        _eventDispatcher->removeEventListener(m_eventDispatcher);
        CC_SAFE_RELEASE_NULL(m_eventDispatcher);
    }
    buffContainer = NULL;
}
bool Avatar::init(const std::string& name)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
     
        m_resourceName = name;
        
        
        buffContainer = Node::create();
        buffContainer->setAnchorPoint(Point(0,0));
        this->addChild(buffContainer,2);
        buffContainer->setCascadeColorEnabled(true);
        buffContainer->setCascadeOpacityEnabled(true);
        bloodContainer = Node::create();
        bloodContainer->setAnchorPoint(Point::ZERO);
        this->addChild(bloodContainer,3);
        buffIconContainer = Node::create();
        buffIconContainer->setAnchorPoint(Point::ZERO);
        this->addChild(buffIconContainer,4);
        bref = true;
    } while (false);
    return bref;
}


void Avatar::setUID(int ID)
{
    m_uid = ID;
}
int Avatar::getUID()
{
    return m_uid;
}
void Avatar::onEnterScene()//进入视野
{
    updateBlood();
    if(m_avatar)
    {
        return;
    }
    if(this->getAvatarProp() && this->getAvatarProp()->health <= 0)
    {
        this->dead();
        return;
    }
    
    isNewEnter = false;
    setAvatar();
    updateShadow();
  
}
void Avatar::onExitScene()//退出视野
{
    if(!m_avatar)
    {
        return;
    }
    hideShadow();
    if(m_avatar)
    {
        m_avatar->pause();
        this->m_avatar->setPositionY(m_avatarPosY);
        m_avatar->removeFromParent();
       
        m_avatar->getAnimation()->setMovementEventCallFunc(NULL);
        m_avatar->getAnimation()->setFrameEventCallFunc(NULL);
        CC_SAFE_RELEASE_NULL(m_avatar);
   
    }
    bloodContainer->removeAllChildren();
    if(this->getAvatarProp()->health < 0)
    {
        this->removeFromParent();
    }

}
void Avatar::setTouchEnabled(bool _enabled)
{
    if(_enabled)
    {
        if(m_eventDispatcher == NULL)
        {
            m_eventDispatcher = EventListenerTouchOneByOne::create();
            CC_SAFE_RETAIN(m_eventDispatcher);
            m_eventDispatcher->onTouchBegan = CC_CALLBACK_2(Avatar::onTouchBegan, this);
            m_eventDispatcher->onTouchMoved = CC_CALLBACK_2(Avatar::onTouchMoved, this);
            m_eventDispatcher->onTouchEnded = CC_CALLBACK_2(Avatar::onTouchEnded, this);
            _eventDispatcher->setPriority(m_eventDispatcher, 0);
            m_eventDispatcher->setSwallowTouches(false);
        }
        _eventDispatcher->removeEventListener(m_eventDispatcher);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventDispatcher, this);
    }
    else
    {
        if(m_eventDispatcher)
        {
            _eventDispatcher->removeEventListener(m_eventDispatcher);
        }
    }
    
    
}
bool Avatar::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void Avatar::onTouchMoved(Touch *touch, Event *unused_event)
{
}
void Avatar::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(!m_avatar)
    {
        return;
    }
    Point point = touch->getLocation();
    point = this->convertToNodeSpace(point);
 
    Rect rect = PublicShowUI::getRect(this->m_avatar);
    if(rect.containsPoint(point))
    {
        if(m_touchCallBack)
        {
            m_touchCallBack(this);
        }
    }
}
void Avatar::showName()
{
    Node* nameBg = (Node*)this->getChildByTag(TAG_NAME);
    if(nameBg)
    {
        Label* label = (Label*)nameBg->getChildByTag(TAG_NAME);
        label->setString(this->_avatarName);
    }
    else
    {
        nameBg = Sprite::create(IMG_PUBLIC_AVATARNAMMEBG);
        nameBg->setAnchorPoint(Point(.5,0));
//        _avatarName = StringUtil::replace(_avatarName, "", "  ");
        Label* label = PublicShowUI::getLabel(_avatarName.c_str(),PublicShowUI::getColor3b(COLOR_NPC_NAME),24,false,false);
        label->setAnchorPoint(Point(0,0));
        if(m_avatar)
        {
            label->setPosition((nameBg->getContentSize().width - label->getContentSize().width)/2, (nameBg->getContentSize().height - label->getContentSize().height)/2);
            nameBg->addChild(label,1,TAG_NAME);
            nameBg->setPosition(0, m_avatar->getPositionY() + m_avatar->getContentSize().height);
            this->addChild(nameBg,10,TAG_NAME);
        }
       
    }
}
void Avatar::setAvatar()
{
    
//  AnimationData *animationData = armatureDataManager->getAnimationData(name)
    AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData(m_resourceName);
    if(!animationData)
    {
    
        const char* path = PublicShowUI::getAvatarPath(AVATAR_ANIMATION_PATH, m_resourceName.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        // 连接该骨骼动画的资源
        ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        animationData = ArmatureDataManager::getInstance()->getAnimationData(m_resourceName);
       if(!animationData)
       {
           log("没这个人物资源");
           return;
       }
    }
    
    if(m_avatar)
    {
        m_avatar->stopAllActions();
        m_avatar->removeFromParent();
        CC_SAFE_RELEASE_NULL(m_avatar);
        
    }
 
    this->m_avatar = Armature::create(m_resourceName.c_str());
    this->_actionState = kActionStateNone;
    this->setContentSize(m_avatar->getContentSize());
    m_avatar->setAnchorPoint(Point(.5,0));

    CC_SAFE_RETAIN(m_avatar);
    
    m_avatar->setPosition(m_avatarPosX, m_avatarPosY);
    this->addChild(m_avatar,1);
    m_avatar->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Avatar::onMovementEvent, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    m_avatar->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Avatar::onFrameEvent, this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    originColor = m_avatar->getColor();
    
    this->_isInRoad = true;
    this->idle();
    _delayState = kdelayStateNone;

    
   
}
void Avatar::updateShadow()
{

    if(this->getChildByTag(TAG_SHADOWE))
    {
        this->removeChildByTag(TAG_SHADOWE);
    }
    if(isBossShadow)
    {
        updateBossShadow();
    }
    else
    {
        Sprite* shadow = Sprite::create(IMG_PUBLIC_SHADOW);
        shadow->setAnchorPoint(Point(0.5,0.5));
        this->addChild(shadow,0,TAG_SHADOWE);
    }

}
void Avatar::updateBossShadow()
{
    if(this->getChildByTag(TAG_SHADOWE))
    {
        this->removeChildByTag(TAG_SHADOWE);
    }

    const char* path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_SHADOWE_BOSS);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    // 连接该骨骼动画的资源
    ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
    Armature* armature = Armature::create(AVATAR_SHADOWE_BOSS);
    armature->getAnimation()->playWithIndex(0);
    
    Sprite* shadow = Sprite::create(IMG_PUBLIC_SHADOW);
    armature->addChild(shadow);
    
    this->addChild(armature,0,TAG_SHADOWE);


}
void Avatar::hideShadow()
{
    if(this->getChildByTag(TAG_SHADOWE))
    {
        this->removeChildByTag(TAG_SHADOWE);
    }
}
ActionState Avatar::getActionState()
{
    return  _actionState;
}
inline void Avatar::setActionState(ActionState state)
{
//    if(state == kActionStateNone)
//    {
//        log("lskdfjlsdjf");
//    }
    _preActionState = _actionState;
    _actionState = state;
}
void Avatar::onMovementEvent(Armature *armature, MovementEventType movementType, const std::string& movementId)
{
    this->movementType = movementType;
    if(movementType != LOOP_COMPLETE && movementType != COMPLETE )
        return;
   
    if(m_actionFinishedCallBack)
    {
        m_actionFinishedCallBack(this);
    }
    else
    {
        onActionCompleted();
    }
  
}
void Avatar::onFrameEvent(Bone *bone, const std::string& evt, int origin, int current)
{
    string str = evt;
    str = StringUtil::replace(str, " ", "");
    vector<string> params = StringUtil::split(str, "_");
    _frameEvent = params[0];
    _frameParam = "";

    if(params.size() > 1)
    {
        _frameParam = params[1];
        
    }
//    if(this->_avatarType == AVATAR_TYPE_HERO)
//    {
//        log("_frameEvent==%s _frameParam=%s origin=%d current==%d ,bone->getName()==%s",_frameEvent.c_str(),_frameParam.c_str(),origin,current,bone->getName().c_str());
//    }
   
    if(_frameEvent == AVATAR_CHANGE_EVENT)//_frameEvent.c_str(), AVATAR_CHANGE_EVENT) == 0
    {
//        _chanedBoneName = bone->getName();
//        changWeaponByBone(bone);
    }
    else if(_frameEvent == SKILL_ATTACK_EVENT)//(strcmp(_frameEvent.c_str(), SKILL_ATTACK_EVENT) == 0
    {
//        log("_frameEvent==%s _frameParam=%s origin=%d current==%d ,bone->getName()==%s",_frameEvent.c_str(),_frameParam.c_str(),origin,current,bone->getName().c_str());
        if(this->m_actionAttackCallBack)
        {
            this->m_actionAttackCallBack(this);
        }
    }
    else if(_frameEvent == AVATAR_ATTACK_EVENT)//strcmp(_frameEvent.c_str(), AVATAR_ATTACK_EVENT) == 0
    {
//        log("_frameEvent==%s _frameParam=%s origin=%d current==%d ,bone->getName()==%s",_frameEvent.c_str(),_frameParam.c_str(),origin,current,bone->getName().c_str());f
        if(this->m_actionAttackCallBack)
        {
            this->m_actionAttackCallBack(this);
        }
    }
    else if (_frameEvent == AVATAR_FLASHMOVE_EVENT)//strcmp(_frameEvent.c_str(), AVATAR_FLASHMOVE_EVENT) == 0
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_FLASHMOVE, this);
    }
    else if (_frameEvent == AVATAR_CAMERA_MOVESELF)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_MOVESELF, this);
    }
    else if (_frameEvent == AVATAR_CAMERA_MOVEENEMY)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_MOVEENEMY, this);
    }
    else if(_frameEvent == AVATR_CAMERA_SCALE)
    {
//        log("_frameEvent==%s _frameParam=%s origin=%d current==%d ,bone->getName()==%s",_frameEvent.c_str(),_frameParam.c_str(),origin,current,bone->getName().c_str());
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_SCALE, this);
    }
    else if(_frameEvent == AVATAR_SOUND_EVENT)
    {
        PublicShowUI::broadUserMsg(CUSTOM_PLAY_SOUND, this);
    }

    else if(strcmp(_frameEvent.c_str(), AVATAR_CAMERA_MOVEUP) == 0)//(_frameEvent == AVATAR_CAMERA_MOVEUP)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_MOVEUP, this);
    }
    else if(strcmp(_frameEvent.c_str(), AVATAR_CAMERA_MOVEDOWN) == 0)//(_frameEvent == AVATAR_CAMERA_MOVEDOWN)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_MOVEDOWN, this);
    }
    else if(_frameEvent == AVATAR_SLOWMONTION)
    {
        Director::getInstance()->getScheduler()->setTimeScale(.5);
    }
    else if(_frameEvent == AVATAR_RESET_SLOWMONTION)
    {
        float rate = GlobalInfo::getInstance()->battleType == kBattleType_TestBattle ? PlayerDataManager::getInstance()->_frameRate : 1;
         Director::getInstance()->getScheduler()->setTimeScale(rate);
    }
    else if(_frameEvent == AVATAR_CHANGE_SKILLBG)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_CHANGESKILLBG, this);
    }
    else if(_frameEvent == AVATAR_HIDE_OTHERAVATAR)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_HIDEOTHER, this);
    }
    else if(_frameEvent == AVATAR_SHOW_OTHERAVATAR)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_SHOWOTHER, this);
    }
    else if(_frameEvent == AVATAR_SHAKE_EVENT)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_SHAKE, this);
    }
    else if(_frameEvent == AVATAR_CALL_HEALPER)
    {
         PublicShowUI::broadUserMsg(CUSTOM_BATTLE_SUMMONED_SKILL, this);
    }
    else if(_frameEvent == AVATAR_POSITIONMOVE_EVENT)
    {
         PublicShowUI::broadUserMsg(CUSTOM_POSITION_MOVE, this);
    }
    else if(_frameEvent == AVATAR_STOP_ACTION)
    {
        PublicShowUI::broadUserMsg(CUSTOMM_STOP_ACTION, this);
    }
    else if (_frameEvent == AVATAR_STOP_DASH)
    {
        this->unscheduleUpdate();
        _velocity = Point::ZERO;
        this->onAvatarResume(this->isLeft,false);

    }
    else if(_frameEvent == AVATAR_ACTION_LOOP)
    {
//        PublicShowUI::broadUserMsg(CUSTOM_ACTION_LOOP, this);
        loopAction(atoi(_frameParam.c_str()));
       if(_acitonLoopTime <= 0)
       {
           _acitonLoopTime = time(0);
           DelayTime* delay = DelayTime::create(3);//3秒自动解除block
           CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Avatar::onLoopActionEnd, this));
           Sequence* action = Sequence::create(delay,callback, NULL);
           
           this->runAction(action);

       }
    }

}
void Avatar::onLoopActionEnd()
{
    _acitonLoopTime = 0;
    onMovementEvent(this->m_avatar, LOOP_COMPLETE, this->m_avatar->getAnimation()->getCurrentMovementID());
}
void Avatar::loopAction(int startFrameIndex)
{
    if(this->m_avatar)
    {
        this->m_avatar->getAnimation()->gotoAndPlay(startFrameIndex);
    }
}
void Avatar::onSkillEffectMoventEvent(Ref* target)
{
    SkillEffect* skillEffect = (SkillEffect*)target;
    if(skillEffect)
    {
        DelayTime* delay = DelayTime::create(.1);
        RemoveSelf* remove = RemoveSelf::create();
        skillEffect->runAction(Sequence::create(delay,remove,NULL));
    }
}
void Avatar::addEffect(const char* effectName,float offY ,bool isAdded)
{
   
    if(this->getChildByTag(TAG_EFFECT) && !isAdded)
    {
        return;
    }
    SkillEffect* skillEffect = SkillEffect::create(effectName,offY);
    skillEffect->setAnchorPoint(Point::ZERO);
    skillEffect->setPosition(-skillEffect->getContentSize().width/2 + m_avatarPosX, -this->getContentSize().height/2 + m_avatarPosY);
    skillEffect->m_actionMovementCallBack = CC_CALLBACK_1(Avatar::onSkillEffectMoventEvent, this);
    
    this->addChild(skillEffect,1,TAG_EFFECT);
}
bool Avatar::hasBuffState(int buffState)
{
    if(buffListMap)
    {
        auto iter = buffListMap->find(buffState);
        return iter != buffListMap->end();
    }
    return false;
}
BuffEffectData* Avatar::getBuffEffectData(int buffType)
{
    if(buffListMap && hasBuffState(buffType))
    {
       BuffEffectData* buffData = buffListMap->at(buffType);
        return buffData;
    }
    return NULL;
}
void Avatar::onBuff(int buffID,double damage,Avatar* attacker)
{
    DictBuff* dictBuff = DictBuffManager::getInstance()->getData(buffID);
    
    this->onTruntBuff(dictBuff->type, attacker);
    if(dictBuff->type == DictBuffTypeEnumShield)
    {
        double addLife = attacker->getAvatarProp()->attack * dictBuff->effect / 100;
 
        damage = addLife;
         onBuff(buffID,damage);
        _shieldBlood = addLife;
        addShieldBlood();
    }
    else
    {
        onBuff(buffID,damage);
    }
   

    
}
void Avatar::addShieldBlood()//添加护盾血条
{
    Sprite* progressBg = Sprite::create(IMG_PUBLIC_AVATAR_BLOODBG);
    progressBg->setAnchorPoint(Point::ZERO);
    this->addChild(progressBg,11,TAG_SHIELD_BLOOD);

    Sprite* blood = Sprite::create(IMG_PUBLIC_AVATAR_BLOOD_WHITE);
    blood->setAnchorPoint(Point::ZERO);
    blood->setColor(Color3B::WHITE);
    
    ProgressTimer* pt = ProgressTimer::create(blood);
    pt->setType(ProgressTimer::Type::BAR);
    pt->setMidpoint(Point(0,1));
    pt->setBarChangeRate(Point(1,0));
    pt->setAnchorPoint(Point::ZERO);
    
    
    pt->setPosition((progressBg->getContentSize().width - pt->getContentSize().width)/2 , (progressBg->getContentSize().height - pt->getContentSize().height)/2);
    pt->setPercentage(100);
    progressBg->addChild(pt,2,TAG_SHIELD_BLOOD);
    if(m_avatar)
    {
        progressBg->setPosition(m_avatar->getPositionX() - progressBg->getContentSize().width/2, m_avatar->getContentSize().height + 10);
    }
    
}
void Avatar::onBuff(int buffID,double damage)
{

    DictBuff* dictBuff = DictBuffManager::getInstance()->getData(buffID);
    if(!dictBuff)
    {
        return;
    }
 
    if(dictBuff->type == DictBuffTypeEnumFix || dictBuff->type == DictBuffTypeEnumStun || dictBuff->type == DictBuffTypeEnumSleep || dictBuff->type == DictBuffTypeEnumFrozen)
    {//霸体	clash		不会受到击退，击飞，击倒，定身，晕眩，睡眠，冰冻效果影响，直到持续时间结束
        if(this->hasBuffState(DictBuffTypeEnumClash))
        {
            return;
        }
    }
//    if(this->_avatarType == AVATAR_TYPE_MONSTER)
//    {
//        log("lsdjkfls");
//    }
    
    BuffEffectData* buffData = buffListMap->at(dictBuff->type);;
   
    long long nativeTime = time(0);
    if(buffData)
    {
        long long leftTime = buffData->endTime - nativeTime;
        if(leftTime >= dictBuff->time - 1)
        {
            return;
        }
        removeBuffByType(dictBuff->type);
        buffData = NULL;
    }

    buffData = BuffEffectData::create(dictBuff->id);
    
    buffData->setAnchorPoint(Point::ZERO);
    buffData->startTime = nativeTime;
    buffData->endTime = nativeTime + dictBuff->time;
    buffData->damage = damage;
//    buffListMap->insert(std::make_pair(dictBuff->type, buffData));
    buffListMap->insert(dictBuff->type, buffData);
//     log("add buff type=%d",dictBuff->type);
    if(dictBuff->type == DictBuffTypeEnumFrozen && this->getAvatarProp()->health > 0)
    {
        this->idle();
    }
    if(dictBuff->heroZoom >0)
    {
        this->runAction(ScaleTo::create(.3, (float)dictBuff->heroZoom / 10000 * GlobalInfo::getInstance()->m_avatarScale));
    }
    onAddSpeedBuff(dictBuff->type,dictBuff->effect);
    onMinusSpeedBuff(dictBuff->type,dictBuff->effect);

    onAddAttribBuff(dictBuff->type,dictBuff->effect);
    onMinusAttribBuff(dictBuff->type,dictBuff->effect);
    
    onHurtBloodBuff(dictBuff->type);
    onAddBloodBuff(dictBuff->type);
    onShieldBuff(dictBuff->type,damage);
    
    buffData->unscheduleUpdate();
    float xx = dictBuff->x - buffData->getContentSize().width/2;
    float yy = m_avatarPosY;
    if(dictBuff->point == DictBuffPointTypeEnumHead && m_avatar)
    {
        yy = yy + this->m_avatar->getContentSize().height;
       buffContainer->addChild(buffData, 1, buffContainer->getChildrenCount());
        buffData->setScale(.5);
        xx = dictBuff->x - buffData->getContentSize().width * .5 / 2;
         buffData->setOpacity(0);
    }
    if(dictBuff->level ==0 || dictBuff->level == 2)
    {
        this->addChild(buffData,3);
    }
    else
    {
        this->addChild(buffData,0);
    }
    
    if(dictBuff->point == DictBuffPointTypeEnumBody && m_avatar)
    {
         yy = yy + this->m_avatar->getContentSize().height / 2;
    }
 
    yy += dictBuff->y;
     buffData->setPosition(xx, yy);
    if(dictBuff->time > 0)
    {
        DelayTime* delay = DelayTime::create((float)dictBuff->time);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Avatar::removeBuffByType, this,dictBuff->type));
        buffData->runAction(Sequence::create(delay,callback,NULL));
    }
 
   
    buffData->setCascadeOpacityEnabled(true);
    if(buffContainer->getChildrenCount() == 1)
    {
        onBuffShadeIn(0);
    }
    
    if(buffData->icon)
    {
        buffData->icon->setPosition(buffIconContainer->getChildrenCount() * (buffData->icon->getContentSize().width + 5), 0);
        this->buffIconContainer->addChild(buffData->icon);
        Size size = buffData->icon->getContentSize();
        size.width = buffData->icon->getPositionX() + buffData->icon->getContentSize().width;
        
        buffIconContainer->setContentSize(size);
    }
    if(this->m_avatar)
    {
        buffIconContainer->setPosition(-buffIconContainer->getContentSize().width/2, m_avatar->getContentSize().height + 10);
    }
    
    SoundManager::playEffectMusic(dictBuff->voice.c_str());
     buffData = buffListMap->at(dictBuff->type);;
    if(dictBuff->type == DictBuffTypeEnumBlock)
    {
        MapDataManager::getInstance()->_blockAvatars->insert(this,__Bool::create(true));// (this);
    }
    onBuffAttribInfo(buffID);
}
void Avatar::onBuffAttribInfo(int buffID)
{
     DictBuff* dictBuff = DictBuffManager::getInstance()->getData(buffID);
//    dictBuff->characterShow = "at,up";
    vector<string> list = StringUtil::split(dictBuff->characterShow, ",");
    float toScale1 = .6;
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    for(string str : list)
    {
        str = PublicShowUI::getResImgPath(IMG_BATTLE_ATTRIBINFO, str.c_str());
        Sprite* spr = Sprite::create(str.c_str());
        if(!spr)
        {
            return;
        }
        spr->setAnchorPoint(Point::ZERO);
        int tag = (int)node->getChildrenCount();
        node->addChild(spr,tag,tag);
        if(tag != 0)
        {
            Node* pre = node->getChildByTag(tag-1);
            spr->setPositionX(pre->getPositionX() + pre->getContentSize().width);
        }
    }
    
    node->setScale(.1);
    node->setCascadeOpacityEnabled(true);
    node->setPosition(0, this->getContentSize().height);
    bloodContainer->addChild(node,int(this->getChildrenCount() + 1));
    
    ScaleTo* scaleTo = ScaleTo::create(.05, toScale1);
   
    RemoveSelf* remove = RemoveSelf::create();
    MoveBy* moveby1 = MoveBy::create(.5, Point(0,110));
    DelayTime* delay = DelayTime::create(.5);
    node->runAction(Sequence::create(scaleTo,moveby1, delay,remove,NULL));
}
void Avatar::clearBuff()
{
//    vector<int>* keys = buffListMap->keys();
    for (auto iter = buffListMap->begin(); iter != buffListMap->end(); ++iter)
    {
       
        BuffEffectData* buffData = iter->second;
        if(buffData->getParent())
        {
            buffData->removeFromParent();
        }
        buffData = NULL;
    }
    buffListMap->clear();
    
}
void Avatar::onBuffShadeIn(int buffTag)
{
    BuffEffectData* buffdata = (BuffEffectData*)buffContainer->getChildByTag(buffTag);
    if(buffdata)
    {
        FadeIn* fadeIn = FadeIn::create(.8);
        FadeOut* fadeout = FadeOut::create(.8);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::onShadeOut, this,buffTag));
        buffdata->runAction(Sequence::create(fadeIn,fadeout, callBack,NULL));
    }
    
}
void Avatar::onShadeOut(int buffTag)
{
    if(buffTag >= buffContainer->getChildrenCount() - 1)
    {
        buffTag = 0;
    }
    else
    {
        buffTag ++;
    }
    onBuffShadeIn(buffTag);
}
void Avatar::onShieldBuff(int buffType,int addLife)
{
     if(buffType != DictBuffTypeEnumShield)
     {
         return;
     }
    this->getAvatarProp()->health = this->getAvatarProp()->health + addLife;
  
   
}
void Avatar::onShieldAttack(float dt)//护盾攻击
{
    this->unschedule(schedule_selector(Avatar::onShieldAttack));
    this->idle();
    this->attack1();
}
void Avatar::onAddSpeedBuff(int buffType,int value)//速度buff
{
    if(buffType == DictBuffTypeEnumMoveSpeedPlus)
    {//加速度
        if(this->hasBuffState(DictBuffTypeEnumMoveSpeedMinus))
        {
            BuffEffectData* buffData = this->buffListMap->at(DictBuffTypeEnumMoveSpeedMinus);
            value = value - buffData->getDictBuff()->effect;
        }
       
        this-> _walkSpeed = this->_baseSpeed + this->_baseSpeed * value / 100;
    }
}
void Avatar::onMinusSpeedBuff(int buffType,int value)
{
    if(buffType == DictBuffTypeEnumMoveSpeedMinus)
    {//减速度
        if(this->hasBuffState(DictBuffTypeEnumMoveSpeedPlus))
        {
            BuffEffectData* buffData = this->buffListMap->at(DictBuffTypeEnumMoveSpeedPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        
        this-> _walkSpeed = this->_baseSpeed - this->_baseSpeed * value / 100;
    }
}
void Avatar::onTruntReset(int buffType)
{
     if(buffType == DictBuffTypeEnumTrunt)
     {
         this->trunter = NULL;
     }
}
void Avatar::onShieldBuffReset(int buffType)//护盾buff重置
{
   
    if(buffType == DictBuffTypeEnumShield)
    {
        this->getAvatarProp()->health -= this->_shieldBlood;
        this->_shieldBlood = 0;
    
        this->unschedule(schedule_selector(Avatar::onShieldAttack));
        this->removeChildByTag(TAG_SHIELD_BLOOD);
        this->unBlock();
    }
}
void Avatar::onSpeedReset(int buffType)
{
    int value = 0;

    if(buffType == DictBuffTypeEnumMoveSpeedMinus)
    {//减速度
        if(this->hasBuffState(DictBuffTypeEnumMoveSpeedPlus))
        {
            BuffEffectData* buffData = this->buffListMap->at(DictBuffTypeEnumMoveSpeedPlus);
            value = buffData->getDictBuff()->effect;
        }
        
        this-> _walkSpeed = this->_baseSpeed + this->_baseSpeed * value / 100;
     
    }
    else if(buffType == DictBuffTypeEnumMoveSpeedPlus)
    {
        if(this->hasBuffState(DictBuffTypeEnumMoveSpeedMinus))
        {
            BuffEffectData* buffData = this->buffListMap->at(DictBuffTypeEnumMoveSpeedMinus);
            value = buffData->getDictBuff()->effect;
        }
        
        this-> _walkSpeed = this->_baseSpeed - this->_baseSpeed * value / 100;
    }
}
//DictBuffTypeEnumHealthPlus=11,//增属性生命
//DictBuffTypeEnumAttackPlus=12,//增属性攻击
//DictBuffTypeEnumDefendPlus=13,//增属性防御
//DictBuffTypeEnumCriticPlus=14,//增属性暴击加成
//DictBuffTypeEnumTenaciPlus=15,//增属性韧性加成
//DictBuffTypeEnumHitPlus=16,//增属性精准加成
//DictBuffTypeEnumBlockPlus=17,//增属性格挡加成
//DictBuffTypeEnumDamageAddPlus=18,//增属性伤害加成率
//DictBuffTypeEnumFireResistPlus=19,//增属性火焰抗性率
//DictBuffTypeEnumIceResistPlus=20,//增属性冰霜抗性率
//DictBuffTypeEnumBoltResistPlus=21,//增属性雷电抗性率
//DictBuffTypeEnumWindResistPlus=22,//增属性飓风抗性率
//DictBuffTypeEnumPoisonResistPlus=23,//增属性巫毒抗性率

void Avatar::onAddAttribBuff(int buffType,int value)//增加属性buff
{
    BuffEffectData* buffData = NULL;
    if(buffType == DictBuffTypeEnumHealthPlus)
    {//增属性生命
        if(this->hasBuffState(DictBuffTypeEnumHealthMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumHealthMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->health == 0)
        {
            this->getAvatarProp()->health = this->getAvatarProp()->health + value / 100;
        }
        else
        {
            this->getAvatarProp()->health = this->getAvatarProp()->health +this->getBaseAvatarProp()->health * value / 100;
        }
        
    }
    else if(buffType == DictBuffTypeEnumAttackPlus)
    {//增属性攻击
        if(this->hasBuffState(DictBuffTypeEnumAttackMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumAttackMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->attack == 0)
        {
             this->getAvatarProp()->attack = value / 100;
        }
        else
        {
             this->getAvatarProp()->attack = this->getAvatarProp()->attack +this->getBaseAvatarProp()->attack * value / 100;
        }
       
    }
    else if(buffType == DictBuffTypeEnumDefendPlus)
    {//增属性防御
        if(this->hasBuffState(DictBuffTypeEnumDefendMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumDefendMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->defend == 0)
        {
            this->getAvatarProp()->defend = value / 100;
        }
        else
        {
            this->getAvatarProp()->defend = this->getAvatarProp()->defend +this->getBaseAvatarProp()->defend * value / 100;
        }
    
    }
    else if(buffType == DictBuffTypeEnumCriticPlus)
    {//增属性暴击加成
        if(this->hasBuffState(DictBuffTypeEnumCriticMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumCriticMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->critic == 0)
        {
            this->getAvatarProp()->critic = value ;
        }
        else
        {
            this->getAvatarProp()->critic = this->getAvatarProp()->critic +this->getBaseAvatarProp()->critic * value;
        }
        
    }
    else if(buffType == DictBuffTypeEnumTenaciPlus)
    {//增属性韧性加成
        if(this->hasBuffState(DictBuffTypeEnumTenaciMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumTenaciMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->tenaci == 0)
        {
            this->getAvatarProp()->tenaci = value;
        }
        else
        {
            this->getAvatarProp()->tenaci = this->getAvatarProp()->tenaci +this->getBaseAvatarProp()->tenaci * value ;
        }
        
    }
    else if(buffType == DictBuffTypeEnumHitPlus)
    {//增属性精准加成
        if(this->hasBuffState(DictBuffTypeEnumHitMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumHitMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        
        if(this->getAvatarProp()->hit == 0)
        {
            this->getAvatarProp()->hit =  value ;
        }
        else
        {
            this->getAvatarProp()->hit = this->getAvatarProp()->hit + this->getBaseAvatarProp()->hit * value;
        }
    }
    else if(buffType == DictBuffTypeEnumBlockPlus)
    {//增属性格挡加成
        if(this->hasBuffState(DictBuffTypeEnumBlockMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumBlockMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->block == 0)
        {
             this->getAvatarProp()->block = value ;
        }
        else
        {
            this->getAvatarProp()->block = this->getAvatarProp()->block + this->getBaseAvatarProp()->block * value;
        }
       
    }
    else if(buffType == DictBuffTypeEnumDamageAddPlus)
    {
        //增属性伤害加成率
        if(this->hasBuffState(DictBuffTypeEnumDamageAddMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumDamageAddMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if( this->getAvatarProp()->damageAdd == 0)
        {
              this->getAvatarProp()->damageAdd = value;
        }
        else
        {
             this->getAvatarProp()->damageAdd = this->getAvatarProp()->damageAdd + this->getBaseAvatarProp()->damageAdd * value;
        }
      
    }
    else if(buffType == DictBuffTypeEnumFireResistPlus)
    {//增属性火焰抗性率
        if(this->hasBuffState(DictBuffTypeEnumFireResistMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumFireResistMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->fireResist == 0)
        {
             this->getAvatarProp()->fireResist = value ;
        }
        else
        {
             this->getAvatarProp()->fireResist = this->getAvatarProp()->fireResist + this->getBaseAvatarProp()->fireResist * value ;
        }
       
    }
    else if(buffType == DictBuffTypeEnumIceResistPlus)
    {//增属性冰霜抗性率
        if(this->hasBuffState(DictBuffTypeEnumIceResistMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumIceResistMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if( this->getAvatarProp()->iceResist)
        {
            this->getAvatarProp()->iceResist = value;
        }
        else
        {
            this->getAvatarProp()->iceResist = this->getAvatarProp()->iceResist + this->getBaseAvatarProp()->iceResist * value ;
        }
       
    }
    else if(buffType == DictBuffTypeEnumBoltResistPlus)
    {//增属性雷电抗性率
        if(this->hasBuffState(DictBuffTypeEnumBoltResistMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumBoltResistMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->boltResist)
        {
            this->getAvatarProp()->boltResist = value;
        }
        else
        {
            this->getAvatarProp()->boltResist = this->getAvatarProp()->boltResist + this->getBaseAvatarProp()->boltResist * value;
        }
      
    }
    else if(buffType == DictBuffTypeEnumWindResistPlus)
    {//增属性飓风抗性率
        if(this->hasBuffState(DictBuffTypeEnumWindResistMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumWindResistMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getBaseAvatarProp()->windResist == 0)
        {
            this->getAvatarProp()->windResist = value ;
        }
        else
        {
             this->getAvatarProp()->windResist = this->getAvatarProp()->windResist + this->getBaseAvatarProp()->windResist * value ;
        }
//        log("heroName==%s,value==%f",this->_avatarName.c_str(),this->getBaseAvatarProp()->windResist);
       
    }
    else if(buffType == DictBuffTypeEnumPoisonResistPlus)
    {//增属性巫毒抗性率
        if(this->hasBuffState(DictBuffTypeEnumPoisonResistMinus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumPoisonResistMinus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->poisonResist == 0)
        {
            this->getAvatarProp()->poisonResist = value / 100;
        }
        else
        {
            this->getAvatarProp()->poisonResist = this->getAvatarProp()->poisonResist + this->getBaseAvatarProp()->poisonResist * value ;
        }
        
    }
}
//DictBuffTypeEnumHealthMinus=24,//减属性生命
//DictBuffTypeEnumAttackMinus=25,//减属性攻击
//DictBuffTypeEnumDefendMinus=26,//减属性防御
//DictBuffTypeEnumCriticMinus=27,//减属性暴击加成
//DictBuffTypeEnumTenaciMinus=28,//减属性韧性加成
//DictBuffTypeEnumHitMinus=29,//减属性精准加成
//DictBuffTypeEnumBlockMinus=30,//减属性格挡加成
//DictBuffTypeEnumDamageAddMinus=31,//减属性伤害加成率
//DictBuffTypeEnumFireResistMinus=32,//减属性火焰抗性率
//DictBuffTypeEnumIceResistMinus=33,//减属性冰霜抗性率
//DictBuffTypeEnumBoltResistMinus=34,//减属性雷电抗性率
//DictBuffTypeEnumWindResistMinus=35,//减属性飓风抗性率
//DictBuffTypeEnumPoisonResistMinus=36,//减属性巫毒抗性率
void Avatar::onMinusAttribBuff(int buffType,int value)
{
    BuffEffectData* buffData = NULL;
    if(buffType == DictBuffTypeEnumHealthMinus)
    {//减属性生命
        if(this->hasBuffState(DictBuffTypeEnumHealthPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumHealthPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->health == 0)
        {
            this->getAvatarProp()->health = this->getAvatarProp()->health  -  value / 100;
        }
        else
        {
            this->getAvatarProp()->health = this->getAvatarProp()->health  - this->getBaseAvatarProp()->health * value / 100;
        }
        
    }
    else if(buffType == DictBuffTypeEnumAttackMinus)
    {//属性攻击
        if(this->hasBuffState(DictBuffTypeEnumAttackPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumAttackPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        
        if(this->getAvatarProp()->attack == 0)
        {
            this->getAvatarProp()->attack = this->getAvatarProp()->attack  -  value / 100;
        }
        else
        {
            this->getAvatarProp()->attack = this->getAvatarProp()->attack  - this->getBaseAvatarProp()->attack * value / 100;
        }
        
     
    }
    else if(buffType == DictBuffTypeEnumDefendMinus)
    {//属性防御
        if(this->hasBuffState(DictBuffTypeEnumDefendPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumDefendPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->defend == 0)
        {
            this->getAvatarProp()->defend = this->getAvatarProp()->defend  -  value / 100;
        }
        else
        {
            this->getAvatarProp()->defend = this->getAvatarProp()->defend  - this->getBaseAvatarProp()->defend * value / 100;
        }
      
    }
    else if(buffType == DictBuffTypeEnumCriticMinus)
    {//属性暴击加成
        if(this->hasBuffState(DictBuffTypeEnumCriticPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumCriticPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->critic == 0)
        {
             this->getAvatarProp()->critic = this->getAvatarProp()->critic  - value;
        }
        else
        {
            this->getAvatarProp()->critic = this->getAvatarProp()->critic  - this->getBaseAvatarProp()->critic * value ;
        }
        
    }
    else if(buffType == DictBuffTypeEnumTenaciMinus)
    {//属性韧性加成
        if(this->hasBuffState(DictBuffTypeEnumTenaciPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumTenaciPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->tenaci == 0)
        {
            this->getAvatarProp()->tenaci = this->getAvatarProp()->tenaci  - value;
        }
        else
        {
            this->getAvatarProp()->tenaci = this->getAvatarProp()->tenaci  - this->getBaseAvatarProp()->tenaci * value ;
        }
        
    }
    else if(buffType == DictBuffTypeEnumHitMinus)
    {//属性精准加成
        if(this->hasBuffState(DictBuffTypeEnumHitPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumHitPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->hit == 0)
        {
            this->getAvatarProp()->hit = this->getAvatarProp()->hit  - value;
        }
        else
        {
            this->getAvatarProp()->hit = this->getAvatarProp()->hit  - this->getBaseAvatarProp()->hit * value ;
        }
      
    }
    else if(buffType == DictBuffTypeEnumBlockMinus)
    {//属性格挡加成
        if(this->hasBuffState(DictBuffTypeEnumBlockPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumBlockPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->block == 0)
        {
            this->getAvatarProp()->block = this->getAvatarProp()->block  - value;
        }
        else
        {
            this->getAvatarProp()->block = this->getAvatarProp()->block  - this->getBaseAvatarProp()->block * value ;
        }
     
    }
    else if(buffType == DictBuffTypeEnumDamageAddMinus)
    {
        //属性伤害加成率
        if(this->hasBuffState(DictBuffTypeEnumDamageAddPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumDamageAddPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->damageAdd == 0)
        {
            this->getAvatarProp()->damageAdd = this->getAvatarProp()->damageAdd  - value;
        }
        else
        {
            this->getAvatarProp()->damageAdd = this->getAvatarProp()->damageAdd  - this->getBaseAvatarProp()->damageAdd * value ;
        }
       
    }
    else if(buffType == DictBuffTypeEnumFireResistMinus)
    {//属性火焰抗性率
        if(this->hasBuffState(DictBuffTypeEnumFireResistPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumFireResistPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->fireResist == 0)
        {
            this->getAvatarProp()->fireResist = this->getAvatarProp()->fireResist  - value;
        }
        else
        {
            this->getAvatarProp()->fireResist = this->getAvatarProp()->fireResist  - this->getBaseAvatarProp()->fireResist * value ;
        }
    }
    else if(buffType == DictBuffTypeEnumIceResistMinus)
    {//属性冰霜抗性率
        if(this->hasBuffState(DictBuffTypeEnumIceResistPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumIceResistPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->iceResist == 0)
        {
            this->getAvatarProp()->iceResist = this->getAvatarProp()->iceResist  - value;
        }
        else
        {
            this->getAvatarProp()->iceResist = this->getAvatarProp()->iceResist  - this->getBaseAvatarProp()->iceResist * value ;
        }
       
    }
    else if(buffType == DictBuffTypeEnumBoltResistMinus)
    {//属性雷电抗性率
        if(this->hasBuffState(DictBuffTypeEnumBoltResistPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumBoltResistPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->boltResist == 0)
        {
            this->getAvatarProp()->boltResist = this->getAvatarProp()->boltResist  - value;
        }
        else
        {
            this->getAvatarProp()->boltResist = this->getAvatarProp()->boltResist  - this->getBaseAvatarProp()->boltResist * value ;
        }
    
    }
    else if(buffType == DictBuffTypeEnumWindResistMinus)
    {//属性飓风抗性率
        if(this->hasBuffState(DictBuffTypeEnumWindResistPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumWindResistPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->windResist == 0)
        {
            this->getAvatarProp()->windResist = this->getAvatarProp()->windResist  - value;
        }
        else
        {
            this->getAvatarProp()->windResist = this->getAvatarProp()->windResist  - this->getBaseAvatarProp()->windResist * value ;
        }
   
    }
    else if(buffType == DictBuffTypeEnumPoisonResistMinus)
    {//属性巫毒抗性率
        if(this->hasBuffState(DictBuffTypeEnumPoisonResistPlus))
        {
            buffData = this->buffListMap->at(DictBuffTypeEnumPoisonResistPlus);
            value = value - buffData->getDictBuff()->effect;
        }
        if(this->getAvatarProp()->poisonResist == 0)
        {
            this->getAvatarProp()->poisonResist = this->getAvatarProp()->poisonResist  - value;
        }
        else
        {
            this->getAvatarProp()->poisonResist = this->getAvatarProp()->poisonResist  - this->getBaseAvatarProp()->poisonResist * value ;
        }
   
    }
}
void Avatar::onAddAttribReset(int buffType)//增加属性到期
{
    BuffEffectData* buffDatta = NULL;
    if(buffType == DictBuffTypeEnumHealthPlus)
    {//增属性生命
        if(this->hasBuffState(DictBuffTypeEnumHealthMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->health = this->getAvatarProp()->health - this->getBaseAvatarProp()->health * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->health = this->getBaseAvatarProp()->health;
        }
      
    }
    else if(buffType == DictBuffTypeEnumAttackPlus)
    {//增属性攻击
      
        if(this->hasBuffState(DictBuffTypeEnumAttackMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->attack = this->getAvatarProp()->attack - this->getBaseAvatarProp()->attack * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->attack = this->getBaseAvatarProp()->attack;
        }
    }
    else if(buffType == DictBuffTypeEnumDefendPlus)
    {//增属性防御
        if(this->hasBuffState(DictBuffTypeEnumDefendMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->defend = this->getAvatarProp()->defend - this->getBaseAvatarProp()->defend * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->defend = this->getBaseAvatarProp()->defend;
        }
    }
    else if(buffType == DictBuffTypeEnumCriticPlus)
    {//增属性暴击加成
        if(this->hasBuffState(DictBuffTypeEnumCriticMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->critic = this->getAvatarProp()->critic - this->getBaseAvatarProp()->critic * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->critic = this->getBaseAvatarProp()->critic;
        }
    }
    else if(buffType == DictBuffTypeEnumTenaciPlus)
    {//增属性韧性加成
        if(this->hasBuffState(DictBuffTypeEnumTenaciMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->tenaci = this->getAvatarProp()->tenaci - this->getBaseAvatarProp()->tenaci * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->tenaci = this->getBaseAvatarProp()->tenaci;
        }
    }
    else if(buffType == DictBuffTypeEnumHitPlus)
    {//增属性精准加成
        if(this->hasBuffState(DictBuffTypeEnumHitMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->hit = this->getAvatarProp()->hit - this->getBaseAvatarProp()->hit * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->hit = this->getBaseAvatarProp()->hit;
        }
    }
    else if(buffType == DictBuffTypeEnumBlockPlus)
    {//增属性格挡加成
        if(this->hasBuffState(DictBuffTypeEnumBlockMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->block = this->getAvatarProp()->block - this->getBaseAvatarProp()->block * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->block = this->getBaseAvatarProp()->block;
        }
    }
    else if(buffType == DictBuffTypeEnumDamageAddPlus)
    {
        //增属性伤害加成率
        if(this->hasBuffState(DictBuffTypeEnumDamageAddMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->damageAdd = this->getAvatarProp()->damageAdd - this->getBaseAvatarProp()->damageAdd * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->damageAdd = this->getBaseAvatarProp()->damageAdd;
        }
    }
    else if(buffType == DictBuffTypeEnumFireResistPlus)
    {//增属性火焰抗性率
        if(this->hasBuffState(DictBuffTypeEnumDamageAddMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->fireResist = this->getAvatarProp()->fireResist - this->getBaseAvatarProp()->fireResist * buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->fireResist = this->getBaseAvatarProp()->fireResist;
        }
    }
    else if(buffType == DictBuffTypeEnumIceResistPlus)
    {//增属性冰霜抗性率
        if(this->hasBuffState(DictBuffTypeEnumIceResistMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->iceResist = this->getAvatarProp()->iceResist - this->getBaseAvatarProp()->iceResist * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->iceResist = this->getBaseAvatarProp()->iceResist;
        }
    }
    else if(buffType == DictBuffTypeEnumBoltResistPlus)
    {//增属性雷电抗性率
        if(this->hasBuffState(DictBuffTypeEnumBoltResistMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->boltResist = this->getAvatarProp()->boltResist - this->getBaseAvatarProp()->boltResist * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->boltResist = this->getBaseAvatarProp()->boltResist;
        }
    }
    else if(buffType == DictBuffTypeEnumWindResistPlus)
    {//增属性飓风抗性率

        if(this->hasBuffState(DictBuffTypeEnumWindResistMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->windResist = this->getAvatarProp()->windResist - this->getBaseAvatarProp()->windResist * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->windResist = this->getBaseAvatarProp()->windResist;
        }
    }
    else if(buffType == DictBuffTypeEnumPoisonResistPlus)
    {//增属性巫毒抗性率
        if(this->hasBuffState(DictBuffTypeEnumPoisonResistMinus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->poisonResist = this->getAvatarProp()->poisonResist - this->getBaseAvatarProp()->poisonResist * buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->poisonResist = this->getBaseAvatarProp()->poisonResist;
        }
    }
}
void Avatar::onTruntBuff(int buffType,Avatar* attacker)
{
    if(buffType != DictBuffTypeEnumTrunt)
    {
        return;
    }
    trunter = attacker;

}
void Avatar::onAddBloodBuff(int buffType)//持续回血
{
    if(buffType != DictBuffTypeEnumHealOnTime)
    {
        return;
    }
    BuffEffectData* buffDatta = buffListMap->at(buffType);
    
    showBloodPlus(buffDatta->damage);
    DelayTime* delay = DelayTime::create(buffDatta->getDictBuff()->onTime);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::Avatar::onAddBloodBuff, this,buffType));
    buffDatta->runAction(Sequence::create(delay,callBack, NULL));
    
}
void Avatar::onHurtBloodBuff(int buffType)//持续伤害
{
    if(buffType != DictBuffTypeEnumDamageOnTime)
    {
        return;
    }
    BuffEffectData* buffDatta = buffListMap->at(buffType);
    showBloodMinus(buffDatta->damage,false,false,false);
   
    DelayTime* delay = DelayTime::create(buffDatta->getDictBuff()->onTime);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::Avatar::onHurtBloodBuff, this,buffType));
    buffDatta->runAction(Sequence::create(delay,callBack, NULL));

}
void Avatar::onMinusAttribBuff(int buffType)//减少属性到期
{
    BuffEffectData* buffDatta = NULL;
    if(buffType == DictBuffTypeEnumHealthMinus)
    {//增属性生命
        if(this->hasBuffState(DictBuffTypeEnumHealthPlus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->health = this->getAvatarProp()->health + this->getBaseAvatarProp()->health * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->health = this->getBaseAvatarProp()->health;
        }
        
    }
    else if(buffType == DictBuffTypeEnumAttackMinus)
    {//增属性攻击
        
        if(this->hasBuffState(DictBuffTypeEnumAttackPlus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->attack = this->getAvatarProp()->attack + this->getBaseAvatarProp()->attack * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->attack = this->getBaseAvatarProp()->attack;
        }
    }
    else if(buffType == DictBuffTypeEnumDefendMinus)
    {//增属性防御
        if(this->hasBuffState(DictBuffTypeEnumDefendPlus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->defend = this->getAvatarProp()->defend + this->getBaseAvatarProp()->defend * buffDatta->getDictBuff()->effect / 100;
        }
        else
        {
            this->getAvatarProp()->defend = this->getBaseAvatarProp()->defend;
        }
    }
    else if(buffType == DictBuffTypeEnumCriticMinus)
    {//增属性暴击加成
        if(this->hasBuffState(DictBuffTypeEnumCriticPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->critic = this->getBaseAvatarProp()->critic + this->getBaseAvatarProp()->critic * buffDatta->getDictBuff()->effect / 100;
             this->getAvatarProp()->critic = this->getAvatarProp()->critic +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->critic = this->getBaseAvatarProp()->critic;
        }
    }
    else if(buffType == DictBuffTypeEnumTenaciMinus)
    {//增属性韧性加成
        if(this->hasBuffState(DictBuffTypeEnumTenaciPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->tenaci = this->getBaseAvatarProp()->tenaci + this->getBaseAvatarProp()->tenaci * buffDatta->getDictBuff()->effect / 100;
            
             this->getAvatarProp()->tenaci = this->getAvatarProp()->tenaci +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->tenaci = this->getBaseAvatarProp()->tenaci;
        }
    }
    else if(buffType == DictBuffTypeEnumHitMinus)
    {//增属性精准加成
        if(this->hasBuffState(DictBuffTypeEnumHitPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->hit = this->getBaseAvatarProp()->hit + this->getBaseAvatarProp()->hit * buffDatta->getDictBuff()->effect / 100;
              this->getAvatarProp()->hit = this->getAvatarProp()->hit +  buffDatta->getDictBuff()->effect ;
        }
        else
        {
            this->getAvatarProp()->hit = this->getBaseAvatarProp()->hit;
        }
    }
    else if(buffType == DictBuffTypeEnumBlockMinus)
    {//增属性格挡加成
        if(this->hasBuffState(DictBuffTypeEnumBlockPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->block = this->getBaseAvatarProp()->block + this->getBaseAvatarProp()->block * buffDatta->getDictBuff()->effect / 100;
            this->getAvatarProp()->block = this->getAvatarProp()->block +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->block = this->getBaseAvatarProp()->block;
        }
    }
    else if(buffType == DictBuffTypeEnumDamageAddMinus)
    {
        //增属性伤害加成率
        if(this->hasBuffState(DictBuffTypeEnumDamageAddPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->damageAdd = this->getBaseAvatarProp()->damageAdd + this->getBaseAvatarProp()->damageAdd * buffDatta->getDictBuff()->effect / 100;
            this->getAvatarProp()->damageAdd = this->getAvatarProp()->damageAdd +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->damageAdd = this->getBaseAvatarProp()->damageAdd;
        }
    }
    else if(buffType == DictBuffTypeEnumFireResistMinus)
    {//增属性火焰抗性率
        if(this->hasBuffState(DictBuffTypeEnumFireResistMinus))
        {
            buffDatta = buffListMap->at(buffType);

             this->getAvatarProp()->fireResist = this->getAvatarProp()->fireResist +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->fireResist = this->getBaseAvatarProp()->fireResist;
        }
    }
    else if(buffType == DictBuffTypeEnumIceResistMinus)
    {//增属性冰霜抗性率
        if(this->hasBuffState(DictBuffTypeEnumIceResistPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->iceResist = this->getBaseAvatarProp()->iceResist + this->getBaseAvatarProp()->iceResist * buffDatta->getDictBuff()->effect / 100;
            this->getAvatarProp()->iceResist = this->getAvatarProp()->iceResist +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->iceResist = this->getBaseAvatarProp()->iceResist;
        }
    }
    else if(buffType == DictBuffTypeEnumBoltResistMinus)
    {//增属性雷电抗性率
        if(this->hasBuffState(DictBuffTypeEnumBoltResistPlus))
        {
            buffDatta = buffListMap->at(buffType);
//            this->getAvatarProp()->boltResist = this->getBaseAvatarProp()->boltResist + this->getBaseAvatarProp()->boltResist * buffDatta->getDictBuff()->effect / 100;
            this->getAvatarProp()->boltResist = this->getAvatarProp()->boltResist +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->boltResist = this->getBaseAvatarProp()->boltResist;
        }
    }
    else if(buffType == DictBuffTypeEnumWindResistMinus)
    {//增属性飓风抗性率
        
        if(this->hasBuffState(DictBuffTypeEnumWindResistPlus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->windResist = this->getAvatarProp()->windResist +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->windResist = this->getBaseAvatarProp()->windResist;
        }
    }
    else if(buffType == DictBuffTypeEnumPoisonResistMinus)
    {//增属性巫毒抗性率
        if(this->hasBuffState(DictBuffTypeEnumPoisonResistPlus))
        {
            buffDatta = buffListMap->at(buffType);
            this->getAvatarProp()->poisonResist = this->getAvatarProp()->poisonResist +  buffDatta->getDictBuff()->effect;
        }
        else
        {
            this->getAvatarProp()->poisonResist = this->getBaseAvatarProp()->poisonResist;
        }
    }
}
void Avatar::removeBuffByType(int buffType)
{

    BuffEffectData* buffData = (BuffEffectData*)buffListMap->at(buffType);
    if(buffData)
    {
        buffListMap->erase(buffType);
        onAddAttribReset(buffType);
        onMinusAttribBuff(buffType);
        onSpeedReset(buffType);
        onTruntReset(buffType);
        onShieldBuffReset(buffType);
        if(buffType == DictBuffTypeEnumFrozen)
        {
            resumeAction();
        }
       
        if(buffData->getDictBuff()->heroZoom >0)
        {
            this->setScale(GlobalInfo::getInstance()->m_avatarScale);
        }
        if(buffData->getParent())
        {
            buffData->removeFromParent();
        }
        
        buffData = NULL;
    
        if(buffType == DictBuffTypeEnumBlock)
        {
        
            MapDataManager::getInstance()->_blockAvatars->erase(this);//(this,true)
        }
      
    }
    if(this->getAvatarProp() && this->getAvatarProp()->health <= 0)
    {
        this->dead();
    }
}

void Avatar::idle()//空闲，站立
{
 
    if(this->_isPause || this->getActionState() == kActionStateWin)
    {
        return;
    }
    this->_velocity = Point::ZERO;

    if(!_isInRoad)
    {
        return;
    }
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getCurrentMovementID() != AN_STAND || this->_actionState != kActionStateIdle)
        {
            if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_STAND))
            {
                m_avatar->getAnimation()->play(AN_STAND,-1,1);
                this->setActionState(kActionStateIdle);
            }
            
//            if(this->_avatarType == AVATAR_TYPE_HERO)
//            {
//                log("idle1111 111111111");
//            }
        }
        m_avatar->setPosition(m_avatarPosX, m_avatarPosY);
    }
    this->unscheduleUpdate();
    if(this->hasBuffState(DictBuffTypeEnumFrozen))
    {
        pauseAction();
    }
    else if(this->hasBuffState(DictBuffTypeEnumShield) && _actionState != kActionStateWalk)
    {
        this->block(false);
        this->unschedule(schedule_selector(Avatar::onShieldAttack));
        this->schedule(schedule_selector(Avatar::onShieldAttack), 3);
    }
}
void Avatar::knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack)
{
    if(this->hasBuffState(DictBuffTypeEnumClash) || this->hasBuffState(DictBuffTypeEnumFrozen))
    {//霸体buff 冰冻
        return;
    }
    if(this->getAvatarProp()->health <= 0)
    {
        return;
    }
    if(m_avatar && isAblePlayAction())
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_HURT1))
        {
             m_avatar->getAnimation()->play(AN_HURT1,-1,0);
             this->setActionState(kActionStateKnockBack);
        }
   
    }
    
    showBloodMinus(damage,isCrit,isBlock,isSkillAttack);
    if(this->getActionByTag(TAG_KNOCKBACK_ACTION))
    {
        this->stopActionByTag(TAG_KNOCKBACK_ACTION);
    }
    CallFunc* callBack = NULL;
    MoveTo* moveTo = NULL;
    if(this->hasBuffState(DictBuffTypeEnumSteady))
    {
        if(this->getAvatarProp()->health <= 0)
        {
            this->dead();
        }
    }
    else
    {
        moveTo = MoveTo::create(.3, targetPoint);
        if(this->getAvatarProp()->health <= 0)
        {
            callBack = CallFunc::create(CC_CALLBACK_0(Avatar::dead, this));
        }
        
        Sequence* action = Sequence::create(moveTo,callBack, NULL);
        action->setTag(TAG_KNOCKBACK_ACTION);
        this->runAction(action);
    }
    
}
bool Avatar::isAblePlayAction()
{
    bool bref = _actionState == kActionStateWalk  || _actionState == kActionStateIdle || _actionState == kActionStateNone || _actionState == kActionStateHurt;
    return bref && !this->hasBuffState(DictBuffTypeEnumFrozen) && !this->hasBuffState(DictBuffTypeEnumShield);
}

void Avatar::hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//受伤
{
    if(!this->_isInRoad)
    {
        return;
    }
    if(this->_actionState == kActionStateDead)
    {
        return;
    }
   
    if(this->getAvatarProp()->health > 0)
    {
        showBloodMinus(damage,isCrit,isBlock,isSkillAttack);
        if(this->getAvatarProp()->health <= 0)
        {
            this->dead();
            return;
        }
    }

    if(m_avatar && isAblePlayAction())
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_HURT1))
        {
            if(m_avatar->getAnimation()->getCurrentMovementID() == AN_HURT1 )
            {
                if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_HURT2))
                {
                     m_avatar->getAnimation()->play(AN_HURT2);
                }
                else
                {
                     m_avatar->getAnimation()->play(AN_HURT1);
                }
            }
            else if(m_avatar->getAnimation()->getCurrentMovementID() != AN_HURT2)
            {
                m_avatar->getAnimation()->play(AN_HURT1);
            }
            this->setActionState(kActionStateHurt);
        }
        else if(m_avatar->getAnimation()->getAnimationData()->getMovement("Hurt"))
        {
            m_avatar->getAnimation()->play("Hurt");
            this->setActionState(kActionStateHurt);
        }
        
         _velocity = Point::ZERO;
    }
   
}
void Avatar::onHurtReset()//恢复受伤变红效果
{
    if(this->m_avatar)
    {
        m_avatar->setColor(originColor);
    }
}
void Avatar::showBloodMinus(float damageNum,bool isCrit,bool isBlock,bool isSkillAttack)
{
    if(damageNum == 0)
    {
        return;
    }
    this->getAvatarProp()->health -= abs(damageNum);
    if(this->hasBuffState(DictBuffTypeEnumShield))
    {
        BuffEffectData* buffEffectData = this->buffListMap->at(DictBuffTypeEnumShield);
        buffEffectData->damage -= abs(damageNum);
        if( buffEffectData->damage <= 0)
        {
            this->removeBuffByType(DictBuffTypeEnumShield);
            _shieldBlood = 0;
            
        }
    }
    this->updateBlood();
    
    const char* path = NULL;
    float toScale1 = 1;
    float toScale2 = 1;
    float space = -15;
    if(isCrit || isSkillAttack)
    {
        path = IMG_PUBLIC_NUMBER2;
        toScale1 = 1.5;
        toScale2 = .5;
        space = - 15;
    }
    else
    {
        
        path = IMG_PUBLIC_NUMBER7;
        toScale1 = 3;
        toScale2 = 1.5;
        space = 0;
    }
  
    Node* node = PublicShowUI::getNumbers(abs(damageNum),path,false, space);
    if(!node)
    {
        return;
    }

    node->setScale(.1);
    node->setCascadeOpacityEnabled(true);
    node->setPosition(-node->getContentSize().width/2 + CCRANDOM_0_1() * node->getContentSize().width/2, this->getContentSize().height);
    bloodContainer->addChild(node,int(this->getChildrenCount() + 1));
    
    ScaleTo* scaleTo = ScaleTo::create(.05, toScale1);
    ScaleTo* scaleTo2 = ScaleTo::create(.08, toScale2);
    Shake* shake = Shake::create(.1, 5);
    RemoveSelf* remove = RemoveSelf::create();
    MoveBy* moveby1 = MoveBy::create(1, Point(0,110));
    DelayTime* delay = NULL;
    node->runAction(Sequence::create(scaleTo,scaleTo2,shake,moveby1, remove,NULL));
  
    if(isCrit)
    {
        Sprite* critSpr = Sprite::create(IMG_BATTLE_CRIT);
        critSpr->setAnchorPoint(Point::ZERO);
        critSpr->setScale(.1);
        critSpr->setPosition(node->getPositionX() - critSpr->getContentSize().width, this->getContentSize().height);
        bloodContainer->addChild(critSpr,int(this->getChildrenCount() + 1));
        
        
        scaleTo = ScaleTo::create(.05, 1.5);
        scaleTo2 = ScaleTo::create(.08, 0.5);
        delay = DelayTime::create(1);
        RemoveSelf* remove = RemoveSelf::create();
        moveby1 = MoveBy::create(1, Point(0,110));
        critSpr->runAction(Sequence::create(scaleTo,scaleTo2,delay, remove,NULL));
    }
    if(isBlock)
    {
        Sprite* blockSpr = Sprite::create(IMG_BATTLE_BLOCK);
        blockSpr->setAnchorPoint(Point::ZERO);
        blockSpr->setScale(.1);
        blockSpr->setPosition(node->getPositionX()+ node->getContentSize().width, this->getContentSize().height);
        bloodContainer->addChild(blockSpr,int(this->getChildrenCount() + 1));
        
        
        scaleTo = ScaleTo::create(.05, 1.5);
        scaleTo2 = ScaleTo::create(.08, 0.5);
        delay = DelayTime::create(1);
        RemoveSelf* remove = RemoveSelf::create();
     
        blockSpr->runAction(Sequence::create(scaleTo,scaleTo2,delay, remove,NULL));
    }
}
void Avatar::showBloodPlus(float blood)//加血效果
{
    if(blood == 0)
    {
        return;
    }
    this->getAvatarProp()->health += blood;
    Node* node = PublicShowUI::getNumbers(blood,IMG_PUBLIC_NUMBER6);
    if(!node)
    {
        return;
    }

    node->setScale(.7);
    node->setCascadeOpacityEnabled(true);
    node->setPosition(-node->getContentSize().width/2, this->getContentSize().height);
    bloodContainer->addChild(node,int(this->getChildrenCount() + 1));
    
    MoveBy* moveby1 = MoveBy::create(1, Point(0,110));
    FadeOut* fadeout = FadeOut::create(1.5);
    RemoveSelf* remove = RemoveSelf::create();
    node->runAction(moveby1);
    node->runAction(Sequence::create(fadeout, remove,NULL));
}

void Avatar::dead()//死亡
{
    if(!this->getParent())
    {
        this->setActionState(kActionStateDead);
        return;
    }
    if(this->_actionState == kActionStateDead)
    {
        return;
    }
    this->stopAllActions();
    this->_isPause  = false;
    this->setActionState(kActionStateDead);
   
    clearBuff();
    
    if(m_avatar)
    {
         m_avatar->stopAllActions();
        if(m_avatar->getAnimation()->getCurrentMovementID() != AN_DEAD)
        {
            if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_DEAD))
            {
                m_avatar->getAnimation()->play(AN_DEAD,-1,0);
            }
        }

        this->m_avatar->setPosition(m_avatarPosX,m_avatarPosY);
    
        this->runAction(this->deadAction);
    }
    else
    {
        this->removeFromParent();
    }
}
bool Avatar::ableAction()//是否可以操作
{
    //DictBuffTypeEnumStun晕眩
//    DictBuffTypeEnumSleep=3,//睡眠
//    DictBuffTypeEnumFrozen=4,//冰冻
    int buffList[] = {DictBuffTypeEnumStun,DictBuffTypeEnumSleep,DictBuffTypeEnumFrozen};
    size_t count=sizeof(buffList)/sizeof(int);
    for(int i = 0; i < count; i++)
    {
        if(this->hasBuffState(buffList[i]))
        {
            return false;
        }
    }
    return true;
}
bool Avatar::ableHurt()//是否可以伤害
{
    if(this->getActionState() == kActionStateDuck || this->getAvatarProp()->health <= 0)
    {//闪避
        return false;
    }
    //无敌
    int buffList[] = {DictBuffTypeEnumProtect};
    size_t count=sizeof(buffList)/sizeof(int);
    for(int i = 0; i < count; i++)
    {
        if(this->hasBuffState(buffList[i]))
        {
            return false;
        }
    }
    return true;
}
void Avatar::walkWithDirection(Point direction,bool isHold)//行走
{
 
 
    if(!isHold && this->_actionState != kActionStateIdle && _taskState != kTaskStateFollowMainHero
       && _actionState != kActionStateWalk)
    {
        
        return;
    }
    if(_isDashing)
    {
        return;
    }
    if(this->_actionState == kActionStateKnockFly && !_isInRoad)
    {
        return;//击飞不能行走
    }
    if(this->hasBuffState(DictBuffTypeEnumFix) || this->hasBuffState(DictBuffTypeEnumStun) || this->hasBuffState(DictBuffTypeEnumSleep) || this->hasBuffState(DictBuffTypeEnumFrozen) || this->hasBuffState(DictBuffTypeEnumSeal) || this->hasBuffState(DictBuffTypeEnumSteady))
    {
        return;
    }

    this->_velocity = Point(direction.x * this->_walkSpeed,direction.y * this->_walkSpeed * .7);//Y轴方向要慢点
    if(this->_delayState != kdelayStateSlowAway)
    {
        setDirection(direction);
    }
    else
    {
        log("this->_delaystate==%d  m_resourceName=%s",this->_delayState,m_resourceName.c_str());
    }
  
    
   
    
    if(this->_actionState != kActionStateWalk)
    {
        if((m_avatar && _actionState == kActionStateIdle && this->_isInRoad) || this->hasBuffState(DictBuffTypeEnumShield) )
        {
            m_isHolding = isHold;
            m_avatar->getAnimation()->play(AN_MOVE);
            this->setActionState(kActionStateWalk);
    
        }
    }
    
    if(this->hasBuffState(DictBuffTypeEnumShield))
    {
         this->unschedule(schedule_selector(Avatar::onShieldAttack));
    }
    
    
    
}
Point Avatar::getGridPoint()
{
    Point cp =  this->getPosition();
    cp.x = int(cp.x/ GlobalInfo::getInstance()->map_tiled_width);//格坐标
    cp.y = int((MapDataManager::getInstance()->_mapHeight - cp.y)/GlobalInfo::getInstance()->map_tiled_height);
    return cp;
}
void Avatar::setDirection(Point direction)
{
    if(!m_avatar || _actionState == kActionStateDuck)//闪避不改变方向
    {
        return;
    }
//    if(this->m_resourceName == "guanbinghaojie")
//    {
//        log("direiction.x=%f",direction.x);
//    }
    if(direction.x > 0 && this->m_avatar->getScaleX() != 1)
    {
     
        this->isLeft=false;
        this->m_avatar->setScaleX(1);
        m_avatarPosX = this->m_initAvatarPosX;

    }
    else if(direction.x < 0 && this->m_avatar->getScaleX() != -1)
    {
  
        this->isLeft=true;
        this->m_avatar->setScaleX(-1);
        m_avatarPosX = -this->m_initAvatarPosX;
       

    }
     this->m_avatar->setPositionX(m_avatarPosX);
}
bool Avatar::attack1()//攻击
{

    if(_actionState != kActionStateIdle && _actionState != kActionStateWalk && _actionState != kActionStateBlock)
    {
        return false;
    }
    if(!_isInRoad || _actionState == kActionStateWin)
    {
        return false;
    }
   
    if(m_avatar)
    {
        MovementData* _movementData = m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK);
        if(_movementData)
        {
            m_avatar->getAnimation()->play(AN_ATTACK,0,0);
            
            this->setActionState(kActionStateAttack1);
            this->_velocity = Point::ZERO;
        }
        else if(m_avatar->getAnimation()->getAnimationData()->getMovement(MONSTER_ATTACK))
        {
            m_avatar->getAnimation()->play(MONSTER_ATTACK,0,0);
            
            this->setActionState(kActionStateAttack1);
            this->_velocity = Point::ZERO;
        }
 
    }
    
     return true;
}

bool Avatar::attack2()// 攻击2
{
    if(this->_actionState == kActionStateAttack2 || _isDashing || _actionState == kActionStateWin)
    {
        return false;
    }
    
    if(m_avatar && m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK2))
    {

        m_avatar->getAnimation()->play(AN_ATTACK2,0,0);
 
        this->setActionState(kActionStateAttack2);
    }
    else
    {
        this->setActionState(kActionStateAttack2);
        onMovementEvent(this->m_avatar,LOOP_COMPLETE,AN_ATTACK2);
    }

     return true;
}

bool Avatar::attack3() //攻击3
{
    if(this->_actionState == kActionStateAttack3 || _isDashing || _actionState == kActionStateWin)
    {
        return false;
    }

    if(m_avatar && m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK3))
    {
        m_avatar->getAnimation()->play(AN_ATTACK3,0,0);
    
         this->setActionState(kActionStateAttack3);
    }
    else
    {
        this->setActionState(kActionStateAttack3);
        onMovementEvent(this->m_avatar,LOOP_COMPLETE,AN_ATTACK3);
    }
    
     return true;
}
bool Avatar::attack4()
{
    if(this->_actionState == kActionStateAttack4 || _isDashing || _actionState == kActionStateWin)
    {
        return false;
    }
   
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK4))
        {
            m_avatar->getAnimation()->play(AN_ATTACK4,0,0);
            this->setActionState(kActionStateAttack4);
        
        }
        else
        {
            this->setActionState(kActionStateAttack4);
            onMovementEvent(this->m_avatar,LOOP_COMPLETE,AN_ATTACK4);
        }
       
    }

     return true;
}
bool Avatar::attack5()// 攻击
{
    if(this->_actionState == kActionStateAttack5 || _isDashing || _actionState == kActionStateWin)
    {
        return false;
    }

    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK5))
        {
            m_avatar->getAnimation()->play(AN_ATTACK5,0,0);
            this->setActionState(kActionStateAttack5);

        }
        else
        {
            this->setActionState(kActionStateAttack5);
            onMovementEvent(this->m_avatar,LOOP_COMPLETE,AN_ATTACK5);
       
        }
       
    }
    return true;
}
void Avatar::jump()//跳
{
    if(this->_actionState == kActionStateJump || _actionState == kActionStateDown || _actionState == kActionStateJumpAttact || _isDashing || _actionState == kActionStateKnockFly || _actionState == kActionStateWin)
    {
        return;
    }
    if(!this->_isInRoad)
    {
        return;
    }
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_JUMP))
        {
              m_avatar->getAnimation()->play(AN_JUMP,-1,0);
            _isInRoad = false;
            _isAbleJumpAttack = false;
            DelayTime* delayTime = DelayTime::create(.35);
            CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::setAbleJumpAttackFlag, this,true));
            m_avatar->runAction(Sequence::create(delayTime,callBack, NULL));
            this->setActionState(kActionStateJump);
            SoundManager::playEffectMusic(EFFECT_JUMP);
        }
    }
    

}
bool Avatar::usePassSkill()//使用被动技能
{
    
}
void Avatar::setAbleJumpAttackFlag(bool flag)
{
    this->_isAbleJumpAttack = flag;
}
void Avatar::jumpDown()//落
{
    _isInRoad = true;
    if(this->_actionState == kActionStateDown || this->_actionState == kActionStateJumpAttact)
    {
        return;
    }
 
    if(m_avatar && m_avatar->getAnimation()->getAnimationData()->getMovement(AN_DOWN))
    {
        m_avatar->getAnimation()->play(AN_DOWN);
        DelayTime* delayTime = DelayTime::create(.15);
        CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(Avatar::setAbleJumpAttackFlag, this,false));
        m_avatar->runAction(Sequence::create(delayTime,callfun, NULL));
        this->setActionState(kActionStateDown);
    }
    
    
//     MoveTo* moveby = MoveTo::create(.3, Point(m_avatarPosX,m_avatarPosY));
//    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::onJumpEnded, this));
//    EaseSineOut* easeOut = EaseSineOut::create(moveby);
//    Sequence* action = Sequence::create(easeOut,callBack,NULL);
//    action->setTag(kActionStateDown);
//    m_avatar->runAction(action);
    
}
void Avatar::onJumpEnded()
{
    _knockFlyCount = 0;
    this->unscheduleUpdate();
    this->_isInRoad = true;
  
    setAbleJumpAttackFlag(false);
    if(m_avatar)
    {
        m_avatar->setPositionY(m_avatarPosY);
    }
  
    if(this->getAvatarProp() && this->getAvatarProp()->health <= 0)
    {
        this->dead();
    }
    else
    {
          this->idle();
    }
   
}
void Avatar::jumpAttact(float dt)//跳击
{
    if(this->_actionState != kActionStateJump && _actionState != kActionStateDown && this->_actionState != kActionStatePrePareJumpAttack)
    {
        return;
    }
    if(!this->_isAbleJumpAttack)
    {
        return;
    }
    if(this->_actionState == kActionStateJumpAttact || _actionState == kActionStateWin)
    {
        return;
    }
//    if(this->m_avatar->getPositionY() < m_avatarPosY + _jumpHeight - 50)
//    {
//        if(this->m_avatar->getPositionY() == m_avatarPosY)
//        {
//            this->idle();
//        }
//        return;
//    }
//    if(m_avatar->getActionByTag(kActionStateJumpAttact) )
//    {
//        return;
//    }
//    if(m_avatar->getActionByTag(kActionStateDown))
//    {
//        m_avatar->stopActionByTag(kActionStateDown);
//    }
    m_jumpAttackTime = dt;
    if(m_avatar)
    {
        this->_isInRoad = false;
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_JUMP_ATTACT))
        {
             m_avatar->getAnimation()->play(AN_JUMP_ATTACT,-1,0);
              this->setActionState(kActionStateJumpAttact);
             setAbleJumpAttackFlag(false);
        }
       
//        MoveTo* moveTo = MoveTo::create(m_jumpAttackTime, Point(m_avatarPosX,m_avatarPosY));
//        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::onJumpEnded, this));
//        Sequence* action = Sequence::create(moveTo,callBack,NULL);
//        action->setTag(kActionStateJumpAttact);
//        m_avatar->runAction(action);
//        this->m_avatar->stopAllActions();
      
    }
   
}
void Avatar::prepareJumpAttack(float delayTime)//准备跳击
{
    if(this->_actionState == kActionStatePrePareJumpAttack || this->_actionState == kActionStateJumpAttact || this->_actionState == kActionStateKnockFly)
    {
        return;
    }
    if(!m_avatar)
    {
        return;
    }
    this->m_jumpAttackTime = delayTime;
    jump();
    
    this->setActionState(kActionStatePrePareJumpAttack);
}
void Avatar::dash(float distance,float time)//冲撞
{
    if(_isDashing || _actionState == kActionStateDuck)
    {
        return;
    }
    if(m_avatar)
    {
     

        float dt =  time > 0 ? time : abs(distance) / _walkSpeed;
        DelayTime* delay = DelayTime::create(dt); 
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(Avatar::onAvatarResume,this, isLeft,false));//冲击动作完成，并不是本状态完成，冲击动作是属于某个状态里的。
        this->runAction(Sequence::create(delay, callBack,NULL));
        this->isLeft = distance < 0 ? !isLeft : isLeft;
        this->_walkSpeed = abs(distance) / dt;
        _isDashing = true;
    }
    _velocity = Point::ZERO;
//    if(_velocity == Point::ZERO)
    {
        this->unscheduleUpdate();
        this->scheduleUpdate();
    }
}
bool Avatar::getIsDashing()
{
    return _isDashing;
}
void Avatar::win()
{

    if(this->_actionState == kActionStateWin)
    {
        return;
    }

    if(m_avatar)
    {
       if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_WIN))
       {
           m_avatar->getAnimation()->play(AN_WIN,-1,0);
           this->_actionState = kActionStateWin;
       }
       
    }
}
void Avatar::unBlock()
{
    if(this->_actionState != kActionStateBlock)
    {
        return;
    }
    long leftTime = time(0) - _blockStartTime;
    if(leftTime < 1)
    {//不够1秒要等1秒
        this->stopActionByTag(TAG_BLOCKDELAY);
        DelayTime* delay = DelayTime::create(1);
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Avatar::idle, this));
        Sequence* action = Sequence::create(delay,callback, NULL);
        action->setTag(TAG_BLOCKDELAY);
        this->runAction(action);
    }
    else
    {
          this->idle();
    }
  
    
}
bool Avatar::block(bool isAutoUnBlock)//格档
{
    if(this->_actionState == kActionStateBlock || _actionState == kActionStateWin || _actionState == kActionStateJump || _actionState == kActionStateDown || _actionState == kActionStateJumpAttact)
    {
        return false;
    }
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_BLOCK))
        {
            m_avatar->getAnimation()->play(AN_BLOCK,-1,0);
//            if(this->_avatarType == AVATAR_TYPE_HERO)
//            {
//                log("block 11111111122222");
//            }
            this->stopActionByTag(TAG_BLOCKDELAY);
            _blockStartTime = time(0);
            
            if(isAutoUnBlock)
            {
                DelayTime* delay = DelayTime::create(3);//3秒自动解除block
                CallFunc* callback = CallFunc::create(CC_CALLBACK_0(Avatar::unBlock, this));
                Sequence* action = Sequence::create(delay,callback, NULL);
                action->setTag(TAG_BLOCKDELAY);
                this->runAction(action);
               
            }
           
            this->_actionState = kActionStateBlock;
            return true;
        }
    }
    return false;
}
bool Avatar::duck(float distance,float time)//闪避
{
    if(this->_actionState == kActionStateDuck || _actionState == kActionStateWin || _isDashing || _actionState == kActionStateJump || _actionState == kActionStateDown || _actionState == kActionStateJumpAttact)
    {
        return false;
    }
    if(m_avatar)
    {
     
        this->dash(distance,time);
       
        Point direction = MapDataManager::getInstance()->getAvatarWalkDirection(this, this->isLeft);
        this->_velocity = Point(direction.x * this->_walkSpeed,direction.y * this->_walkSpeed);
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_DUCK))
        {
            m_avatar->getAnimation()->play(AN_DUCK,-1,0);
            this->_actionState = kActionStateDuck;
            return true;
        }
        
       
    }
    return false;
}
void Avatar::update(float dt)
{
    Point direction;
    if(_isDashing)
    {
         direction = MapDataManager::getInstance()->getAvatarWalkDirection(this, this->isLeft);
    }
    else if(this->_actionState == kActionStateKnockFly || this->_actionState == kActionStateKnockBack)
    {
        direction = MapDataManager::getInstance()->getAvatarWalkDirection(this, !this->isLeft);
    }
    else if(this->_actionState == kActionStateDuck)
    {
        direction = MapDataManager::getInstance()->getAvatarWalkDirection(this, this->isLeft);
    }
    else if(this->_actionState == kActionStateJump)
    {
        direction.x = 0;
        direction.y = 1;
    }
    else if(this->_actionState == kActionStateDown || this->_actionState == kActionStateJumpAttact)
    {
        direction.x = 0;
        direction.y = -1;
    }
 
    this->_velocity = Point(direction.x * this->_walkSpeed,direction.y * this->_walkSpeed);
}
void Avatar::onAvatarResume(int oldDirection,bool isCallBack)//恢复动作
{
    
    this->_walkSpeed = this->_baseSpeed;
    if(m_avatar)
    {
         this->isLeft= m_avatar->getScaleX() == -1;
    }
    else
    {
        this->isLeft = oldDirection;
    }
   
    this->unscheduleUpdate();
    
    if(_isDashing)
    {
         _isDashing = false;
        if(isCallBack)
        {
            onMovementEvent(this->m_avatar,LOOP_COMPLETE,"DASH");
        }
      
     
    }
    _dashSkillID = 0;
    
}
bool Avatar::skill1()//必杀
{
    if(!ableAction())
    {
        return false;
    }
    if(!this->_isInRoad)
    {
        return false;
    }
    if(this->getActionState() == kActionStateSkill1 || this->getActionState() == kActionStateSkill2 || this->getActionState() == kActionStateSkill3 || this->getActionState() == kActionStateSkill4)
    {
        return false;
    }
     resumeAction();
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_SKILL1))
        {
            m_avatar->getAnimation()->play(AN_SKILL1);
           
        }
        else if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_ATTACK))
        {
            m_avatar->getAnimation()->play(AN_ATTACK);
        }
        else if(m_avatar->getAnimation()->getAnimationData()->getMovement(MONSTER_ATTACK))
        {
             m_avatar->getAnimation()->play(MONSTER_ATTACK);
        }
        _isDashing = false;
        this->setActionState(kActionStateSkill1);
    }
   
    return true;
}

bool Avatar::skill2()//必杀
{
    if(!ableAction())
    {
        return false;
    }
    if(!this->_isInRoad)
    {
        return false;
    }
    if(this->getActionState() == kActionStateSkill1 || this->getActionState() == kActionStateSkill2 || this->getActionState() == kActionStateSkill3 || this->getActionState() == kActionStateSkill4)
    {
        return false;
    }
    resumeAction();
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_SKILL2))
        {
            m_avatar->getAnimation()->play(AN_SKILL2);
            
        }
        else
        {
            this->attack1();
        }
        _isDashing = false;
        this->setActionState(kActionStateSkill2);
      
    }
    
     return true;
}
bool Avatar::skill3()//必杀
{
    if(!ableAction())
    {
        return false;
    }
    if(!this->_isInRoad)
    {
        return false;
    }
    if(this->getActionState() == kActionStateSkill1 || this->getActionState() == kActionStateSkill2 || this->getActionState() == kActionStateSkill3 || this->getActionState() == kActionStateSkill4)
    {
        return false;
    }
   resumeAction();
    if(m_avatar)
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_SKILL3))
        {
            m_avatar->getAnimation()->play(AN_SKILL3);
            
        }
        else
        {
           this->attack1();
        }
        _isDashing = false;
        this->setActionState(kActionStateSkill3);
        
    }
   
    return true;
}
bool Avatar::skill4()
{
    if(!ableAction())
    {
        return false;
    }
    if(!this->_isInRoad)
    {
        return false;
    }
    if(this->getActionState() == kActionStateSkill1 || this->getActionState() == kActionStateSkill2 || this->getActionState() == kActionStateSkill3 || this->getActionState() == kActionStateSkill4)
    {
        return false;
    }
   
    if(m_avatar)
    {
      if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_SKILL4))
      {
          m_avatar->getAnimation()->play(AN_SKILL4);
          this->setActionState(kActionStateSkill4);
          _isDashing = false;
      }
      else
      {
          this->attack1();
      }
    }
    resumeAction();
    this->hideShadow();
    return true;
}
bool Avatar::getIsCDState(int skillID)
{
    auto iter = skillCDMap->find(skillID);
    if (iter == skillCDMap->end())
    {
        return false;
    }

    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
    long long lastTime = skillCDMap->at(skillID);
    long long time = TimeUtil::getNativeTime() - lastTime;
    return time < dictSkill->coldDowm * 1000;
}
void Avatar::knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击倒
{
    if(this->hasBuffState(DictBuffTypeEnumClash))
    {//霸体buff
        return;
    }
    if(m_avatar && isAblePlayAction())
    {
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_DEAD))
        {
            m_avatar->getAnimation()->play(AN_DEAD,-1,0);
            this->setActionState(kActionStateKnockDown);
        }
    }
  
    
    showBloodMinus(damage,isCrit,isBlock,isSkillAttack);
  
    if(this->getAvatarProp()->health <= 0)
    {
        this->dead();
    }
 
}
void Avatar::knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击飞
{
    if(this->hasBuffState(DictBuffTypeEnumClash))
    {//霸体buff
        return;
    }
    if(this->getActionState() == kActionStateDead)
    {
        return;
    }
    bool isAbleFly = true;
    if(this->_actionState == kActionStateKnockFly)
    {
         isAbleFly = FormulaManager::isAbleKnockFly(this->_knockFlyCount);
        _knockFlyCount++;
    }
    else
    {
        _knockFlyCount = 1;
    }
   
    if(m_avatar && !this->hasBuffState(DictBuffTypeEnumFrozen) && isAblePlayAction() && isAbleFly)
    {
    
        this->_isInRoad = false;
        m_avatar->stopAction(flyAction);
        m_avatar->runAction(flyAction);
        if(m_avatar->getAnimation()->getAnimationData()->getMovement(AN_DEAD))
        {
            m_avatar->getAnimation()->play(AN_DEAD,-1,0);
        }
      
        this->setActionState(kActionStateKnockFly);
        
        this->unscheduleUpdate();
        this->scheduleUpdate();
         showBloodMinus(damage,isCrit,isBlock,isSkillAttack);
    }
    else
    {
        this->hurtWithDamage(damage, isCrit,isBlock,isSkillAttack);
    }
  
}
void Avatar::onEnter()
{
    Node::onEnter();
    if(this->isShowBlood)
    {
        setBloodProgress();
    }
}
void Avatar::onExit()
{
    Node::onExit();
    if(m_avatar)
    {
        this->m_avatar->pause();
        this->m_avatar->setPositionY(m_avatarPosY);
        this->m_avatar->stopAllActions();
    }
    
    bloodContainer->removeAllChildren();
    this->_isInRoad = true;
    
}
void Avatar::setFrameScale(float value)//设置播放帧速
{
    if(this->m_avatar)
    {
        this->m_avatar->getAnimation()->setSpeedScale(value);
    }
    
}
void Avatar::updatePositon(float dt)
{
    if(this->_actionState != kActionStateWalk && _actionState != kActionStateJump && _actionState != kActionStateDown && !_isDashing && _actionState != kActionStateKnockFly && _taskState != kTaskStateFollowMainHero && _actionState != kActionStateKnockBack && _actionState != kActionStateDuck)
    {//有些动作，比如受伤，是不会更新位置的
        return;
    }
    Point cp  = this->getPosition() + _velocity * dt;
    bool m_isLeft = cp.x < _destinatsionPostion.x;

    cp = MapDataManager::getInstance()->getAvatarPosition(cp, this->_wayNumber,m_isLeft,this);

    if(cp == Point::ZERO)
    {
        cp = this->getPosition();
        cp.x = cp.x + _velocity.x * dt;
        cp = MapDataManager::getInstance()->getAvatarPosition(cp, this->_wayNumber,m_isLeft,this);
    }
    if(cp.x != 0 || cp.y != 0)
    {
//        log("name=%s,posX=%f,posY=%f toX=%f,toY=%f",this->_avatarName.c_str(),this->getPositionX(),this->getPositionY(),cp.x,cp.y);
        _destinatsionPostion = cp;
        this->setPosition(_destinatsionPostion.x,_destinatsionPostion.y);
    }
    if(this->m_resourceName == "guanbinghaojie")
        
    {
        log("this->_delaystate==%d  m_resourceName=%s",this->_delayState,m_resourceName.c_str());
    }
    


}
void Avatar::changeWeapon(const char* weaponName)
{
    _weaponName = weaponName;
}
void Avatar::changWeaponByBone(Bone* bone)
{
    if(!m_avatar || _weaponName == "")
    {
        return;
    }

    if(bone)
    {
        Skin* skin = Skin::create(this->_weaponName.c_str());
        if(!skin)
        {
            skin = Skin::createWithSpriteFrameName(this->_weaponName.c_str());
        }
    
        bone->addDisplay(skin, 1);
        bone->changeDisplayWithIndex(1, true);
    }
}
void Avatar::onFlashMove(DictSkill* dictSkill)
{
    if(dictSkill->flashMove == 0)
    {
        return;
    }
    int gridNum = abs(dictSkill->flashMove);
    bool isLeft = dictSkill->flashMove > 0 ? this->isLeft : !this->isLeft;
    
    Point postion = this->getPosition();
    
    Point cp;
    for(int i =0; i< gridNum; i++)
    {
        cp = MapDataManager::getInstance()->getAvatarWalkDirection(this,isLeft);
        cp = cp * GlobalInfo::getInstance()->map_tiled_width;
        postion += cp;
        this->_destinatsionPostion = postion;
        this->setPosition(postion.x, postion.y);
    }
    postion = MapDataManager::getInstance()->getAvatarPosition(this->_destinatsionPostion,this->_wayNumber,isLeft);
    this->setPosition(postion.x, postion.y);
}

BoundingBox Avatar::createBoundingBoxWithOrigin(Point origin,Size size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
    boundingBox.actual.size = size;
    return boundingBox;
}
void Avatar::transformBoxes()
{
    this->_hitBox.actual.origin = this->getPosition() + _hitBox.original.origin;
    _attackBox.original.origin.x = this->getScaleX() == -1 ?-(_attackBox.original.size.width +_hitBox.original.size.width) : 0;
    _attackBox.actual.origin = this->getPosition() + _attackBox.original.origin ;
}
void Avatar::setPosition(float xx,float yy)
{
    Node::setPosition(xx, yy);
    this->transformBoxes();
}

void Avatar::onFiveAttack()
{

    switch (this->_actionState)
    {
        case kActionStateSkill1:
        case kActionStateSkill2:
        case kActionStateSkill3:
            this->attack1();
            break;
        case kActionStateAttack1:
             this->attack2();
             break;
        case kActionStateAttack2:
             this->attack3();
             break;
        case kActionStateAttack3:
            this->attack4();
            break;
        case kActionStateAttack4:
            this->attack5();
            break;
        default:
            this->idle();
            this->_taskState = kTaskStateGuard;
            break;
    }
}
void Avatar::onActionCompleted()
{
    if(!m_avatar)
    {
        return;
    }
    this->m_avatar->setColor(originColor);

    switch (this->_actionState)
    {
        case kActionStateIdle:
            break;
        case kActionStateDead:
             this->unscheduleUpdate();
            this->_velocity = Point::ZERO;
            bloodContainer->removeAllChildren();
            break;
        case kActionStateWalk:
            if(!m_isHolding)
            {
                this->idle(); 
            }
            break;
        case kActionStateJump:
            jumpDown();
        break;
        case kActionStatePrePareJumpAttack:
           
            this->jumpAttact(m_jumpAttackTime);
            break;
        case kActionStateSkill1:
        case kActionStateSkill2:
        case kActionStateSkill3:
            if(!this->_isInRoad)
            {
                this->jumpDown();
            }
            else
            {
                 this->idle();
            }
            break;
        case kActionStateSkill4:
            this->idle();
            PublicShowUI::broadUserMsg(CUSTOM_SKILL4_OVER, this);
            this->updateShadow();
            break;
            
        case kActionStateKnockFly:
           if(this->_isInRoad)
           {
               this->idle();
           }
            break;
        case kActionStateKnockBack:
            this->unscheduleUpdate();
            this->idle();
            break;
        case kActionStateWin:
            break;
        case kActionStateJumpAttact:
            this->_isInRoad = true;
            this->idle();
            break;
        case kActionStateBlock:
//            this->unBlock();
            break;
            
        default:
            if(this->_taskState == kTaskStateAttack)
            {
                onFiveAttack();
            }
            else
            {
                if(!this->_isInRoad)
                {
                    this->jumpDown();
                }
                else
                {
                    this->idle();
                }
            }
            break;
    }
    if(isCamreIn)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_RESET, NULL);
        isCamreIn = false;
    }
    if(Director::getInstance()->getScheduler()->getTimeScale() != 1)
    {
        float rate = GlobalInfo::getInstance()->battleType == kBattleType_TestBattle ? PlayerDataManager::getInstance()->_frameRate : 1;
        Director::getInstance()->getScheduler()->setTimeScale(rate);
    }
    if(_actionState != kActionStateJump && _actionState != kActionStateDown && _actionState != kActionStateJumpAttact)
    {
        setAbleJumpAttackFlag(false);
    }

    
  
}
bool Avatar::isPauseState()
{
    return _isPause;
}
void Avatar::pauseAction()//暂停动作
{
    if(this->m_avatar)
    {
         m_avatar->getAnimation()->pause();
        _isPause = true;
    }
}
void Avatar::resumeAction()//恢复动作
{
    if(this->m_avatar && _isPause)
    {
          _isPause = false;
        m_avatar->getAnimation()->resume();
        this->idle();
      
    }
}
int Avatar::getCurSkillID()
{
    return 0;
}
void Avatar::setBloodProgress()
{
    Sprite* progressBg = Sprite::create(IMG_PUBLIC_AVATAR_BLOODBG);
    progressBg->setAnchorPoint(Point::ZERO);
    this->addChild(progressBg,10,TAG_BLOOD);
    progressBg->setVisible(false);
    Sprite* blood = Sprite::create(IMG_PUBLIC_AVATAR_BLOOD);
    blood->setAnchorPoint(Point::ZERO);
    m_bloodPt = ProgressTimer::create(blood);
    m_bloodPt->setType(ProgressTimer::Type::BAR);
    m_bloodPt->setMidpoint(Point(0,1));
    m_bloodPt->setBarChangeRate(Point(1,0));
    m_bloodPt->setAnchorPoint(Point::ZERO);
    
    
    m_bloodPt->setPosition((progressBg->getContentSize().width - m_bloodPt->getContentSize().width)/2 , (progressBg->getContentSize().height - m_bloodPt->getContentSize().height)/2);
    m_bloodPt->setPercentage(100);
    progressBg->addChild(m_bloodPt,2);

}
void Avatar::updateBlood()
{
    if(m_bloodPt && this->m_avatar && this->getAvatarProp())
    {
        Node* progress = this->getChildByTag(TAG_BLOOD);
        progress->setVisible(true);
        progress->setPosition(m_avatar->getPositionX() - progress->getContentSize().width/2, m_avatar->getContentSize().height);
        float percent = this->getAvatarProp()->health / this->_totalHitPoints;
        
        m_bloodPt->stopAllActions();
        m_bloodPt->runAction(ProgressFromTo::create(.3, m_bloodPt->getPercentage(), percent * 100 ));
    }
    
    Node* shieldProgress = this->getChildByTag(TAG_SHIELD_BLOOD);
    if(shieldProgress)
    {
        ProgressTimer* pt = (ProgressTimer*)shieldProgress->getChildByTag(TAG_SHIELD_BLOOD);
        if(pt)
        {
            BuffEffectData* buffEffectData = this->buffListMap->at(DictBuffTypeEnumShield);
            if(buffEffectData)
            {
                float percent = buffEffectData->damage / this->_shieldBlood;
                pt->stopAllActions();
                RemoveSelf* removeSelf = NULL;
                if(percent <= 0)
                {
                    shieldProgress->runAction(Sequence::create(DelayTime::create(.3),removeSelf, NULL));
                }
                pt->runAction(ProgressFromTo::create(.3, pt->getPercentage(), percent * 100 ));
            }
           
        }
        
    }
}
