//
//  MarketPurchaseLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/27.
//
//

#include "MarketPurchaseLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../marketData/ShopPageListDataManager.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/market/shop/ShopBuyMsg/ShopBuyMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/shop/ShopPageListMsg/ShopPageListMsg.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../../tdTalkData/TDTalkDataManager.hpp"
#include "../../../common/Dialog/Dialog.h"
MarketPurchaseLayer::MarketPurchaseLayer()
:m_nowcount(1)
,TAG_COUNT(2)
,TAG_ALLCOUNT(3)
,m_idx(1)
,allPrice(1)
,TAG_GOLD(14)
,m_baselist(NULL)
{
    m_baselist = new Vector<BaseTypeData*>();
}

MarketPurchaseLayer::~MarketPurchaseLayer()
{
}


bool MarketPurchaseLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_idx = idx;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setButton();
        setPrice(m_nowcount);
        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}

MarketPurchaseLayer* MarketPurchaseLayer::create(int idx)
{
    MarketPurchaseLayer* list = new MarketPurchaseLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketPurchaseLayer::show(int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MarketPurchaseLayer* layer = MarketPurchaseLayer::create(idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void MarketPurchaseLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketPurchaseLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketPurchaseLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void MarketPurchaseLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MarketPurchaseLayer::setButton()
{

    float sx = GlobalInfo::getInstance()->screenScaleX;
    ShopPageListData* data = ShopPageListDataManager::getInstance()->shopList->at(m_idx);
    
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    PublicShowUI::setTargetScale(head);
    head->setPosition(30*sx ,this->getContentSize().height-head->getContentSize().height-40*sx);
    this->addChild(head,1);

    
    
    //道具名称背景
    Sprite* namebg = Sprite::create(IMG_MARKET_MARKETSHOP_DAOJUBG);
    namebg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(namebg);
    namebg->setPosition(this->getContentSize().width/2-namebg->getContentSize().width/2-40*sx ,this->getContentSize().height/2+namebg->getContentSize().height/2+70*sx);
    this->addChild(namebg,1);
    string daojunameStr = ShopPageListDataManager::getInstance()->shopList->at(m_idx)->itemName;
    Label* nameLabel = PublicShowUI::getLabel(daojunameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(nameLabel);
    nameLabel->setPosition(namebg->getPositionX()+15*sx,namebg->getPositionY()+4*sx);
    this->addChild(nameLabel,4);
    
    //刷新时间b
    Sprite* buytime = Sprite::create(IMG_MARKET_MARKETSHOP_BUYTIME);
    buytime->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buytime);
    buytime->setPosition(head->getPositionX(),head->getPositionY()-20*sx);
//    this->addChild(buytime,1);
    
    //当前拥有
    string renwuWord= "当前拥有";
    Label* renwuLabel = PublicShowUI::getLabel(renwuWord.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    renwuLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel);
    renwuLabel->setPosition(namebg->getPositionX(),namebg->getPositionY()-40*sx);
    this->addChild(renwuLabel,2);
    
    int nowCount = ShopPageListDataManager::getInstance()->shopList->at(m_idx)->ownCount;
    string numCard = StringUtils::format("%d",nowCount);
    Label* numLabel = PublicShowUI::getLabel(numCard.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    numLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(numLabel);
    numLabel->setPosition(renwuLabel->getPositionX()+renwuLabel->cocos2d::Node::getContentSize().width+20*sx,renwuLabel->getPositionY());
    this->addChild(numLabel,1);
    
    
    //减10
    Button * minTen = Button::create(IMG_VIP_RECHARGE_RECBTN, IMG_VIP_RECHARGE_RECBTN, CC_CALLBACK_1(MarketPurchaseLayer::onBuyclick, this));
    minTen->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(minTen);
    minTen->setPosition(renwuLabel->getPositionX()-10*sx,renwuLabel->getPositionY()-60*sx);
    this->addChild(minTen,2 ,TAG_MINUSTEN);
    Sprite* mintenword = Sprite::create(IMG_VIP_RECHARGE_MINRECBTNTEN);
    mintenword->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(mintenword);
    mintenword->setPosition(minTen->getPositionX(),minTen->getPositionY());
    this->addChild(mintenword,5);
    //减1
    Button * min = Button::create(IMG_MARKET_MARKETSHOP_MIN, IMG_MARKET_MARKETSHOP_MIN, CC_CALLBACK_1(MarketPurchaseLayer::onBuyclick, this));
    min->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(min);
    min->setPosition(minTen->getPositionX()-getPositionX()+minTen->getContentSize().width+5*sx,minTen->getPositionY());
    this->addChild(min,2,TAG_MINUS);
    
    //价格背景
    Sprite* priceBg = Sprite::create(IMG_MARKET_MARKETSHOP_PRICEBG);
    priceBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(priceBg);
    priceBg->setPosition(min->getPositionX()+min->getContentSize().width+5*sx,min->getPositionY()+10*sx);
    this->addChild(priceBg,1);
    //加1
    
    Button * add = Button::create(IMG_MARKET_MARKETSHOP_ADD, IMG_MARKET_MARKETSHOP_ADD, CC_CALLBACK_1(MarketPurchaseLayer::onBuyclick, this));
    add->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(add);
    add->setPosition(priceBg->getPositionX()+priceBg->getContentSize().width+5*sx,priceBg->getPositionY()-10*sx);
    this->addChild(add,2,TAG_ADD);
    //加10
    Button * addTen = Button::create(IMG_VIP_RECHARGE_RECBTN, IMG_VIP_RECHARGE_RECBTN, CC_CALLBACK_1(MarketPurchaseLayer::onBuyclick, this));
    addTen->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(addTen);
    addTen->setPosition(add->getPositionX()+add->getContentSize().width+5*sx,add->getPositionY());
    this->addChild(addTen,2,TAG_ADDTEN);
    
    Sprite* tenword = Sprite::create(IMG_VIP_RECHARGE_ADDRECBTNTEN);
    tenword->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(tenword);
    tenword->setPosition(addTen->getPositionX(),addTen->getPositionY());
    this->addChild(tenword,5);
    
    
    
}

void MarketPurchaseLayer::onBuyclick(Ref* psender)
{
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case TAG_ADD:
            m_nowcount += 1;
            break;
        case TAG_ADDTEN:
            m_nowcount += 10;
            break;
        case TAG_MINUS:
            m_nowcount -= 1;
            break;
        case TAG_MINUSTEN:
            m_nowcount -= 10;
            break;
        default:
            break;
    }
    if (m_nowcount <= 1) {
        m_nowcount = 1;
    }else if (m_nowcount>ShopPageListDataManager::getInstance()->shopList->at(m_idx)->maxBuyCount-ShopPageListDataManager::getInstance()->shopList->at(m_idx)->todayBuyCount)
    {
        m_nowcount =ShopPageListDataManager::getInstance()->shopList->at(m_idx)->maxBuyCount-ShopPageListDataManager::getInstance()->shopList->at(m_idx)->todayBuyCount;
    }
    setPrice(m_nowcount);
}
void MarketPurchaseLayer::setPrice(int nowCount)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string nowcountStr = StringUtils::format("%d",nowCount);
    Label* countLabel = (Label*)this->getChildByTag(TAG_COUNT);
    if(countLabel)
    {
        countLabel->setString(nowcountStr.c_str());
    }
    else
    {
        countLabel = PublicShowUI::getLabel(nowcountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
        countLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(countLabel);
        countLabel->setPosition(this->getContentSize().width/2-countLabel->getContentSize().width/2+40*sx,this->getContentSize().height/2-countLabel->getContentSize().height/2+10*sx);
        this->addChild(countLabel,2,TAG_COUNT);
    }
    
    allPrice = ShopPageListDataManager::getInstance()->shopList->at(m_idx)->goldnow;;
    allPrice = allPrice * nowCount;
    string allPriceStr = StringUtils::format("总价格：%d",allPrice);

    Label* allPriceLabel = (Label*)this->getChildByTag(TAG_ALLCOUNT);
    if(allPriceLabel)
    {
        allPriceLabel->setString(allPriceStr);
    }
    else
    {
        allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
        allPriceLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(allPriceLabel);
        allPriceLabel->setPosition(this->getContentSize().width/2-allPriceLabel->getContentSize().width/2-70*sx,this->getContentSize().height/2-allPriceLabel->getContentSize().height/2-40*sx);
        this->addChild(allPriceLabel,2,TAG_ALLCOUNT);
    }
    
    Sprite* gold = (Sprite*)this->getChildByTag(TAG_GOLD);
    if (gold) {
        return;
    }else{
        Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
        gold->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(gold);
        gold->setScale(0.7*sx);
        gold->setPosition(allPriceLabel->getPositionX()+allPriceLabel->getContentSize().width+50*sx,allPriceLabel->getPositionY()-4*sx);
        this->addChild(gold,3,TAG_GOLD);
    }
    
    
}

void MarketPurchaseLayer::setSureBuyBtn()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_PUBLIC_LABEL_BUYWORD, IMG_PUBLIC_LABEL_BUYWORD, CC_CALLBACK_1(MarketPurchaseLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(MarketPurchaseLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);

}
void MarketPurchaseLayer::onSureBuyClick(Ref* psender)
{
    requestListMsg(ShopPageListDataManager::getInstance()->shopList->at(m_idx)->shopId,m_nowcount);
}
void MarketPurchaseLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/******------------------------------------访问服务器------------------------------*************/
void MarketPurchaseLayer::requestListMsg(int shopId, int count)//请求列表信息
{
    Dialog::showServerLoading();
    ShopBuyMsg* msg = new ShopBuyMsg(shopId,count);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketPurchaseLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_SHOP_ShopBuyResp)
    {
        if(message->state)//返回成功
        {
            
            ShopPageListData* data = ShopPageListDataManager::getInstance()->shopList->at(m_idx);
            BaseTypeData* basedata = new BaseTypeData;
            basedata->dataType = data->itemType;
            basedata->dataId = data->itemId;
            basedata->dataQuality = data->quality;
            basedata->dataName = data->itemName;
            basedata->dataCount = m_nowcount;
            m_baselist->pushBack(basedata);
            TDTalkDataManager::getInstance()->onPurchase(basedata->dataName.c_str(), m_nowcount, data->goldnow);
            AwardBox_Layer* layer = AwardBox_Layer::create(m_baselist);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
            this->removeFromParent();
            broadMsg(CUSTOM_MARKER_UPDATASHOP,__Integer::create(m_nowcount));
        }
        else
        {
            return;
        }
    }
}
void MarketPurchaseLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SHOP_ShopBuyResp).c_str(), CC_CALLBACK_1(MarketPurchaseLayer::onMsgProcess, this));
}
void MarketPurchaseLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}