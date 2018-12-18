//
//  UserBigEquipLayer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/27.
//
//

#include "UserBigEquipLayer.h"
#include "UserEquipLayer.h"
#include "../../commonData/dictData/DictItemMater/DictItemMaterManager.h"
#include "../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../common/TouchSprite/Button.h"
UserBigEquipLayer::UserBigEquipLayer()
{
    materData=new MaterData();
}

UserBigEquipLayer::~UserBigEquipLayer()
{
    CC_SAFE_DELETE(materData);
    materData=NULL;
}


bool UserBigEquipLayer::init(MaterData* _data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        materData=_data;
        this->isClickClose = true;
        this->isAnimation=true;
        this->setBackground(IMG_MARKET_MARKETFIND_EQUIPBG);
        this->setGrayBg();
        
        this->setCardItem();
        
        bref = true;
    } while (false);
    return bref;
}

UserBigEquipLayer* UserBigEquipLayer::create(MaterData* _data)
{
    UserBigEquipLayer* list = new UserBigEquipLayer();
    if(list && list->init(_data))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void UserBigEquipLayer::onEnter()
{
    BaseLayer::onEnter();
    setClickEnabled(true);
    
}
void UserBigEquipLayer::onExit()
{
    BaseLayer::onExit();
    setClickEnabled(false);
    
}
void UserBigEquipLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void UserBigEquipLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void UserBigEquipLayer::setCardItem()
{
    
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Sprite* juxianbg = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBG);
//    juxianbg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(juxianbg);
//    juxianbg->setPosition((this->getContentSize().width-juxianbg->getContentSize().width)/2,(this->getContentSize().height-juxianbg->getContentSize().height)/2);
//    this->addChild(juxianbg,2);
//
    Sprite* juxianbg =(Sprite*)this->getChildByTag(TAG_BG);
    juxianbg->setContentSize(juxianbg->getContentSize()/sx);
    
    DictItemMater* itemMaterData=DictItemMaterManager::getInstance()->getData(materData->materId);
    if (!itemMaterData) {
        return;
    }
    string resource = itemMaterData->resource;
    UserEquipLayer* head = UserEquipLayer::create(resource,materData->materQuality);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(juxianbg->getContentSize().width/2-head->getContentSize().width/2,260);
    juxianbg->addChild(head,2);
    
    DictItemEquip* equipData=DictItemEquipManager::getInstance()->getData(itemMaterData->targetId);
    string sellnameStr =equipData->name;
    Label* sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    sellnameLabel->setAnchorPoint(Point::ZERO);
    sellnameLabel->setPosition(juxianbg->getContentSize().width/2-sellnameLabel->getContentSize().width/2,juxianbg->getContentSize().height/2-sellnameLabel->getContentSize().height/2+30);
    juxianbg->addChild(sellnameLabel,4);
    
    string pinzhiStr ="品质";
    Label* pinzhiLabel = PublicShowUI::getLabel(pinzhiStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    pinzhiLabel->setAnchorPoint(Point::ZERO);
    pinzhiLabel->setPosition(juxianbg->getContentSize().width/2-pinzhiLabel->getContentSize().width/2-75,juxianbg->getContentSize().height/2-pinzhiLabel->getContentSize().height/2-3);
    juxianbg->addChild(pinzhiLabel,4);
    
    //品质
    int  pingzhiNum= materData->materQuality;
    string pinzhicountStr =StringUtils::format("%d",pingzhiNum);
    Label* pinzhicountLabel = PublicShowUI::getLabel(pinzhicountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    pinzhicountLabel->setAnchorPoint(Point::ZERO);
    pinzhicountLabel->setPosition(juxianbg->getContentSize().width/2-pinzhicountLabel->getContentSize().width/2+10,juxianbg->getContentSize().height/2-pinzhicountLabel->getContentSize().height/2-5);
    juxianbg->addChild(pinzhicountLabel,4);
    //描述
    int _id=DictItemMaterManager::getInstance()->getData(materData->materId)->targetId;
    string  itemdescStr= DictItemEquipManager::getInstance()->getData(_id)->desc;
    
    Label* itemdescLabel = PublicShowUI::getLabel(itemdescStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    itemdescLabel->setAnchorPoint(Point(0.5,0.5));
    itemdescLabel->setMaxLineWidth(180);
    itemdescLabel->setPosition(juxianbg->getContentSize().width/2-itemdescLabel->getContentSize().width/2+80,juxianbg->getContentSize().height/2-itemdescLabel->getContentSize().height/2-30);
    juxianbg->addChild(itemdescLabel,4);
    
    //确认按钮
    Sprite* buyWord = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBUTTON);
    buyWord->setAnchorPoint(Point::ZERO);
    buyWord->setPosition(juxianbg->getContentSize().width/2-buyWord->getContentSize().width/2,juxianbg->getContentSize().height/2-170);
    juxianbg->addChild(buyWord);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(UserBigEquipLayer::onClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
}
void UserBigEquipLayer::onClick(Ref* psender)
{
    this->removeFromParent();
}
bool UserBigEquipLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return  true;
}
void UserBigEquipLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void UserBigEquipLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    backScene();
}
void UserBigEquipLayer::backScene()
{
    this->removeFromParent();
}
