//
//  BattleInfo.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/22.
//
//

#include "BattleInfo.hpp"
#include "../../commonData/dictData/DictStageBattleMonster/DictStageBattleMonsterManager.h"
#include "../../commonData/dictData/DictStage/DictStageManager.h"
#include "../../commonData/dictData/DictMonster/DictMonsterManager.h"
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../tips/TipsLayer.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/stage/RequestSweepMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../battle/BattleLoader.h"
#include "../../protocol/UserCustomEvent.h"
#include "../battleTest/PlayerDataManager.hpp"
#include "../../common/commonEffect/CommonEffect.h"
BattleInfo::BattleInfo()
:m_battleDataList(NULL)
,m_stageID(0)
,selectedNode(NULL)
,m_nowSelectedIndex(0)
,TAG_CONDITION(20)//从20开始，不能小于20
,TAG_DESCRIPT(21)
,TAG_NAME(22)
,TAG_PRIZE(23)
,TAG_TARGETTEAM(24)
,TAG_FIGHTBTN(25)
,TAG_TENBTN(26)
,TAG_ONEBTN(27)
,TAG_POWER(28)
,TAG_RAIDS(29)
,rewardList(NULL)
{
    rewardList = DictStageBattleRewardManager::getInstance()->getDataList();
}
BattleInfo::~BattleInfo()
{
    m_battleDataList = NULL;
    CC_SAFE_DELETE(rewardList);
    rewardList = NULL;
}
bool BattleInfo::init(int stageID,Vector<BattleData*>* battleDataList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        this->isAbleGuiding = false;
        this->m_battleDataList = battleDataList;
        m_stageID = stageID;
      
        this->setBackground(IMG_STAGEBATTLEINFO_BG,Point::ZERO,false);
        this->setClickEnabled(true);
        setButton();
        setRaidsCard();
        setStageName();
        setStageBattleButton();
    
        bref = true;
    } while (false);
    return bref;

}
BattleInfo* BattleInfo::create(int stageID,Vector<BattleData*>* battleDataList)
{
    BattleInfo* layer = new BattleInfo();
    if(layer && layer->init(stageID, battleDataList))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void BattleInfo::setStageBattleButton()
{
    ssize_t len = this->m_battleDataList->size();
    BattleData* battleData = NULL;
    int startX = 40;
    int startY = 65;
    int nowIndex = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        battleData = m_battleDataList->at(i);
        Node* node = getBattleBtn(battleData);
        node->setPositionX(startX + (i % 2) * 150);
        node->setPositionY(startY + (len - 1 - i) * (node->getContentSize().height + 15));
        this->addChild(node,3,i);
        
        if(GlobalInfo::getInstance()->selectedStageBattle == battleData->battleId)
        {
            m_nowSelectedIndex = i;
        }
        else if(battleData->state == 2 && nowIndex  <= 0)
        {
            m_nowSelectedIndex = i;
        }
        
    }
   
    battleData = NULL;
}
Node* BattleInfo::getBattleBtn(BattleData* battleData)
{
    Sprite* node = Sprite::create();
    node->setAnchorPoint(Point::ZERO);
  
    m_stageBattleID = battleData->battleId;
    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    
    //背景图
    const char* path = PublicShowUI::getResImgPath(IMG_BATTLEINFO_SMALLMAP, dictStage->cardResource.c_str());

    Button* btn = Button::create(path, "", CC_CALLBACK_1(BattleInfo::onItemClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setEnabled(battleData->state != 3);
    node->addChild(btn,0,battleData->battleId);
    
    Sprite* starbg = NULL;
    Sprite* starSpr = NULL;
    for (int i = 0; i < 3; i++)
    {
        starbg = Sprite::create(IMG_BATTLERESULT_STARBG);
        starbg->setAnchorPoint(Point::ZERO);
        starbg->setScale(0.3);
        starbg->setPosition(i*(starbg->getContentSize().width-70),btn->getContentSize().height + 4);
        node->addChild(starbg,2);
        
        if(i < battleData->starCount)
        {
            starSpr = Sprite::create(IMG_BATTLERESULT_STAR);
            starSpr->setAnchorPoint(Point::ZERO);
            starSpr->setScale(0.3);
            starSpr->setPosition(starbg->getPosition());
            node->addChild(starSpr,3);
        }
        
    }
   
    Size size = btn->getContentSize();
    size.height = starbg->getPositionY() + starbg->getContentSize().height * .3;
    node->setContentSize(size);
    
    
    return node;
}
void BattleInfo::setStageName()
{
    DictStage* dictData = DictStageManager::getInstance()->getData(m_stageID);
    Label* label = PublicShowUI::getLabel(dictData->name.c_str(),Color3B::WHITE,24,false,false);
    label->setAnchorPoint(Point(0,0));
    this->addChild(label,10);
    label->setPosition(30,this->getContentSize().height - label->getContentSize().height - 27);
}
void BattleInfo::onItemClick(Ref* pSender)
{
    
    Button* btn = (Button*)pSender;
    
    Node* parent = btn->getParent();
    int index = parent->getTag();
    Sprite* node = this->getSelectedNode(index == 1);
    m_stageBattleID = btn->getTag();
    if(!node->getParent())
    {
        this->addChild(node,100);
    }
//    node->setPosition(parent->getPositionX() - 30, parent->getPositionY() - 40);
    node->setPosition(parent->getPositionX()-30 , parent->getPositionY()-40 );
    
    setStartCondition();
    setDescript();
    setBattleName();
    setTargetTeam();
    setPrize();
    setCost();
    
    m_nowSelectedIndex = index;
    BattleData* battleData = m_battleDataList->at(index);
    
    Button* tenBtn = (Button*)this->getChildByTag(TAG_TENBTN);
    Button* oneBtn = (Button*)this->getChildByTag(TAG_ONEBTN);
    Button* fightBtn = (Button*)this->getChildByTag(TAG_FIGHTBTN);
    fightBtn->setEnabled(battleData->state != 3);
    tenBtn->setEnabled(battleData->starCount >= 3 && battleData->usableCount);
    oneBtn->setEnabled(battleData->starCount >= 3 && battleData->usableCount);
}
void BattleInfo::setCost()//设置消耗
{
    DictStageBattle* dictStageBattle = DictStageBattleManager::getInstance()->getData(this->m_stageBattleID);
    //消耗体力
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStageBattle->costPowerElite : dictStageBattle->costPower;
    string powStr= PublicShowUI::numberToString(costPower);//消耗体力
    Label* powLabel = (Label*)this->getChildByTag(TAG_POWER);
    if(powLabel)
    {
        powLabel->setString(powStr);
    }
    else
    {
        powLabel = PublicShowUI::getLabel(powStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
        powLabel->setAnchorPoint(Point::ZERO);
        powLabel->setPosition(130,15);
        this->addChild(powLabel,2,TAG_POWER);
    }
   
}
void BattleInfo::setRaidsCard(EventCustom* msg)//设置扫荡令
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
        label->setPosition(300, 15);
        this->addChild(label,3,TAG_RAIDS);
    }
    
    
}


void BattleInfo::setStartCondition()//设置通关条件
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
    Label* label = (Label*)this->getChildByTag(TAG_CONDITION);
    if(label)
    {
        label->setString(str);
    }
    else
    {
        label = PublicShowUI::getLabel(str.c_str(),Color3B::GREEN,16,false,false);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,10,TAG_CONDITION);
    }
    
    Node* bg = this->getChildByTag(TAG_BG);
    
    label->setPosition(bg->getContentSize().width/2 + 40 , bg->getContentSize().height - label->getContentSize().height - 20);

}
void BattleInfo::setDescript()
{
    Node* bg = this->getChildByTag(TAG_BG);
    DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    Label* label = (Label*)this->getChildByTag(TAG_DESCRIPT);
    if(label)
    {
        label->setString(stageBattle->desc);
    }
    else
    {
        label = PublicShowUI::getLabel(stageBattle->desc.c_str(),PublicShowUI::getColor3b(COLOR_BLUE_FLOUR),20,false,false);
        label->setAnchorPoint(Point(0,.5));
        this->addChild(label,10,TAG_DESCRIPT);
        label->setMaxLineWidth(bg->getContentSize().width/2);
    }
    
    
    label->setPosition(bg->getContentSize().width/2 - 40 , bg->getContentSize().height  - 110);
}
void BattleInfo::setBattleName()
{
    
    DictStageBattle* stageBattle = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    Label* label = (Label*)this->getChildByTag(TAG_NAME);
    if(label)
    {
        label->setString(stageBattle->name);
    }
    else
    {
        label = PublicShowUI::getLabel(stageBattle->name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),24,false,false);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,10,TAG_NAME);
    }
    Node* bg = this->getChildByTag(TAG_BG);
    
    label->setPosition(bg->getContentSize().width/2 - 30 , bg->getContentSize().height/2  + 80);
}
void BattleInfo::setTargetTeam()
{
    Node* node = this->getChildByTag(TAG_TARGETTEAM);
    if(node)
    {
        node->removeFromParent();
    }
    node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    Vector<DictStageBattleMonster*>* list = DictStageBattleMonsterManager::getInstance()->getDataList();
    UserHeadLayer* userHead = NULL;
    int index = 0;
    for(DictStageBattleMonster* monster : *list)
    {
        if(monster->stageBattleId != this->m_stageBattleID)
        {
            continue;
        }
        DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(monster->monsterId);
        userHead=UserHeadLayer::create(dictMonster->resource.c_str(),monster->monsterQuality,true);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setScale(.7);
        node->addChild(userHead);
        userHead->hideHeadInfo();
        userHead->setPosition(index * (userHead->getContentSize().width * .8), 0);

        index ++;
    }
     Node* bg = this->getChildByTag(TAG_BG);
    node->setPosition(bg->getContentSize().width/2 - 60,  bg->getContentSize().height/2 - userHead->getContentSize().height * .7 + 22);
    this->addChild(node,11,TAG_TARGETTEAM);
}
bool sortPrizeItem(DictStageBattleReward* a,DictStageBattleReward* b)
{
    return a->id > b->id;
}
void BattleInfo::setPrize()
{
    Node* container = this->getChildByTag(TAG_PRIZE);
    if(container)
    {
        container->removeFromParent();
    }
    container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    
    const char* path = NULL;
    UserHeadLayer* userHead = NULL;
    UserEquipLayer* head = NULL;
    int itemID = 0;
    sort(rewardList->begin(), rewardList->end(), sortPrizeItem);
    ssize_t len = rewardList->size();
    DictStageBattleReward* data = NULL;
    int itemType = 0;// GlobalInfo::getInstance()->stageMode == kStageModeCommon ?
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        data = rewardList->at(i);
        if(data->stageBattleId == m_stageBattleID)
        {
            itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
            itemType = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemType : data->itemTypeElite;
            path = PublicShowUI::getGoods(itemType, itemID);
            if(strcmp(path, "") == 0)
            {
                continue;
            }
            if(  data->itemType == DictItemTypeEnumItemHero)
            {
                
                userHead=UserHeadLayer::create(path,PublicShowUI::getQuality(itemType, itemID),false);
                userHead->setHeadInfo(1, 1);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.7);
                userHead->setPosition(index * (userHead->getContentSize().width * .8),0);
                userHead->setContentSize(userHead->getContentSize() * .7);
                container->addChild(userHead,5,i);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(BattleInfo::onIconClick));
                index++;
            }
            else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
            {
                head = UserEquipLayer::create(path,PublicShowUI::getQuality(itemType, itemID),false);
                head->setAnchorPoint(Point::ZERO);
                if (data->itemType == DictItemTypeEnumItemMater) {
                    head->setFragment();
                }else if (data->itemType == DictItemTypeEnumItemBook)
                {
                    head->setLetterFragment();
                }
                head->setScale(0.7);
               
                head->setPosition(index * (head->getContentSize().width * .8),0);
                head->setContentSize(head->getContentSize() * .7);
                container->addChild(head,5,i);
                head->addTouchBegainCallBack(this, callfuncN_selector(BattleInfo::onIconClick));
                index++;
            }
        }
    }
    if(userHead || head)
    {
        Node* bg = this->getChildByTag(TAG_BG);
        container->setPosition(bg->getContentSize().width/2 - 60, 75);
        this->addChild(container,14,TAG_PRIZE);
    
    }
}
void BattleInfo::onIconClick(Node* pSender)
{
    DictStageBattleReward* data = rewardList->at(pSender->getTag());
    int itemType = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemType : data->itemTypeElite;
    int itemID = GlobalInfo::getInstance()->stageMode == kStageModeCommon ? data->itemId : data->itemIdElite;
    TipsLayer::show(itemType, itemID, 0);
}
Sprite* BattleInfo::getSelectedNode(bool isFlipX)
{
    if(selectedNode && selectedNode->getParent())
    {
        selectedNode->removeFromParent();
        selectedNode = NULL;
    }

    //特效
    CommonEffect* commonEffect = CommonEffect::create("saodangkuang");
    commonEffect->setAnchorPoint(Point::ZERO);
    selectedNode = (Sprite*)commonEffect;
    
//    commonEffect->setPosition(layer->getContentSize().width/2 - commonEffect->getContentSize().width/2,layer->getContentSize().height/2-commonEffect->getContentSize().height/2);
//    layer->addChild(commonEffect,30);
    
//    Sprite* node = Sprite::create(IMG_STAGEBATTLEINFO_SELECTED);
//    node->setAnchorPoint(Point::ZERO);
//    node->setFlippedX(isFlipX);
//    Sprite* arrow = Sprite::create(IMG_PUBLIC_DOWNARROW);
//    arrow->setAnchorPoint(Point(.5,0));
//    arrow->setRotation( isFlipX ? -90 : 90);
//    arrow->setPosition(isFlipX ? -arrow->getContentSize().width : node->getContentSize().width, node->getContentSize().height/2);
//    MoveBy* moveBy = MoveBy::create(.5, Point(50,0));
//    Sequence* sequence = Sequence::create(moveBy,moveBy->reverse(), NULL);
//    arrow->runAction(RepeatForever::create(sequence));
//    
//    node->addChild(arrow);
//    selectedNode = node;
    
    
   
    return selectedNode;
}
void BattleInfo::setButton()
{
    Button* tenBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED, "", CC_CALLBACK_1(BattleInfo::onTenBtnClick, this));
    this->addChild(tenBtn,12,TAG_TENBTN);
    Sprite* title = Sprite::create(IMG_STAGEBATTLEINFO_TEN);
    tenBtn->addChild(title,10);
    tenBtn->setPosition(this->getContentSize().width/2 + 20, 40);
    tenBtn->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumClearing));

    
    
    Button* oneBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_RED, "", CC_CALLBACK_1(BattleInfo::onOneBtnClick, this));
    this->addChild(oneBtn,12,TAG_ONEBTN);
    title = Sprite::create(IMG_STAGEBATTLEINFO_ONE);
    oneBtn->addChild(title,10);
    oneBtn->setPosition(tenBtn->getPositionX() + tenBtn->getContentSize().width + 40, tenBtn->getPositionY());
    oneBtn->setVisible(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumClearing));
    Button* fightBtn = Button::create(IMG_STAGEBATTLEINFO_ENGERGAME, "", CC_CALLBACK_1(BattleInfo::onFightClick, this));
    fightBtn->setAnchorPoint(Point(.5,.5));
    this->addChild(fightBtn,12,TAG_FIGHTBTN);
   
    fightBtn->setPosition(oneBtn->getPositionX() + oneBtn->getContentSize().width + 40, oneBtn->getPositionY() + 20);
    
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAttack, fightBtn);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSpeedButton, oneBtn);
}
void BattleInfo::onTenBtnClick(Ref* pSender)
{
    
    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->costPowerElite : dictStage->costPower;
    
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    
    Dialog::showServerLoading();

    RequestSweepMsg* msg = new RequestSweepMsg(m_stageBattleID,10);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void BattleInfo::onOneBtnClick(Ref* pSender)
{
    
    if(GlobalInfo::getInstance()->isDebug)
    {
        PlayerDataManager::getInstance()->initData();
        return;
    }
    
    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->costPowerElite : dictStage->costPower;
    
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    
    Dialog::showServerLoading();
    
    RequestSweepMsg* msg = new RequestSweepMsg(m_stageBattleID,1);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSpeedButton);
}
void BattleInfo::onFightClick(Ref* pSender)
{

    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAttack);

    GlobalInfo::getInstance()->battleType = kBattleType_MingZhanYi;

    DictStageBattle* dictStage = DictStageBattleManager::getInstance()->getData(m_stageBattleID);
    int costPower = GlobalInfo::getInstance()->stageMode == kStageModeBest ? dictStage->costPowerElite : dictStage->costPower;
    
    if(GlobalInfo::getInstance()->bodyPower < costPower)
    {
        Dialog::showNoPowerDialog(SCENE_TAG_CHAPTER);
        return;
    }
    
    BattleData* battleData = m_battleDataList->at(m_nowSelectedIndex);
    GlobalInfo::getInstance()->isShowStoryTalk = battleData->starCount <= 0 && GlobalInfo::getInstance()->stageMode == kStageModeCommon;

    this->getParent()->removeFromParent();

    BattleLoader::requestStageBattle(battleData->battleId);
    
    
}
void BattleInfo::onEnter()
{
    BaseLayer::onEnter();
}
void BattleInfo::onExit()
{
    BaseLayer::onExit();
}

void BattleInfo::addEventListener()
{
    addUserMsg(CUSTOM_UPDATE_USER_RAIDSCARD, CC_CALLBACK_1(BattleInfo::setRaidsCard, this));
}
void BattleInfo::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void BattleInfo::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAttack);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSpeedButton);
}
void BattleInfo::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    BattleData* battleData = m_battleDataList->at(m_nowSelectedIndex);
    Node* node = this->getChildByTag(m_nowSelectedIndex);
    Node* btn = node->getChildByTag(battleData->battleId);
    onItemClick(btn);
    NewPlayerGuild::getInstance()->showNowGuide();
}