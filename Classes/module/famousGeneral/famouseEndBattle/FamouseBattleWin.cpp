//
//  FamouseBattleWin.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#include "FamouseBattleWin.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/famouseGeneral/FamouseEndBattle.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictLegendBattle/DictLegendBattleManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../commonData/dictData/DictLegendBattleMonster/DictLegendBattleMonsterManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../famousGeneral/GeneralScene.hpp"
FamouseBattleWin::FamouseBattleWin()
:m_bossID(0)
,m_hurt(0)
,m_useBloodBottle(0)

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
{
    heroList = new Vector<DictAvatarProp*>();
}
FamouseBattleWin::~FamouseBattleWin()
{
    CC_SAFE_DELETE(heroList);
    heroList = NULL;
}
bool FamouseBattleWin::init(int bossID,int hurt,int useHpBottleCount)
{
    m_bossID = bossID;
    m_hurt = hurt;
    m_useBloodBottle = useHpBottleCount;
    this->setBackground(IMG_FAMOUSE_SETTLE_BG);
    setTitle();
    setEndBtn();
    setVSFlag();
    this->isShowGrayBg = true;
    this->isAnimation = true;
    return true;
}
void FamouseBattleWin::show(int bossID,int hurt,int useHpBottleCount)
{
    FamouseBattleWin* layer = FamouseBattleWin::create(bossID, hurt, useHpBottleCount);
    layer->setAnchorPoint(Point::ZERO);
 
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
    
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
}
void FamouseBattleWin::setBossHead()
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
void FamouseBattleWin::setEndBtn()
{
    Node* bg = this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, CC_CALLBACK_1(FamouseBattleWin::onEndBtnClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->addTitle(IMG_FAMOUSE_SETTLE_END, IMG_FAMOUSE_SETTLE_END);
    PublicShowUI::setTargetScale(btn);
    this->addChild(btn);
    
    btn->setPosition(this->getContentSize().width + 10 * sx,bg->getContentSize().height/2 );

    
    CustomButton* againBtn = CustomButton::create(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, CC_CALLBACK_1(FamouseBattleWin::onAgainClick, this));
    againBtn->setAnchorPoint(Point::ZERO);
    againBtn->addTitle(IMG_FAMOUSE_SETTLE_VIEW, IMG_FAMOUSE_SETTLE_VIEW);
    PublicShowUI::setTargetScale(againBtn);
    
    this->addChild(againBtn);
    againBtn->setPosition(btn->getPositionX(), btn->getPositionY() - againBtn->getContentSize().height - 20 * sx);

//    ComboBoxBtn* comboBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL, 15, CC_CALLBACK_1(FamouseBattleWin::onComboClick, this));
//    comboBtn->setAnchorPoint(Point::ZERO);
//    comboBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_FAMOUSE_SETTLE_END, IMG_FAMOUSE_SETTLE_END);//结束
//    comboBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE, IMG_PUBLIC_COMBOBOX_BTNCHOSE, IMG_FAMOUSE_SETTLE_VIEW, IMG_FAMOUSE_SETTLE_VIEW);//查看
//    
}
void FamouseBattleWin::onComboClick(Ref* pSender)
{
    
}
void FamouseBattleWin::onAgainClick(Ref* pSender)
{
    GeneralScene::show(SCENE_TAG_MAINUI,GeneralScene::PAGE_DETAILS);
//    this->removeFromParent();
//    broadMsg(CUSTOM_BATTLE_REPLAY);
}
void FamouseBattleWin::onEndBtnClick(Ref* pSender)
{
    broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(true));
    this->removeFromParent();
    
}
void FamouseBattleWin::setTitle()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size size = this->getContentSize();
    Sprite* title = Sprite::create(IMG_FAMOUSE_SETTLE_WINTITLE);
    PublicShowUI::setTargetScale(title,false,false);
    title->setPosition(size.width/2, size.height + title->getContentSize().height * sx/2 + 20 * sx);
    this->addChild(title,1);
    size.height = size.height + title->getContentSize().height * sx;
    this->setContentSize(size);
}
FamouseBattleWin* FamouseBattleWin::create(int bossID,int hurt,int useHpBottleCount)
{
    FamouseBattleWin* layer = new FamouseBattleWin();
    if(layer && layer->init(bossID, hurt, useHpBottleCount))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void FamouseBattleWin::onEnter()
{
    BaseLayer::onEnter();
}
void FamouseBattleWin::onExit()
{
    BaseLayer::onExit();
}
void FamouseBattleWin::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseBattleWin::onEnterTransitionDidFinish()
{
    SoundManager::stopBackgroundMusic();
    BaseLayer::onEnterTransitionDidFinish();
    requestWinMsg();
}
void FamouseBattleWin::requestWinMsg()
{
    Dialog::showServerLoading();
    if(m_hurt < 0)
    {
        m_hurt = 0;
    }
    FamouseEndBattle* msg = new FamouseEndBattle(2,this->m_bossID,this->m_hurt,this->m_useBloodBottle);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = nullptr;
}
void FamouseBattleWin::onMsgProcess(EventCustom* message)
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
void FamouseBattleWin::setHeroList()
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
void FamouseBattleWin::setUserInfo()
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
    PublicShowUI::setTargetScale(coinSpr);
    this->addChild(coinSpr,3);
    coinSpr->setPosition(expNode->getPositionX() + expNode->getContentSize().width + 15 * sx, expNode->getPositionY() - 10 * sx);
}
void FamouseBattleWin::setVSFlag()
{
    Node* node = this->getChildByTag(TAG_BG);
    Sprite* vsSpr = Sprite::create(IMG_FAMOUSE_SETTLE_VS);
 
    this->addChild(vsSpr,5);
    vsSpr->setPosition(node->getContentSize().width/2 + 10 * GlobalInfo::getInstance()->screenScaleX, node->getContentSize().height/2 + 30 * GlobalInfo::getInstance()->screenScaleX);
    PublicShowUI::setTargetScale(vsSpr,false,false);
    
}
void FamouseBattleWin::setScore()
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
    Sprite* blood = Sprite::create(IMG_FAMOUSE_COME_BLOOD);
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
void FamouseBattleWin::setFightPower()
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
void FamouseBattleWin::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendEndBattleResp).c_str(), CC_CALLBACK_1(FamouseBattleWin::onMsgProcess, this));
}
void FamouseBattleWin::removeEventListener()
{
    BaseLayer::removeEventListener();
}