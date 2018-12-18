//
//  GeneralsExperience_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/7/31.
//
//

#include "GeneralsExperience_Layer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/experience/ExperienceMsg.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../data/CardDataManager.h"
#include "../../../commonData/dictData/DictHeroLevel/DictHeroLevelManager.h"
#include "../../../message/Decoding/generals/experience/ExperienceDetermineMsg.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../commonData/dictData/DictHeroLevel/DictHeroLevelManager.h"
#include "../../../message/Decoding/generals/experience/ChooseCardMsg.h"

GeneralsExperience_Layer::GeneralsExperience_Layer()
:cardId(1)
,heroDictId(0)//当前武将ID
,heroLeve(0)//当前武将等级；
,heroPrestige(0)//当前武将声望
,nextLevel(0)//升级后等级
,prestigeAdd(0)//声望提升
,cost(0)//花费铜钱或元宝
,TAG_UPLEVEL(11)//升级后TAG
,TAG_ADDPRESTIGE(12)//加声望
,TAG_CONSUME(13)//需要铜钱
,TAG_CURRENTLV(14)//当前经验
,cardLeve(0)
{
    cardList=new vector<CardPropertyData*>() ;
}
GeneralsExperience_Layer::~GeneralsExperience_Layer()
{
    cardList->clear();
    CC_SAFE_DELETE(cardList);
}
void GeneralsExperience_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsExperience_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsExperience_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralsExperience_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    this->requestListMsg();
}
bool GeneralsExperience_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        this->setBackground(IMG_GENERALS_EXPERIENCE_LIST_BG);
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
void GeneralsExperience_Layer::createLayer()
{
        
}
void GeneralsExperience_Layer::updataCardLocation(CardPropertyData* data)
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    
    Sprite* _card=(Sprite*)bgSprite->getChildByTag(10000+data->cardOldLocation);
    if (_card) {
        bgSprite->removeChildByTag(10000+data->cardOldLocation);
    }
    
    if (data->cardLocation!=0) {
        Sprite* _card=(Sprite*)bgSprite->getChildByTag(data->cardLocation);
        int tempNum=data->heroDictId;
        DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
        if (!dictHero) {
            return;
        }
        UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->quality);
        userHead->setHeadInfo(data->level, data->prestige);
        userHead->setPosition(_card->getPositionX()-_card->getContentSize().width/2+5,_card->getPositionY()-_card->getContentSize().height/2+5);
        bgSprite->addChild(userHead,2,10000+data->cardLocation);
    }
    this->updataData();
}
void GeneralsExperience_Layer::headAction()
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    for (int i=0; i<7; i++) {
        UserHeadLayer* userHead=(UserHeadLayer*)bgSprite->getChildByTag(10000+i);
        if (userHead) {
            ccBezierConfig bezierCon;
            bezierCon.controlPoint_1=Point(-100, 400);//控制点1
            bezierCon.controlPoint_2=Point(-100, 400);//控制点2
            bezierCon.endPosition =Point(-200, 300);// 结束位置
            ActionInterval * action = BezierTo::create(0.8, bezierCon);
            Spawn* twoAction=Spawn::createWithTwoActions(action, ScaleTo::create(0.8, 0));
            userHead->runAction(CCSequence::create(twoAction,DelayTime::create(0.05),CallFuncN::create(CC_CALLBACK_1(GeneralsExperience_Layer::deleteAction, this)), NULL));
            userHead->setCascadeOpacityEnabled(true);
            userHead->setOpacity(125);
//            userHead->runAction(action);
        }
    }
}
void GeneralsExperience_Layer::deleteAction(Node* pSprite)
{
    
    pSprite->setVisible(false);
}
void GeneralsExperience_Layer::updataData()
{
    Sprite* bgSprite=(Sprite*) this->getChildByTag(TAG_BG);
    
    //等级
    int level=CardDataManager::getInstance()->getPresentData()->level;
    int exper=CardDataManager::getInstance()->getPresentData()->heroExperience;
    
    Label* currLabel=(Label*)bgSprite->getChildByTag(TAG_CURRENTLV);
    if (currLabel) {
        currLabel->setString("LV. "+PublicShowUI::numberToString(level));
    }
    int upgradeLevel=0;
    int totalExper=0;

    int sizeList=(int)CardDataManager::getInstance()->getDataList()->size();
    for (int i=0; i<sizeList; i++) {
        totalExper+=CardDataManager::getInstance()->getCardDataByIndex(i)->cardGetExperience;
    }
    
    Vector<DictHeroLevel*>* dictHroLevel=DictHeroLevelManager::getInstance()->getDataList();
    //品质等级表
    Vector<DictHeroQuality*>* dictHeroQuality=  DictHeroQualityManager::getInstance()->getDataList();
    //当前历练的品质
    int tempQuality=CardDataManager::getInstance()->getPresentData()->quality;
    int MaxLeve=0;
    for(DictHeroQuality* monster :* dictHeroQuality)
    {
        if (monster->level==tempQuality) {
            MaxLeve=monster->levelUpLimit;
            break;
        }
    }
    int sizeLeve=(int)dictHroLevel->size();
    for (int i=0; i<sizeLeve; i++) {
        if (dictHroLevel->at(i)->heroLevel==level) {
            if (dictHroLevel->at(i)->heroLevelUpExp<totalExper) {
                upgradeLevel+=1;
                level+=1;
                if (level>MaxLeve) {
                    level=MaxLeve;
                }
                totalExper-=exper;
                exper=dictHroLevel->at(i)->heroLevelUpExp;
                i=0;
            }
        }
    }
    
    Label* expUpLabel=(Label*)bgSprite->getChildByTag(TAG_UPLEVEL);
    expUpLabel->setString("LV. "+PublicShowUI::numberToString(level));
    //声望
    int prestige=0;
    for (int i=0; i<sizeList; i++) {
        if (CardDataManager::getInstance()->getPresentData()->heroDictId==CardDataManager::getInstance()->getCardDataByIndex(i)->heroDictId) {
            prestige+=CardDataManager::getInstance()->getCardDataByIndex(i)->prestige;
        }
    }
    
    Label* prestigeLabel=(Label*)bgSprite->getChildByTag(TAG_ADDPRESTIGE);
    prestigeLabel->setString("+ "+PublicShowUI::numberToString(prestige));
    
    //花费
    
    int consume=0;
    for (int i=0; i<sizeList; i++) {
        consume+=CardDataManager::getInstance()->getCardDataByIndex(i)->cardConsumeCoin;
    }
    Node* consumeNode=(Node*)bgSprite->getChildByTag(TAG_CONSUME);
    if (consumeNode) {
        bgSprite->removeChildByTag(TAG_CONSUME);
    }
    string consumeStr=PublicShowUI::numberToString(consume);
    Node* cooperNode = getNode(IMG_ICON_PUBLIC_COIN, consumeStr.c_str(),true,false);
    cooperNode->setAnchorPoint(Point::ZERO);
    cooperNode->setPosition(32,15);
    bgSprite->addChild(cooperNode,1,TAG_CONSUME);
    CC_SAFE_DELETE(dictHroLevel);
    dictHroLevel = NULL;
    CC_SAFE_DELETE(dictHeroQuality);
    dictHeroQuality = NULL;
}
Sprite* GeneralsExperience_Layer::getNode(const char* iconPath,const char* labelStr,bool isHaveBtn,bool isPower)
{
    Sprite* container = Sprite::create();
    container->setAnchorPoint(Point::ZERO);
    
    Sprite* icon = Sprite::create(iconPath);
    icon->setAnchorPoint(Point::ZERO);
    if (isHaveBtn) {
        icon->setScale(0.7);
        icon->setContentSize(icon->getContentSize()*0.7);
    }
    
    container->addChild(icon);
    Label* label = PublicShowUI::getLabel(labelStr,PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),14,false,false);
    label->setAnchorPoint(Point::ZERO);
    if (isPower) {
        icon->setPositionX(-(icon->getContentSize().width+10));
        label->setPosition(icon->getPositionX() + icon->getContentSize().width*2 -10, (icon->getContentSize().height - label->getContentSize().height)/2);
    }else
    {
        icon->setPositionX(-8);
        label->setPosition(icon->getPositionX() + icon->getContentSize().width + 1, (icon->getContentSize().height - label->getContentSize().height)/2);
    }
    
    container->addChild(label);
    label->setTag(1);
    
    Size size = Size(Point::ZERO);
    size.width=icon->getPositionX()+label->getContentSize().width+label->getPositionX();
    size.height=icon->getContentSize().height;
    
    container->setContentSize(size);
    return container;
    
}
void GeneralsExperience_Layer::onBtnClick(Ref* pSender)
{
//    this->headAction();
    ExperienceDetermineMsg* msg = new ExperienceDetermineMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsExperience_Layer::onButtonClick(Node* pSender)
{
    UserHeadLayer* card=(UserHeadLayer*)pSender;
    
//    this->broadMsg(CUSTOM_CHOOSE_CARD_OVER_FUN);
    
    log("dddddddddddddddxxxxxxxxxxxxxxxxxxx%f",card->cardId);
}

void GeneralsExperience_Layer::requestListMsg()
{
    ChooseCardMsg* msg = new ChooseCardMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsExperience_Layer::onMsgProcess(EventCustom* msg)
{
    cardList->clear();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_HERO_HeroMaterialSelPageResp)
    {
        if (message->state==false) {
            return;
        }
        for (int i=0; i<6; i++) {
            CardPropertyData* cardData=new CardPropertyData();
            CardDataManager::getInstance()->addData(cardData);
        }
        CardPropertyData* prestionCardData=new CardPropertyData();
        prestionCardData->heroExperience=message->byteStream->getInt();
        prestionCardData->level=cardLeve=message->byteStream->getShort();
        prestionCardData->heroDictId=message->byteStream->getInt();
        prestionCardData->quality=message->byteStream->getByte();
        
        //-------------------赋值------------------------------//
        
        //        prestionCardData->level=cardLeve;
        //        CardDataManager::getInstance()->setPresentData(prestionCardData);
        //-------------------赋值结束----------------------------//
        
        int sizeInt=message->byteStream->getShort();
        for (int i=0; i<sizeInt; i++) {
            CardPropertyData* cardData=new CardPropertyData();
            //            cardData->autorelease();
            cardData->heroId=message->byteStream->getInt();
            cardData->heroDictId=message->byteStream->getInt();
            cardData->level=message->byteStream->getShort();
            cardData->prestige=message->byteStream->getShort();
            cardData->quality=message->byteStream->getByte();
            
            DictHero* dictHero = DictHeroManager::getInstance()->getData(cardData->heroDictId);
            cardData->cardGetExpValue=dictHero->initialStar/100;
            cardData->cardGetExperience=this->setCardInfoData("quality",cardData->quality);
            cardData->cardConsumeCoin=this->setCardInfoData("consumeCoin",cardData->quality);
            cardList->push_back(cardData);
        }
    }
    
}

int GeneralsExperience_Layer::setCardInfoData(string valueStr , int value)
{
    
    int valueNum=0;
    Vector<DictHeroPrestigeUpCost*>* list = DictHeroPrestigeUpCostManager::getInstance()->getDataList();
    for (DictHeroPrestigeUpCost* stage : *list) {
        if (stage->level==cardLeve and stage->quality==value) {
            if (valueStr=="quality") {
                valueNum=stage->rewardExp;
            }else if (valueStr=="consumeCoin")
            {
                valueNum=stage->consumeCoin;
            }
            break;
        }
        
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return valueNum;
}


void GeneralsExperience_Layer::onChooseCard(EventCustom* msg)
{
//    Sprite* chooseCard=(Sprite*)this->getChildByTag(TAG_CHOOSECARD);
//    if (!chooseCard) {
//        Sprite* cardBg=(Sprite*)this->getChildByTag(TAG_CARDBG);
//        cardBg->setVisible(false);
//        ChooseCard_layer* layer=ChooseCard_layer::create();
//        layer->setPosition(cardBg->getPosition());
//        this->addChild(layer,2,TAG_CHOOSECARD);
//    }
}
void GeneralsExperience_Layer::onAddCardFun(EventCustom* msg)
{
    CardPropertyData* cardData=(CardPropertyData*)msg->getUserData();
    this->updataCardLocation(cardData);
}
void GeneralsExperience_Layer::addEventListener()
{
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroStartPlacesResp).c_str(), CC_CALLBACK_1(GeneralsExperience_Layer::onMsgProcess, this));
    
    addUserMsg(CUSTOM_ADD_CARD_FUN,CC_CALLBACK_1(GeneralsExperience_Layer::onAddCardFun, this));
    addUserMsg(CUSTOM_REMOVE_CARD_FUN,CC_CALLBACK_1(GeneralsExperience_Layer::onAddCardFun, this));
}
void GeneralsExperience_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

