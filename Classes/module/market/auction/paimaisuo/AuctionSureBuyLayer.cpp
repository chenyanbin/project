//
//  AuctionSureBuyLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/10.
//
//

#include "AuctionSureBuyLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../message/Decoding/market/paimai/paimaiHomeMsg/buyItemMsg/BuyItemMsg.h"
#include "../../marketData/auctionData/AuctionHomeDataManager.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../awardBox/AwardBox_Layer.h"
AuctionSureBuyLayer::AuctionSureBuyLayer()
:m_itemId(0)
,m_owngold(1)
,m_baseList(NULL)
{
    m_baseList = new Vector<BaseTypeData*>();
}

AuctionSureBuyLayer::~AuctionSureBuyLayer()
{
}


bool AuctionSureBuyLayer::init(int itemId)
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

AuctionSureBuyLayer* AuctionSureBuyLayer::create(int itemId)
{
    AuctionSureBuyLayer* list = new AuctionSureBuyLayer();
    if(list && list->init(itemId))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void AuctionSureBuyLayer::show(int findId)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    AuctionSureBuyLayer* layer = AuctionSureBuyLayer::create(findId);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void AuctionSureBuyLayer::onEnter()
{
    BaseLayer::onEnter();
}
void AuctionSureBuyLayer::onExit()
{
    BaseLayer::onExit();
}
void AuctionSureBuyLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void AuctionSureBuyLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void AuctionSureBuyLayer::setUiSpr()
{
  
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //消耗
    string nameStr = "是否购买？";
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),26,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(nameLabel);
    nameLabel->setPosition(this->getContentSize().width/2-nameLabel->getContentSize().width/2 +10*sx ,this->getContentSize().height/2+nameLabel->getContentSize().height/2+50*sx );
    this->addChild(nameLabel,1);
    
    int goldmoney = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->price;
    string militaryStr = StringUtils::format("消耗：%d",goldmoney);
    Label* militaryLabel = PublicShowUI::getLabel(militaryStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),22,false,false);
    militaryLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(militaryLabel);
    militaryLabel->setPosition(this->getContentSize().width/2-militaryLabel->getContentSize().width/2-10*sx  ,this->getContentSize().height/2+militaryLabel->getContentSize().height/2-7*sx );
    this->addChild(militaryLabel,2);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setScale(0.7*sx);
    gold->setPosition(militaryLabel->getPositionX()+militaryLabel->getContentSize().width+10*sx ,militaryLabel->getPositionY()-4*sx);
    this->addChild(gold,1);
    
}

void AuctionSureBuyLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(AuctionSureBuyLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(AuctionSureBuyLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void AuctionSureBuyLayer::onSureBuyClick(Ref* psender)
{
    
    this->requestSureBuyMsg(AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->sellId);

//    int needgold = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->price;
//    if (needgold < m_owngold) {
//        this->requestSureBuyMsg(AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->sellId);
//    }
//    else
//    {
//        this->removeFromParent();

//    }
}

void AuctionSureBuyLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/**************--------------------------访问服务器------------------------------------*****************/
void AuctionSureBuyLayer::requestSureBuyMsg(int SellId)//请求购买
{
    Dialog::showServerLoading();
    BuyItemMsg* msg = new BuyItemMsg(SellId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void AuctionSureBuyLayer::onSureBuyMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketBuyResp)
    {
        if(message->state)//返回成功
        {
            
            BaseTypeData* basedata = new BaseTypeData();
            basedata->dataId = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->itemId;
            basedata->dataType = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->itemType;
            basedata->dataName = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->itemName;
            basedata->dataQuality = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->quality;
            basedata->dataCount = AuctionHomeDataManager::getInstance()->homeList->at(m_itemId)->sellCount;
            m_baseList->pushBack(basedata);
            
            AwardBox_Layer* layer = AwardBox_Layer::create(m_baseList);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene = Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
//            Dialog::show("购买成功!");
            this->removeFromParent();
             broadMsg(CUSTOM_MARKER_SUCCEEDBUY,__Integer::create(m_itemId));
        }
        else
        {
            return;
        }
    }
}
void AuctionSureBuyLayer::addEventListener()
{
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketBuyResp).c_str(), CC_CALLBACK_1(AuctionSureBuyLayer::onSureBuyMsgProcess, this));
}
void AuctionSureBuyLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
