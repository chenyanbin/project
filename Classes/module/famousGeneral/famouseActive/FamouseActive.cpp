//
//  FamouseActive.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "FamouseActive.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseActiveMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../../../commonData/dictData/DictLegendBattleMonster/DictLegendBattleMonsterManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../limitCard/LimitCardLayer.h"
#include "../../../common/customButton/CustomButton.hpp"
FamouseActive::FamouseActive()
:TAG_BOSSBG(1)
,TAG_SCOREBG(2)
,m_scoreToday(0)
,m_scoreTotal(0)
,m_selfRank(0)
,dictLegend(NULL)
{
    
}
FamouseActive::~FamouseActive()
{
    dictLegend = NULL;
}
bool FamouseActive::init()
{
    this->isAnimation = false;
    this->setBossBg();
    this->setScoreBg();
    this->setZhaoMuButton();
    return true;
}
void FamouseActive::setBossBg()
{
//    Sprite* bossBg = Sprite::create(IMG_FAMOUSE_ACTIVE_BOSSBG);
    Sprite* bossBg = Sprite::create(IMAGE_FAMOUSE_BOSS);
    if(bossBg)
    {
        bossBg->setAnchorPoint(Point::ZERO);
        bossBg->setPosition(Point::ZERO);
        this->addChild(bossBg,0,TAG_BOSSBG);
    }
   
}
void FamouseActive::setScoreBg()
{
    Node* bossBg = this->getChildByTag(TAG_BOSSBG);
    if(!bossBg)
    {
        return;
    }
    Sprite* scorebg = Sprite::create(IMG_FAMOUSE_ACTIVE_SCOREBG);
    scorebg->setAnchorPoint(Point::ZERO);
    this->addChild(scorebg,1,TAG_SCOREBG);
    scorebg->setPosition(bossBg->getContentSize().width + 10, bossBg->getPositionY());
    
    Size size = scorebg->getContentSize();
    size.width = scorebg->getPositionX() + scorebg->getContentSize().width;
    this->setContentSize(size);
}
void FamouseActive::onEnter()
{
    BaseLayer::onEnter();
}
void FamouseActive::onExit()
{
    BaseLayer::onExit();
}
void FamouseActive::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseActive::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestInfo();
}
void FamouseActive::requestInfo()
{
    Dialog::showServerLoading(1);
    FamouseActiveMsg* msg = new FamouseActiveMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseActive::setScore()
{
    Node* scoreBg = this->getChildByTag(TAG_SCOREBG);
    if(!scoreBg)
    {
        return;
    }
    //总分数
    string str = PublicShowUI::numberToString(m_scoreTotal);
    Label* totalLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
    totalLabel->setAnchorPoint(Point::ZERO);
    scoreBg->addChild(totalLabel,2);
    totalLabel->setPosition(scoreBg->getContentSize().width / 2 + 15, scoreBg->getContentSize().height - 95);
    //今日分数
    str = PublicShowUI::numberToString(m_scoreToday);
    Label* todayLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
    todayLabel->setAnchorPoint(Point::ZERO);
    scoreBg->addChild(todayLabel,3);
    todayLabel->setPosition(totalLabel->getPositionX(), totalLabel->getPositionY() - todayLabel->getContentSize().height - 15);
    
    //今日排行
    str = "第" + PublicShowUI::numberToString(m_selfRank) + "名";
    Label* rankLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_ORANGEYELLOW),24,false,false);
    rankLabel->setAnchorPoint(Point::ZERO);
    scoreBg->addChild(rankLabel,4);
    rankLabel->setPosition(todayLabel->getPositionX(), todayLabel->getPositionY() - todayLabel->getContentSize().height - 15);
    
}
void FamouseActive::setBoss()
{
    int bossID = 0;
    Vector<DictLegendBattleMonster*>* battleMonsters = DictLegendBattleMonsterManager::getInstance()->getDataList();
    for(DictLegendBattleMonster* monster : *battleMonsters)
    {
        if(monster->type == 2)
        {
            bossID = monster->id;
        }
    }
    Node* bossBg = this->getChildByTag(TAG_BOSSBG);
    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(bossID);
    if(!dictMonster || !bossBg)
    {
        return;
    }
   
//    const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictMonster->halfbodyrResource());
//    Sprite* bossSpr = Sprite::create(path);
//    bossSpr->setAnchorPoint(Point::ZERO);
//    bossSpr->setScale(.75);
//    bossSpr->setContentSize(bossSpr->getContentSize() * .7);
//    bossSpr->setPosition((bossBg->getContentSize().width - bossSpr->getContentSize().width)/2, (bossBg->getContentSize().height - bossSpr->getContentSize().height)/2);
//    bossBg->addChild(bossSpr,1);
    
    Label* nameLabel = PublicShowUI::getLabel(dictMonster->name.c_str(),Color3B::WHITE,20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    bossBg->addChild(nameLabel,3);
    nameLabel->setPosition((bossBg->getContentSize().width - nameLabel->getContentSize().width)/2, bossBg->getContentSize().height - nameLabel->getContentSize().height -3);
    
    int typeNum =  dictMonster->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* forceSprite = Sprite::create(stt);
    forceSprite->setAnchorPoint(Point::ZERO);
    forceSprite->setPosition(-5, bossBg->getContentSize().height - forceSprite->getContentSize().height + 15);
    bossBg->addChild(forceSprite,4);
    
}
void FamouseActive::setGenernal()
{
     Node* scoreBg = this->getChildByTag(TAG_SCOREBG);
    DictHero* dictHero = DictHeroManager::getInstance()->getData(dictLegend->multiItemHeroId);
    if(!dictHero || !scoreBg)
    {
        return;
    }
    const char* resource = dictHero ? dictHero->resource.c_str() : "zhaoyun";

    UserHeadLayer* userHead = UserHeadLayer::create(resource,5,true);
    userHead->setAnchorPoint(Point::ZERO);
    userHead->setPosition(65, 40);
    userHead->hideHeadInfo();
    scoreBg->addChild(userHead,4);
    
    Label* nameLabel = PublicShowUI::getLabel(dictHero->name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    scoreBg->addChild(nameLabel,5);
    nameLabel->setPosition(userHead->getPositionX() + userHead->getContentSize().width + 5, userHead->getPositionY() + userHead->getContentSize().height - nameLabel->getContentSize().height);
    string str = "通过招募获得给予当前名将";
    Label* descriptLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
    descriptLabel->setAnchorPoint(Point::ZERO);
    descriptLabel->setPosition(nameLabel->getPositionX(), nameLabel->getPositionY() - descriptLabel->getContentSize().height - 10);
    scoreBg->addChild(descriptLabel,5);
    
    str = "五倍伤害";
    Label* hurtLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_RED),20,false,false);
    hurtLabel->setAnchorPoint(Point::ZERO);
    hurtLabel->setPosition(descriptLabel->getPositionX(), descriptLabel->getPositionY() - hurtLabel->getContentSize().height - 10);
    scoreBg->addChild(hurtLabel,6);
    
}
void FamouseActive::setZhaoMuButton()
{
    Node* scoreBg = this->getChildByTag(TAG_SCOREBG);
    if(!scoreBg)
    {
        return;
    }
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FamouseActive::onZhaoMuClick, this));
    btn->addTitle(IMG_PUBLIC_LABEL_ZHAOMU, IMG_PUBLIC_LABEL_ZHAOMU);
    btn->setAnchorPoint(Point(.5,.5));
    btn->setPosition(scoreBg->getContentSize().width - btn->getContentSize().width - 10, btn->getContentSize().height/2 + 25);
    scoreBg->addChild(btn,4);
}
void FamouseActive::onZhaoMuClick(Ref* pSender)
{
    LimitCardLayer::show();
}
void FamouseActive::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendActivityPageResp)
    {
        int id = msg->byteStream->get();
        dictLegend = DictLegendManager::getInstance()->getData(id);
        m_scoreToday = msg->byteStream->getInt();
        m_scoreTotal = msg->byteStream->getInt();
        m_selfRank = msg->byteStream->getInt();
        
        setScore();
        if(dictLegend)
        {
            setBoss();
            setGenernal();
        }
        
    }
    
}
void FamouseActive::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendActivityPageResp).c_str(), CC_CALLBACK_1(FamouseActive::onMsgProcess, this));
}
void FamouseActive::removeEventListener()
{
    BaseLayer::removeEventListener();
}
