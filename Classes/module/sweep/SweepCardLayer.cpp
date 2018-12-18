//
//  SweepCardLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/7/1.
//
//

#include "SweepCardLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "CoverView.h"
#include "../../commonData/dictData/DictChapter/DictChapterManager.h"
#include <math.h>
#include "../../commonData/dictData/DictRoleLevel/DictRoleLevelManager.h"
#include "../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../protocol/UserCustomEvent.h"
#include "../battle/BattleLoader.h"
#include "../../message/Decoding/stage/RequestSweepMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../tips/TipsLayer.h"
SweepCardLayer::SweepCardLayer()
:m_stageID(0)
,cardList(NULL)
,rewardList(NULL)
,prestigeList(NULL)
{
    rewardList = DictStageBattleRewardManager::getInstance()->getDataList();
    prestigeList = DictStageBattlePrestigeRewardManager::getInstance()->getDataList();
}
SweepCardLayer::~SweepCardLayer()
{
    CC_SAFE_DELETE(rewardList);
    CC_SAFE_DELETE(prestigeList);
    m_battleDataList = NULL;
    rewardList = NULL;
    prestigeList = NULL;
}

bool SweepCardLayer::init(int stageID,Vector<StageBattleData*>* battleDataList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        this->isAbleGuiding =true;
        this->m_battleDataList = battleDataList;
        m_stageID = stageID;
        setBackGround();
        setCardLayer();
    
        
        bref = true;
    } while (false);
    return bref;
}

SweepCardLayer* SweepCardLayer::create(int stageID,Vector<StageBattleData*>* battleDataList)
{
    SweepCardLayer* list = new SweepCardLayer();
    if(list && list->init(stageID,battleDataList))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void SweepCardLayer::setBackGround()
{
     this->setContentSize(Director::getInstance()->getWinSize());
}
void SweepCardLayer::setCardLayer()
{
    

    DictRoleLevel* dictRoleLevel = DictRoleLevelManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->level);
    long expNum = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? dictRoleLevel-> stageBattleExp : dictRoleLevel->stageBattleExp * 3;
    long coinNum = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? dictRoleLevel-> stageBattleCoin : dictRoleLevel->stageBattleCoin * 3;
    Sprite* bottomSpr = NULL;
    
    Rect swRect = Rect(0,0,Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height);//scrollView大小
    Size slSize = SDResource.size;//scrollLayer 大小
    float disDistance = 0.31f * SDResource.size.width;//card距离间隔
    float disScale = 0.12f;//crad缩放间隔0.05
    CoverView* coverView = CoverView::create(swRect,slSize,disDistance,disScale);
    ssize_t m_totoalCard = m_battleDataList->size();
    StageBattleData* stageBattle = NULL;
    DictStageBattle* dictStage = NULL;
    int initIndex = -1;
    for (int i = 0; i < m_totoalCard; i++)
    {
        stageBattle = m_battleDataList->at(i);
        if(stageBattle->state == 2 && initIndex == -1)
        {
            initIndex = i;
        }
        bottomSpr = Sprite::create(IMG_SWEEP_BOTTOMSPR);
        bottomSpr->setAnchorPoint(Point::ZERO);
        coverView->addCard(bottomSpr,i);
        Sprite* topSpr = Sprite::create(IMG_SWEEP_TOPSPR);
        topSpr->setAnchorPoint(Point::ZERO);
        topSpr->setPosition(Point(15,0));
        bottomSpr->addChild(topSpr,1);
        
        dictStage = DictStageBattleManager::getInstance()->getData(stageBattle->battleId);
        //名字
        Label* nameLabel = PublicShowUI::getLabel(dictStage->name.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        nameLabel->setAnchorPoint(Point::ZERO);
        nameLabel->setPosition((topSpr->getContentSize().width - nameLabel->getContentSize().width)/2 ,topSpr->getContentSize().height - 38);
        bottomSpr->addChild(nameLabel,2);
        
        //描述
        Label* descLabel = PublicShowUI::getLabel(dictStage->desc.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),14,false,false);
        descLabel->setAnchorPoint(Point::ZERO);
        descLabel->setMaxLineWidth(bottomSpr->getContentSize().width - 115);
        descLabel->setPosition(100 , topSpr->getContentSize().height/2  + 29);
        bottomSpr->addChild(descLabel,2);
        
        //第几张
        string numCard = StringUtils::format("%d/%ld",i+1,m_totoalCard);
        Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
        numLabel->setAnchorPoint(Point::ZERO);
        numLabel->setPosition(topSpr->getContentSize().width/2+135,topSpr->getContentSize().height-40);
        bottomSpr->addChild(numLabel,2);
        
    
        
        string timeStr= PublicShowUI::numberToString(stageBattle->usableCount);//当日可用攻击次数
        Label* timeLabel = PublicShowUI::getLabel(timeStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        timeLabel->setAnchorPoint(Point::ZERO);
        timeLabel->setPosition(topSpr->getContentSize().width/2- 50,topSpr->getContentSize().height/2-27);
        bottomSpr->addChild(timeLabel,2);
        
        string powStr= PublicShowUI::numberToString(dictStage->costPower);//消耗体力
        Label* powLabel = PublicShowUI::getLabel(powStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        powLabel->setAnchorPoint(Point::ZERO);
        powLabel->setPosition(topSpr->getContentSize().width/2+120,topSpr->getContentSize().height/2-27);
        bottomSpr->addChild(powLabel,2);
        
        //通关获得
        string expWordstr = "EXP";
        Label* expWord = PublicShowUI::getLabel(expWordstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),20,false,false);
        expWord->setAnchorPoint(Point::ZERO);
        expWord->setPosition(topSpr->getContentSize().width/2- 50,topSpr->getContentSize().height/2-58);
        bottomSpr->addChild(expWord);
        
        string expStr = PublicShowUI::numberToString(expNum);//经验
        Label* expLabel = PublicShowUI::getLabel(expStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        expLabel->setAnchorPoint(Point::ZERO);
        expLabel->setPosition(expWord->getPositionX() + expWord->getContentSize().width, expWord->getPositionY());
        bottomSpr->addChild(expLabel);
        
        
        Sprite* coinIcon = Sprite::create(IMG_ICON_PUBLIC_COIN);
        coinIcon->setAnchorPoint(Point::ZERO);
        coinIcon->setPosition(expLabel->getPositionX() + expLabel->getContentSize().width + 10,expWord->getPositionY() - 10);
        bottomSpr->addChild(coinIcon,2);
        
        string coinStr = PublicShowUI::numberToString(coinNum);//经验
        Label* coinLabel = PublicShowUI::getLabel(coinStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        coinLabel->setAnchorPoint(Point::ZERO);
        coinLabel->setPosition(coinIcon->getContentSize().width, expWord->getPositionY());
        coinIcon->addChild(coinLabel);
        
        
        Sprite* starSpr = NULL;
        for (int i = 0; i < stageBattle->starCount; i++) {
            starSpr = Sprite::create(IMG_SWEEP_STAR);
            starSpr->setAnchorPoint(Point::ZERO);
            starSpr->setScale(0.6);
            starSpr->setPosition(65,i*(starSpr->getContentSize().height-4)+bottomSpr->getContentSize().height/2+63);
            bottomSpr->addChild(starSpr,2);
        }
    
        //进击
        Button* jinjiBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_YELLOW, "", CC_CALLBACK_1(SweepCardLayer::onFightClick, this));
        jinjiBtn->setEnabled(stageBattle->state != 3);
        jinjiBtn->setAnchorPoint(Point::ZERO);
        jinjiBtn->setPosition(295,17);
        bottomSpr->addChild(jinjiBtn,5,i);
        cardList.pushBack(jinjiBtn);
        Sprite* jinjiWord = Sprite::create(IMG_PUBLIC_LABEL_JINJIWORD);
//        jinjiWord->setAnchorPoint(Point::ZERO);
        jinjiWord->setPosition(jinjiBtn->getContentSize().width*.5,jinjiBtn->getContentSize().height * .5);
        jinjiBtn->addChild(jinjiWord,10);
        if(initIndex == i || (initIndex == -1 && i == 0))
        {
            GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAttack);
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAttack, jinjiBtn);
        }
        
        //扫荡
        if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumClearing))
        {
            Button* saodangFiveBtn = Button::create(IMG_BUTTON__DAODANGFIVE,  IMG_BUTTON__DAODANGFIVE, CC_CALLBACK_1(SweepCardLayer::onSweepClick, this));
            saodangFiveBtn->setEnabled(stageBattle->starCount >= 3 && stageBattle->usableCount);
            
            saodangFiveBtn->setAnchorPoint(Point::ZERO);
            saodangFiveBtn->setPosition(70,25);
            bottomSpr->addChild(saodangFiveBtn,5,dictStage->id);
            cardList.pushBack(saodangFiveBtn);
            
            Button* saodangOneBtn = Button::create(IMG_BUTTON__SAODANGONE,  IMG_BUTTON__SAODANGONE, CC_CALLBACK_1(SweepCardLayer::onSweepOneClick, this));
            saodangOneBtn->setEnabled(stageBattle->starCount >= 3 && stageBattle->usableCount);
            
            saodangOneBtn->setAnchorPoint(Point::ZERO);
            saodangOneBtn->setPosition(saodangFiveBtn->getPositionX()+saodangFiveBtn->getContentSize().width-20,saodangFiveBtn->getPositionY());
            bottomSpr->addChild(saodangOneBtn,5,dictStage->id);
            cardList.pushBack(saodangOneBtn);
        }
        
        //普通背景
        Sprite* ptWordpic =  GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? Sprite::create(IMG_SWEEP_PICPT) : Sprite::create(IMG_SWEEP_PICJY);
        ptWordpic->setAnchorPoint(Point::ZERO);
        ptWordpic->setPosition(Point(65, topSpr->getContentSize().height-ptWordpic->getContentSize().height-16));
        bottomSpr->addChild(ptWordpic,6);
        
        const char* path = PublicShowUI::getResImgPath(IMG_BATTLE_SMALLMAP, dictStage->cardResource.c_str());
        Sprite* ptPic = Sprite::create(path);
        ptPic->setAnchorPoint(Point::ZERO);
        ptPic->setScale(.9);
        ptPic->setPosition(80,topSpr->getContentSize().height/2+40);
        bottomSpr->addChild(ptPic,0);
        
        setDropItems(bottomSpr,stageBattle->battleId);
        setDropPrestigeItems(bottomSpr,stageBattle->battleId);
    }
    
    if(initIndex <= 0)
    {
         coverView->setCurCardByIndex(0);
    }
    else
    {
         coverView->setCurCardByIndex(initIndex);
    }

    coverView->setPosition(swRect.origin.x,swRect.origin.y-30);
    addChild(coverView);
//    PublicShowUI::setTargetScale(coverView);
}
bool sortDropItem(DictStageBattleReward* a,DictStageBattleReward* b)
{
    return a->id > b->id;
}
void SweepCardLayer::setDropItems(Node* parent,int stageBattleID)//设置掉落物 概率获得
{

    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    TouchSprite* icon = NULL;
    int itemID = 0;
    sort(rewardList->begin(), rewardList->end(), sortDropItem);
    ssize_t len = rewardList->size();
    DictStageBattleReward* data = NULL;
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        data = rewardList->at(i);
        if(data->stageBattleId == stageBattleID)
        {
            itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
           
            path = PublicShowUI::getGoods(data->itemType, itemID);
            icon = getItemIcon(path,PublicShowUI::getQuality(data->itemType, itemID));
            
            if(icon)
            {
                icon->addTouchBegainCallBack(this, callfuncN_selector(SweepCardLayer::onItemClick));
                icon->setAnchorPoint(Point::ZERO);
                icon->setPositionX(index * (icon->getContentSize().width + 4));
                container->addChild(icon,index,i);
                index++;
            }
        }
    }
    if(icon)
    {
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(160, 155);
        parent->addChild(container,10);
    }
}
bool sortDropPrestigeItem(DictStageBattlePrestigeReward* a,DictStageBattlePrestigeReward* b)
{
    return a->id > b->id;
}
void SweepCardLayer::setDropPrestigeItems(Node* parent,int stageBattleID)//声望获得
{
    int index = 0;
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    TouchSprite* icon = NULL;
    int itemID = 0;
    ssize_t len = prestigeList->size();
    sort(prestigeList->begin(), prestigeList->end(),sortDropPrestigeItem);
    DictStageBattlePrestigeReward* data = NULL;
    for (int i = 0; i < len; i++)
    {
        data = prestigeList->at(i);
        if(data->stageBattleId == stageBattleID)
        {
            itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
            
            path = PublicShowUI::getGoods(data->itemType, itemID);
            if(strcmp(path, "") != 0)
            {
                icon = getItemIcon(path,PublicShowUI::getQuality(data->itemType,itemID));
                if(icon)
                {
                    icon->addTouchBegainCallBack(this, callfuncN_selector(SweepCardLayer::onDropPrestigeClick));
                    icon->setAnchorPoint(Point::ZERO);
                    icon->setPositionX(index * (icon->getContentSize().width + 4));
                    container->addChild(icon,index,i);
                    index++;
                }
            }
            
        }
    }
    if(icon)
    {
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(160, 90);
        parent->addChild(container,10);
    }
}
void SweepCardLayer::onItemClick(Node* node)
{
    DictStageBattleReward* data = rewardList->at(node->getTag());
     int itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
    TipsLayer::show(data->itemType, itemID, 0);
}
void SweepCardLayer::onDropPrestigeClick(Node* node)
{
    DictStageBattlePrestigeReward* data = prestigeList->at(node->getTag());
    int itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
    TipsLayer::show(data->itemType,itemID, 0);
}
TouchSprite* SweepCardLayer::getItemIcon(const char* resource,int quality)
{
    if(strcmp(resource, "") == 0)
    {
        return NULL;
    }
    char sttr[100]="";
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
  
    TouchSprite* headBg = TouchSprite::createWithPic(sttr, NULL, NULL);
    headBg->setAnchorPoint(Point::ZERO);
  
    Sprite* head = Sprite::create(resource);
    if(!head)
    {
        return NULL;
    }
    headBg->addChild(head);
    head->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
    
    
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
   
    Sprite* headForm = Sprite::create(stt);
    float sx = (headForm->getContentSize().width - 10) / head->getContentSize().width;
    head->setScale(sx);
    headBg->addChild(headForm);
    headForm->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
    headBg->setScale(.5);
    headBg->setContentSize(headBg->getContentSize() * .5);
    return headBg;
}


void SweepCardLayer::onFightClick(Ref* psender)
{

    Dialog::showServerLoading();
    Button* target = (Button*)psender;
    int index = target->getTag();
    StageBattleData* stageBattle = m_battleDataList->at(index);
    GlobalInfo::getInstance()->isShowStoryTalk = stageBattle->starCount <= 0;
    
    BattleLoader::requestStageBattle(stageBattle->battleId);
    NewPlayerGuild::getInstance()->pause();
    this->getParent()->removeFromParent();
}
void SweepCardLayer::onSweepClick(Ref* pSender)
{
    Dialog::showServerLoading();
    Button* target = (Button*)pSender;
    int battleid = (target->getTag());
    RequestSweepMsg* msg = new RequestSweepMsg(battleid,5);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void SweepCardLayer::onSweepOneClick(Ref* pSender)
{
    Dialog::showServerLoading();
    Button* target = (Button*)pSender;
    int battleid = (target->getTag());
    RequestSweepMsg* msg = new RequestSweepMsg(battleid,1);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void SweepCardLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SweepCardLayer::onExit()
{
    BaseLayer::onExit();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAttack);
}

