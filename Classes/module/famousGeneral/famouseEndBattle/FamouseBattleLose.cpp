//
//  FamouseBattleLose.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseBattleLose.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/famouseGeneral/FamouseEndBattle.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictLegendBattle/DictLegendBattleManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../commonData/dictData/DictLegendBattleMonster/DictLegendBattleMonsterManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/GraySprite/GraySprite.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../famouseShare/FamouseFriendLayer.hpp"
#include "../../../common/customButton/CustomButton.hpp"
#include "../famouseBossCome/FamouseReset.hpp"
FamouseBattleLose::FamouseBattleLose()
:m_bossID(0)
,m_hurt(0)
,m_useBloodBottle(0)
,m_isEascape(false)
,m_score(0)
,expAdd(0)
,coinAdd(0)
,roleLevelOld(0)
,roleLevelNew(0)
,bossRemainSeconds(0)
,lineupCombatPower(0)
,lineupPrestige(0)
,bossDictId(0)
,bossLevel(0)
,bossHp(0)
,bossMaxHp(0)
,attackCount(0)
,attackCountMax(0)
,TAG_TOPBTNS(3)
{
    heroList = new Vector<DictAvatarProp*>();
}
FamouseBattleLose::~FamouseBattleLose()
{
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
}
bool FamouseBattleLose::init(bool isEascape ,int bossID,int hurt,int useHpBottleCount)
{
    m_isEascape = isEascape;
    m_bossID = bossID;
    m_hurt = hurt;
    m_useBloodBottle = useHpBottleCount;
   
    GraySprite* bg =GraySprite::create(IMG_FAMOUSE_SETTLE_BG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg);
    this->setContentSize(bg->getContentSize());
    this->addChild(bg,0,TAG_BG);
    
    setTitle();
    setEndBtn();
    setVSFlag();
    this->isShowGrayBg = true;
    this->isAnimation = true;
    return true;
}
void FamouseBattleLose::show(bool isEascape ,int bossID,int hurt,int useHpBottleCount)
{
    FamouseBattleLose* layer = FamouseBattleLose::create( isEascape ,bossID, hurt, useHpBottleCount);
    layer->setAnchorPoint(Point::ZERO);
    
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
    
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
}
void FamouseBattleLose::setBossHead()
{
    float sx =GlobalInfo::getInstance()->screenScaleX;
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(this->bossDictId);
    Node* node = this->getChildByTag(TAG_BG);
    if(dictMonster)
    {
        
        DictLegendBattleMonster* legendMonster = DictLegendBattleMonsterManager::getInstance()->getData(this->bossDictId);
        int quality = legendMonster ? legendMonster->monsterQuality : 1;
        UserHeadLayer* head=UserHeadLayer::create(dictMonster->resource.c_str(),quality,true);
        PublicShowUI::setTargetScale(head);
        head->hideHeadInfo();
        head->setPosition(this->getContentSize().width - head->getContentSize().width - 20 * sx, node->getContentSize().height/2 + 30 * sx );
        this->addChild(head,8);
        
        Sprite* hitFlag = Sprite::create(IMG_FAMOUSE_SETTLE_HIT);
        PublicShowUI::setTargetScale(hitFlag,false,false);
        hitFlag->setPosition(head->getPositionX() + head->getContentSize().width / 2, node->getContentSize().height /2 - 30 * sx);
        this->addChild(hitFlag,9);
        
        Label* nameLabel = PublicShowUI::getLabel(dictMonster->name.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),24,false,true);
        nameLabel->setAnchorPoint(Point::ZERO);
        nameLabel->setPosition(this->getContentSize().width/2 + 45 * sx, head->getPositionY() - head->getContentSize().height/2 - 60 * sx);
        this->addChild(nameLabel,10);
        string str = "LV" + PublicShowUI::numberToString(this->bossLevel);
        Label* lvLabel = PublicShowUI::getLabel(str.c_str(),Color3B::GREEN,24,false,true);
        lvLabel->setAnchorPoint(Point::ZERO);
        lvLabel->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + 10 * sx, nameLabel->getPositionY());
        this->addChild(lvLabel,11);
    }
    
}
void FamouseBattleLose::setEndBtn()
{
    Node* bg = this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Button* btn = Button::create(IMG_BATTLERESULT_ENDBTN, "", CC_CALLBACK_1(FamouseBattleLose::onEndBtnClick, this));
//    btn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(btn);
//    this->addChild(btn);
//    
//    btn->setPosition(this->getContentSize().width + 10 * sx,bg->getContentSize().height/2 );
//    
//    
//    Button* againBtn = Button::create(IMG_BATTLERESULT_AGAINBTN, "", CC_CALLBACK_1(FamouseBattleLose::onAgainClick, this));
//    againBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(againBtn);
//    this->addChild(againBtn);
//    againBtn->setPosition(btn->getPositionX(), btn->getPositionY() - againBtn->getContentSize().height - 20 * sx);
    
    ComboBoxBtn* comboBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, 15, CC_CALLBACK_1(FamouseBattleLose::onComboClick, this));
    comboBtn->setAnchorPoint(Point::ZERO);
    comboBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_FAMOUSE_SETTLE_END, IMG_FAMOUSE_SETTLE_END);//结束
    comboBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_FAMOUSE_SETTLE_AGAIN, IMG_FAMOUSE_SETTLE_AGAIN);//再战
    comboBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_FAMOUSE_SETTLE_SUPPORT, IMG_FAMOUSE_SETTLE_SUPPORT);//支援
    PublicShowUI::setTargetScale(comboBtn);
    comboBtn->setPosition(this->getContentSize().width + 10 * sx,7 * sx);
    this->addChild(comboBtn,4,TAG_TOPBTNS);
}
void FamouseBattleLose::onComboClick(Ref* pSender)
{
    ComboBoxBtn* comBtn = (ComboBoxBtn*)this->getChildByTag(TAG_TOPBTNS);
    CustomButton* btn = (CustomButton*)pSender;
    int tag = btn->getTag();
    if(tag == 0)
    {
        onEndBtnClick(NULL);
    }
    else if(tag == 1)
    {
        onAgainClick(NULL);
    }
    else if(tag == 2)
    {
        comBtn->resetAllBtn();
        FamouseFriendLayer::show();
    }
}
void FamouseBattleLose::onAgainClick(Ref* pSender)
{
   
    if(GlobalInfo::getInstance()->famouseChallengeCount <= 0)
    {
        onResetClick(pSender);
        return;
    }
    this->removeFromParent();
    broadMsg(CUSTOM_BATTLE_REPLAY);
}
void FamouseBattleLose::onEndBtnClick(Ref* pSender)
{
    broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(false));
    this->removeFromParent();
    
}
void FamouseBattleLose::setTitle()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size size = this->getContentSize();
    Sprite* title = Sprite::create(IMG_FAMOUSE_SETTLE_LOSETITLE);
    PublicShowUI::setTargetScale(title,false,false);
    title->setPosition(size.width/2, size.height + title->getContentSize().height * sx/2 + 10 * sx);
    this->addChild(title,1);
    size.height = size.height + title->getContentSize().height * sx;
    this->setContentSize(size);
}
FamouseBattleLose* FamouseBattleLose::create(bool isEascape,int bossID,int hurt,int useHpBottleCount)
{
    FamouseBattleLose* layer = new FamouseBattleLose();
    if(layer && layer->init(isEascape,bossID, hurt, useHpBottleCount))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void FamouseBattleLose::onEnter()
{
    BaseLayer::onEnter();
    SoundManager::playEffectMusic(EFFECT_LOSE);
}
void FamouseBattleLose::onExit()
{
    BaseLayer::onExit();
}
void FamouseBattleLose::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseBattleLose::onEnterTransitionDidFinish()
{
    SoundManager::stopBackgroundMusic();
    BaseLayer::onEnterTransitionDidFinish();

    requestLoseMsg();
}
void FamouseBattleLose::requestLoseMsg()
{
    Dialog::showServerLoading();
    if(m_hurt < 0)
    {
        m_hurt = 0;
    }
    int state = m_isEascape ? 3 : 1;
    FamouseEndBattle* msg = new FamouseEndBattle(state,this->m_bossID,this->m_hurt,this->m_useBloodBottle);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = nullptr;
}
void FamouseBattleLose::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendEndBattleResp)
    {
        this->m_score = msg->byteStream->getInt();
        this->expAdd = msg->byteStream->getInt();
        this->coinAdd = msg->byteStream->getInt();
        this->roleLevelOld = msg->byteStream->getInt();
        this->roleLevelNew = msg->byteStream->getInt();
        this->bossRemainSeconds = msg->byteStream->getInt();
        this->lineupCombatPower = msg->byteStream->getInt();
        this->lineupPrestige = msg->byteStream->getInt();
        this->bossDictId = msg->byteStream->getInt();
        this->bossLevel	= msg->byteStream->getShort();
        this->bossHp = msg->byteStream->getInt();
        this->bossMaxHp	= msg->byteStream->getInt();
        this->attackCount = msg->byteStream->getShort();
        this->attackCountMax = msg->byteStream->getShort();
        GlobalInfo::getInstance()->famouseChallengeCount = attackCount;
        int heroSize = msg->byteStream->get();
        for(int i = 0; i < heroSize; i++)
        {
            DictAvatarProp* avatar = new DictAvatarProp();
            avatar->autorelease();
            avatar->dictID = msg->byteStream->getInt();
            avatar->id = msg->byteStream->getInt();
            avatar->level = msg->byteStream->getInt();
            avatar->prestige = msg->byteStream->getInt();
            avatar->quality = msg->byteStream->get();
            heroList->pushBack(avatar);
            
        }
        setBossHead();
        setUserInfo();
        setHeroList();
        setFightPower();
        setScore();
    }
}

void FamouseBattleLose::setHeroList()
{
    Node* node = this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    int len = heroList->size();
    
    DictAvatarProp* hero = NULL;
    DictHero* dictHero = NULL;
    UserHeadLayer* userHead = NULL;
    for(int i = 0; i < len; i++)
    {
        hero = heroList->at(i);
        if(hero->id == 0)
        {
            continue;
        }
        dictHero = DictHeroManager::getInstance()->getData(hero->dictID);
        if(dictHero)
        {
            userHead=UserHeadLayer::create(dictHero->resource.c_str(),hero->quality,true);
            PublicShowUI::setTargetScale(userHead);
            userHead->setHeadInfo(hero->level, hero->prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setCascadeOpacityEnabled(true);
            
            if( i == 0)
            {
                userHead->setPosition(115 * sx, node->getContentSize().height/2 + 30 * sx);
            }
            else
            {
                userHead->setPosition(60 * sx + (i-1) * (userHead->getContentSize().width + 10 * sx), node->getContentSize().height/2 - userHead->getContentSize().height + 20 * sx);
            }
            this->addChild(userHead,4);
            
        }
        
    }
    
}
void FamouseBattleLose::setUserInfo()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* node = this->getChildByTag(TAG_BG);
    int fontSize = 24;
    //名将传名字
    string str = GlobalInfo::getInstance()->famouseName;
    Label* nameLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),fontSize,false,true);
    nameLabel->setAnchorPoint(Point::ZERO);
    this->addChild(nameLabel,3);
    nameLabel->setPosition(25 * sx, node->getContentSize().height - nameLabel->getContentSize().height - 20 * sx);
    
    //玩家等级
    str = "LV" + PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->level);
    Label* levelLabel = PublicShowUI::getLabel(str.c_str(),Color3B::GREEN,fontSize,false,true);
    levelLabel->setAnchorPoint(Point::ZERO);
    this->addChild(levelLabel,3);
    levelLabel->setPosition(nameLabel->getPositionX() + nameLabel->getContentSize().width + 10 * sx, nameLabel->getPositionY());
    //经验
    Node* expNode = Node::create();
    expNode->setAnchorPoint(Point::ZERO);
    Label* expSpr = PublicShowUI::getLabel("EXP ",PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),fontSize,false,false);
    expSpr->setAnchorPoint(Point::ZERO);
    expNode->addChild(expSpr,0);
    str = PublicShowUI::numberToString(this->expAdd);
    Label* expLevel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    expLevel->setAnchorPoint(Point::ZERO);
    expNode->addChild(expLevel,10);
    expLevel->setPosition(expSpr->getContentSize().width, 0);
    Size size = expSpr->getContentSize();
    size.width = size.width + expLevel->getContentSize().width;
    expNode->setContentSize(size);
    PublicShowUI::setTargetScale(expNode);
    this->addChild(expNode,3);
    expNode->setPosition(levelLabel->getPositionX() + levelLabel->getContentSize().width + 15 * sx, levelLabel->getPositionY());
    
    //金币
    Sprite* coinSpr = Sprite::create(IMG_ICON_PUBLIC_COIN);
    coinSpr->setAnchorPoint(Point::ZERO);
    str = PublicShowUI::numberToString(this->coinAdd);
    Label* coinLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    coinSpr->addChild(coinLabel,3);
  
    coinLabel->setPosition(coinSpr->getContentSize().width, (coinSpr->getContentSize().height - coinLabel->getContentSize().height)/2);
    size = coinSpr->getContentSize();
    size.width = coinLabel->getPositionX() + coinLabel->getContentSize().width;
    coinSpr->setContentSize(size);
    
    PublicShowUI::setTargetScale(coinSpr);
    this->addChild(coinSpr,3);
    coinSpr->setPosition(expNode->getPositionX() + expNode->getContentSize().width + 15 * sx, expNode->getPositionY() - 10 * sx);
    //挑战次数
    str = "挑战次数" + PublicShowUI::numberToString(GlobalInfo::getInstance()->famouseChallengeCount) + "/" + PublicShowUI::numberToString(attackCountMax);
    Label* attackCountLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),fontSize,false,true);
    attackCountLabel->setAnchorPoint(Point::ZERO);
    this->addChild(attackCountLabel,3);
    attackCountLabel->setPosition(coinSpr->getPositionX() + coinSpr->getContentSize().width + 5 * sx, expNode->getPositionY());
    
//    //重置按钮
//    CustomButton* resetBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FamouseBattleLose::onResetClick, this));
//    resetBtn->setPosition(attackCountLabel->getPositionX() + attackCountLabel->getContentSize().width + resetBtn->getContentSize().width / 2 + 5 * sx, attackCountLabel->getPositionY() + resetBtn->getContentSize().height/2);
//    resetBtn->addTitle(IMG_PUBLIC_LABEL_RESET, IMG_PUBLIC_LABEL_RESET);
//    this->addChild(resetBtn,4);

}
void FamouseBattleLose::onResetClick(Ref* pSender)
{
    FamouseReset::show(GlobalInfo::getInstance()->famouseChallengeCount);
}
void FamouseBattleLose::setVSFlag()
{
    Node* node = this->getChildByTag(TAG_BG);
    GraySprite* vsSpr = GraySprite::create(IMG_FAMOUSE_SETTLE_VS);
    
    this->addChild(vsSpr,5);
    vsSpr->setPosition(node->getContentSize().width/2 + 10 * GlobalInfo::getInstance()->screenScaleX, node->getContentSize().height/2 + 30 * GlobalInfo::getInstance()->screenScaleX);
    PublicShowUI::setTargetScale(vsSpr,false,false);
    
}
void FamouseBattleLose::setScore()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string str = PublicShowUI::numberToString(this->m_score);
    Label* scoreLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,true);
    scoreLabel->setAnchorPoint(Point::ZERO);
    this->addChild(scoreLabel,10);
    scoreLabel->setPosition(this->getContentSize().width - 175 * sx, 16 * sx);
    
    //伤害
    str = PublicShowUI::numberToString(this->m_hurt);
    Label* hurtLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,true);
    hurtLabel->setAnchorPoint(Point::ZERO);
    this->addChild(hurtLabel,11);
    hurtLabel->setPosition(this->getContentSize().width - 210 * sx, scoreLabel->getPositionY() + scoreLabel->getContentSize().height + 3 * sx);
    
    //血条
    GraySprite* blood = GraySprite::create(IMG_FAMOUSE_COME_BLOOD);
    blood->setAnchorPoint(Point::ZERO);
    
    ProgressTimer* bloodPt = ProgressTimer::create(blood);
    bloodPt->setAnchorPoint(Point::ZERO);
    bloodPt->setScale(.98 * sx ,sx);
    Size size = bloodPt->getContentSize();
    size.width *= .98 * sx;
    size.height *= sx;
    bloodPt->setContentSize(size);
    bloodPt->setType(ProgressTimer::Type::BAR);
    bloodPt->setMidpoint(Point(0,1));
    bloodPt->setBarChangeRate(Point(1,0));
    
    bloodPt->setPosition(this->getContentSize().width/2 + 25 * sx,hurtLabel->getPositionY() + hurtLabel->getContentSize().height + 4 * sx);
    
    this->addChild(bloodPt,8);
    
    bloodPt->setPercentage(bossHp / bossMaxHp * 100);
    
    str = PublicShowUI::numberToString((int)bossHp) + "/" + PublicShowUI::numberToString((int)bossMaxHp);
    Label* percentLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,true);
    percentLabel->setAnchorPoint(Point::ZERO);
    percentLabel->setPosition(bloodPt->getPositionX() + (bloodPt->getContentSize().width - percentLabel->getContentSize().width)/2, bloodPt->getPositionY() + (bloodPt->getContentSize().height - percentLabel->getContentSize().height)/2);
    this->addChild(percentLabel,9);
    
}
void FamouseBattleLose::setFightPower()
{
    //
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string str = PublicShowUI::numberToString(lineupCombatPower);
    Label* powerLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),20,false,true);
    powerLabel->setAnchorPoint(Point::ZERO);
    this->addChild(powerLabel,4);
    powerLabel->setPosition(92 * sx, 50 * sx);
    
    str = PublicShowUI::numberToString(lineupPrestige);
    Label* prestigeLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),20,false,true);
    prestigeLabel->setAnchorPoint(Point::ZERO);
    this->addChild(prestigeLabel,4);
    prestigeLabel->setPosition(powerLabel->getPositionX() + 150 * sx, powerLabel->getPositionY());
}
void FamouseBattleLose::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendEndBattleResp).c_str(), CC_CALLBACK_1(FamouseBattleLose::onMsgProcess, this));
}
void FamouseBattleLose::removeEventListener()
{
    BaseLayer::removeEventListener();
}