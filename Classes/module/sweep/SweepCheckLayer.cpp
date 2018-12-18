//
//  SweepCheckLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/9.
//
//

#include "SweepCheckLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../commonData/data/FunctionOpenManager.h"
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
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/CustomMsgProcesser.h"
#include "../battleTest/PlayerDataManager.hpp"
SweepCheckLayer::SweepCheckLayer()
:m_stageID(0)
,rewardList(NULL)
,m_chack(0)
,TAG_NODE(10)
,TAG_PTPIC(11)
,TAG_RAIDS(12)
{
    rewardList = DictStageBattleRewardManager::getInstance()->getDataList();
}
SweepCheckLayer::~SweepCheckLayer()
{
    CC_SAFE_DELETE(rewardList);
    m_battleDataList = NULL;
    rewardList = NULL;
}

bool SweepCheckLayer::init(int stageID,Vector<StageBattleData*>* battleDataList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        this->isAbleGuiding = false;
        this->m_battleDataList = battleDataList;
        m_stageID = stageID;
        setBackGround();
        setRaidsCard();
        bref = true;
    } while (false);
    return bref;
}

SweepCheckLayer* SweepCheckLayer::create(int stageID,Vector<StageBattleData*>* battleDataList)
{
    SweepCheckLayer* list = new SweepCheckLayer();
    if(list && list->init(stageID,battleDataList))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void SweepCheckLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SweepCheckLayer::onExit()
{
    BaseLayer::onExit();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAttack);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSpeedButton);
}
void SweepCheckLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void SweepCheckLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    CustomMsgProcesser::getInstance()->nextMsgListData();
}
void SweepCheckLayer::setRaidsCard(EventCustom* msg)//设置扫荡令
{
    //扫荡令
    Label* label = (Label*)this->getChildByTag(TAG_RAIDS);
    string str = PublicShowUI::numberToString(GlobalInfo::getInstance()->raidsCard);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(400, 15);
        this->addChild(label,3,TAG_RAIDS);
    }
   

}
void SweepCheckLayer::setBackGround()
{
    Sprite* boxbg = Sprite::create(IMG_SWEEP_BOXBG);
    boxbg->setAnchorPoint(Point::ZERO);
    boxbg->setPosition(Point::ZERO);
    this->addChild(boxbg,1);
    this->setContentSize(boxbg->getContentSize());
    
    const char* pathList[3] = {IMG_SWEEP_BUTTOMTHREE,IMG_SWEEP_BUTTOMTWO,IMG_SWEEP_BUTTOMONE};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL,-10, CC_CALLBACK_1(SweepCheckLayer::onComboBoxClick, this));
    for (int i = 0; i<3; i++) {
        
        boxBtn->addBtn(IMG_SWEEP_BUTTOMSAODANGUNCHOSE,IMG_SWEEP_BUTTOMSAODANGCHOSE, pathList[i],true);
    }
    boxBtn->setPosition(100,this->getContentSize().height/2-boxBtn->getContentSize().height/2+50);
    this->addChild(boxBtn,1);
    
    ssize_t len = m_battleDataList->size();
    for (int i = 0; i< len; i++) {
        if (m_battleDataList->at(i)->state == 2) {
            m_chack = i;
        }
    }
    
    if (m_chack == 0) {
//        setCardLayer(2);
        boxBtn->selectedAt(2);
    }else if (m_chack == 1)
    {
//        setCardLayer(1);
        boxBtn->selectedAt(1);
    }else if (m_chack == 2)
    {
//        setCardLayer(0);
        boxBtn->selectedAt(0);
    }
    
}
void SweepCheckLayer::onComboBoxClick(Ref* pSender)
{
    
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    switch (tag) {
        case 0:
            setCardLayer(2);
            break;
        case 1:
            setCardLayer(1);
            break;
        case 2:
            setCardLayer(0);
            break;
        default:
            break;
    }
}
void SweepCheckLayer::setCardLayer(int tag)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //进入战斗
   if(m_battleDataList->size() <= 0)
   {
       return;
   }
    StageBattleData* stageBattle = m_battleDataList->at(tag);
    m_stageBattleID = stageBattle->battleId;
    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    
    
    if (this->getChildByTag(TAG_NODE)) {
        this->removeChildByTag(TAG_NODE);
    }
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    
    if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumClearing))
    {
        Button* saodangOneBtn = Button::create(IMG_SWEEP_BUTTOMSAODANG,  IMG_SWEEP_BUTTOMSAODANG, CC_CALLBACK_1(SweepCheckLayer::onSweepOneClick, this));
        saodangOneBtn->setEnabled(stageBattle->starCount >= 3 && stageBattle->usableCount);
        saodangOneBtn->setAnchorPoint(Point::ZERO);
        saodangOneBtn->setPosition(500,5);
        node->addChild(saodangOneBtn,5,dictStage->id);
        Sprite* oneword = Sprite::create(IMG_SWEEP_BUTTOMSAODANGONE);
        oneword->setAnchorPoint(Point::ZERO);
        oneword->setPosition(Point::ZERO);
        saodangOneBtn->addChild(oneword,10);
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSpeedButton, saodangOneBtn);
        
        Button* saodangFiveBtn = Button::create(IMG_SWEEP_BUTTOMSAODANG,  IMG_SWEEP_BUTTOMSAODANG, CC_CALLBACK_1(SweepCheckLayer::onSweepClick, this));
        saodangFiveBtn->setEnabled(stageBattle->starCount >= 3 && stageBattle->usableCount);
        saodangFiveBtn->setAnchorPoint(Point::ZERO);
        saodangFiveBtn->setPosition(saodangOneBtn->getPositionX()+saodangOneBtn->getContentSize().width+20,saodangOneBtn->getPositionY());
        node->addChild(saodangFiveBtn,5,dictStage->id);
        Sprite* fiveword = Sprite::create(IMG_SWEEP_BUTTOMSAODANGFIVE);
        fiveword->setAnchorPoint(Point::ZERO);
        fiveword->setPosition(Point::ZERO);
        saodangFiveBtn->addChild(fiveword,10);
    }
    //进入战斗
    Button* jinjiBtn = Button::create(IMG_SWEEP_BOTTOMFIGHT, "", CC_CALLBACK_1(SweepCheckLayer::onFightClick, this));
    jinjiBtn->setEnabled(stageBattle->state != 3);
    jinjiBtn->setAnchorPoint(Point::ZERO);
    jinjiBtn->setPosition(880,5);
    node->addChild(jinjiBtn,2,tag);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAttack, jinjiBtn);
    //剩余次数
    int totalTimes = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->oneDayTimesElite : dictStage->oneDayTimes;
    string str = "剩余次数:" + PublicShowUI::numberToString(stageBattle->usableCount) + "/" + PublicShowUI::numberToString(totalTimes);
    Label* leftCount = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    leftCount->setAnchorPoint(Point::ZERO);
    leftCount->setPosition(jinjiBtn->getPositionX() + (jinjiBtn->getContentSize().width - leftCount->getContentSize().width)/2, jinjiBtn->getPositionY() + jinjiBtn->getContentSize().height + 20);
    node->addChild(leftCount,7);
    
    //名字
    Label* nameLabel = PublicShowUI::getLabel(dictStage->name.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(720,417);
    node->addChild(nameLabel,2);
    
    
    DictRoleLevel* dictRoleLevel = DictRoleLevelManager::getInstance()->getData(GlobalInfo::getInstance()->gameRole->level);
    long expNum = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? dictRoleLevel-> stageBattleExp : dictRoleLevel->stageBattleExp * 3;
    long coinNum = GlobalInfo::getInstance()->stageMode == StageMode::kStageModeCommon ? dictRoleLevel-> stageBattleCoin : dictRoleLevel->stageBattleCoin * 3;
    
    //通关获得
    string expWordstr = "EXP";
    Label* expWord = PublicShowUI::getLabel(expWordstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),20,false,false);
    expWord->setAnchorPoint(Point::ZERO);
    expWord->setPosition(830,355);
    node->addChild(expWord);
    
//    Sprite* expIcon = Sprite::create(IMG_ICON_EXP);
//    expIcon->setAnchorPoint(Point::ZERO);
//    expIcon->setPosition(830,350);
//    node->addChild(expIcon,2);
    string expStr = PublicShowUI::numberToString(expNum);//经验
    Label* expLabel = PublicShowUI::getLabel(expStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    expLabel->setAnchorPoint(Point::ZERO);
    expLabel->setPosition(expWord->getPositionX() + expWord->getContentSize().width+10, expWord->getPositionY());
    node->addChild(expLabel);
    
    Sprite* coinIcon = Sprite::create(IMG_ICON_PUBLIC_COIN);
    coinIcon->setAnchorPoint(Point::ZERO);
    coinIcon->setScale(0.8);
    coinIcon->setPosition(expLabel->getPositionX() + expLabel->getContentSize().width + 20,expLabel->getPositionY() - 10);
    node->addChild(coinIcon,2);
    
    string coinStr = PublicShowUI::numberToString(coinNum);//铜币
    Label* coinLabel = PublicShowUI::getLabel(coinStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    coinLabel->setPosition(expLabel->getPositionX() + expLabel->getContentSize().width +coinIcon->getContentSize().width+10,expLabel->getPositionY());
    node->addChild(coinLabel);
    
    //消耗体力
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->costPowerElite : dictStage->costPower;
    string powStr= PublicShowUI::numberToString(costPower);//消耗体力
    Label* powLabel = PublicShowUI::getLabel(powStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    powLabel->setAnchorPoint(Point::ZERO);
    powLabel->setPosition(200,15);
    node->addChild(powLabel,2);
    
    //星星获得数
    log("%f,%f",this->getContentSize().height,sx);
    Sprite* starbg = NULL;
    for (int i = 0; i < 3; i++) {
        starbg = Sprite::create(IMG_BATTLERESULT_STARBG);
        starbg->setAnchorPoint(Point::ZERO);
        starbg->setScale(0.5);
        starbg->setPosition(40+i*(starbg->getContentSize().width-50),510);
        node->addChild(starbg,2);
    }
    Sprite* starSpr = NULL;
    for (int i = 0; i < stageBattle->starCount; i++){
        starSpr = Sprite::create(IMG_BATTLERESULT_STAR);
        starSpr->setAnchorPoint(Point::ZERO);
        starSpr->setScale(0.5);
        starSpr->setPosition(40+i*(starSpr->getContentSize().width-50),510);
        node->addChild(starSpr,2);
    }
    
    setDropItems(node,stageBattle->battleId);
    setStartCondition(node);
    this->addChild(node,2,TAG_NODE);
    
    //背景图
    const char* path = PublicShowUI::getResImgPath(IMG_BATTLE_SMALLMAP, dictStage->cardResource.c_str());
    Sprite* ptPic = (Sprite*)this->getChildByTag(TAG_PTPIC);
    if (ptPic) {
        ptPic->setTexture(path);
    }else{
        ptPic = Sprite::create(path);
        ptPic->setAnchorPoint(Point::ZERO);
        this->addChild(ptPic,-1,TAG_PTPIC);
    }
    ptPic->setPosition(Point::ZERO);
    
    
}
void SweepCheckLayer::setStartCondition(Node* parent)//设置通关条件
{
    DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    string str = "";
    if(stageBattle->starDetermine1 > 0)//通关
    {
       
        str += "1.消灭所有敌人;";
       
    }
    if(stageBattle->starDetermine2 > 0)
    {
         str += "2.剩余血量>="+ PublicShowUI::numberToString(stageBattle->starDetermine2 * 100) + "%";
    }
    
    if(stageBattle->starDetermine3 > 0)
    {
        str += "3.用时<=" + PublicShowUI::numberToString(stageBattle->starDetermine3) +"秒";
   
    }
    Label* label = NULL;
   
    label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_PINK),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    parent->addChild(label,10);
    label->setPosition(400 , 525);
    
    
}
void SweepCheckLayer::onFightClick(Ref* pSedner)//进击
{

  
  
    if(GlobalInfo::getInstance()->stageMode == kStageModeBest)
    {
         NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAttack);
    }
    NewPlayerGuild::getInstance()->pause();
    GlobalInfo::getInstance()->battleType = kBattleType_MingZhanYi;
    Button* target = (Button*)pSedner;
    int index = target->getTag();
    StageBattleData* stageBattle = m_battleDataList->at(index);
    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(stageBattle->battleId);
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->costPowerElite : dictStage->costPower;
  
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    
    
    GlobalInfo::getInstance()->isShowStoryTalk = stageBattle->starCount <= 0;
    
    BattleLoader::requestStageBattle(stageBattle->battleId);
    
    this->getParent()->removeFromParent();
}

void SweepCheckLayer::onSweepClick(Ref* pSender)//扫荡五次
{
    Dialog::showServerLoading();
    Button* target = (Button*)pSender;
    int battleid = (target->getTag());
    RequestSweepMsg* msg = new RequestSweepMsg(battleid,5);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void SweepCheckLayer::onSweepOneClick(Ref* pSender)//扫荡一次
{
    if(GlobalInfo::getInstance()->isDebug)
    {
        PlayerDataManager::getInstance()->initData();
        return;
    }
    Dialog::showServerLoading();
    Button* target = (Button*)pSender;
    int battleid = (target->getTag());
    RequestSweepMsg* msg = new RequestSweepMsg(battleid,1);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSpeedButton);
}

bool sortDroptimeItem(DictStageBattleReward* a,DictStageBattleReward* b)
{
    return a->id > b->id;
}
void SweepCheckLayer::setDropItems(Node* parent,int stageBattleID)//设置掉落物 概率获得
{

    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
//    TouchSprite* icon = NULL;
    UserHeadLayer* userHead = NULL;
    UserEquipLayer* head = NULL;
    int itemID = 0;
    sort(rewardList->begin(), rewardList->end(), sortDroptimeItem);
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
            if(strcmp(path, "") == 0)
            {
                continue;
            }
            if(  data->itemType == DictItemTypeEnumItemHero)
            {
                
                userHead=UserHeadLayer::create(path,PublicShowUI::getQuality(data->itemType, itemID),false);
                userHead->setHeadInfo(1, 1);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.7);
                userHead->setPosition(700+index * (userHead->getContentSize().width-30),185);
                container->addChild(userHead,5,i);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(SweepCheckLayer::onItemClick));
                index++;
            }
            else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
            {
                head = UserEquipLayer::create(path,PublicShowUI::getQuality(data->itemType, itemID),false);
                head->setAnchorPoint(Point::ZERO);
                if (data->itemType == DictItemTypeEnumItemMater) {
                    head->setFragment();
                }else if (data->itemType == DictItemTypeEnumItemBook)
                {
                    head->setLetterFragment();
                }
                head->setScale(0.7);
                head->setPosition(700+index * (head->getContentSize().width-30),180);
                container->addChild(head,5,i);
                head->addTouchBegainCallBack(this, callfuncN_selector(SweepCheckLayer::onItemClick));
                index++;
            }
        }
    }
    if(userHead || head)
    {
        parent->addChild(container,10);
    }
}
//TouchSprite* SweepCheckLayer::getItemIcon(const char* resource,int quality)
//{
//    if(strcmp(resource, "") == 0)
//    {
//        return NULL;
//    }
//    char sttr[100]="";
//    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
//    
//    TouchSprite* headBg = TouchSprite::createWithPic(sttr, NULL, NULL);
//    headBg->setAnchorPoint(Point::ZERO);
//    
//    Sprite* head = Sprite::create(resource);
//    if(!head)
//    {
//        return NULL;
//    }
//    headBg->addChild(head);
//    head->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
//    
//    
//    char stt[100]="";
//    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
//    
//    Sprite* headForm = Sprite::create(stt);
//    float sx = (headForm->getContentSize().width - 10) / head->getContentSize().width;
//    head->setScale(sx);
//    headBg->addChild(headForm);
//    headForm->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
//    headBg->setScale(.8);
//    headBg->setContentSize(headBg->getContentSize() * .5);
//    return headBg;
//}
void SweepCheckLayer::onItemClick(Node* node)
{
    DictStageBattleReward* data = rewardList->at(node->getTag());
    int itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
    TipsLayer::show(data->itemType, itemID, 0);
}



void SweepCheckLayer::addEventListener()
{
    addUserMsg(CUSTOM_UPDATE_USER_RAIDSCARD, CC_CALLBACK_1(SweepCheckLayer::setRaidsCard, this));
}
void SweepCheckLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}



