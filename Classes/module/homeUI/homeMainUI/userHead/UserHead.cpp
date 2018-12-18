//
//  UserHead.cpp
//  SuiTang
//
//  Created by mac on 14-6-8.
//
//
#include "../../../../common/ImagePath.h"
#include "UserHead.h"
#include "../../../../common/PublicShowUI.h"
#include "../../../../commonData/GlobalInfo.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/commonEffect/CommonEffect.h"
#include "../../../../common/GameConfig.h"
#include "../../../../commonData/dictData/DictRoleLevel/DictRoleLevelManager.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../vip/VipLayer.h"
#include "../../../setup/SetupLayer.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../firstRecharge/FirstRechargeLayer.h"
UserHead::UserHead()
:TAG_LEVEL_LABEL(1)
,TAG_EXPERENCE(2)
,TAG_EXPERENCE_LABEL(3)
,TAG_VIPBTN(4)
,TAG_HEADBG(5)
,TAG_FIGHTPOWER(6)
,TAG_BG(7)
,TAG_EXPPROGRESS(8)
,TAG_VIP_LABEL(9)
,TAG_NAME(10)
,TAG_POWER(11)
,TAG_EFFECT(12)
,sx(0)
{
    
}
UserHead::~UserHead()
{
    
}
void UserHead::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    _eventDispatcher->removeCustomEventListeners(CUSTOM_UPDATE_USER_LEVEL);
     _eventDispatcher->removeCustomEventListeners(CUSTOM_UPDATE_NICK_NAME);
    _eventDispatcher->removeCustomEventListeners(CUSTOM_UPDATE_VIP_LEVEL);
    _eventDispatcher->removeCustomEventListeners(CUSTOM_UPDATE_USERPROP_VALUE);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSetButton);
}
void UserHead::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    _eventDispatcher->addCustomEventListener(CUSTOM_UPDATE_USER_LEVEL, CC_CALLBACK_1(UserHead::updateUserLevel, this));
    _eventDispatcher->addCustomEventListener(CUSTOM_UPDATE_NICK_NAME, CC_CALLBACK_1(UserHead::updateUserName, this));
    _eventDispatcher->addCustomEventListener(CUSTOM_UPDATE_VIP_LEVEL, CC_CALLBACK_1(UserHead::updateVip, this));
    _eventDispatcher->addCustomEventListener(CUSTOM_UPDATE_USERPROP_VALUE, CC_CALLBACK_1(UserHead::updateUserLevel, this));
    
    
    Node* node = this->getChildByTag(TAG_HEADBG);
    CommonEffect* effect = (CommonEffect*)node->getChildByTag(TAG_EFFECT);
    if(effect)
    {
        effect->rePlay();
    }
}

bool UserHead::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        setHeadInfo();
        bref = true;
    } while (false);
    return bref;
}
void UserHead::updateUserLevel(EventCustom* msg)
{
    Label* lvLabel = (Label*)this->getChildByTag(TAG_LEVEL_LABEL);
    if(lvLabel)
    {
         string labelLvStr= PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->level);
        lvLabel->setString(labelLvStr);
    }

}
void UserHead::updateUserName(EventCustom* msg)
{
    Label* nameLabel = (Label*)this->getChildByTag(TAG_NAME);
    if(nameLabel)
    {
        string nameStr = GlobalInfo::getInstance()->gameRole->name;
        nameLabel->setString(nameStr);
    }
}
void UserHead::setHeadInfo()
{
        //vip
    
    Sprite* headBg=Sprite::create(IMG_USERHEAD_HEADBG);
    headBg->setAnchorPoint(Point::ZERO);
    
    headBg->setPosition(Point::ZERO);
    this->addChild(headBg,0,TAG_HEADBG);
    this->setContentSize(headBg->getContentSize());
    
    
    //设置
    Button* settingBtn=Button::create(IMG_USERHEAD_SETTING, IMG_USERHEAD_SETTING, CC_CALLBACK_1(UserHead::onHeadClick, this));
    settingBtn->setAnchorPoint(Point::ZERO);
    settingBtn->setPosition(270,70);
    this->addChild(settingBtn,4);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSetButton, settingBtn);
    Size _size;
    _size=headBg->getContentSize();
    _size.width+=settingBtn->getContentSize().width;
    this->setContentSize(_size);
    
    
    Button* heroHendBg=Button::create(IMG_USERHEAD_HEADLITTLEBG, IMG_USERHEAD_HEADLITTLEBG, CC_CALLBACK_1(UserHead::onHeadClick, this));
    heroHendBg->setAnchorPoint(Point::ZERO);
    heroHendBg->setPosition(8,30);
    this->addChild(heroHendBg,4);
    DictHero* dictHero =  DictHeroManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->mainHeroDictID);
    if (dictHero) {
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, dictHero->headResource.c_str());
        Sprite* head = Sprite::create(imgPath);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.85);
        head->setPosition(Point::ZERO);
        heroHendBg->addChild(head,3);
    }
    
    Button* vipBtn=Button::create(IMG_USERHEAD_VIP_BTN, IMG_USERHEAD_VIP_BTN, CC_CALLBACK_1(UserHead::onVipdClick, this));
    vipBtn->setAnchorPoint(Point::ZERO);
    vipBtn->setPosition(207,8);
    this->addChild(vipBtn,1,TAG_VIPBTN);
    updateVip();

    
    //等级
    string labelLvStr=PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->level);
    Label* lvLabel = PublicShowUI::getLabel(labelLvStr.c_str(),PublicShowUI::getColor3b(0x00eaff),21,false,false);
    lvLabel->setAnchorPoint(Point::ZERO);
    lvLabel->setPosition(160,94);
    this->addChild(lvLabel,4,TAG_LEVEL_LABEL);
//    updateUserExp();
    //名字
    string labelStr = GlobalInfo::getInstance()->gameRole->name == "" ? "修改昵称" : GlobalInfo::getInstance()->gameRole->name;
//    labelStr="一剑封";
    Label* nameLabel = PublicShowUI::getLabel(labelStr.c_str(),PublicShowUI::getColor3b(0xbdeaff),22,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(130,70);
    this->addChild(nameLabel,3,TAG_NAME);
    
    
    //战力背景
    CommonEffect* effect = CommonEffect::create("zhanlizhujiemian",true,true);
    effect->setAnchorPoint(Point::ZERO);
    effect->setPosition(10,-20);
    this->addChild(effect,2);
    
//    Sprite* sprfight = Sprite::create(IMG_USERHEAD_POWER);
//    sprfight->setAnchorPoint(Point::ZERO);
//    sprfight->setPosition(10,-20);
//    this->addChild(sprfight,2);
    //战力
    labelStr = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->combatPower);
    Label* powerLabel = PublicShowUI::getLabel(labelStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),22,false,false);
    powerLabel->setAnchorPoint(Point::ZERO);
    powerLabel->setPosition(120,-16);
    this->addChild(powerLabel,3,TAG_POWER);
}
void UserHead::updatePower()
{
    Label* powerLabel = (Label*)this->getChildByTag(TAG_POWER);
    if(powerLabel)
    {
        string labelStr = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->combatPower);
        powerLabel->setString(labelStr);
    }
}
void UserHead::updateVip(EventCustom* msg)
{
//    Node* vipBtn = this->getChildByTag(TAG_VIPBTN);
    Label* vipLabel = (Label*)this->getChildByTag(TAG_VIP_LABEL);
    string labelStr=PublicShowUI::numberToString(GlobalInfo::getInstance()->vipLevel);
    if(vipLabel)
    {
        vipLabel->setString(labelStr);
        return;
    }
    vipLabel = PublicShowUI::getLabel(labelStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    vipLabel->setAnchorPoint(Point::ZERO);
    vipLabel->setPosition(190,29);
    this->addChild(vipLabel,10,TAG_VIP_LABEL);
}
void UserHead::updateUserExp()//更新经验
{
//    DictRoleLevel* roleLevel = DictRoleLevelManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->level);
//    ProgressTimer* progressTimer = (ProgressTimer*)this->getChildByTag(TAG_EXPPROGRESS);
//    float percent = GlobalInfo::getInstance()->gameRole->experience / roleLevel->needExp * 100;
//    if(!progressTimer)
//    {
//        Node* vipBtn = this->getChildByTag(TAG_VIPBTN);
//        Sprite* spr = Sprite::create(IMG_USERHEAD_PROGRESS);
//        spr->setAnchorPoint(Point::ZERO);
//        progressTimer = ProgressTimer::create(spr);
//        progressTimer->setType(ProgressTimer::Type::BAR);
//        progressTimer->setMidpoint(Point(0,1));
//        progressTimer->setBarChangeRate(Point(1,0));
//        progressTimer->setAnchorPoint(Point::ZERO);
//        
//        progressTimer->setPosition(vipBtn->getContentSize().width,14.5);
//        this->addChild(progressTimer,5,TAG_EXPPROGRESS);
//        progressTimer->setPercentage(percent);
//    }
//
//     progressTimer->setPercentage(percent);
      
}
void UserHead::onHeadClick(Ref* pSender)
{
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSetButton);
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId != DictNewGuideEventEnumSetButton)
    {
        return;
    }
    SetupLayer::show();

}
void UserHead::onVipdClick(Ref* pSender)
{
    if(NewPlayerGuild::getInstance()->getNowData() && NewPlayerGuild::getInstance()->getNowData()->bottomId == DictNewGuideEventEnumSetButton)
    {
        return;
    }
    if(GlobalInfo::getInstance()->firstRechargeStatus == 1 || GlobalInfo::getInstance()->firstRechargeStatus == 2)
    {
        FirstRechargeLayer::show(0);
    }else if (GlobalInfo::getInstance()->firstRechargeStatus == 3)
    {
        VipLayer::show(SCENE_TAG_MAINUI,VipLayer::TAG_RECHARGE);
    }else{
        log("输出错误");
    }
//    VipLayer::show(SCENE_TAG_MAINUI,VipLayer::TAG_RECHARGE);
}
