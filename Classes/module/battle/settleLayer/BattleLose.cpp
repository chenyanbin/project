//
//  BattleLose.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/23.
//
//

#include "BattleLose.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/stage/RequestEndStageBattle.h"
#include "../../../message/Decoding/arena/ArenaBattleEndMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../generals/generalsCard/GeneralsCard_Layer.h"
#include "../../generals/generalsEquip/GeneralsEquip_Scene.h"
#include "../../publicLayer/GotoModule.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
#include "../../battleTest/PlayerDataManager.hpp"
BattleLose::BattleLose()
:m_battleID(0)
,m_bloodBottle(0)
{
//    SoundManager::setBackgroundMusicVolume(0);
}
BattleLose::~BattleLose()
{
    
}
bool BattleLose::init(int battleID,int bloodBottle)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isShowGrayBg = true;
        m_battleID = battleID;
        this->m_bloodBottle = bloodBottle;
        this->setBackground(IMG_BATTLERESULT_LOSEBG,Point::ZERO,false);
        setButtons();
        setTitle();
        
        CommonEffect* commonEffect = CommonEffect::create("zhandaoushibaid");
//        commonEffect->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
        this->addChild(commonEffect,40);
        
        
        bref = true;
    } while (false);
    return bref;
}
BattleLose* BattleLose::create(int battleID,int bloodBottle)
{
    BattleLose* layer = new BattleLose();
    if(layer && layer->init(battleID,bloodBottle))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void BattleLose::setTitle()
{
    Sprite* title = Sprite::create(IMG_BATTLERESULT_LOSETITLE);
    title->setAnchorPoint(Point::ZERO);
    this->addChild(title);
    title->setPosition((this->getContentSize().width - title->getContentSize().width)/2, this->getContentSize().height);
    Size size = this->getContentSize();
    size.height = title->getPositionY()+title->getContentSize().height;
    this->setContentSize(size);
    
    Sprite* lostWord = Sprite::create(IMG_BATTLERESULT_LOSTWORD);
    lostWord->setAnchorPoint(Point::ZERO);
    this->addChild(lostWord);
    lostWord->setPosition(-lostWord->getContentSize().width-10, this->getContentSize().height/2-lostWord->getContentSize().height/2);
    
    const char* path = NULL;
    TouchSprite* touchSpr = NULL;
//    TouchSprite* itemSpr = NULL;
    for (int i = 0; i<4; i++) {
        path = PublicShowUI::getResImgPath(IMG_BATTLERESULT_ITEMLABEL,  PublicShowUI::numberToString(i + 1).c_str());
        touchSpr = TouchSprite::createWithPic(path, this, callfuncN_selector(BattleLose::onClick));
        touchSpr->isButtonMode = true;
        touchSpr->setAnchorPoint(Point::ZERO);
//        itemSpr = TouchSprite::createWithPic(path, this, callfuncN_selector(BattleLose::onClick));
//        itemSpr->setAnchorPoint(Point::ZERO);
//        itemSpr->setScaleX(.7);
//        itemSpr->setContentSize(itemSpr->getContentSize() * .7);
//        itemSpr->isButtonMode = true;
//        touchSpr->addChild(itemSpr,2);
        this->addChild(touchSpr,1,i);
        touchSpr->setPositionY(10);
        if (i == 0)
        {
            touchSpr->setPositionX(18);
        }
        else if (i == 1)
        {
            touchSpr->setPositionX(touchSpr->getContentSize().width-45);
            touchSpr->setPositionY(12);
        }
        else if (i == 2)
        {
            touchSpr->setPositionX(touchSpr->getContentSize().width*2-68);
        }
        else if (i == 3)
        {
            touchSpr->setPositionX(touchSpr->getContentSize().width*3-37);
        }
    }

}
void BattleLose::onClick(Node* pSender)
{

    switch (pSender->getTag())
    {
        case 0:
            GotoModule::gotoModuleByFunctionID(DictFunctionEnumHeroPrestige, SCENE_TAG_MAINUI);
            GotoModule::gotoModuleByFunctionID(DictFunctionEnumHero, SCENE_TAG_MAINUI);//先跳转到武将吧
            break;
        case 1:
         //   GotoModule::gotoModuleByFunctionID(DictFunctionEnumHeroQuality, SCENE_TAG_MAINUI);
            GotoModule::gotoModuleByFunctionID(DictFunctionEnumHero, SCENE_TAG_MAINUI);//先跳转到武将吧
            break;
        case 2:
            //GotoModule::gotoModuleByFunctionID(DictFunctionEnumEquipHarden, SCENE_TAG_MAINUI);
             GotoModule::gotoModuleByFunctionID(DictFunctionEnumEquip, SCENE_TAG_MAINUI);//先跳转装备吧
            break;
        case 3:
//            GotoModule::gotoModuleByFunctionID(DictFunctionEnumEquipForge, SCENE_TAG_MAINUI);
            GotoModule::gotoModuleByFunctionID(DictFunctionEnumEquip, SCENE_TAG_MAINUI);//先跳转装备吧

            break;
        default:
            break;
    }
}
void BattleLose::setButtons()
{
    Sprite* spr = Sprite::create(IMG_BATTLERESULT_AGAINBTN);
    spr->setAnchorPoint(Point::ZERO);
    MenuItemLabel* again = MenuItemLabel::create(spr,CC_CALLBACK_1(BattleLose::onAgainClick, this));
    again->setAnchorPoint(Point::ZERO);
    
    spr = Sprite::create(IMG_BATTLERESULT_ENDBTN);
    spr->setAnchorPoint(Point::ZERO);
    MenuItemLabel* end = MenuItemLabel::create(spr, CC_CALLBACK_1(BattleLose::onEndBtnCick, this));
    end->setAnchorPoint(Point::ZERO);
    end->setPositionY(200);
    Menu* menu = Menu::create(again,end, NULL);
    Size size = end->getContentSize();
    size.width = end->getPositionX() + end->getContentSize().width;
    menu->setContentSize(size);
    this->addChild(menu);
    menu->setPosition(this->getContentSize().width+10,this->getContentSize().height/2 - menu->getContentSize().height);
}
void BattleLose::onAgainClick(Ref* pSender)
{
    SoundManager::playEffectMusic(EFFECT_CLICK);
    int costPower = 0;
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
         DictStageBattle* dictStageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
        costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStageBattle->costPowerElite : dictStageBattle->costPower;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* dictMusouBattle = DictMusouBattleManager::getInstance()->getData(m_battleID);
        costPower = dictMusouBattle->costPower;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        onEndBtnCick(pSender);
        return;
    }
    
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
//        NoticeManager::getInstance()->showNotice("体力不足！无法再战");
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    
    this->removeFromParent();
    GlobalInfo::getInstance()->isShowStoryTalk = false;
    broadMsg(CUSTOM_BATTLE_REPLAY);
}
void BattleLose::onEndBtnCick(Ref* pSender)
{
     SoundManager::playEffectMusic(EFFECT_CLICK);
    this->removeFromParent();
    broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(false));
}
void BattleLose::show(int battleID,int bloodBottle)
{
    
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(SCENE_TAG_SETTLE))
    {
        return;
    }
    BattleLose* layer = BattleLose::create(battleID,bloodBottle);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
    
    scene->addChild(layer,SCENE_LAYER_ZORDER,SCENE_TAG_SETTLE);
}
void BattleLose::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
    
    SoundManager::playEffectMusic(EFFECT_LOSE);
//
    
}
void BattleLose::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void BattleLose::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
//    SoundManager::resetBackgroundMusicVolume();
}
void BattleLose::onEnterTransitionDidFinish()
{
      SoundManager::stopBackgroundMusic();
    BaseLayer::onEnterTransitionDidFinish();
    MessageSendI* msg = NULL;
    if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
       msg = new ArenaBattleEndMsg(false,PlayerDataManager::getInstance()->_targetRoleID);
    }
    else
    {
       msg = new RequestEndStageBattle(m_battleID,0,0,m_battleID);
    }
    
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    TDTalkDataManager::getInstance()->onMissionFailed(PublicShowUI::numberToString(m_battleID).c_str());
}
void BattleLose::addEventListener()
{
    BaseLayer::addEventListener();
}
void BattleLose::removeEventListener()
{
    BaseLayer::removeEventListener();
}