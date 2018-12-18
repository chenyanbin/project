//
//  UserWealthLayer.cpp
//  SuiTang
//
//  Created by mac on 14-6-27.
//
//

#include "UserWealthLayer.h"
#include "../../common/ImagePath.h"
#include "../../common/PublicShowUI.h"
#include "../../commonData/GlobalInfo.h"
#include "../../common/GameConfig.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/TouchSprite/Button.h"
#include "../vip/VipLayer.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../market/MarketLayer.h"
#include "../dart/DartLayer.hpp"
#include "../buyPower/BuyPowerLayer.hpp"
#include "../firstRecharge/FirstRechargeLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
UserWealthLayer::UserWealthLayer()
:TAG_BODY_STRENGTH(1)
,TAG_COIN(2)
,TAG_GOLD(3)
,TAG_POWER(4)
,TAG_TITLE_BG(6)
,TAG_TITLE(7)
,TAG_BG(8)
,TAG_MEDAL(9)
,TAG_PLUS(10)
,TAG_VALUELABEL(11)
{
    
}
UserWealthLayer::~UserWealthLayer()
{
//    log("~UserWealthLayer ~UserWealthLayer");
}
bool UserWealthLayer::init(ModeId mode)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->nowMode=mode;
        this->setWealth();
        bref = true;
    } while (false);
    return bref;
}
UserWealthLayer* UserWealthLayer::create(ModeId mode)
{
    UserWealthLayer* layer = new UserWealthLayer();
    if(layer && layer->init(mode))
    {
        layer->autorelease();
        return layer;
    }
    else{
        delete layer;
        layer = NULL;
        return NULL;
    }
}

void UserWealthLayer::setWealth()
{
    this->removeAllChildren();
    switch (this->nowMode) {
        case GENERAL:
            this->setHomeWealth();
            break;
        case MATRIX:
            this->setHomeWealth();
            break;
        case STAGE:
            this->setBelongWealth();
            break;
        case BELONG:
            this->setBelongWealth();
            break;
        case MARKET:
            this->setMarketFind();
            break;
        case FAMOUSE:
            this->setFamouseTitle();
            break;
  
        default:
            break;
    }
}

void UserWealthLayer::setHomeWealth()
{

//    Sprite* topBg = Sprite::create(IMG_PUBLIC_MODULE_MASK_TOP);
//    topBg->setAnchorPoint(Point::ZERO);
//    topBg->setPositionX(-287);
//    topBg->setPositionY(-25);
//    
//    this->addChild(topBg,0,TAG_BG);
    float offX = 5;
    //战力
    string num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->gameRole->combatPower);
  
    
    //体力
    string str1= PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPower);
    string str2="/"+PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPowerMax);
    Node* bodyStrength = bodyNode(IMG_ICON_PUBLIC_POWER,str1.c_str(),str2.c_str(),true);
    
    //铜币
    num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userCopper);
    Node* cooperNode = getNode(IMG_ICON_PUBLIC_COIN, num.c_str(),true);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumCoinsPlusRight, cooperNode->getChildByTag(TAG_PLUS));
    //元宝
    num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userGold);
    Node* goldNode = getNode(IMG_ICON_PUBLIC_GOLD,num.c_str(),true);
    

//    powerNode->setPositionX(0);
//    powerNode->setPositionY(0);
    bodyStrength->setPositionX(0 );
    cooperNode->setPositionX(bodyStrength->getPositionX() + bodyStrength->getContentSize().width + offX);
    goldNode->setPositionX(cooperNode->getPositionX() + cooperNode->getContentSize().width + offX);
    
    this->addChild(bodyStrength,1,TAG_BODY_STRENGTH);
    this->addChild(cooperNode,2,TAG_COIN);
    this->addChild(goldNode,3,TAG_GOLD);
//    this->addChild(powerNode, 4, TAG_POWER);
    Size size = goldNode->getContentSize();
    size.width = goldNode->getPositionX() + goldNode->getContentSize().width;
    this->setContentSize(size);
}

void UserWealthLayer::setBelongWealth()
{
    Button* powerNode=Button::create(IMG_PUBLIC_MODULE_MASK_TOP,IMG_PUBLIC_MODULE_MASK_TOP,NULL);
    powerNode->setAnchorPoint(Point::ZERO);
    this->addChild(powerNode,1,TAG_BG);
    
    Sprite* topTitleBg=Sprite::create(IMG_PUBLIC_TITLE_BG);
    topTitleBg->setAnchorPoint(Point::ZERO);
    topTitleBg->setPosition(0,powerNode->getContentSize().height-topTitleBg->getContentSize().height);
    topTitleBg->setTag(TAG_TITLE_BG);
    powerNode->addChild(topTitleBg,2);
    
   
    
//    //体力
    string str1= PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPower);
    string str2="/"+PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPowerMax);
    Node* bodyStrength = bodyNode(IMG_ICON_PUBLIC_POWER,str1.c_str(),str2.c_str(),true);
    //铜币
    
    string num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userCopper);
    Node* cooperNode = getNode2(IMG_ICON_PUBLIC_COIN, num.c_str(),true,false);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumCoinsPlusRight, cooperNode->getChildByTag(TAG_PLUS));
    //元宝
    num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userGold);;
    Node* goldNode = getNode2(IMG_ICON_PUBLIC_GOLD,num.c_str(),true,false);
    
    bodyStrength->setPosition(topTitleBg->getContentSize().width+topTitleBg->getPositionX()+20,(powerNode->getContentSize().height-bodyStrength->getContentSize().height)/2);
    cooperNode->setPosition(bodyStrength->getPositionX()+bodyStrength->getContentSize().width+30,bodyStrength->getPositionY());
    goldNode->setPosition(cooperNode->getPositionX() + cooperNode->getContentSize().width+30,bodyStrength->getPositionY());
    
    this->addChild(bodyStrength,2,TAG_BODY_STRENGTH);
    this->addChild(cooperNode,3,TAG_COIN);
    this->addChild(goldNode,4,TAG_GOLD);
    
    
    Sprite* bottomBg=Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    bottomBg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bottomBg);
    bottomBg->setPosition(0,powerNode->getContentSize().height-VisibleRect::bottom().y);
    this->addChild(bottomBg);
    
    this->setContentSize(powerNode->getContentSize());
}
void UserWealthLayer::setMarketFind()
{
    Sprite* powerNode=Sprite::create(IMG_PUBLIC_MODULE_MASK_TOP);
    powerNode->setAnchorPoint(Point::ZERO);
    this->addChild(powerNode,1,TAG_BG);
    
    Sprite* topTitleBg=Sprite::create(IMG_PUBLIC_TITLE_BG);
    topTitleBg->setAnchorPoint(Point::ZERO);
    topTitleBg->setPosition(0,powerNode->getContentSize().height-topTitleBg->getContentSize().height);
    topTitleBg->setTag(TAG_TITLE_BG);
    powerNode->addChild(topTitleBg);

    string num = PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userGold);
    Node* goldNode = getNode2(IMG_ICON_PUBLIC_GOLD,num.c_str(),true,false);
    goldNode->setPosition(topTitleBg->getContentSize().width+topTitleBg->getPositionX()+20,(powerNode->getContentSize().height-goldNode->getContentSize().height)/2+6);
    
    //军贡
    num= GlobalInfo::getInstance()->gameRole->expLoit;
    Node* cooperNode = getNode2(IMG_MARKET_MARKETFIND_MILITARYSLIDER, num.c_str(),true,false);
    cooperNode->setPosition(goldNode->getPositionX()+goldNode->getContentSize().width+30,goldNode->getPositionY());
    
    powerNode->addChild(goldNode,2,TAG_GOLD);
    powerNode->addChild(cooperNode,2,TAG_MEDAL);
    this->setContentSize(powerNode->getContentSize());

}

void UserWealthLayer::setFamouseTitle()
{
    Sprite* powerNode=Sprite::create(IMG_PUBLIC_MODULE_MASK_TOP);
    powerNode->setAnchorPoint(Point::ZERO);
    this->addChild(powerNode,1,TAG_BG);
    
    Sprite* topTitleBg=Sprite::create(IMG_PUBLIC_TITLE_BG);
    topTitleBg->setAnchorPoint(Point::ZERO);
    topTitleBg->setPosition(0,powerNode->getContentSize().height-topTitleBg->getContentSize().height);
    topTitleBg->setTag(TAG_TITLE_BG);
    powerNode->addChild(topTitleBg);
    
    
    
    
    this->setContentSize(powerNode->getContentSize());
}
/*
*1.图片路径
*2.第一个数字
*3.第二个数字
*4.是否要加号
*/
Sprite* UserWealthLayer::bodyNode(const char* iconPath,const char* labelStr,const char* labelStr2,bool isHaveBtn)
{
    Sprite* container = Sprite::create();
    container->setAnchorPoint(Point::ZERO);
    
    Sprite* bg = Sprite::create(IMG_USERHEAD_NUMBG);
    bg->setAnchorPoint(Point::ZERO);
    bg->setPosition(Point::ZERO);
    container->addChild(bg);
    Sprite* icon = Sprite::create(iconPath);
    icon->setAnchorPoint(Point::ZERO);
    if (isHaveBtn)
    {
        
        TouchSprite* plus=TouchSprite::createWithPic(IMG_PUBLIC_PLUS,this,callfuncN_selector(UserWealthLayer::onBodyClick));
        plus->setPosition(bg->getContentSize().width - plus->getContentSize().width/2 + 2, bg->getContentSize().height/2);
        bg->addChild(plus);
    }
    icon->setScale(0.7);
    icon->setContentSize(icon->getContentSize()*0.7);
    icon->setPositionX(5);
    icon->setPositionY((bg->getContentSize().height - icon->getContentSize().height)/2);
    bg->addChild(icon);
    Color3B bodyPowerRgb=PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW);
    if (GlobalInfo::getInstance()->bodyPower>=GlobalInfo::getInstance()->bodyPowerMax) {
        bodyPowerRgb=PublicShowUI::getColor3b(COLOR_DARK_GREEN);
    }
    Sprite* label=PublicShowUI::getAttribLabel(labelStr, labelStr2,bodyPowerRgb,PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),false,20,20,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(icon->getPositionX() + icon->getContentSize().width, (bg->getContentSize().height - label->getContentSize().height)/2);
    container->addChild(label);
    label->setTag(TAG_VALUELABEL);
    Size size = bg->getContentSize();
    container->setContentSize(size);
    
    return container;
}
Sprite* UserWealthLayer::getNode2(const char* iconPath,const char* labelStr,bool isHaveBtn,bool isPower)
{
    Sprite* container = Sprite::create(IMG_USERHEAD_NUMBG);
    container->setAnchorPoint(Point::ZERO);

    
    TouchSprite* plus=TouchSprite::createWithPic(IMG_PUBLIC_PLUS,this,callfuncN_selector(UserWealthLayer::onClick));
//    plus->setAnchorPoint(Point::ZERO);
    plus->setSwallowTouches(true);
    plus->setPosition(container->getContentSize().width - plus->getContentSize().width/2 + 2, container->getContentSize().height/2);
    container->addChild(plus,3,TAG_PLUS);
    
    Sprite* icon = Sprite::create(iconPath);
    icon->setAnchorPoint(Point::ZERO);
    if (isHaveBtn) {
        icon->setScale(0.7);
        icon->setContentSize(icon->getContentSize()*0.7);
    }
    
    icon->setPositionY((container->getContentSize().height - icon->getContentSize().height)/2);
    container->addChild(icon);
    Label* label = PublicShowUI::getLabel(labelStr,PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    if (isPower) {
        icon->setPositionX(-(icon->getContentSize().width+10));
        label->setPosition(icon->getPositionX() + icon->getContentSize().width*2 -10, (container->getContentSize().height - label->getContentSize().height)/2);
    }else
    {
        icon->setPositionX(-8);
        label->setPosition(icon->getPositionX() + icon->getContentSize().width + 1, (container->getContentSize().height - label->getContentSize().height)/2);
    }
    
    container->addChild(label,4,TAG_VALUELABEL);
    
    Size size = container->getContentSize();
    
    container->setContentSize(size);
    return container;
    
}

void UserWealthLayer::setTitle(const char* path)
{
    Sprite* spriteBg=(Sprite*)this->getChildByTag(TAG_BG);
    if(!spriteBg)
    {
        return;
    }
    Sprite* titleBg=(Sprite*)spriteBg->getChildByTag(TAG_TITLE_BG);
    titleBg->removeChildByTag(TAG_TITLE);
 
    Sprite* title=Sprite::create(path);
    title->setAnchorPoint(Point::ZERO);
    titleBg->addChild(title,1,TAG_TITLE);
    
    title->setPosition((titleBg->getContentSize().width-title->getContentSize().width)/2,(titleBg->getContentSize().height-title->getContentSize().height)/2);
    
}
/*
 *1.iconPath=资源
 *2.labelStr=数量
 *
 */
Sprite* UserWealthLayer::getNode(const char* iconPath,const char* labelStr,bool isHaveBtn)
{
    Sprite* container = Sprite::create(IMG_USERHEAD_NUMBG);
    container->setAnchorPoint(Point::ZERO);

    Sprite* icon = Sprite::create(iconPath);
    icon->setAnchorPoint(Point::ZERO);
    if (isHaveBtn)
    {
        
        TouchSprite* plus=TouchSprite::createWithPic(IMG_PUBLIC_PLUS,this,callfuncN_selector(UserWealthLayer::onClick));
        plus->setPosition(container->getContentSize().width - plus->getContentSize().width/2 + 2, container->getContentSize().height/2);
        container->addChild(plus,3,TAG_PLUS);

    }
    icon->setScale(0.7);
    icon->setContentSize(icon->getContentSize()*0.7);
    icon->setPositionX(5);
    icon->setPositionY((container->getContentSize().height - icon->getContentSize().height)/2);
    
    container->addChild(icon);

    Label* label = PublicShowUI::getLabelNumber(labelStr,PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(icon->getPositionX() + icon->getContentSize().width, (container->getContentSize().height - label->getContentSize().height)/2);
    
    container->addChild(label,4,TAG_VALUELABEL);

    return container;
    
}
void UserWealthLayer::onClick(Node* sper)
{
    int tag = sper->getParent()->getTag();
    if(tag == TAG_GOLD)
    {
//        VipLayer::show(SCENE_TAG_MAINUI);
//        DartLayer::show();
        if(GlobalInfo::getInstance()->firstRechargeStatus == 1 || GlobalInfo::getInstance()->firstRechargeStatus == 2)
        {
            FirstRechargeLayer::show(0);
        }else if (GlobalInfo::getInstance()->firstRechargeStatus == 3)
        {
            VipLayer::show(SCENE_TAG_MAINUI);
        }
        
    }
    else if(tag == TAG_COIN)
    {
        
        DartLayer::show();
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumCoinsPlusRight);
    }
    else if(tag == TAG_BODY_STRENGTH)
    {
        BuyPowerLayer::show();
//        MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_SHANGDIAN);
    }

}
void UserWealthLayer::onBodyClick(Node* pSender)
{
    BuyPowerLayer::show();
}
void UserWealthLayer::onUpdateAttrib(EventCustom* msg)
{
    //体力
    Node* body=(Node*)this->getChildByTag(TAG_BODY_STRENGTH);
    
    if (body) {
        string str1= PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPower);
        string str2="/"+PublicShowUI::numberToString(GlobalInfo::getInstance()->bodyPowerMax);
        Node* bodyStrength = bodyNode(IMG_ICON_PUBLIC_POWER,str1.c_str(),str2.c_str(),true);
        bodyStrength->setPosition(body->getPosition());
        bodyStrength->setTag(TAG_BODY_STRENGTH);
        this->removeChildByTag(TAG_BODY_STRENGTH);
        this->addChild(bodyStrength,2);
    }
    //铜币
    Node* coinNode=(Node*)this->getChildByTag(TAG_COIN);
    if (coinNode) {
        Label* label=(Label*)coinNode->getChildByTag(TAG_VALUELABEL);
        if (label) {
            string num =PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userCopper);
            label->setString(num.c_str());
        }
    }
    //元宝
    Node* goldNode=(Node*)this->getChildByTag(TAG_GOLD);
    if (goldNode) {
        Label* label=(Label*)goldNode->getChildByTag(TAG_VALUELABEL);
        if (label) {
            string num =PublicShowUI::getUpperlimit(GlobalInfo::getInstance()->userGold);
            label->setString(num.c_str());
        }
    }
    //战力
    Node* powerNode=(Node*)this->getChildByTag(TAG_POWER);
    if (powerNode) {
        Label* label=(Label*)powerNode->getChildByTag(TAG_VALUELABEL);
        if (label) {
            string num = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->combatPower);
            label->setString(num.c_str());
        }
    }
    //军贡
    Node* medalNode=(Node*)this->getChildByTag(TAG_MEDAL);
    if (medalNode) {
        Label* label=(Label*)medalNode->getChildByTag(TAG_VALUELABEL);
        if (label) {
            string num = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->combatPower);
            label->setString(num.c_str());
        }
    }

}
void UserWealthLayer::onCommonEffect(float percent)
{
    if(percent < 1)
    {
        return;
    }
    Node* parent = this->getChildByTag(TAG_BG);
    parent = parent ? parent : this;
    
    //元宝
    Node* goldNode=(Node*)parent->getChildByTag(TAG_GOLD);
    goldNode = goldNode ? goldNode : this->getChildByTag(TAG_GOLD);
    if (goldNode)
    {
        CommonEffect* commonEffect = CommonEffect::create("yuanbao",true,false);
        commonEffect->setAnchorPoint(Point::ZERO);
        commonEffect->setPosition(0,0);
        goldNode->addChild(commonEffect,2);
    }
    
    
}
void UserWealthLayer::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    removeUserEventListener();
    CommonEffect::pureCache("yuanbao");
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumCoinsPlusRight);
    
}
void UserWealthLayer::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    addUserEventListener();
//    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, "yuanbao");
//    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
//    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(UserWealthLayer::onCommonEffect));
    
}
void UserWealthLayer::addUserEventListener()
{
   _eventDispatcher->addCustomEventListener(CUSTOM_UPDATE_USERPROP_VALUE, CC_CALLBACK_1(UserWealthLayer::onUpdateAttrib, this));
}
void UserWealthLayer::removeUserEventListener()
{
 _eventDispatcher->removeCustomEventListeners(CUSTOM_UPDATE_USERPROP_VALUE);
}
