//
//  ControlBtnPanel.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/9.
//
//

#include "ControlBtnPanel.h"
#include "../../../common/ImagePath.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../../common/PublicShowUI.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/data/FunctionOpenManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../commonData/data/GuideButtonManager.h"
#include "../../../commonData/enum/DictNewGuideEventEnum.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../commonData/enum/DictSkillCostWayEnum.h"
ControlBtnPanel::ControlBtnPanel()
:m_callBack(NULL)
,TAG_CD(1)
,TAG_CDLABEL(2)
,m_MainHero(NULL)
,m_isMoveing(false)
,m_isInited(false)
{
    
}
ControlBtnPanel::~ControlBtnPanel()
{
    m_callBack = NULL;
    m_releaseBack = NULL;
    m_MainHero = NULL;
}
bool ControlBtnPanel::init(const ccMenuCallback& callback,const ccMenuCallback& releaseCallBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->m_callBack = callback;
        this->m_releaseBack = releaseCallBack;
        this->isAnimation = false;
        this->isShowGrayBg = false;
//        setBg();
        setButton();
        bref = true;
    } while (false);
    return bref;
}
void ControlBtnPanel::setBg()
{
//    Sprite* bg = Sprite::create(IMG_BATTLE_BTNBG);
//    bg->setAnchorPoint(Point::ZERO);
//    this->addChild(bg,0);
//    this->setContentSize(bg->getContentSize());
}
ControlBtnPanel* ControlBtnPanel::create(const ccMenuCallback& callback,const ccMenuCallback& releaseCallBack)
{
    ControlBtnPanel* panel = new ControlBtnPanel();
    if(panel && panel->init(callback,releaseCallBack))
    {
        panel->autorelease();
        return panel;
    }
    CC_SAFE_DELETE(panel);
    panel = NULL;
    return NULL;
}
void ControlBtnPanel::reset(Hero* mainHero)
{
    if(m_MainHero == mainHero)
    {
        return;
    }
    this->m_MainHero = mainHero;
    this->removeChildByTag(BUTTON_SKILL1);
    this->removeChildByTag(BUTTON_SKILL2);
    this->removeChildByTag(BUTTON_SKILL3);
    this->removeChildByTag(BUTTON_SKILL4);
    this->removeChildByTag(BUTTON_ATTACK);
    this->removeChildByTag(BUTTON_PROTECTED);
    setButton();
}
void ControlBtnPanel::setButton()
{
    if(!m_MainHero)
    {
        return;
    }
    DictHero* dictHero = m_MainHero ? m_MainHero->getDictHero() : DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    if(!dictHero)
    {
        return;
    }
    Sprite* cdSprite = NULL;
    TouchSprite* skillBtn3 = NULL;
    ProgressTimer* pt = NULL;
    float leftTime = 0;
    int offX = 15;
    const char* iconPath = NULL;
    Node* nowNode = NULL;
    DictSkill* skill3 = DictSkillManager::getInstance()->getData(dictHero->skill9);
    Point cp = Point::ZERO;
    Sprite* skillform = Sprite::create(IMG_SKILL_FORM);
    if(skill3 && skill3->icon.size() && m_MainHero->getAvatarProp()->quality >= SKILL3_OPEN_QUALITY)
    {
        iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, skill3->icon.c_str());
        skillBtn3 = TouchSprite::createWithPic(iconPath);
        skillBtn3->isButtonMode = true;
        skillBtn3->addTouchBegainCallBack(this, callfuncN_selector(ControlBtnPanel::onButtonClick));
        skillBtn3->setPosition(cp);
        this->addChild(skillBtn3,3,BUTTON_SKILL3);
        cdSprite = Sprite::create(iconPath);
        cdSprite->setColor(Color3B::BLACK);
        cdSprite->setOpacity(225);
        pt=ProgressTimer::create(cdSprite);
        
        pt->setPosition(skillBtn3->getContentSize().width/2, skillBtn3->getContentSize().height/2);
        //转圈的CD实现
        pt->setType(ProgressTimer::Type::RADIAL);
        skillBtn3->addChild(pt,2,TAG_CD);
        skillBtn3->addChild(skillform,4);
        skillform->setPosition(skillBtn3->getContentSize().width/2, skillBtn3->getContentSize().height/2);
        leftTime = m_MainHero ? m_MainHero->getLeftCdTime(skill3->id) / 1000: 0;
        //    pt->setPercentage(100 - leftTime / skill3->coldDowm * 100);
        pt->setPercentage(leftTime / skill3->coldDowm * 100);
        onSkill3CD(leftTime,false);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSkillAttack3,skillBtn3);
        nowNode = skillBtn3;
        if(GlobalInfo::getInstance()->isPlayedGuideBattle && !m_isInited)
        {
            skillBtn3->setVisible(false);
        }
        else
        {
            skillBtn3->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumCoolDownSkill3));
        }
      
        cp = skillBtn3->getPosition();
        cp.x = cp.x + skillBtn3->getContentSize().width + offX;
    }
   
    DictSkill* skill2 = DictSkillManager::getInstance()->getData(dictHero->skill8);
    TouchSprite* skillBtn2 = NULL;
    if(skill2 && skill2->icon.size() && m_MainHero->getAvatarProp()->quality >= SKILL2_OPEN_QUALITY)
    {
        skillform = Sprite::create(IMG_SKILL_FORM);
        
        iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, skill2->icon.c_str());
        skillBtn2 = TouchSprite::createWithPic(iconPath);
        if(!skillBtn2)
        {
            return;
        }
         skillform->setPosition(skillBtn2->getContentSize().width/2, skillBtn2->getContentSize().height/2);
        skillBtn2->isButtonMode = true;
        skillBtn2->addTouchBegainCallBack(this, callfuncN_selector(ControlBtnPanel::onButtonClick));
        skillBtn2->setPosition(cp);
        this->addChild(skillBtn2,2,BUTTON_SKILL2);
        cdSprite = Sprite::create(iconPath);
        cdSprite->setColor(Color3B::BLACK);
        cdSprite->setOpacity(225);
        pt=ProgressTimer::create(cdSprite);
        
        pt->setPosition(skillBtn2->getContentSize().width/2, skillBtn2->getContentSize().height/2);
        //转圈的CD实现
        pt->setType(ProgressTimer::Type::RADIAL);
        skillBtn2->addChild(pt,2,TAG_CD);
        skillBtn2->addChild(skillform,4);
        leftTime = m_MainHero ? m_MainHero->getLeftCdTime(skill2->id) / 1000: 0;
        pt->setPercentage(leftTime / skill2->coldDowm * 100);
        onSkill2CD(leftTime,false);
         GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSkillAttack2,skillBtn2);
        nowNode = skillBtn2;
        if(GlobalInfo::getInstance()->isPlayedGuideBattle && !m_isInited)
        {
            skillBtn2->setVisible(false);
        }
        else
        {
            skillBtn2->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumCoolDownSkill2));
        }
        cp = skillBtn2->getPosition();
        cp.x = cp.x + skillBtn2->getContentSize().width + offX;
    }
    TouchSprite* skillBtn1 = NULL;
 
    DictSkill* skill1 = DictSkillManager::getInstance()->getData(dictHero->skill7);
    if(skill1 && m_MainHero->getAvatarProp()->quality >= SKILL1_OPEN_QUALITY)
    {
        iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, skill1->icon.c_str());
        skillBtn1 = TouchSprite::createWithPic(iconPath);
    }
    
    if(skillBtn1)
    {
        
        skillform = Sprite::create(IMG_SKILL_FORM);
        skillform->setPosition(skillBtn1->getContentSize().width/2, skillBtn1->getContentSize().height/2);
        skillBtn1->isButtonMode = true;
        skillBtn1->addTouchBegainCallBack(this, callfuncN_selector(ControlBtnPanel::onButtonClick));
        skillBtn1->setPosition(cp);
        skillBtn1->addChild(skillform,4);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSkillAttack1, skillBtn1);
        this->addChild(skillBtn1,1,BUTTON_SKILL1);
        cdSprite = Sprite::create(iconPath);
        cdSprite->setColor(Color3B::BLACK);
        cdSprite->setOpacity(225);
        pt=ProgressTimer::create(cdSprite);
        //转圈的CD实现
        
        pt->setPosition(skillBtn1->getContentSize().width/2, skillBtn1->getContentSize().height/2);
        pt->setType(ProgressTimer::Type::RADIAL);
        skillBtn1->addChild(pt,2,TAG_CD);
      
        leftTime = m_MainHero ? m_MainHero->getLeftCdTime(skill1->id) / 1000: 0;
        pt->setPercentage(leftTime / skill1->coldDowm * 100);
        onSkill1CD(leftTime,false);
        nowNode = skillBtn1;
        if(GlobalInfo::getInstance()->isPlayedGuideBattle && !m_isInited)
        {
            skillBtn1->setVisible(false);
        }
        else
        {
            skillBtn1->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumCoolDownSkill));
        }
        cp = skillBtn1->getPosition();
        cp.x = skillBtn1->getPositionX() + skillBtn1->getContentSize().width + offX;
    }

  
    
    //防御或闪避

    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(dictHero->skill12);
    iconPath = NULL;
    if(dictSkill)
    {
        if(dictSkill->costWay == DictSkillCostWayEnumDodgeSkill)//闪避
        {
            iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, "dodge");
        }
        else if(dictSkill->costWay == DictSkillCostWayEnumBlockSkill)//格档
        {
            iconPath = PublicShowUI::getResImgPath(IMG_SKILL_ICON, "block");
        }
    }
    
    if(iconPath)
    {
        skillform = Sprite::create(IMG_SKILL_FORM);
        TouchSprite* protectedBtn = TouchSprite::createWithPic(iconPath,this,callfuncN_selector(ControlBtnPanel::onButtonRelease));
        protectedBtn->isButtonMode = true;
        skillform->setPosition(protectedBtn->getContentSize().width/2, protectedBtn->getContentSize().height/2);
        protectedBtn->addChild(skillform,4);
        float sx = skillBtn1->getContentSize().width / protectedBtn->getContentSize().width;
        protectedBtn->setScale(sx);
        skillform->setScale( 1 + sx);
        protectedBtn->addTouchBegainCallBack(this, callfuncN_selector(ControlBtnPanel::onButtonClick));
        protectedBtn->setPosition(cp);
        this->addChild(protectedBtn,4,BUTTON_PROTECTED);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumDodgeParryButton, protectedBtn);
        
        
        
        cdSprite = Sprite::create(iconPath);
        cdSprite->setColor(Color3B::BLACK);
        cdSprite->setOpacity(225);
        pt=ProgressTimer::create(cdSprite);
        //转圈的CD实现
        
        pt->setPosition(protectedBtn->getContentSize().width/2, protectedBtn->getContentSize().height/2);
        pt->setType(ProgressTimer::Type::RADIAL);
        protectedBtn->addChild(pt,2,TAG_CD);
        
        leftTime = m_MainHero ? m_MainHero->getLeftCdTime(dictSkill->id) / 1000: 0;
        pt->setPercentage(leftTime / dictSkill->coldDowm * 100);
        onSkill5CD(leftTime,false);
        nowNode = protectedBtn;
        if(GlobalInfo::getInstance()->isPlayedGuideBattle && !m_isInited)
        {
            protectedBtn->setVisible(false);
        }
//        else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi && GlobalInfo::getInstance()->stageMode == kStageModeCommon)
//        {
//            if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->id < 33)
//            {
//               protectedBtn->setVisible(false);
//            }
//            
//        }
        else
        {
            protectedBtn->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumDodgeParrySkill));
        }
    }
    if(nowNode)
    {
        Size size = nowNode->getContentSize();
        size.width = nowNode->getPositionX() + nowNode->getContentSize().width;
        this->setContentSize(size);
    }
   
    m_isInited = true;
    //跳跃不显示。为了回调方便。用了个空的结点代替
    Node* skillBtn4 = Node::create();
    this->addChild(skillBtn4,4,BUTTON_SKILL4);
}
void ControlBtnPanel::onButtonRelease(Node* pSender)
{
    if(this->m_releaseBack)
    {
        this->m_releaseBack(pSender);
    }
}
void ControlBtnPanel::onSkill1CD(float time,bool isCommonCD)
{
    
    Node* skillBtn1 = this->getChildByTag(BUTTON_SKILL1);
    if(!skillBtn1)
    {
        return;
    }
    onTimeDelay(skillBtn1,time);
    ProgressTimer* pt = (ProgressTimer*)skillBtn1->getChildByTag(TAG_CD);
//    ProgressFromTo *t1=ProgressFromTo::create(time,pt->getPercentage(), 100);
    float percent = pt->getPercentage() == 0 ? 100 : pt->getPercentage();
    ProgressFromTo *t1=ProgressFromTo::create(time,percent, 0);
    ProgressTo *t2 = NULL;//ProgressTo::create(0,0);
    pt->runAction(Sequence::create(t1,t2, NULL));
//    if(isCommonCD)
//    {
//        playCommonCD(skillBtn1);
//    }
  
}
void ControlBtnPanel::onSkill2CD(float time,bool isCommonCD)
{
    Node* skillBtn2 = this->getChildByTag(BUTTON_SKILL2);
    if(!skillBtn2)
    {
        return;
    }
    ProgressTimer* pt = (ProgressTimer*)skillBtn2->getChildByTag(TAG_CD);
    onTimeDelay(skillBtn2,time);
//    pt->stopAllActions();
//    ProgressFromTo *t1=ProgressFromTo::create(time,pt->getPercentage(), 100);
    float percent = pt->getPercentage() == 0 ? 100 : pt->getPercentage();
    ProgressFromTo *t1=ProgressFromTo::create(time,percent, 0);
    ProgressTo *t2 = NULL;//ProgressTo::create(0,0);
    pt->runAction(Sequence::create(t1,t2, NULL));
//    if(isCommonCD)
//    {
//        playCommonCD(skillBtn2);
//    }
}
void ControlBtnPanel::onSkill3CD(float time,bool isCommonCD)
{
    Node* skillBtn3 = this->getChildByTag(BUTTON_SKILL3);
    if(!skillBtn3)
    {
        return;
    }
    onTimeDelay(skillBtn3,time);
    ProgressTimer* pt = (ProgressTimer*)skillBtn3->getChildByTag(TAG_CD);

//    pt->stopAllActions();
//    ProgressFromTo *t1=ProgressFromTo::create(time,pt->getPercentage(), 100);
    float percent = pt->getPercentage() == 0 ? 100 : pt->getPercentage();
    ProgressFromTo *t1=ProgressFromTo::create(time,percent, 0);
    ProgressTo *t2 = NULL;//ProgressTo::create(0,0);
    pt->runAction(Sequence::create(t1,t2, NULL));
//    if(isCommonCD)
//    {
//        playCommonCD(skillBtn3);
//    }
}
void ControlBtnPanel::onSkill4CD(float time,bool isCommonCD)
{
//    Node* skillBtn4 = this->getChildByTag(BUTTON_SKILL4);
//    ProgressTimer* pt = (ProgressTimer*)skillBtn4->getChildByTag(TAG_CD);
//    ProgressFromTo *t1=ProgressFromTo::create(time,pt->getPercentage(), 100);
//    ProgressTo *t2=ProgressTo::create(0,0);
//    pt->runAction(Sequence::create(t1,t2, NULL));
//    if(isCommonCD)
//    {
//        playCommonCD(skillBtn4);
//    }
}
void ControlBtnPanel::onSkill5CD(float time,bool isCommonCD)
{
    Node* skillBtn5 = this->getChildByTag(BUTTON_PROTECTED);
    if(!skillBtn5)
    {
        return;
    }
    onTimeDelay(skillBtn5,time);
    ProgressTimer* pt = (ProgressTimer*)skillBtn5->getChildByTag(TAG_CD);

    float percent = pt->getPercentage() == 0 ? 100 : pt->getPercentage();
    ProgressFromTo *t1=ProgressFromTo::create(time,percent, 0);
    ProgressTo *t2 = NULL;
    pt->runAction(Sequence::create(t1,t2, NULL));
    //    if(isCommonCD)
    //    {
    //        playCommonCD(skillBtn3);
    //    }
}
void ControlBtnPanel::onTimeDelay(Node* target,float time)
{
    if(!target)
    {
        return;
    }
    Label* label = (Label*)target->getChildByTag(TAG_CDLABEL);
    if(!label)
    {
        label = PublicShowUI::getLabel(PublicShowUI::numberToString(time).c_str(),Color3B::WHITE,24,true,false);
       
        target->addChild(label,3,TAG_CDLABEL);
        label->setPosition(target->getContentSize().width/2, target->getContentSize().height/2);
    }
    if(time > 0)
    {
        
        CallFunc* callfun = CallFunc::create(CC_CALLBACK_0(ControlBtnPanel::onTimeDelay,this,target,time-1));
        target->runAction(Sequence::create(DelayTime::create(1),callfun, NULL));
        label->setString(PublicShowUI::numberToString((int)time));
        
    }
    else
    {
        label->setString("");
    }
}
void ControlBtnPanel::playCommonCD(Node* target)
{
    ProgressTimer* pt = NULL;
    Node* skillBtn1 = this->getChildByTag(BUTTON_SKILL1);
    Node* skillBtn2 = this->getChildByTag(BUTTON_SKILL2);
    Node* skillBtn3 = this->getChildByTag(BUTTON_SKILL3);
    if(target != skillBtn1 && skillBtn1)
    {
        pt = (ProgressTimer*)skillBtn1->getChildByTag(TAG_CD);
        if(pt->getPercentage() <= 0)
        {
            pt->stopAllActions();
            ProgressTo *t1=ProgressTo::create(COMMON_CD_TIME,100);
            ProgressTo *t2=ProgressTo::create(0,0);
            pt->runAction(Sequence::create(t1,t2, NULL));
        }
    }
    if(target != skillBtn2 && skillBtn2)
    {
        pt = (ProgressTimer*)skillBtn2->getChildByTag(TAG_CD);
        if(pt->getPercentage() <= 0)
        {
            pt->stopAllActions();
            ProgressTo *t1=ProgressTo::create(COMMON_CD_TIME,100);
            ProgressTo *t2=ProgressTo::create(0,0);
            pt->runAction(Sequence::create(t1,t2, NULL));
        }
    }
    if(target != skillBtn3 && skillBtn3)
    {
        pt = (ProgressTimer*)skillBtn3->getChildByTag(TAG_CD);
        if(pt->getPercentage() <= 0)
        {
            pt->stopAllActions();
            ProgressTo *t1=ProgressTo::create(COMMON_CD_TIME,100);
            ProgressTo *t2=ProgressTo::create(0,0);
            pt->runAction(Sequence::create(t1,t2, NULL));
        }
    }
}
bool ControlBtnPanel::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(!this->isVisible())
    {
        return false;
    }
     handMoveFlag = 0;
    m_beginPostion = touch->getLocation();
    m_isMoveing = false;
    if(m_beginPostion.x < VisibleRect::center().x + 20 * GlobalInfo::getInstance()->screenScaleX)
    {
        return false;
    }
    if(m_beginPostion.y > VisibleRect::top().y - 30 * GlobalInfo::getInstance()->screenScaleY)
    {
        return false;
    }
    return true;
}
void ControlBtnPanel::onTouchMoved(Touch *touch, Event *unused_event)
{
   
    Point distanceCp = touch->getLocation() - touch->getPreviousLocation();
    float radian = distanceCp.getAngle();
    float degrees =CC_RADIANS_TO_DEGREES(radian);//孤度转角度
    if(distanceCp.getLength() >= 40 * GlobalInfo::getInstance()->screenScaleX)
    {
        if(degrees >= -15 && degrees <= 20)
        {//右
            handMoveFlag = BUTTON_SKILL1;
        }
        else if(degrees >= 60 && degrees <= 120)
        {
            handMoveFlag = BUTTON_SKILL4;//上，跳
        }
        else if(degrees >= 135 && degrees < 180)
        {//左
            handMoveFlag = BUTTON_SKILL3;
        }
        else if(degrees > -180 && degrees < -135)
        {
             handMoveFlag = BUTTON_SKILL3;
        }
        else if(degrees < -50 && degrees > -145)
        {//下
            handMoveFlag = BUTTON_SKILL2;
        }
    }

}
void ControlBtnPanel::onTouchEnded(Touch *touch, Event *unused_event)
{
  
    Node* target = this->getChildByTag(handMoveFlag);
    if(target && !target->isVisible())
    {
        return;
    }
    if(!target)
    {
        DictNewGuide* newGuide = NewPlayerGuild::getInstance()->getNowData();
        if(newGuide && newGuide->id == 4)
        {
            return;
        }
    }
   
    onButtonClick(target);
    handMoveFlag = 0;
    if(NewPlayerGuild::getInstance()->isShowing())
    {
        PublicShowUI::broadUserMsg(CUSTOM_RESET_AVATAR_ACTION, NULL);
    }
}
void ControlBtnPanel::onButtonClick(Node* pSender)
{
    
    Node* target = (Node*)pSender;
    if(!this->isVisible() || (target && !target->isVisible()))
    {
        return;
    }
    if(target)
    {
        int tag = target->getTag();
   
               
        
        switch (tag)
        {
            case ControlBtnPanel::BUTTON_ATTACK:
                break;
            case ControlBtnPanel::BUTTON_SKILL1:
               
                if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumSkillAttack1)
                {
                    NewPlayerGuild::getInstance()->pause();
                }
                
                break;
            case  ControlBtnPanel::BUTTON_SKILL2:
               
                if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumSkillAttack2)
                {
                    NewPlayerGuild::getInstance()->next();
                    NewPlayerGuild::getInstance()->pause();
                }
                break;
            case  ControlBtnPanel::BUTTON_SKILL3:
            
                if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumSkillAttack3)
                {
                    NewPlayerGuild::getInstance()->pause();
                }
                break;
            case  ControlBtnPanel::BUTTON_SKILL4:
          
                break;
            case ControlBtnPanel::BUTTON_PROTECTED:
             
                if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumDodgeParryButton)
                {
                    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumDodgeParryButton);
                }
                break;
            default:
                break;
        }
        
        
        
        
        
        ProgressTimer* pt = (ProgressTimer*)target->getChildByTag(TAG_CD);
        if(pt && pt->getPercentage() > 0)
        {
            return;
        }
    }

    if(this->m_callBack)
    {
        this->m_callBack(target);
    }
}
void ControlBtnPanel::showSkill1(EventCustom* msg )
{
    Node* node = this->getChildByTag(ControlBtnPanel::BUTTON_SKILL1);
    if(node)
    {
       node->setVisible(true);
    }
  
}
void ControlBtnPanel::showSkill2(EventCustom* msg )
{
    Node* node = this->getChildByTag(ControlBtnPanel::BUTTON_SKILL2);
    if(node)
    {
        node->setVisible(true);
    }
}
void ControlBtnPanel::showSkill3(EventCustom* msg )
{
    Node* node = this->getChildByTag(ControlBtnPanel::BUTTON_SKILL3);
    if(node)
    {
        node->setVisible(true);
    }
}
void ControlBtnPanel::showProtectedBtn(EventCustom* msg )
{
    Node* node = this->getChildByTag(ControlBtnPanel::BUTTON_PROTECTED);
    if(node)
    {
        node->setVisible(true);
    }
}
void ControlBtnPanel::onEnter()
{
    Layer::onEnter();
    this->setClickEnabled(true);
    addUserMsg(CUSTOM_SHOW_SKILL1_BTN, CC_CALLBACK_1(ControlBtnPanel::showSkill1, this));
    addUserMsg(CUSTOM_SHOW_SKILL2_BTN, CC_CALLBACK_1(ControlBtnPanel::showSkill2, this));
    addUserMsg(CUSTOM_SHOW_SKILL3_BTN, CC_CALLBACK_1(ControlBtnPanel::showSkill3, this));
    addUserMsg(CUSTOM_SHOW_PROTECTED_BTN, CC_CALLBACK_1(ControlBtnPanel::showProtectedBtn, this));
}
void ControlBtnPanel::onExit()
{
    BaseLayer::onExit();
    BaseLayer::removeEventListener();
 
     this->setClickEnabled(false);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumCommonAttack);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSkillAttack1);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumDodgeParryButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSkillAttack2);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSkillAttack3);

}