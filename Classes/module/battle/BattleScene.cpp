//
//  BattleLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/23.
//
//

#include "BattleScene.h"
#include "../../common/TouchSprite/Button.h"
#include "battleUI/ControlBtnPanel.h"
#include "../../protocol/UserCustomEvent.h"
#include "battleUI/DoubleHitManager.h"
//#include "battleUI/MapProgressLayer.h"
#include "battleUI/AngryProgressManager.h"
#include "BattleLoader.h"
#include "../login/LoginLayer.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "battleUI/BattlePause.h"
#include "settleLayer/BattleWin.h"
#include "../../module/newPlayerGuide/NewPlayerGuild.h"
#include "../../protocol/Protocal.h"
#include "../chapter/ChapterLayer.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "battleUI/BattleCountDown.hpp"
#include "../../message/Decoding/famouseGeneral/FamouseTouchMsg.hpp"
#include "../../net/NetworkDataProcessing.h"
#include "../famousGeneral/GeneralScene.hpp"
#include "../../commonData/data/FunctionOpenManager.h"
#include "monsterAI/HeroAIManager.h"
#include "../battleTest/PlayerDataManager.hpp"
#include "../arena/ArenaLayer.hpp"
#include "../../commonData/data/DictManager.h"

BattleScene::BattleScene()
:m_mapLayer(NULL)
,m_simplePad(NULL)
,TAG_CONTROLBUTTON(1)
,TAG_FULLEFFECT(2)
,TAG_BATTLENAME(3)
,TAG_SKYEFFECT(4)
,TAG_HEALTHWARNING(5)
,TAG_BOSS_COME(6)
,TAG_PAUSEBTN(7)
,TAG_AUTOBTN(8)
,TAG_BOTTLE(9)
,TAG_BOTTLELABEL(10)
,TAG_AUTOEFFECT(11)
,m_lastAttackTime(0)
,m_battleID(0)
,heroPropList(NULL)
{
    heroPropList = new Vector<DictAvatarProp*>();
}
BattleScene::~BattleScene()
{
   
    CC_SAFE_RELEASE_NULL(m_mapLayer);
    if(GlobalInfo::getInstance()->battleType != kBattleType_TestBattle && GlobalInfo::getInstance()->battleType != kBattleType_ArenaBattle)
    {
        heroPropList->clear();
        CC_SAFE_DELETE(heroPropList);
    }
 
    heroPropList = NULL;
}
bool BattleScene::init(ByteStream* byteStream)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->isAbleGuiding = false;
        float sx = GlobalInfo::getInstance()->screenScaleX;
        float sy = GlobalInfo::getInstance()->screenScaleY;
        if(byteStream)
        {
            m_battleID = byteStream->getInt();
            parseMsg(byteStream);
        }
        else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
        {
            CC_SAFE_DELETE(heroPropList);
            heroPropList = PlayerDataManager::getInstance()->getLeftHeroList();
        }
       
        setMaskLayer();
        
        setControlButton();
       
        this->addChild(BossBloodManager::getInstance(),4);
        PublicShowUI::setTargetScale(BossBloodManager::getInstance());
        BossBloodManager::getInstance()->setVisible(false);
        BossBloodManager::getInstance()->setPosition(VisibleRect::center().x - BossBloodManager::getInstance()->getContentSize().width/2 + 150 * sx,VisibleRect::top().y - 135 * sx);
        this->addChild(AngryProgressManager::getInstance(),6);
        AngryProgressManager::getInstance()->setAnchorPoint(Point::ZERO);
        AngryProgressManager::getInstance()->setVisible(false);
        PublicShowUI::setTargetScale(AngryProgressManager::getInstance());
        AngryProgressManager::getInstance()->setPosition(VisibleRect::center().x - AngryProgressManager::getInstance()->getContentSize().width/2 - 150 * sx, VisibleRect::bottom().y + 30 * sy);
        setPauseBtn();
        setAutoFightBtn();
        setBattleName();
        setheadListLayer();
    
        setBloodBottle();
        bref = true;
    } while (false);
    return bref;
}
BattleScene* BattleScene::create(ByteStream* byteStream)
{
    BattleScene* layer = new BattleScene();
    if(layer && layer->init(byteStream))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
Scene* BattleScene::createScene(ByteStream* byteStream,int fromScene)
{
    Scene* scene = Scene::create();
    BattleScene* layer = BattleScene::create(byteStream);
    if(layer)
    {
        layer->setAnchorPoint(Point::ZERO);
        layer->setFromScene(fromScene);
        scene->addChild(layer, 0, SCENE_TAG_BATTLE);
    }
    return scene;
}
void BattleScene::setBloodBottle()
{
    Node* autoBtn = this->getChildByTag(TAG_AUTOBTN);
    Sprite* bg = Sprite::create(IMG_BATTLE_BOTTLEBG);
    bg->setAnchorPoint(Point::ZERO);
    
    TouchSprite* bloodBottle = TouchSprite::createWithPic(IMG_ICON_BLOODBOTTLE, this, callfuncN_selector(BattleScene::onBottleClick));
    bloodBottle->isButtonMode = true;
    bloodBottle->setAnchorPoint(Point::ZERO);
    bloodBottle->setPosition(25, (bg->getContentSize().height - bloodBottle->getContentSize().height)/2);
    bg->addChild(bloodBottle,1,TAG_BOTTLE);
    
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumWaterButton, bloodBottle);

    Sprite* cdSprite = Sprite::create(IMG_ICON_BLOODBOTTLE);
    cdSprite->setColor(Color3B::BLACK);
    cdSprite->setOpacity(225);
    ProgressTimer* pt = ProgressTimer::create(cdSprite);
    //转圈的CD实现
    pt->setPosition(bloodBottle->getContentSize().width/2, bloodBottle->getContentSize().height/2);
    pt->setType(ProgressTimer::Type::RADIAL);
    bloodBottle->addChild(pt,2,TAG_BOTTLE);
    pt->setPercentage(0);
    
    PublicShowUI::setTargetScale(bg);
    bg->setPosition(autoBtn->getPositionX() - bg->getContentSize().width - 10 * GlobalInfo::getInstance()->screenScaleX, autoBtn->getPositionY() - autoBtn->getContentSize().height / 2);
    this->addChild(bg,10,TAG_BOTTLE);
    

    
}
void BattleScene::updateBottleCount()
{
  
    Node* bottle = this->getChildByTag(TAG_BOTTLE);
    
    Label* label = (Label*)bottle->getChildByTag(TAG_BOTTLELABEL);
    string str = "X" + PublicShowUI::numberToString(this->m_mapLayer->m_bloodBottle);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),18,false,false);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(90, 25);
        bottle->addChild(label, 5,TAG_BOTTLELABEL);
    }
}
void BattleScene::onBottleClick(Node* pSender)
{
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumWaterButton);
    if(GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
         NoticeManager::getInstance()->showNotice("竞技场中，禁止磕药哦！",NoticeManager::COLOR_RED);
        return;
    }
    
    PublicShowUI::broadUserMsg(CUSTOM_RESET_AVATAR_ACTION, NULL);
    ProgressTimer* pt = (ProgressTimer*)pSender->getChildByTag(TAG_BOTTLE);
    if(pt->getPercentage() > 0)
    {
        NoticeManager::getInstance()->showNotice("血瓶使用中。。请等待！",NoticeManager::COLOR_RED);
        return;
    }
    if(m_mapLayer->m_bloodBottle > 0)
    {
        PublicShowUI::broadUserMsg(CUSTOM_BATTLE_EAT_BLOODBOTTLE, NULL);
        
        pt->runAction(Sequence::create(ProgressFromTo::create(15, 100, 0),NULL));
        updateBottleCount();
    }
    else
    {
        NoticeManager::getInstance()->showNotice("血瓶不足，请到商城购买！",NoticeManager::COLOR_RED);
    }

}
void BattleScene::setPauseBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Button* btn = Button::create(IMG_BATTLE_PAUSE, "", CC_CALLBACK_1(BattleScene::onPauseClick, this));
    PublicShowUI::setTargetScale(btn);
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi && GlobalInfo::getInstance()->stageMode == kStageModeCommon)
    {
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(this->m_battleID);
        
        btn->setEnabled(stageBattle->isPause > 0 || GlobalInfo::getInstance()->isDebug);
    }
    if(GlobalInfo::getInstance()->battleType == kBattleType_LoginBattle)
    {
        btn->setEnabled(false);
    }
    btn->setPosition(VisibleRect::right().x -btn->getContentSize().width/2, VisibleRect::top().y - btn->getContentSize().height/2 + 10 * sx) ;
    this->addChild(btn,8,TAG_PAUSEBTN);
    
   
    this->addChild(DoubleHitManager::getInstance(), 5);
    DoubleHitManager::getInstance()->setPosition(VisibleRect::right().x - 160 * sx,btn->getPositionY() - btn->getContentSize().height/2 - DoubleHitManager::getInstance()->getContentSize().height - 15 * sx);
    PublicShowUI::setTargetScale(DoubleHitManager::getInstance());
}
void BattleScene::onPauseClick(Ref* pSender)
{
   if(m_mapLayer && m_mapLayer->getMainHero())
   {
       if(m_mapLayer->getMainHero()->getActionState() == kActionStateWin || m_mapLayer->getMainHero()->getActionState() == kActionStateDead)
       {
           return;
       }
   }
    BattlePause::show();
}
void BattleScene::setAutoFightBtn()
{
    Armature* armature = NULL;
    Button* btn = NULL;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* pauseBtn = this->getChildByTag(TAG_PAUSEBTN);
    btn = (Button*)this->getChildByTag(TAG_AUTOBTN);

    armature = (Armature*)this->getChildByTag(TAG_AUTOEFFECT);
    if(armature)
    {
        armature->pause();
        this->removeChildByTag(TAG_AUTOEFFECT);
    }
    armature = NULL;
    string str = "";
  
    if(HeroAIManager::getInstance()->isAutoFight)
    {
        btn = Button::create(IMG_BATTLE_UNAUTOFIGHTBTN, "", CC_CALLBACK_1(BattleScene::onAutoFightClick, this));//
        str = "手动";
        AnimationData* animationData = ArmatureDataManager::getInstance()->getAnimationData(AUTOFIGHT_EFFECT);
        if(animationData)
        {
            armature = Armature::create(AUTOFIGHT_EFFECT);
          
            this->addChild(armature,11,TAG_AUTOEFFECT);
        }
        
    }
    else
    {
        btn = Button::create(IMG_BATTLE_AUTOFIGHTBTN, "", CC_CALLBACK_1(BattleScene::onAutoFightClick, this));
        str = "自动";
    }

    
    
    PublicShowUI::setTargetScale(btn);
 
    btn->setPosition(pauseBtn->getPositionX() - pauseBtn->getContentSize().width/2 - 15 * sx, pauseBtn->getPositionY() ) ;
    this->addChild(btn,8,TAG_AUTOBTN);
    if(armature)
    {
        PublicShowUI::setTargetScale(armature,false,false);
         armature->setPosition(btn->getPosition());
         armature->getAnimation()->playWithIndex(0);
    }

    this->addChild(BattleCountDown::getInstance(),8);
    BattleCountDown::getInstance()->setPosition(VisibleRect::center().x  -BattleCountDown::getInstance()->getContentSize().width/2 + 20 * sx,btn->getPositionY());
    

}
void BattleScene::onAutoFightClick(Ref* pSender)
{
    double autoFightLv = DictManager::getFormulaValue("autoFightLv");
    double autoFightVip = DictManager::getFormulaValue("autoFightVip");
    if(GlobalInfo::getInstance()->vipLevel < autoFightVip && GlobalInfo::getInstance()->gameRole->level < autoFightLv && !GlobalInfo::getInstance()->isDebug)
    {
        NoticeManager::getInstance()->showDictTipsMsg(6001015);
        return;
    }
    if(GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        NoticeManager::getInstance()->showNotice("竞技中不能操作！");
        return;
    }
    HeroAIManager::getInstance()->isAutoFight = !HeroAIManager::getInstance()->isAutoFight;
    setAutoFightBtn();
    
}
void BattleScene::parseMsg(ByteStream* byteStream)
{
    int bloodBottle = byteStream->getInt();
    GlobalInfo::getInstance()->bloodBottle = bloodBottle;
    DictAvatarProp* prop = NULL;
    int len = byteStream->get();
    for(int i = 0; i < len; i++)
    {
        prop = new DictAvatarProp();
        prop->autorelease();
        heroPropList->pushBack(prop);
        
        prop->id = byteStream->getInt();
        if(prop->id == 0)
        {
            continue;
        }
        prop->dictID = byteStream->getInt();
        prop->quality = byteStream->get();
        prop->level = byteStream->getInt();
        prop->prestige = byteStream->getInt();
        prop->health = byteStream->getInt();
        prop->attack = byteStream->getInt();
        prop->defend = byteStream->getInt();
        prop->critic = byteStream->getInt();
        prop->tenaci = byteStream->getInt();
        prop->hit = byteStream->getInt();
        prop->block = byteStream->getInt();
        prop->damageAdd = byteStream->getInt();//攻击强度就是伤害加成率
        prop->fireResist = byteStream->getInt();
        prop->iceResist = byteStream->getInt();
        prop->boltResist = byteStream->getInt();
        prop->windResist = byteStream->getInt();
        prop->poisonResist = byteStream->getInt();
        
    }

}
void BattleScene::setMapLayer()
{

    m_mapLayer = BattleMapLayer::create(this->m_battleID,heroPropList);
   
    CC_SAFE_RETAIN(m_mapLayer);
    this->addChild(m_mapLayer,1);
    m_mapLayer->setAnchorPoint(Point::ZERO);
    m_mapLayer->setPositionX(VisibleRect::left().x);
    m_mapLayer->setPositionY(0);
 
    this->setContentSize(m_mapLayer->getContentSize());
    
    updateBottleCount();
}
void BattleScene::setMaskLayer()//遮罩
{
//    Sprite* layer = Sprite::create(IMG_BATTLE_MASK);
//    layer->setAnchorPoint(Point::ZERO);
//    
//    PublicShowUI::setTargetScale(layer,true);
//    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
//    this->addChild(layer,2);
    
}
void BattleScene::setheadListLayer()
{
    HeroHeadListLayer* headListLayer = HeroHeadListLayer::getInstance();
    headListLayer->setAnchorPoint(Point::ZERO);
    headListLayer->setClickEnable(false);
    headListLayer->setPositionX(VisibleRect::left().x + 15 * GlobalInfo::getInstance()->screenScaleX);
    headListLayer->setPositionY(VisibleRect::top().y - 105 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(headListLayer,4);
    
    
   
//    MapProgressLayer* layer = MapProgressLayer::getInstance();
//    layer->setAnchorPoint(Point::ZERO);
//    
//    layer->setPositionX(battleName->getPositionX() - layer->getContentSize().width);
//    layer->setPositionY(battleName->getPositionY());
//    this->addChild(layer,5);
}
void BattleScene::showControlBar(EventCustom* event)
{
    if(m_simplePad && GlobalInfo::getInstance()->battleType != kBattleType_ArenaBattle)
    {
        m_simplePad->setVisible(true);
    }
    
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    if(btnPanel && GlobalInfo::getInstance()->battleType != kBattleType_ArenaBattle)
    {
        btnPanel->setVisible(true);
    }
}
void BattleScene::setBattleName()
{
//    Node* autoBtn = this->getChildByTag(TAG_AUTOBTN);
//    string name = "";
//    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
//    {
//         DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
//        name = stageBattle->name;
//    }
//    else if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
//    {
//        DictMusouBattle* musouBattle = DictMusouBattleManager::getInstance()->getData(m_battleID);
//        name = musouBattle->name;
//    }
//    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
//    {
//        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(m_battleID);
//        if(legendBattle)
//        {
//             name = legendBattle->name;
//        }
//       
//    }
//   
//    Sprite* namebg = Sprite::create(IMG_BATTLE_BATTLENAME);
//    namebg->setAnchorPoint(Point::ZERO);
//    Label* label = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
//    label->setPosition(namebg->getContentSize().width/2, namebg->getContentSize().height/2);
//    namebg->addChild(label,1);
//    PublicShowUI::setTargetScale(namebg);
//    namebg->setPosition(autoBtn->getPositionX() - namebg->getContentSize().width - autoBtn->getContentSize().width/2 + 10 * GlobalInfo::getInstance()->screenScaleX,autoBtn->getPositionY() - namebg->getContentSize().height/2);
//    this->addChild(namebg, 4,TAG_BATTLENAME);
}
void BattleScene::setControlBar()
{
  
    m_simplePad = SimplePad::create(IMG_BATTLE_CONTROLBAR, 70 * GlobalInfo::getInstance()->screenScaleX);
    m_simplePad->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(m_simplePad);
    m_simplePad->setDelegate(this->m_mapLayer);
    m_simplePad->setPosition(150* GlobalInfo::getInstance()->screenScaleX,150* GlobalInfo::getInstance()->screenScaleX);
    this->addChild(m_simplePad, 3);
//    m_simplePad->setVisible(GlobalInfo::getInstance()->battleMode != kBattleModeHeroRun);
    m_simplePad->setVisible(false);
}
void BattleScene::setControlButton()//设置按钮
{
    ControlBtnPanel* panel = ControlBtnPanel::create(CC_CALLBACK_1(BattleScene::onControlBtnClick, this),CC_CALLBACK_1(BattleScene::onControlBtnRelease, this));
    panel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(panel);
    panel->setPosition(VisibleRect::right().x - 425 * GlobalInfo::getInstance()->screenScaleX, VisibleRect::bottom().y + 50 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(panel,6,TAG_CONTROLBUTTON);
    panel->setVisible(false);
}
void BattleScene::onControlBtnRelease(Ref* pSender)
{
    Node* target = (Node*)pSender;
    if(target)
    {
        switch (target->getTag()) {
            case ControlBtnPanel::BUTTON_PROTECTED:
                 m_mapLayer->onReleaseProtected();
                break;
                
            default:
                break;
        }
       
    }
}
void BattleScene::onControlBtnClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    
    if(!target)
    {
//        long long time = TimeUtil::getNativeTime();
//        if(time - m_lastAttackTime < 50)
//        {
//            return;
//        }
//        m_lastAttackTime = time;
        DictNewGuide* newGuide = NewPlayerGuild::getInstance()->getNowData();
       
        m_mapLayer->onAttack();
        if(newGuide && newGuide->id == 3)
        {
            NewPlayerGuild::getInstance()->pause();
        }
        return;

    }

//    log("onControlBtnClick==%d",target->getTag());
    switch (target->getTag()) {
        case ControlBtnPanel::BUTTON_ATTACK:
            break;
        case ControlBtnPanel::BUTTON_SKILL1:
             m_mapLayer->onSkill(ControlBtnPanel::BUTTON_SKILL1);
          
            break;
        case  ControlBtnPanel::BUTTON_SKILL2:
            m_mapLayer->onSkill(ControlBtnPanel::BUTTON_SKILL2);
          
            break;
        case  ControlBtnPanel::BUTTON_SKILL3:
             m_mapLayer->onSkill(ControlBtnPanel::BUTTON_SKILL3);
           
            break;
        case  ControlBtnPanel::BUTTON_SKILL4:
            m_mapLayer->onSkill(ControlBtnPanel::BUTTON_SKILL4);
            break;
        case ControlBtnPanel::BUTTON_PROTECTED:
            m_mapLayer->onProtected();
            
            break;
        default:
            break;
    }
}
void BattleScene::showFullScreenSkill(EventCustom* msg)
{
    SkillEffect* effect = (SkillEffect*)this->getChildByTag(TAG_FULLEFFECT);
    if(effect)
    {
        if(!effect->isPlayOver())
        {
            this->removeChildByTag(TAG_FULLEFFECT);
        }
    }
    SkillAttackData* attackData = (SkillAttackData*)msg->getUserData();
    if(attackData)
    {
        effect = attackData->getReleaseEffect();
        PublicShowUI::setTargetScale(effect);
        effect->setPosition(VisibleRect::center().x - effect->getContentSize().width/2,VisibleRect::center().y - effect->getContentSize().height/2);
        this->addChild(effect, 800,TAG_FULLEFFECT);
    }
}
void BattleScene::showBossComeEffect(EventCustom* msg)
{
    if(this->getChildByTag(TAG_BOSS_COME))
    {
        return;
    }
    CommonEffect* commonEffect = CommonEffect::create(BOSS_COME_EFFECT,false);
    PublicShowUI::setTargetScale(commonEffect);
    commonEffect->setPosition(VisibleRect::center().x - commonEffect->getContentSize().width/2,VisibleRect::center().y - commonEffect->getContentSize().height/2);
    this->addChild(commonEffect, 800,TAG_BOSS_COME);
    
}
void BattleScene::onCameraIn(EventCustom* msg)
{
    Avatar* avatar = (Avatar*)msg->getUserData();
    avatar->isCamreIn = true;
    m_mapLayer->stopAllActions();
    m_mapLayer->pauseOtherAvatar(avatar);
    CameraIn* cameraIn = CameraIn::create(.3, 150 * GlobalInfo::getInstance()->m_avatarScale);
    m_mapLayer->runAction(cameraIn);
   
}
void BattleScene::onCameraReset(EventCustom* msg)
{
     m_mapLayer->stopAllActions();
    CameraIn* cameraIn = CameraIn::create(.3, 0);
    m_mapLayer->runAction(cameraIn);
    m_mapLayer->resumeOtherAvatar();
}
void BattleScene::onSkill1Cd(EventCustom* msg)
{
    __Integer* integer = (__Integer*)msg->getUserData();
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(integer->getValue());
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->onSkill1CD(dictSkill->coldDowm);
}
void BattleScene::onSkill2Cd(EventCustom* msg)
{
    __Integer* integer = (__Integer*)msg->getUserData();
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(integer->getValue());
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->onSkill2CD(dictSkill->coldDowm);
}
void BattleScene::onSkill3Cd(EventCustom* msg)
{
    __Integer* integer = (__Integer*)msg->getUserData();
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(integer->getValue());
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->onSkill3CD(dictSkill->coldDowm);
}
void BattleScene::onSkill4Cd(EventCustom* msg)
{
    __Integer* integer = (__Integer*)msg->getUserData();
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(integer->getValue());
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->onSkill4CD(dictSkill->coldDowm);

}
void BattleScene::onSkill5Cd(EventCustom* msg)
{
    __Integer* integer = (__Integer*)msg->getUserData();
    DictSkill* dictSkill = DictSkillManager::getInstance()->getData(integer->getValue());
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->onSkill5CD(dictSkill->coldDowm);

}
void BattleScene::onChangeMainHero(EventCustom* msg)
{
    Hero* hero = (Hero*)msg->getUserData();
    if(this->m_mapLayer)
    {
        m_mapLayer->changeMainHero(hero);
    }
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    btnPanel->reset(hero);
    AngryProgressManager::getInstance()->updateMainHero(hero);
}
void BattleScene::onEnter()
{
    BaseLayer::onEnter();
}
void BattleScene::onExit()
{
    BaseLayer::onExit();
}
void BattleScene::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();

    string envirEffect = "";
    string skyeffect = "";
    if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* musouBattle = DictMusouBattleManager::getInstance()->getData(m_battleID);
        envirEffect = musouBattle->envirEffect;
        skyeffect = musouBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
        DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
        envirEffect = stageBattle->envirEffect;
        skyeffect = stageBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(m_battleID);
        envirEffect = legendBattle->envirEffect;
        skyeffect = legendBattle->skyEffect;
    }
    const char* path = NULL;
    if(envirEffect.size())
    {
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, envirEffect.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }
    
    if(skyeffect.size())
    {
        path = PublicShowUI::getAvatarPath(IMG_SCENE_EFFECT, skyeffect.c_str());
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    }
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumWaterButton);
}
void BattleScene::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setMapLayer();
    setControlBar();
    createEnvirEffects();
    
   
    
   
}
void BattleScene::createEnvirEffects()
{

    float sx = GlobalInfo::getInstance()->screenScaleX;
    string envirEffect = "";
    string skyeffect = "";
    if(GlobalInfo::getInstance()->battleType == kBattleTYPe_SanGuoWushuan)
    {
        DictMusouBattle* musouBattle = DictMusouBattleManager::getInstance()->getData(m_battleID);
        envirEffect = musouBattle->envirEffect;
        skyeffect = musouBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi)
    {
         DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_battleID);
        envirEffect = stageBattle->envirEffect;
        skyeffect = stageBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        DictLegendBattle* legendBattle = DictLegendBattleManager::getInstance()->getData(m_battleID);
        envirEffect = legendBattle->envirEffect;
        skyeffect = legendBattle->skyEffect;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle || GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        envirEffect = "shuye";
        skyeffect = "sun";
    }
    if(envirEffect.size())
    {
        
        Armature* leaf = Armature::create(envirEffect);
        leaf->setAnchorPoint(Point(0,0));
        leaf->getAnimation()->playWithIndex(0,-1,1);
        PublicShowUI::setTargetScale(leaf,false,false);
        leaf->setPosition(VisibleRect::left().x - 150 * sx,VisibleRect::top().y - leaf->getContentSize().height * sx + 150 * GlobalInfo::getInstance()->screenScaleY);
        this->addChild(leaf,20);
    }
    
    if(skyeffect.size())
    {
        if( ArmatureDataManager::getInstance()->getAnimationData(skyeffect))
        {
            Armature* sunLight = Armature::create(skyeffect);
            sunLight->setAnchorPoint(Point(.5,.5));
            PublicShowUI::setTargetScale(sunLight,false,false);
            sunLight->setPosition(VisibleRect::right().x + 100 * sx,VisibleRect::top().y + 100 * sx);
            sunLight->getAnimation()->playWithIndex(0,-1,1);
            this->addChild(sunLight,10,TAG_SKYEFFECT);

        }
    }
}
void BattleScene::hideSkyEffect(EventCustom* msg)//隐藏阳光层大招的时候隐藏
{
    Node* sunLight = this->getChildByTag(TAG_SKYEFFECT);
    if(sunLight)
    {
        sunLight->setVisible(false);
        sunLight->pause();
    }
    
    ControlBtnPanel* btnPanel = (ControlBtnPanel*)this->getChildByTag(TAG_CONTROLBUTTON);
    if(btnPanel)
    {
        btnPanel->setVisible(false);
    }
    m_simplePad->setVisible(false);
}
void BattleScene::showSkyEffect(EventCustom* msg)//隐藏阳光层大招的时候隐藏
{
    Node* sunLight = this->getChildByTag(TAG_SKYEFFECT);
    if(sunLight)
    {
        sunLight->setVisible(true);
        sunLight->resume();
    }

    this->showControlBar();
  
}
void BattleScene::onTargetFlashMove(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onTargetFlashMove((Avatar*)msg->getUserData());
    }
}
void BattleScene::onSkill4Over(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onSkill4Over();
    }
    onCameraReset(msg);

    
}
void BattleScene::onCameraSelf(EventCustom* msg)//摄像机移动到自己身上
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onFocusToSelf((Avatar*)msg->getUserData());
    }
}
void BattleScene::onCameraEnemy(EventCustom* msg)//摄像机移动到敌方身上
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onFocusToEnemy((Avatar*)msg->getUserData());
    }
}
void BattleScene::onCameraScale(EventCustom* msg)
{
    Avatar* target = (Avatar*)msg->getUserData();
  
    int num = atoi(target->_frameParam.c_str());
    target->isCamreIn = num != 0;
    CameraIn* cameraIn = CameraIn::create(.3, num);
    m_mapLayer->runAction(cameraIn);
}
void BattleScene::onCameraMoveUp(EventCustom* msg)//摄像机上移
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onFocusUp((Avatar*)msg->getUserData());
    }
}
void BattleScene::onCameraMoveDown(EventCustom* msg)//摄像机下移
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onFocusDown((Avatar*)msg->getUserData());
    }
}
void BattleScene::onChangeBigSkillBg(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onChangeSkillBg((Avatar*)msg->getUserData());
    }
}
void BattleScene::onReleaseBigSkill(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onReleaseBigSkill((Avatar*)msg->getUserData());
    }
}
void BattleScene::onShowOtherAvatar(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onShowOtherAvatar((Avatar*)msg->getUserData());
    }
}
void BattleScene::onHideOtherAvatar(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onHideOtherAvatar((Avatar*)msg->getUserData());
    }
}
void BattleScene::onMonsterDead(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onMonsterDead((Avatar*)msg->getUserData());
    }
}
void BattleScene::onHeroDead(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onHeroDead((Hero*)msg->getUserData());
    }
}
void BattleScene::onHeroRemove(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onHeroRemove((Hero*)msg->getUserData());
    }
}

void BattleScene::showHealthWarning(EventCustom* msg)
{
    hideHealthWarning(NULL);
    if(!ArmatureDataManager::getInstance()->getAnimationData(AVATAR_DEAD_WARNING))
    {
        return;
    }
    Armature* armature = Armature::create(AVATAR_DEAD_WARNING);
 
    armature->setAnchorPoint(Point(.5,.5));
    PublicShowUI::setTargetScale(armature,false,false);
    armature->setPosition(VisibleRect::center().x,VisibleRect::center().y);
    armature->getAnimation()->playWithIndex(0,-1,1);
    this->addChild(armature,11,TAG_HEALTHWARNING);
    HeroHeadListLayer::getInstance()->showBloodEffect();
    
}
void BattleScene::hideHealthWarning(EventCustom* msg)
{
    if(this->getChildByTag(TAG_HEALTHWARNING))
    {
        this->removeChildByTag(TAG_HEALTHWARNING);
        HeroHeadListLayer::getInstance()->hideBloodEffect();
    }
}
void BattleScene::onBattleEatBloodBottle(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        m_mapLayer->onEatBlood();
    }
}

void BattleScene::addEventListener()
{
    addUserMsg(CUSTOM_SHOW_SIMPLEPAD,CC_CALLBACK_1(BattleScene::showControlBar, this));
    addUserMsg(CUSTOM_SHOW_FULLSCREEN,CC_CALLBACK_1(BattleScene::showFullScreenSkill, this));
    addUserMsg(CUSTOM_CAMERA_IN,CC_CALLBACK_1(BattleScene::onCameraIn, this));
    addUserMsg(CUSTOM_CAMERA_RESET,CC_CALLBACK_1(BattleScene::onCameraReset, this));
    
    addUserMsg(CUSTOM_SKILL1_CD,CC_CALLBACK_1(BattleScene::onSkill1Cd, this));
    addUserMsg(CUSTOM_SKILL2_CD,CC_CALLBACK_1(BattleScene::onSkill2Cd, this));
    addUserMsg(CUSTOM_SKILL3_CD,CC_CALLBACK_1(BattleScene::onSkill3Cd, this));
    addUserMsg(CUSTOM_SKILL4_CD,CC_CALLBACK_1(BattleScene::onSkill4Cd, this));
    addUserMsg(CUSTOM_SKILL5_CD,CC_CALLBACK_1(BattleScene::onSkill5Cd, this));
 
    addUserMsg(CUSTOM_BATTLE_CHANGE_MAINHERO,CC_CALLBACK_1(BattleScene::onChangeMainHero, this));
    addUserMsg(CUSTOM_BATTLE_FLASHMOVE,CC_CALLBACK_1(BattleScene::onTargetFlashMove, this));
    
    addUserMsg(CUSTOM_SKILL4_OVER,CC_CALLBACK_1(BattleScene::onSkill4Over, this));
    

    addUserMsg(CUSTOM_CAMERA_MOVESELF,CC_CALLBACK_1(BattleScene::onCameraSelf, this));
    addUserMsg(CUSTOM_CAMERA_MOVEENEMY,CC_CALLBACK_1(BattleScene::onCameraEnemy, this));

    addUserMsg(CUSTOM_CAMERA_MOVEUP,CC_CALLBACK_1(BattleScene::onCameraMoveUp, this));
    addUserMsg(CUSTOM_CAMERA_MOVEDOWN,CC_CALLBACK_1(BattleScene::onCameraMoveDown, this));
     addUserMsg(CUSTOM_CAMERA_SCALE, CC_CALLBACK_1(BattleScene::onCameraScale, this));
    
    addUserMsg(CUSTOM_HIDE_MAPRESOURCE,CC_CALLBACK_1(BattleScene::hideSkyEffect, this));
    addUserMsg(CUSTOM_SHOW_MAPREOURCE,CC_CALLBACK_1(BattleScene::showSkyEffect, this));
    addUserMsg(CUSTOM_BATTLE_CHANGESKILLBG, CC_CALLBACK_1(BattleScene::onChangeBigSkillBg, this));
    addUserMsg(CUSTOM_BATTLE_RELEASEBIGSKILL, CC_CALLBACK_1(BattleScene::onReleaseBigSkill, this));
    
    addUserMsg(CUSTOM_BATTLE_HIDEOTHER, CC_CALLBACK_1(BattleScene::onHideOtherAvatar, this));
    addUserMsg(CUSTOM_BATTLE_SHOWOTHER, CC_CALLBACK_1(BattleScene::onShowOtherAvatar, this));
    
    addUserMsg(CUSTOM_BATTLE_MONSTER_DEAD, CC_CALLBACK_1(BattleScene::onMonsterDead, this));
    addUserMsg(CUSTOM_BATTLE_HERO_DEAD, CC_CALLBACK_1(BattleScene::onHeroDead, this));
    addUserMsg(CUSTOM_BATTLE_HERO_LIFETIME, CC_CALLBACK_1(BattleScene::onHeroRemove, this));
    addUserMsg(CUSTOM_BATTLE_QUITBATTLE, CC_CALLBACK_1(BattleScene::onQuitBattle, this));
    addUserMsg(CUSTOM_BATTLE_REPLAY, CC_CALLBACK_1(BattleScene::onReplayBattle, this));
    
     addUserMsg(CUSTOM_SHOW_HEALTHWARNING, CC_CALLBACK_1(BattleScene::showHealthWarning, this));
     addUserMsg(CUSTOM_HIDE_HEALTHWARNING, CC_CALLBACK_1(BattleScene::hideHealthWarning, this));
    addUserMsg(CUSTOM_BATTLE_EAT_BLOODBOTTLE, CC_CALLBACK_1(BattleScene::onBattleEatBloodBottle, this));
    addUserMsg(CUSTOM_BATTLE_SHOW_BOSS_WARNING, CC_CALLBACK_1(BattleScene::showBossComeEffect, this));
    addUserMsg(CUSTOM_BATTLE_SHAKE, CC_CALLBACK_1(BattleScene::onShakeScreen, this));
    addUserMsg(CUSTOM_PAUSE_AVATAR_ACTION, CC_CALLBACK_1(BattleScene::pauseAvatarAction, this));
    addUserMsg(CUSTOM_RESET_AVATAR_ACTION, CC_CALLBACK_1(BattleScene::resetAvatarAction, this));
    addUserMsg(CUSTOMM_STOP_ACTION, CC_CALLBACK_1(BattleScene::stopActionMovent, this));

}
void BattleScene::stopActionMovent(EventCustom* msg)
{
    this->pauseAvatarAction(NULL);
    DelayTime* delay = DelayTime::create(.2);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(BattleMapLayer::resumeOtherAvatar, m_mapLayer));
    this->runAction(Sequence::create(delay,callBack, NULL));
}
void BattleScene::resetAvatarAction(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        this->m_mapLayer->goonAvatarAction();
    }
}
void BattleScene::pauseAvatarAction(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        this->m_mapLayer->pauseOtherAvatar(NULL);
    }
}
void BattleScene::onShakeScreen(EventCustom* msg)
{
    if(this->m_mapLayer)
    {
        this->m_mapLayer->playShakeScreen();
    }
}
void BattleScene::onReplayBattle(EventCustom* msg)
{
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        BattleLoader::requestStageBattle(GlobalInfo::getInstance()->famouseBossID);
    }
    else
    {
        
        BattleLoader::requestStageBattle(m_battleID);
    }
    
}
void BattleScene::onQuitBattle(EventCustom* msg)
{
    __Bool* isWin = (__Bool*)msg->getUserData();
    if(GlobalInfo::getInstance()->battleType == BattleType::kBattleType_MingZhanYi && GlobalInfo::getInstance()->stageMode == kStageModeCommon && isWin->getValue())
    {
      
        NewPlayerGuild::getInstance()->onStageBattleOver(this->m_battleID);
    }
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingJiangZhuan)
    {
        if(this->m_fromScene == SCENE_TAG_CHAPTER)
        {
            ChapterLayer::requestChapterByID();
        }
        else if(isWin->getValue())
        {
             GeneralScene::show(SCENE_TAG_MAINUI,GeneralScene::PAGE_DETAILS);
        }
        else
        {
            GeneralScene::show(SCENE_TAG_MAINUI,GeneralScene::PAGE_FIGHTGO);
        }

        return;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_TestBattle)
    {
       
        ChapterLayer::requestChapterByID();
        PlayerDataManager::destroyInstance();
        return;
    }
    else if(GlobalInfo::getInstance()->battleType == kBattleType_ArenaBattle)
    {
        ArenaLayer::show(ArenaLayer::PAGE_ARENALIST);
        return;
    }

    backScene();
}
void BattleScene::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void BattleScene::onFamouseTouch()
{
    FamouseTouchMsg* msg = new FamouseTouchMsg(this->m_battleID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void BattleScene::backScene()
{
 
    switch (this->m_fromScene)
    {
        case SCENE_TAG_CHAPTER:
        {
      
            DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(this->m_battleID);
            if(!stageBattle)
            {
                return;
            }
            int index = NewPlayerGuild::getInstance()->getStageBattleIndex(this->m_battleID);
            if(index < 3)
            {
                 GlobalInfo::getInstance()->chapterOpenStage = stageBattle->inStageId;
            }
            else
            {
                GlobalInfo::getInstance()->chapterOpenStage = 0;
            }
           
            ChapterLayer::requestChapterByID(stageBattle->inChapterId);
         
        }
        break;
        default:
        BaseLayer::backScene();
        break;
    }
    if(GlobalInfo::getInstance()->battleType == kBattleType_MingZhanYi && FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLegend) )
    {
        onFamouseTouch();
    }
    
}
