//
//  MarketGoodsLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/5.
//
//

#include "MarketGoodsLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../avatar/hero/Hero.h"
#include "../marketFind/MarketGetHeroLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../tips/TipsLayer.h"
#include "../../../common/Dialog/Dialog.h"
MarketGoodsLayer::MarketGoodsLayer()
:m_nowIndex(0)
,m_bol(false)
,m_headIndex(0)
,m_path("")
,m_quality(0)
{
    
}

MarketGoodsLayer::~MarketGoodsLayer()
{
}


bool MarketGoodsLayer::init(bool _bol)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isShowGrayBg = true;
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->setBackground(IMG_PUBLIC_LAYER_GAIN_BG,Point::ZERO,false);
        settitle();
        m_bol=_bol;
        bref = true;
    } while (false);
    return bref;
}

MarketGoodsLayer* MarketGoodsLayer::create(bool _bol)
{
    MarketGoodsLayer* list = new MarketGoodsLayer();
    if(list && list->init(_bol))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketGoodsLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketGoodsLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketGoodsLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    showItem();
}
void MarketGoodsLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void MarketGoodsLayer::settitle()
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* labelSprite=Sprite::create(IMG_PUBLIC_LAYER_GAIN_LABEL);
    labelSprite->setAnchorPoint(Point::ZERO);
    labelSprite->setPosition(568-labelSprite->getContentSize().width/2,309-labelSprite->getContentSize().height/2);
    layer->addChild(labelSprite);
//    Sprite* juxianbg = Sprite::create(IMG_MARKET_MARKETJUXIAN_JUXIANBG);
//    juxianbg->setAnchorPoint(Point::ZERO);
//    juxianbg->setPosition(Point::ZERO);
//    this->addChild(juxianbg);
//    this->setContentSize(juxianbg->getContentSize());
//
//    Sprite* juxianWord = Sprite::create(IMG_MARKET_MARKETJUXIAN_JUXIANWORD);
//    juxianWord->setAnchorPoint(Point::ZERO);
//    juxianWord->setPosition(juxianbg->getContentSize().width/2-juxianWord->getContentSize().width/2,juxianbg->getContentSize().height-juxianWord->getContentSize().height-5);
//    juxianbg->addChild(juxianWord);
//    
//    //确认按钮
//    Sprite* buyWord = Sprite::create(IMG_MARKET_MARKETFIND_EQUIPBUTTON);
//    buyWord->setAnchorPoint(Point::ZERO);
//    buyWord->setPosition(juxianbg->getContentSize().width/2-buyWord->getContentSize().width/2,30);
//    juxianbg->addChild(buyWord);
//    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(MarketGoodsLayer::onClick, this));
//    surebuy->setAnchorPoint(Point::ZERO);
//    surebuy->setPosition(Point::ZERO);
//    buyWord->addChild(surebuy,2);
//    
//    this->setContentSize(juxianbg->getContentSize());
}
void MarketGoodsLayer::onClick(Ref* pSender)
{
    this->removeFromParent();
}
void MarketGoodsLayer::showItem()
{
    if(m_nowIndex >= MarketFindResultDataManager::getInstance()->dumpList->size())
    {
        if(m_bol)
        {
            if(MarketFindResultDataManager::getInstance()->dumpList->size()<10)
            {
                Dialog::show("您的武将或装备背包已满,未获得的物品会通过邮件发送给您");
            }
        }
        this->isClickClose = true;
        return;
    }
    
    MarketFindResultData* data = MarketFindResultDataManager::getInstance()->dumpList->at(m_nowIndex);
    log("m_nowIndex==============%d",m_nowIndex);
//    const char* path = NULL;
//    CallFunc* callBack = NULL;
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        showHeroEffect(data);
//        if (data->dictId) {
//            DictHero* dicthero = DictHeroManager::getInstance()->getData(data->dictId);
//            path =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->resource.c_str());
//        }else{
//            path = PublicShowUI::getGoods(data->itemType, data->itemId);
//        }
//        callBack = CallFunc::create(CC_CALLBACK_0(MarketGoodsLayer::showHeroEffect, this,data));
    }
    else
    {
        setHeroPos(data);
//        if (data->dictId==0) {
//            path = PublicShowUI::getGoods(data->itemType, data->itemId);
//        }else
//        {
//            path = PublicShowUI::getGoods(data->itemType, data->dictId);
//        }
        
//        callBack = CallFunc::create(CC_CALLBACK_0(MarketGoodsLayer::showItem, this));
    }
    
//    
//    if(  data->itemType == DictItemTypeEnumItemHero)
//    {
//        showHeroEffect(data);
//        m_path = path;
//        m_quality = data->quality;
//        m_headIndex = m_nowIndex;
//        UserHeadLayer* userHead=UserHeadLayer::create(path,data->quality,false);
//        userHead->setHeadInfo(1, 1);
//        userHead->setAnchorPoint(Point::ZERO);
//        userHead->setScale(0.8);
//        userHead->setOpacity(0);
//        userHead->runAction(callBack);
//        this->addChild(userHead,10 + m_nowIndex, m_nowIndex);
//        userHead->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
//        userHead->setPosition(50+(userHead->getContentSize().width-19)*(m_nowIndex%5),350-(userHead->getContentSize().height*floor(m_nowIndex/5)-3));
//        MoveTo* move = MoveTo::create(.1, Point(50+(userHead->getContentSize().width-19)*(m_nowIndex%5),220-(userHead->getContentSize().height*floor(m_nowIndex/5)-3)));
//        FadeIn* fadeIn = FadeIn::create(1.3);
//        userHead->runAction(Sequence::create(callBack,fadeIn,move, NULL));
//        userHead->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
//
//    }
//    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
//    {
//        UserEquipLayer* head = UserEquipLayer::create(path,data->quality,false);
//        head->setAnchorPoint(Point::ZERO);
//        if (data->itemType == 4) {
//            head->setFragment();
//        }else if (data->itemType == 3)
//        {
//            head->setLetterFragment();
//        }
//        head->setScale(0.8);
//        head->setPosition(50+(head->getContentSize().width-20)*(m_nowIndex%5),350-(head->getContentSize().height*floor(m_nowIndex/5)-3));
//        MoveTo* move = MoveTo::create(.1, Point(50+(head->getContentSize().width-20)*(m_nowIndex%5),220-(head->getContentSize().height*floor(m_nowIndex/5))));
//        head->runAction(move);
////        head->setPosition(50+(head->getContentSize().width-20)*(m_nowIndex%5),220-(head->getContentSize().height*floor(m_nowIndex/5)));
//        this->addChild(head, 10 + m_nowIndex, m_nowIndex);
//        head->setOpacity(0);
//        FadeIn* fadeIn = FadeIn::create(0.3);
//        head->runAction(Sequence::create(fadeIn,callBack, NULL));
//        head->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
//    }
//    
//    m_nowIndex ++;
    
}

void MarketGoodsLayer::onHeroHeadClick(Node* pSender)
{
    int index = pSender->getTag();
    MarketFindResultData* data = MarketFindResultDataManager::getInstance()->dumpList->at(index);
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        if(data->itemId){
            TipsLayer::show(data->itemType, data->itemId,0);
            return;
        }
        DictItemHero* itemHero = PublicShowUI::getItemHeroByDictId(data->dictId);
        if(itemHero)
        {
             TipsLayer::show(data->itemType, itemHero->id,0);
        }
       
    }
    else
    {
        if (data->dictId==0) {
            TipsLayer::show(data->itemType, data->itemId,0);
        }else
        {
            TipsLayer::show(data->itemType, data->dictId,0);
        }
        
    }
    
}
void MarketGoodsLayer::showHeroEffect(MarketFindResultData* finddata)
{

    if (m_bol == true) {
        MarketGetHeroLayer::show(finddata,CC_CALLBACK_0(MarketGoodsLayer::setHeroPos, this,finddata));//showItem
    }else
    {
        this->setHeroPos(finddata);
    }
}
void MarketGoodsLayer::setHeroPos(MarketFindResultData* data)
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    const char* path  = NULL;
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        if (data->dictId) {
            DictHero* dicthero = DictHeroManager::getInstance()->getData(data->dictId);
            path =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->resource.c_str());
        }else{
            path = PublicShowUI::getGoods(data->itemType, data->itemId);
        }
        
    }
    else
    {
        if (data->dictId==0) {
            path = PublicShowUI::getGoods(data->itemType, data->itemId);
        }else
        {
            path = PublicShowUI::getGoods(data->itemType, data->dictId);
        }
        
    }
     CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketGoodsLayer::showItem, this));
    
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        UserHeadLayer* userHead=UserHeadLayer::create(path,data->quality,false);
        userHead->setHeadInfo(1, data->prestige);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setScale(0.8);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
        userHead->setPosition(300+(userHead->getContentSize().width-19)*(m_nowIndex%5),300-(userHead->getContentSize().height*floor(m_nowIndex/5)-3));
        MoveTo* move = NULL;
        if (MarketFindResultDataManager::getInstance()->dumpList->size()<=5) {
            move = MoveTo::create(.1, Point(300+(userHead->getContentSize().width-9)*(m_nowIndex%5),100-(userHead->getContentSize().height*floor(m_nowIndex/5)-3)));
        }else{
            move = MoveTo::create(.1, Point(300+(userHead->getContentSize().width-9)*(m_nowIndex%5),170-(userHead->getContentSize().height*floor(m_nowIndex/5)-3)));
        }
        userHead->runAction(move);
        layer->addChild(userHead,10 + m_nowIndex, m_nowIndex);
        userHead->setOpacity(0);
        FadeIn* fadeIn = FadeIn::create(.3);
        userHead->runAction(Sequence::create(fadeIn,callBack, NULL));
        userHead->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
        
        string name=  "x" + PublicShowUI::numberToString(data->itemCount);
        if (data->itemCount>1) {
            Label* countLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
            countLabel->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(countLabel);
            countLabel->setPosition(userHead->getContentSize().width,0);
            userHead->addChild(countLabel);
        }
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        UserEquipLayer* head = UserEquipLayer::create(path,data->quality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        head->setScale(0.8);
        head->setPosition(300+(head->getContentSize().width-20)*(m_nowIndex%5),300-(head->getContentSize().height*floor(m_nowIndex/5)-3));
        
        MoveTo* move = NULL;
        if (MarketFindResultDataManager::getInstance()->dumpList->size()<=5) {
            move = MoveTo::create(.1, Point(300+(head->getContentSize().width-10)*(m_nowIndex%5),100-(head->getContentSize().height*floor(m_nowIndex/5))));
        }else{
            move = MoveTo::create(.1, Point(300+(head->getContentSize().width-10)*(m_nowIndex%5),170-(head->getContentSize().height*floor(m_nowIndex/5))));
        }
        head->runAction(move);
        layer->addChild(head, 10 + m_nowIndex, m_nowIndex);
        head->setOpacity(0);
        FadeIn* fadeIn = FadeIn::create(0.3);
        head->runAction(Sequence::create(fadeIn,callBack, NULL));
        head->addTouchBegainCallBack(this, callfuncN_selector(MarketGoodsLayer::onHeroHeadClick));
        
        string name=  "x" + PublicShowUI::numberToString(data->itemCount);
        if (data->itemCount>1) {
            Label* countLabel = PublicShowUI::getLabel(name.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
            countLabel->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(countLabel);
            countLabel->setPosition(head->getContentSize().width,0);
            head->addChild(countLabel);
        }
    }
   
    m_nowIndex ++;
}
void MarketGoodsLayer::backScene()
{
    if(m_nowIndex >= MarketFindResultDataManager::getInstance()->dumpList->size())
    {
        this->removeFromParent();
    }
}
