//
//  GeneralsProperty_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/3.
//
//

#include "GeneralsProperty_Layer.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/generals/property/PropertyMsg.h"
#include "../data/CardDataManager.h"
#include "../../../protocol/UserCustomEvent.h"
GeneralsProperty_Layer::GeneralsProperty_Layer()
:sx(1)
,propertyData(NULL)
{
    
}
GeneralsProperty_Layer::~GeneralsProperty_Layer()
{
    
}
void GeneralsProperty_Layer::onExit()
{
    BaseLayer::onExit();
}
void GeneralsProperty_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void GeneralsProperty_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void GeneralsProperty_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool GeneralsProperty_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_BG);
//        this->createLayer();
        propertyData=new CardPropertyData();
        bref = true;
    } while (false);
    return bref;
}
void GeneralsProperty_Layer::createLayer()
{
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
//    Sprite* bgbox=Sprite::create(IMG_GENERALS_BASE_BGBOX);
//    bgbox->setAnchorPoint(Point::ZERO);
//    bgbox->setPosition(Point::ZERO);
//    bgSprite->addChild(bgbox);
//    Sprite* bg2=Sprite::create(IMG_GENERALS_BASE_BG2);
//    bg2->setAnchorPoint(Point::ZERO);
//    bgSprite->addChild(bg2);
    bgSprite->removeAllChildren();
    int interval=28;//每个字体间隔距离
    //--------------------------------基础属性--------------------------------//
    Sprite* titleBaseBg=Sprite::create(IMG_GENERALS_PROPERTY_TITLE_BG);
    titleBaseBg->setAnchorPoint(Point::ZERO);
    titleBaseBg->setPosition(13,450);
    bgSprite->addChild(titleBaseBg);
    
    Sprite* baseLabel=Sprite::create(IMG_GENERALS_PROPERTY_BASE_LABEL);
    baseLabel->setAnchorPoint(Point::ZERO);
    baseLabel->setPosition(13,450);
    bgSprite->addChild(baseLabel);
    
    //生命
//    float floatValue;
    int value=propertyData->hp;
    
    string nameStr="生命     "+PublicShowUI::numberToString(value);
    Label* lifeLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    lifeLabel->setAnchorPoint(Point::ZERO);
    lifeLabel->setPosition(30,430);
    bgSprite->addChild(lifeLabel);
    //攻击
    value=propertyData->attack;
    nameStr="攻击     "+PublicShowUI::numberToString(value);
    Label* attackLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    attackLabel->setAnchorPoint(Point::ZERO);
    attackLabel->setPosition(lifeLabel->getPositionX(),lifeLabel->getPositionY()-interval);
    bgSprite->addChild(attackLabel);
    //防御
    value=propertyData->defend;
    nameStr="防御     "+PublicShowUI::numberToString(value);
    Label* defLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    defLabel->setAnchorPoint(Point::ZERO);
    defLabel->setPosition(attackLabel->getPositionX(),attackLabel->getPositionY()-interval);
    bgSprite->addChild(defLabel);
    //分割线
    Sprite* lineSprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    lineSprite->setAnchorPoint(Point::ZERO);
    lineSprite->setPosition((bgSprite->getContentSize().width/sx-lineSprite->getContentSize().width)/2, 370);
    bgSprite->addChild(lineSprite);
    //--------------------------------概率属性--------------------------------//
    Sprite* titleProbBg=Sprite::create(IMG_GENERALS_PROPERTY_TITLE_BG);
    titleProbBg->setAnchorPoint(Point::ZERO);
    titleProbBg->setPosition(13,320);
    bgSprite->addChild(titleProbBg);
    
    Sprite* probLabel=Sprite::create(IMG_GENERALS_PROPERTY_PROB_LABEL);
    probLabel->setAnchorPoint(Point::ZERO);
    probLabel->setPosition(13,320);
    bgSprite->addChild(probLabel);
    //暴击
    value=propertyData->crit;
    float divideNum=100;
    float floatValue=value/divideNum;
    nameStr="暴击   "+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* baojiLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    baojiLabel->setAnchorPoint(Point::ZERO);
    baojiLabel->setPosition(30,300);
    bgSprite->addChild(baojiLabel);
    //抗暴
    value=propertyData->tenaci;
    floatValue=value/divideNum;
    nameStr="韧性   "+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* kangbaoLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    kangbaoLabel->setAnchorPoint(Point::ZERO);
    kangbaoLabel->setPosition(baojiLabel->getPositionX()+150,baojiLabel->getPositionY());
    bgSprite->addChild(kangbaoLabel);
    //命中
    value=propertyData->hit;
    floatValue=value/divideNum;
    nameStr="精准   "+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* mingzhongLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    mingzhongLabel->setAnchorPoint(Point::ZERO);
    mingzhongLabel->setPosition(baojiLabel->getPositionX(),baojiLabel->getPositionY()-interval);
    bgSprite->addChild(mingzhongLabel);
    
    //格挡
    value=propertyData->block;
    floatValue=value/divideNum;
    nameStr="格挡   "+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* gedangLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    gedangLabel->setAnchorPoint(Point::ZERO);
    gedangLabel->setPosition(mingzhongLabel->getPositionX()+150,mingzhongLabel->getPositionY());
    bgSprite->addChild(gedangLabel);
    
    //分割线
    Sprite* line2Sprite=Sprite::create(IMG_GENERALS_SKILL_CONT_LINE);
    line2Sprite->setAnchorPoint(Point::ZERO);
    line2Sprite->setPosition((bgSprite->getContentSize().width/sx-line2Sprite->getContentSize().width)/2, 250);
    bgSprite->addChild(line2Sprite);
    
    //--------------------------------抗性属性--------------------------------//
    Sprite* titleResBg=Sprite::create(IMG_GENERALS_PROPERTY_TITLE_BG);
    titleResBg->setAnchorPoint(Point::ZERO);
    titleResBg->setPosition(13,200);
    bgSprite->addChild(titleResBg);
    
    Sprite* resLabel=Sprite::create(IMG_GENERALS_PROPERTY_RES_LABEL);
    resLabel->setAnchorPoint(Point::ZERO);
    resLabel->setPosition(13,200);
    bgSprite->addChild(resLabel);
    
    //攻击强度
    value=propertyData->attackStrengh;
    floatValue=value/divideNum;
    nameStr="伤害加成率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* gongjiLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    gongjiLabel->setAnchorPoint(Point::ZERO);
    gongjiLabel->setPosition(30,174);
    bgSprite->addChild(gongjiLabel);
    //火焰抗性
    value=propertyData->fireResist;
    floatValue=value/divideNum;
    nameStr="火焰抗性率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* fireLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    fireLabel->setAnchorPoint(Point::ZERO);
    fireLabel->setPosition(gongjiLabel->getPositionX(),gongjiLabel->getPositionY()-interval);
    bgSprite->addChild(fireLabel);
    //冰冻抗性
    value=propertyData->iceResist;
    floatValue=value/divideNum;
    nameStr="冰霜抗性率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* iceLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    iceLabel->setAnchorPoint(Point::ZERO);
    iceLabel->setPosition(fireLabel->getPositionX(),fireLabel->getPositionY()-interval);
    bgSprite->addChild(iceLabel);
    //雷暴抗性
    value=propertyData->boltResist;
    floatValue=value/divideNum;
    nameStr="雷电抗性率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* thunderLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    thunderLabel->setAnchorPoint(Point::ZERO);
    thunderLabel->setPosition(iceLabel->getPositionX(),iceLabel->getPositionY()-interval);
    bgSprite->addChild(thunderLabel);
    //烈风抗性
    value=propertyData->windResist;
    floatValue=value/divideNum;
    nameStr="飓风抗性率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* windLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    windLabel->setAnchorPoint(Point::ZERO);
    windLabel->setPosition(thunderLabel->getPositionX(),thunderLabel->getPositionY()-interval);
    bgSprite->addChild(windLabel);
    //巫毒抗性
    value=propertyData->poisonResist;
    floatValue=value/divideNum;
    nameStr="巫毒抗性率     +"+PublicShowUI::numberToTwoDecimalPlaces(floatValue)+"%";
    Label* venomLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    venomLabel->setAnchorPoint(Point::ZERO);
    venomLabel->setPosition(windLabel->getPositionX(),windLabel->getPositionY()-interval);
    bgSprite->addChild(venomLabel);
    
//    Sprite::create(IMG_GENERALS_PROPERTY_TITLE_BG);
    
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void GeneralsProperty_Layer::requestListMsg()
{
    PropertyMsg* msg = new PropertyMsg(CardDataManager::getInstance()->getPresentData()->heroId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void GeneralsProperty_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroPropertyPageResp)
    {
        
        propertyData->heroId=message->byteStream->getInt();
        propertyData->level=message->byteStream->getInt();
        propertyData->levelMax=message->byteStream->getInt();
        propertyData->prestige=message->byteStream->getInt();
        propertyData->leadership=message->byteStream->getInt();
        propertyData->combatPower=message->byteStream->getInt();
        propertyData->hp=message->byteStream->getInt();
        propertyData->attack=message->byteStream->getInt();
        propertyData->defend=message->byteStream->getInt();
        propertyData->crit=message->byteStream->getInt();
        propertyData->tenaci=message->byteStream->getInt();
        propertyData->hit=message->byteStream->getInt();
        propertyData->block=message->byteStream->getInt();
        propertyData->attackStrengh=message->byteStream->getInt();
        propertyData->fireResist=message->byteStream->getInt();
        propertyData->iceResist=message->byteStream->getInt();
        propertyData->boltResist=message->byteStream->getInt();
        propertyData->windResist=message->byteStream->getInt();
        propertyData->poisonResist=message->byteStream->getInt();
        
    }
    this->createLayer();
}
void GeneralsProperty_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroPropertyPageResp).c_str(), CC_CALLBACK_1(GeneralsProperty_Layer::onMsgProcess, this));
    this->addUserMsg(CUSTOM_UPDATE_HEROBASEPAGEMSG, CC_CALLBACK_0(GeneralsProperty_Layer::requestListMsg, this));
}
void GeneralsProperty_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
