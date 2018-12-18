//
//  Hero.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#include "Hero.h"
#include "../../module/battle/data/MapDataManager.h"
#include "../../module/battle/monsterAI/HeroAIManager.h"
#include "../../common/GameConfig.h"
#include "../../module/newPlayerGuide/NewPlayerGuild.h"
#include "../../module/battle/battleUI/HeroHeadListLayer.h"
#include "../../commonData/enum/DictSkillTypeEnum.h"
Hero::Hero()
:_dictHero(NULL)

,_isMainHero(false)

,_isUserControl(false)
,_angryValue(0)
{
    
}
Hero::~Hero()
{
    _angryValue = 0;
    CC_SAFE_RELEASE_NULL(_dictHero);
}
bool Hero::init(int heroID)
{
    bool bref = false;
    do {
        DictHero* hero = DictHeroManager::getInstance()->getData(heroID);
        CC_BREAK_IF(!hero);
        _avatarType = AVATAR_TYPE_HERO;
        this->_avatarName = hero->name;
        this->setDictHero(hero);
        this->m_avatarPosY = hero->resourceHighShifting;
        this->m_avatarPosX = hero->resourceShifting;
        this->m_initAvatarPosX = this->m_avatarPosX;
        Scene* scene = Director::getInstance()->getRunningScene();
        if(scene->getChildByTag(SCENE_TAG_BATTLE))
        {
            CC_BREAK_IF(!Avatar::init(hero->resource));
        }
        else
        {
            CC_BREAK_IF(!Avatar::init(hero->resourceRun));
        }
        
        onEnterScene();
     
        this->_centerToBottom = 0;
        this->_centerToSide = 50;

        this->_hitBox = this->createBoundingBoxWithOrigin(Point(-this->_centerToSide,-this->_centerToBottom) ,Size(_centerToSide*2,this->getContentSize().height));
        
        this->_attackBox = this->createBoundingBoxWithOrigin(Point(0,this->getContentSize().height/2 - 25), Size(_centerToSide * 3,90));
        bref = true;
    } while (false);
    return bref;
}
Hero* Hero::create(int heroID)
{
    Hero* hero = new Hero();
    if(hero && hero->init(heroID))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    hero = NULL;
    return NULL;
}
void Hero::updateShadow()
{
    if(this->getChildByTag(TAG_SHADOWE))
    {
        this->removeChildByTag(TAG_SHADOWE);
    }
    if(this->_isMainHero)
    {
        const char* path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, AVATAR_SHADOWE_MAINHERO);
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
        // 连接该骨骼动画的资源
        ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        Armature* armature = Armature::create(AVATAR_SHADOWE_MAINHERO);
        armature->getAnimation()->playWithIndex(0);
        
        
        Sprite* shadow = Sprite::create(IMG_PUBLIC_SHADOW);
        armature->addChild(shadow);
        
        this->addChild(armature,0,TAG_SHADOWE);
    }
    else
    {
        Avatar::updateShadow();
    }
        
}
void Hero::idle()
{
    
    Avatar::idle();
  
}
void Hero::prepareJumpAttack(float delayTime)//准备跳击
{
    if(this->_actionState == kActionStatePrePareJumpAttack || this->_actionState == kActionStateJumpAttact)
    {
        return;
    }
 
    this->m_jumpAttackTime = delayTime;
    jump();
     this->setActionState(kActionStatePrePareJumpAttack);
}
void Hero::dash(float distance,float time)//冲撞的距离
{
  
    
    Avatar::dash(distance,time);
}

void Hero::updatePositon(float dt)
{
    Avatar::updatePositon(dt);
   
}
void Hero::walkWithDirection(Point direction,bool isHold)//行走
{
    Avatar::walkWithDirection(direction, isHold);
}
bool Hero::attack1()
{

    if(Avatar::attack1())
    {
         log("%s,attack1",this->getDictHero()->name.c_str());
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictHero()->skill1);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
        auto iter = skillCDMap->find(dictSkill->id);
        if (iter != skillCDMap->end())
        {
            skillCDMap->erase(iter);
        }
        
        skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
        return true;
    }
    return false;
}

bool Hero::attack2()// 攻击2
{

    if(Avatar::attack2())
    {
        log("%s,attack2",this->getDictHero()->name.c_str());
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictHero()->skill2);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
    return true;
    
}
bool Hero::attack3()// 攻击3
{
 
    if(Avatar::attack3())
    {
        log("%s,attack3",this->getDictHero()->name.c_str());
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictHero()->skill3);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
    return true;
}
bool Hero::attack4()
{
//    if(!this->_isMainHero)
//    {
//        log("sldfjk attack2 attack2");
//    }
    if(Avatar::attack4())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictHero()->skill4);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
        return true;
    }
    else
    {
        return false;
    }

}
bool Hero::attack5()
{
   
    if(Avatar::attack5())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictHero()->skill5);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
    return true;
}
bool Hero::skill1()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    if(getIsCDState(getDictHero()->skill7) || !this->_isInRoad || _actionState == kActionStateSkill1)
    {
        return false;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill7);
    if(!dictSkill)
    {
       return false;
    }
 
    if(Avatar::skill1())
    {
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
        if(dictSkill && dictSkill->fullScreen.size() > 0)
        {
            PublicShowUI::broadUserMsg(CUSTOM_CAMERA_IN, this);
        }
        
        auto iter = skillCDMap->find(dictSkill->id);
        if (iter != skillCDMap->end())
        {
            skillCDMap->erase(iter);
        }
        
        skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
        if(this->_isMainHero)
        {
            PublicShowUI::broadUserMsg(CUSTOM_SKILL1_CD, __Integer::create(dictSkill->id));
        }
    }
     onUseSkill(dictSkill);
    return true;

}
bool Hero::skill2()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    
    if(getIsCDState(getDictHero()->skill8) || !this->_isInRoad || _actionState == kActionStateSkill2)
    {
        return false;
    }
    if(Avatar::skill2())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill8);
        if(!dictSkill)
        {
            return false;
        }
        if(dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
        if(dictSkill->fullScreen.size() > 0)
        {
            PublicShowUI::broadUserMsg(CUSTOM_CAMERA_IN, this);
        }
        
        auto iter = skillCDMap->find(dictSkill->id);
        if (iter != skillCDMap->end())
        {
            skillCDMap->erase(iter);
        }
        skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
        if(this->_isMainHero)
        {
            PublicShowUI::broadUserMsg(CUSTOM_SKILL2_CD, __Integer::create(dictSkill->id));
        }
        onUseSkill(dictSkill);
    }
    
    return true;
 
}
bool Hero::skill3()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    
    if(getIsCDState(getDictHero()->skill9) || !this->_isInRoad || _actionState == kActionStateSkill3)
    {
        return false;
    }
    if(!Avatar::skill3())
    {
        return false;
    }
   
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill9);
    if(!dictSkill)
    {
        return false;
    }
    if(dictSkill->soundUse.size())
    {
        SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
    }
    if(dictSkill->fullScreen.size() > 0)
    {
        PublicShowUI::broadUserMsg(CUSTOM_CAMERA_IN, this);
    }
  
    auto iter = skillCDMap->find(dictSkill->id);
    if (iter != skillCDMap->end())
    {
        skillCDMap->erase(iter);
    }
    skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
    if(this->_isMainHero)
    {
         PublicShowUI::broadUserMsg(CUSTOM_SKILL3_CD, __Integer::create(dictSkill->id));
    }
     onUseSkill(dictSkill);
    return true;
  
}
bool Hero::skill4()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    if(getIsCDState(getDictHero()->skill10) || _actionState == kActionStateSkill4)
    {
        return false;
    }
    if(!Avatar::skill4())
    {
        return false;
    }
 
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill10);
    if(!dictSkill)
    {
        return false;
    }
    if(dictSkill->soundUse.size())
    {
        SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
    }
    auto iter = skillCDMap->find(dictSkill->id);
    if (iter != skillCDMap->end())
    {
        skillCDMap->erase(iter);
    }
    skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
    if(this->_isMainHero)
    {
        PublicShowUI::broadUserMsg(CUSTOM_SKILL4_CD, __Integer::create(dictSkill->id));
    }
    this->setActionState(kActionStateSkill4);
    onUseSkill(dictSkill);
    return true;
}
bool Hero::usePassSkill()//使用被动技能
{
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill7);
    string evt  = AVATAR_ATTACK_EVENT;
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt = evt + "_" + PublicShowUI::numberToString(getDictHero()->skill7);
        onFrameEvent(NULL,evt,0,0);
    }
    dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill8);
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt  = AVATAR_ATTACK_EVENT;
         evt = evt + "_" + PublicShowUI::numberToString(getDictHero()->skill8);
        onFrameEvent(NULL,evt,0,0);
    }
    dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill9);
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt  = AVATAR_ATTACK_EVENT;
        evt = evt + "_" + PublicShowUI::numberToString(getDictHero()->skill9);
        onFrameEvent(NULL,evt,0,0);
    }
    return true;
}
void Hero::onUseSkill(DictSkill* dictSkill)
{
//    switch (dictSkill->type) {
//        case DictSkillTypeEnumDictSummonSkill://召唤
//            PublicShowUI::broadUserMsg(CUSTOM_BATTLE_SUMMONED_SKILL, this);
//            break;
//            
//        default:
//            break;
//    }
}
int Hero::getCurSkillID()
{
    int dictSkillID = 0;
    switch (this->_actionState) {
        case kActionStateSkill1:
            dictSkillID = this->getDictHero()->skill7;
            break;
        case kActionStateSkill2:
            dictSkillID = this->getDictHero()->skill8;
            break;
        case kActionStateSkill3:
            dictSkillID = this->getDictHero()->skill9;
            break;
        case kActionStateSkill4:
            dictSkillID = this->getDictHero()->skill10;
            break;
            
        default:
            break;
    }
    return dictSkillID;
}
void Hero::jump()//跳
{
    
    Avatar::jump();
}
void Hero::jumpAttact(float dt)//跳击
{
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill6);
    if(dictSkill && dictSkill->soundUse.size())
    {
        SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
    }
    Avatar::jumpAttact(dt);
}
void Hero::hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//受伤
{
    Avatar::hurtWithDamage(damage, isCrit,isBlock,isSkillAttack);
}
void Hero::setActionState(ActionState state)
{
    Avatar::setActionState(state);
}
void Hero::knockDown(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击倒
{
    Avatar::knockDown(damage,isCrit,isBlock,isSkillAttack);
}
void Hero::knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack)//击飞
{
    Avatar::knockFly(damage,isCrit,isBlock,isSkillAttack);
}
void Hero::knockBack(float damage,Point targetPoint,bool isCrit,bool isBlock,bool isSkillAttack)
{
    Avatar::knockBack(damage, targetPoint,isCrit,isBlock,isSkillAttack);
}
void Hero::onAddBloodBuff(int buffType) //持续回血
{
    if(buffType != DictBuffTypeEnumHealOnTime)
    {
        return;
    }
    Avatar::onAddBloodBuff(buffType);
    BuffEffectData* buffDatta = buffListMap->at(buffType);
    if(buffDatta)
    {
        HeroHeadListLayer::getInstance()->onHeroAddBlood(this->getUID(), buffDatta->damage);
    }
    
}
void Hero::onHurtBloodBuff(int buffType)//持续伤害
{
    if(buffType != DictBuffTypeEnumDamageOnTime)
    {
        return;
    }
    Avatar::onHurtBloodBuff(buffType);
    BuffEffectData* buffDatta = buffListMap->at(buffType);
    if(buffDatta)
    {
        HeroHeadListLayer::getInstance()->onHeroHurt(this->getUID(), buffDatta->damage);
    }
    
}
void Hero::dead()
{
    
    _angryValue = 0;
    if(!this->getParent())
    {
        this->setActionState(kActionStateDead);
        return;
    }
    if(this->_actionState == kActionStateDead)
    {
        return;
    }
    SoundManager::playEffectMusic(this->getDictHero()->dieVoice.c_str());
    Avatar::dead();
    PublicShowUI::broadUserMsg(CUSTOM_BATTLE_HERO_DEAD, this);
}

void Hero::onActionCompleted()
{
    if(this->_isMainHero)
    {
       
    }
    else
    {
        this->m_actionFinishedCallBack = NULL;
    }
   
    Avatar::onActionCompleted();
}
long Hero::getLeftCdTime(int skillID)//得到剩余CD时间
{
    auto iter = skillCDMap->find(skillID);
    if (iter != skillCDMap->end())
    {
         DictSkill* dictSkill = DictSkillManager::getInstance()->getData(skillID);
        long long lastTime = skillCDMap->at(skillID);
        long long time = (lastTime + dictSkill->coldDowm * 1000) - TimeUtil::getNativeTime();
  
        if(time < 0)
        {
            time = 0;
        }
        return time;
    }
    return 0;
}
bool Hero::block()//格档
{
    if(!Avatar::block())
    {
        return false;
    }
    return true;
}
bool Hero::duck()//闪避
{
  
  
    if(getIsCDState(getDictHero()->skill12))
    {
        return false;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictHero()->skill12);
    if(dictSkill)
    {
        float distance = dictSkill->heroShiftForward > 0 ? dictSkill->heroShiftForward * GlobalInfo::getInstance()->map_tiled_width * GlobalInfo::getInstance()->m_avatarScale : -dictSkill->heroShiftBackward * GlobalInfo::getInstance()->map_tiled_width * GlobalInfo::getInstance()->m_avatarScale;
         if(Avatar::duck(distance,.3))
         {
             auto iter = skillCDMap->find(dictSkill->id);
             if (iter != skillCDMap->end())
             {
                 skillCDMap->erase(iter);
             }
             skillCDMap->insert(std::make_pair(dictSkill->id, TimeUtil::getNativeTime()));
             if(this->_isMainHero)
             {
                 PublicShowUI::broadUserMsg(CUSTOM_SKILL5_CD, __Integer::create(dictSkill->id));
             }
         }

        
    }
        
    return false;
}