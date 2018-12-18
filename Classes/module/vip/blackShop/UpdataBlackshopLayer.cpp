//
//  UpdataBlackshopLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/15.
//
//

#include "UpdataBlackshopLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/noticeManager/NoticeManager.h"
UpdataBlackshopLayer::UpdataBlackshopLayer()
:m_needGold(0)

{
    
}

UpdataBlackshopLayer::~ UpdataBlackshopLayer()
{
}


bool UpdataBlackshopLayer::init(int needGold)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_needGold = needGold;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setUiSpr();
        
        setSureBuyBtn();
        
        bref = true;
    } while (false);
    return bref;
}

UpdataBlackshopLayer* UpdataBlackshopLayer::create(int needGold)
{
    UpdataBlackshopLayer* list = new UpdataBlackshopLayer();
    if(list && list->init(needGold))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void UpdataBlackshopLayer::show(int needGold)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    UpdataBlackshopLayer* layer = UpdataBlackshopLayer::create(needGold);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void UpdataBlackshopLayer::onEnter()
{
    BaseLayer::onEnter();
}
void UpdataBlackshopLayer::onExit()
{
    BaseLayer::onExit();
}
void UpdataBlackshopLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void UpdataBlackshopLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void UpdataBlackshopLayer::setUiSpr()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string renwuWord1= "是否刷新物品？";
    Label* renwuLabel1 = PublicShowUI::getLabel(renwuWord1.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    renwuLabel1->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel1);
    renwuLabel1->setPosition(this->getContentSize().width/2-renwuLabel1->getContentSize().width/2 ,this->getContentSize().height/2-renwuLabel1->getContentSize().height/2+80*sx);
    this->addChild(renwuLabel1,2);
    
    string allPriceStr = StringUtils::format("花费：%d",m_needGold);
    Label* allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),22,false,false);
    allPriceLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(allPriceLabel);
    allPriceLabel->setPosition(this->getContentSize().width/2-allPriceLabel->getContentSize().width/2-20*sx,this->getContentSize().height/2-allPriceLabel->getContentSize().height/2+15*sx);
    this->addChild(allPriceLabel,2);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setScale(0.8*sx);
    gold->setPosition(allPriceLabel->getPositionX()+allPriceLabel->getContentSize().width+5*sx,allPriceLabel->getPositionY()-5*sx);
    this->addChild(gold,3);

}

void UpdataBlackshopLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(UpdataBlackshopLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(UpdataBlackshopLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void UpdataBlackshopLayer::onSureBuyClick(Ref* psender)
{
    if (m_needGold>GlobalInfo::getInstance()->userGold) {
        NoticeManager::getInstance()->showNotice("元宝不足，刷新失败");
        return;
    }
    
    broadMsg(CUSTOM_VIP_BLACKSHOP_SHHUAXIN);
    this->removeFromParent();
}

void UpdataBlackshopLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
