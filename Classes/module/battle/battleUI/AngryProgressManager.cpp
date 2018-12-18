 //
//  AngryProgressManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/19.
//
//

#include "AngryProgressManager.h"
#include "../../../common/ImagePath.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/noticeManager/NoticeManager.h"
//#include "../data/BattleDefine.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
AngryProgressManager* AngryProgressManager::_instance = NULL;
AngryProgressManager* AngryProgressManager::getInstance()
{
    if(!_instance)
    {
        _instance = new AngryProgressManager();
        _instance->autorelease();
    }
    return _instance;
}
AngryProgressManager::AngryProgressManager()
:progressTimer(NULL)
,m_hero(NULL)
,TAG_ANGRYEFFECT_BACK(1)
,TAG_ANGRYEFFECT_FRONT(2)
,TAG_SKLLBTN(3)
,isGuided(false)
,isAngry(false)
{
    setProgress();
    setAngryBtn();
}
AngryProgressManager::~AngryProgressManager()
{
    m_hero = NULL;
    progressTimer = NULL;
    _instance = NULL;
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAngerSkill);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAngerTube);
    
}
void AngryProgressManager::setProgress()
{
//    Sprite* progressBg = Sprite::create(IMG_BATTLE_ANGRYPROGRESSBG);
    TouchSprite* progressBg = TouchSprite::createWithPic(IMG_BATTLE_ANGRYPROGRESSBG, this, callfuncN_selector(AngryProgressManager::onProgressClick));
    progressBg->setAnchorPoint(Point::ZERO);
    
    
    Sprite* progress = Sprite::create(IMG_BATTLE_ANGRYPROGRESS);
    progress->setAnchorPoint(Point::ZERO);
    this->progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point::ZERO);
    
    progressTimer->setPosition(progressBg->getContentSize().width - progressTimer->getContentSize().width + 2, 0);
    progressBg->addChild(progressTimer,1);
//    progressTimer->setPercentage(100);
    this->setContentSize(progressBg->getContentSize());
    this->addChild(progressBg);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAngerTube, progressBg);
}
void AngryProgressManager::onProgressClick(Node* pSender)
{
  
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAngerTube);
}
void AngryProgressManager::setAngryBtn()
{
    TouchSprite* btn = TouchSprite::createWithPic(IMG_SKILL_ANGRYICON, this, callfuncN_selector(AngryProgressManager::onBtnClick));
    if(!btn)
    {
        return;
    }
    btn->isButtonMode = true;
    btn->setPosition(this->getContentSize().width  + btn->getContentSize().width/2, 30);
    this->addChild(btn,3,TAG_SKLLBTN);
    Size size = this->getContentSize();
    size.width = btn->getPositionX() + btn->getContentSize().width/2;
    this->setContentSize(size);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAngerSkill, btn);
}
void AngryProgressManager::onBtnClick(Node* psender)
{
    if(!this->isVisible())
    {
        return;
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAngerSkill);
    if(this->progressTimer->getPercentage() < 100 && !GlobalInfo::getInstance()->isDebug)
    {
        NoticeManager::getInstance()->showNotice("您的怒气值还不够哦!");
        if(!GlobalInfo::getInstance()->isDebug)
        {
            return;
        }
   
    }
 
    PublicShowUI::broadUserMsg(CUSTOM_BATTLE_RELEASEBIGSKILL, m_hero);

   
  
}
void AngryProgressManager::updateMainHero(Hero* hero)
{
    m_hero = NULL;
    m_hero = hero;
    updateAngryValue();
}
void AngryProgressManager::showAngryEffect()
{
    const char* path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_BTN_EFFECTBACK);
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(AngryProgressManager::onEffectLoaded));
    
    path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, BIGSKILL_BTN_EFFECTFRONT);
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(AngryProgressManager::onEffectLoaded));
   
}
void AngryProgressManager::onEffectLoaded(float percent)
{
    if(percent < 1)
    {
        return;
    }
    if(this->getChildByTag(TAG_ANGRYEFFECT_BACK))
    {
        return;
    }
    Node* btn =this->getChildByTag(TAG_SKLLBTN);
    Armature* backEffect = Armature::create(BIGSKILL_BTN_EFFECTBACK);
    backEffect->setPosition(btn->getPosition());
    backEffect->getAnimation()->playWithIndex(0);
    Armature* frontEffect = Armature::create(BIGSKILL_BTN_EFFECTFRONT);
    frontEffect->setPosition(btn->getPosition());
    frontEffect->getAnimation()->playWithIndex(0);
    this->addChild(backEffect,1,TAG_ANGRYEFFECT_BACK);
    this->addChild(frontEffect,4,TAG_ANGRYEFFECT_FRONT);
}
void AngryProgressManager::updateAngryValue()
{
    if(!this->isVisible())
    {
        return;
    }
    if(!m_hero || (m_hero->_angryValue >= TOTAL_ANGRY_VALUE && progressTimer->getPercentage() >= 100))
    {
        return;
    }
    progressTimer->stopAllActions();
    float percent = m_hero->_angryValue / TOTAL_ANGRY_VALUE * 100;
    if(percent > progressTimer->getPercentage())
    {
         progressTimer->runAction(ProgressFromTo::create(.5, progressTimer->getPercentage(), percent));
    }
    else
    {    
        progressTimer->setPercentage(percent);
    }
   
    if(percent >= 100)
    {
        if(!isAngry)
        {
            isAngry = true;
            showAngryEffect();
            if(!isGuided)
            {
                isGuided  = true;
            }
            
        }
    }
    else
    {
        isAngry = false;
        if(this->getChildByTag(TAG_ANGRYEFFECT_FRONT))
        {
            this->removeChildByTag(TAG_ANGRYEFFECT_BACK);
            this->removeChildByTag(TAG_ANGRYEFFECT_FRONT);
        }
    }
}