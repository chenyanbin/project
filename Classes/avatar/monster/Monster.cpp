//
//  Monster.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#include "Monster.h"
#include "../../module/battle/data/MapDataManager.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../../commonData/enum/DictSkillTypeEnum.h"
Monster::Monster()
:_dictMonster(NULL)
,_isBoss(false)
,_blockNum(0)
,_turnWaves(0)
,_touch(0)
,_battleMonsterID(0)
,m_attackNode(NULL)
,isReadyAttack(false)
{
    
}
Monster::~Monster()
{
   CC_SAFE_RELEASE_NULL(_dictMonster);
}
bool Monster::init(int monsterID)
{
    bool bref = false;
    do {
        DictMonster* monster = DictMonsterManager::getInstance()->getData(monsterID);
        CC_BREAK_IF(!monster);
        this->setDictMonster(monster);
        this->_avatarName = monster->name;
        this->m_avatarPosY = monster->resourceHighShifting;
        this->m_avatarPosX = monster->resourceShifting;
        this->m_initAvatarPosX = this->m_avatarPosX;
        CC_BREAK_IF(!Avatar::init(monster->resource));
        this->_centerToBottom = 0;
        this->_centerToSide = 50;
        this->_walkSpeed = 80;
        _avatarType = AVATAR_TYPE_MONSTER;
        this->_hitBox = this->createBoundingBoxWithOrigin(Point(-this->_centerToSide,-this->_centerToBottom) ,Size(_centerToSide*2,this->getContentSize().height));
        
        this->_attackBox = this->createBoundingBoxWithOrigin(Point(this->_centerToSide,this->getContentSize().height/2 - 16), Size(32,32));

        isShowBlood = true;
        m_attackNode = DrawNode::create();
        m_attackNode->setAnchorPoint(Point::ZERO);
        this->addChild(m_attackNode,-1);
        bref = true;
    } while (false);
    return bref;
}
Monster* Monster::create(int monsterID)
{
    Monster* monster = new Monster();
    if(monster && monster->init(monsterID))
    {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    monster = NULL;
    return NULL;
}
void Monster::updateShadow()
{
    if(this->_isBoss)
    {
        Avatar::updateBossShadow();
    }
    else
    {
        Avatar::updateShadow();
    }
    
}
bool Monster::attack1()
{
   
    if(Avatar::attack1())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictMonster()->skill1);
        if(dictSkill)
        {
            if(dictSkill->soundUse.size())
            {
                SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
            }
          
        }
       
        
    }
    
    return true;
}
bool Monster::attack2()
{
   
   if(Avatar::attack2())
   {
       DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictMonster()->skill2);
       if(dictSkill)
       {
           if(dictSkill->soundUse.size())
           {
                SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
           }
          
    
       }
       
       
   }
     return true;
}
bool Monster::attack3()
{

    if(Avatar::attack3())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictMonster()->skill3);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
           
        }
    }
    return true;
}
bool Monster::attack4()
{
    if( Avatar::attack4())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictMonster()->skill4);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
   return true;
}
bool Monster::attack5()
{
    if(Avatar::attack5())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(this->getDictMonster()->skill5);
        if(dictSkill && dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
    return true;
        
}
bool Monster::skill1()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    if(this->_actionState != kActionStateIdle && _actionState != kActionStateWalk)
    {
        return false;;
    }
    if(getIsCDState(getDictMonster()->skill7) || !this->_isInRoad)
    {
        return false;
    }
    if(!Avatar::skill1())
    {
        return false;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill7);
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
    isReadyAttack = false;
    return true;
}
bool Monster::skill2()
{
    
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    if(this->_actionState != kActionStateIdle && _actionState != kActionStateWalk)
    {
        return false;
    }
    if(getIsCDState(getDictMonster()->skill8) || !this->_isInRoad)
    {
        return false;
    }
    if(!Avatar::skill2())
    {
        return false;
    }
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill8);
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
     isReadyAttack = false;
     return true;
}
bool Monster::skill3()
{
    if(this->hasBuffState(DictBuffTypeEnumSeal))
    {//封印
        return false;
    }
    if(this->_actionState != kActionStateIdle && _actionState != kActionStateWalk)
    {
        return false;
    }
    if(getIsCDState(getDictMonster()->skill9) || !this->_isInRoad)
    {
        return false;
    }
    if(Avatar::skill3())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill9);
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

    }
    isReadyAttack = false;
    return true;
}
bool Monster::skill4()
{
   
    if(Avatar::skill4())
    {
        DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill10);
        if(dictSkill->soundUse.size())
        {
            SoundManager::playEffectMusic(dictSkill->soundUse.c_str());
        }
    }
    isReadyAttack = false;
    return true;
}
void Monster::dash(float distance,float time)//冲撞的距离
{
    Avatar::dash(distance,time);
    
}
void Monster::knockFly(float damage,bool isCrit,bool isBlock,bool isSkillAttack)
{
    Avatar::knockFly(damage,isCrit,isBlock,isSkillAttack);
}
void Monster::idle()
{
    Avatar::idle();
}
void Monster::dead()
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
    SoundManager::playEffectMusic(this->getDictMonster()->dieVoice.c_str());
    Avatar::dead();
    
}
bool Monster::usePassSkill()//使用被动技能
{
    string evt  = AVATAR_ATTACK_EVENT;
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill7);
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt = evt + "_" + PublicShowUI::numberToString(getDictMonster()->skill7);
        onFrameEvent(NULL,evt,0,0);
    }
    dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill8);
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt = evt + "_" + PublicShowUI::numberToString(getDictMonster()->skill8);
        onFrameEvent(NULL,evt,0,0);
    }
    dictSkill = DictSkillManager::getInstance()->getData(getDictMonster()->skill9);
    if(dictSkill && dictSkill->type == DictSkillTypeEnumPassiveSkill)
    {
        evt = evt + "_" + PublicShowUI::numberToString(getDictMonster()->skill9);
        onFrameEvent(NULL,evt,0,0);
    }
    return true;
}
void Monster::hurtWithDamage(float damage,bool isCrit,bool isBlock,bool isSkillAttack)
{
    Avatar::hurtWithDamage(damage, isCrit,isBlock,isSkillAttack);
}
void Monster::updatePositon(float dt)
{
    Avatar::updatePositon(dt);
}
void Monster::onEnterScene()//进入视野
{
    if(this->getAvatarProp() && this->getAvatarProp()->health <= 0)
    {
        return;
    }
    Avatar::onEnterScene();
    if(this->isNewEnter && this->_isBoss)
    {
        if(this->m_avatar)
        {
            this->m_avatar->setVisible(false);
        }
        addBornEffect(BOSS_BORN_EFFECT);
        this->isNewEnter = false;
    }

   
}
void Monster::showAttackRange(int frontRange,int backRange)
{
    if(!this->_isBoss || isReadyAttack)
    {
        return;
    }
    hideAttackRange();
    if(this->isLeft)
    {
        showLeftAttackRange(frontRange,backRange);
    }
    else
    {
        showRightAttackRange(frontRange,backRange);
    }
    isReadyAttack = true;
}
void Monster::hideAttackRange()
{
  
    m_attackNode->removeAllChildren();
    m_attackNode->clear();
    isReadyAttack = false;
}
int Monster::getCurSkillID()
{
    int dictSkillID = 0;
    switch (this->_actionState) {
        case kActionStateSkill1:
            dictSkillID = this->getDictMonster()->skill7;
            break;
        case kActionStateSkill2:
            dictSkillID = this->getDictMonster()->skill8;
            break;
        case kActionStateSkill3:
            dictSkillID = this->getDictMonster()->skill9;
            break;
        case kActionStateSkill4:
            dictSkillID = this->getDictMonster()->skill10;
            break;
            
        default:
            break;
    }
    return dictSkillID;
}
void Monster::showLeftAttackRange(int frontRange,int backRange)
{
    Size size;
    size.width = GlobalInfo::getInstance()->map_tiled_width * frontRange + backRange * GlobalInfo::getInstance()->map_tiled_width;
    size.height = 3 * GlobalInfo::getInstance()->map_tiled_height;
   
    Point rectangle[4];
    rectangle[0] = Point(-backRange,0);
    rectangle[1] = Point(-size.width, 0);
    rectangle[2] = Point(-size.width,size.height);
    rectangle[3] = Point(0,size.height);
  
    Color4F color(1,0,0,.4);
   
    //画一个多边形
    m_attackNode->drawPolygon(rectangle, 4, color, 0, Color4F(0,0,0,0));
    m_attackNode->setPositionY(-size.height/2);
   

    m_attackNode->setSkewX(45);
 
}
void Monster::showRightAttackRange(int frontRange,int backRange)
{
    Size size;
    size.width = GlobalInfo::getInstance()->map_tiled_width * frontRange + backRange * GlobalInfo::getInstance()->map_tiled_width;
    size.height = 3 * GlobalInfo::getInstance()->map_tiled_height;
    
    Point rectangle[4];
    rectangle[0] = Point(backRange,0);
    rectangle[1] = Point(size.width, 0);
    rectangle[2] = Point(size.width,size.height);
    rectangle[3] = Point(0,size.height);
    
    Color4F color(1,0,0,.4);
    
    //画一个多边形
    m_attackNode->drawPolygon(rectangle, 4, color, 0, Color4F(0,0,0,0));
    m_attackNode->setPositionY(-size.height/2);
    
    
    m_attackNode->setSkewX(45);
}
void Monster::onExitScene()//退出视野
{
    Avatar::onExitScene();
   if(this->getAvatarProp()->health <= 0)
   {
       this->_isPause  = false;
       this->setActionState(kActionStateDead);
       this->removeFromParent();
   }
}
void Monster::onBossBorn()
{
    if(this->m_avatar)
    {
        this->m_avatar->setVisible(true);
    }
}
void Monster::addBornEffect(const char* effectName)
{
    if(this->getChildByTag(TAG_EFFECT))
    {
        return;
    }
    CommonEffect* pArmature = CommonEffect::create(effectName,false,true,CC_CALLBACK_0(Monster::onBossBorn, this));
 
    pArmature->setAnchorPoint(Point(.5,0));
    
    this->addChild(pArmature,10,TAG_EFFECT);

}

