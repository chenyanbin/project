//
//  AuctionSureXiajiaLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/25.
//
//

#include "AuctionSureXiajiaLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../message/Decoding/market/paimai/paimaiShangjiaMsg/AuctionShangjiaMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../marketData/auctionData/AuctionShangjiaDataManger.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../../message/Decoding/market/paimai/paimaiShangjiaMsg/surexuajiaMsg/SureXiajiaMsg.h"
#include "../../../../protocol/UserCustomEvent.h"
AuctionSureXiajiaLayer::AuctionSureXiajiaLayer()
:m_itemId(0)
{
    
}

AuctionSureXiajiaLayer::~ AuctionSureXiajiaLayer()
{
}


bool AuctionSureXiajiaLayer::init(int itemId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_itemId = itemId;
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

AuctionSureXiajiaLayer* AuctionSureXiajiaLayer::create(int itemId)
{
    AuctionSureXiajiaLayer* list = new AuctionSureXiajiaLayer();
    if(list && list->init(itemId))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void AuctionSureXiajiaLayer::show(int findId)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    AuctionSureXiajiaLayer* layer = AuctionSureXiajiaLayer::create(findId);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void AuctionSureXiajiaLayer::onEnter()
{
    BaseLayer::onEnter();
}
void AuctionSureXiajiaLayer::onExit()
{
    BaseLayer::onExit();
}
void AuctionSureXiajiaLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void AuctionSureXiajiaLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void AuctionSureXiajiaLayer::setUiSpr()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //消耗
    string nameStr = "是否下架?";
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),24,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(nameLabel);
    nameLabel->setPosition(this->getContentSize().width/2-nameLabel->getContentSize().width/2 +10*sx ,this->getContentSize().height/2+nameLabel->getContentSize().height/2+30*sx );
    this->addChild(nameLabel,1);
    
}

void AuctionSureXiajiaLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(AuctionSureXiajiaLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(AuctionSureXiajiaLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void AuctionSureXiajiaLayer::onSureBuyClick(Ref* psender)
{
    
    if (AuctionShangjiaDataManger::getInstance()->shangjiaList->size() <= 0) {
        NoticeManager::getInstance()->showNotice("无可下架物品");
    }else{
        requestSurexiajiaMsg(AuctionShangjiaDataManger::getInstance()->shangjiaList->at(m_itemId)->sellId);
    }
}

void AuctionSureXiajiaLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/**************--------------------------访问服务器------------------------------------*****************/
void AuctionSureXiajiaLayer::requestSurexiajiaMsg(int SellId)//请求下架
{
    Dialog::showServerLoading();
    SureXiajiaMsg* msg = new SureXiajiaMsg(SellId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void AuctionSureXiajiaLayer::onSureXiajiaProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketPullOffResp)
    {
        if(message->state)//返回成功
        {
            NoticeManager::getInstance()->showNotice("物品下架成功！",NoticeManager::COLOR_GREEN);
            this->removeFromParent();
             broadMsg(CUSTOM_MARKER_XIAJIABTN,__Integer::create(m_itemId));
        }
    }
}

void AuctionSureXiajiaLayer::addEventListener()
{
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketPullOffResp).c_str(), CC_CALLBACK_1(AuctionSureXiajiaLayer::onSureXiajiaProcess, this));
}
void AuctionSureXiajiaLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
