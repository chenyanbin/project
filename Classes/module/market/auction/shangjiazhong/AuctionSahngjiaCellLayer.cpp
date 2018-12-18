//
//  AuctionSahngjiaCellLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/15.
//
//

#include "AuctionSahngjiaCellLayer.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../marketData/auctionData/AuctionShangjiaDataManger.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../message/Decoding/market/paimai/paimaiShangjiaMsg/AuctionShangjiaMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "AuctionSureXiajiaLayer.h"
#include "../../../tips/TipsLayer.h"
AuctionSahngjiaCellLayer::AuctionSahngjiaCellLayer()
:TAG_SHANGJAITIME(10)
,m_shangjiatimess(1)
,m_shangjiatimeLabel(NULL)
,istips(true)
{
    
}

AuctionSahngjiaCellLayer::~ AuctionSahngjiaCellLayer()
{
    
}


bool AuctionSahngjiaCellLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        shangjiaCellBackGround(idx);
        bref = true;
    } while (false);
    return bref;
}

AuctionSahngjiaCellLayer* AuctionSahngjiaCellLayer::create(int idx)
{
    AuctionSahngjiaCellLayer* list = new AuctionSahngjiaCellLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void AuctionSahngjiaCellLayer::onEnter()
{
    BaseLayer::onEnter();
}
void AuctionSahngjiaCellLayer::onExit()
{
    BaseLayer::onExit();
}
void AuctionSahngjiaCellLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void AuctionSahngjiaCellLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void AuctionSahngjiaCellLayer::shangjiaCellBackGround(int idx)
{
    if(idx >= AuctionShangjiaDataManger::getInstance()->shangjiaList->size())
    {
        return;
    }
    
    AuctionShangjiaData* data = AuctionShangjiaDataManger::getInstance()->shangjiaList->at(idx);
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);

    //头像
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    head->setTag(idx);
    head->setPosition(22,26);
    head->addTouchBegainCallBack(this, callfuncN_selector(AuctionSahngjiaCellLayer::onitemHeadClick));
    layerBg->addChild(head,1);
    //名字
    Sprite* namebg = Sprite::create(IMG_MARKET_MARKETSHOP_DAOJUBG);
    namebg->setAnchorPoint(Point::ZERO);
    namebg->setPosition(150,110);
    layerBg->addChild(namebg,1);
    string nameStr = data->itemName;
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,2);
    namebg->addChild(nameLabel,1);
    
    
    //价格和剩余时间字体
    Sprite* jiage = Sprite::create(IMG_MARKET_AUCTION_JIAGE);
    jiage->setAnchorPoint(Point::ZERO);
    jiage->setPosition(150,30);
    layerBg->addChild(jiage,1);
    //价格
    int price = data->price;//  122;
    string priceStr = StringUtils::format("%d",price);
    Label* priceLabel = PublicShowUI::getLabel(priceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    priceLabel->setAnchorPoint(Point::ZERO);;
    priceLabel->setPosition(210,80);
    layerBg->addChild(priceLabel,2);
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.6);
    gold->setPosition(priceLabel->getPositionX()+priceLabel->getContentSize().width+5, priceLabel->getPositionY()-2);
    layerBg->addChild(gold,2);
    
    //剩余数量
    string countStr = StringUtils::format("%d个",data->sellCount);
    Label* countLabel = PublicShowUI::getLabel(countStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    countLabel->setAnchorPoint(Point::ZERO);
    countLabel->setPosition(210,55);
    layerBg->addChild(countLabel,2);
    
    //剩余时间
    m_shangjiatimess = data->remainingTimes;
    string recuittime=StringUtils::format("%02ld:%02ld:%02ld",m_shangjiatimess/3600, m_shangjiatimess%3600/60,m_shangjiatimess%60);
    m_shangjiatimeLabel = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),18,false,false);
    m_shangjiatimeLabel->setAnchorPoint(Point::ZERO);
    layerBg->addChild(m_shangjiatimeLabel,1);
    m_shangjiatimeLabel->setTag(TAG_SHANGJAITIME);
    m_shangjiatimeLabel->setPosition(jiage->getPositionX()+jiage->getContentSize().width,jiage->getPositionY());
    this->schedule(schedule_selector(AuctionSahngjiaCellLayer::Updata),1);
    
    //下架按钮
    Sprite* buyBg = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyBg->setAnchorPoint(Point::ZERO);
    buyBg->setPosition(300,48);
    layerBg->addChild(buyBg,1);
    Button* beginxunfangSpr=Button::create(IMG_MARKET_AUCTION_XIAJIAWORD, IMG_MARKET_AUCTION_XIAJIAWORD, CC_CALLBACK_1(AuctionSahngjiaCellLayer::onClick, this));
    beginxunfangSpr->setAnchorPoint(Point::ZERO);
    beginxunfangSpr->setPosition(Point::ZERO);
    buyBg->addChild(beginxunfangSpr,1,idx);
    
    this->setContentSize(layerBg->getContentSize());
    this->addChild(layerBg);
}
void AuctionSahngjiaCellLayer::onitemHeadClick(Node* pSender)
{
//    broadMsg(CUSTOM_MARKER_FINDTIPS);
    if (istips) {
        AuctionShangjiaData* data = AuctionShangjiaDataManger::getInstance()->shangjiaList->at(pSender->getTag());
        TipsLayer::show(data->itemType, data->itemId, data->sellCount);
    }else{
        istips = true;
    }
    
    
}
void AuctionSahngjiaCellLayer::onClick(Ref* psender)//点击头像
{
    Node* target = (Node*)psender;
    AuctionSureXiajiaLayer::show(target->getTag());
}
void AuctionSahngjiaCellLayer::Updata(float delta)
{
    m_shangjiatimess -= 1;
    if (m_shangjiatimess <= 0) {
        m_shangjiatimess =0;
//      requestAuctionsahngjiaListMsg(0);
        log("........................%ld",m_shangjiatimess);
        unschedule(schedule_selector(AuctionSahngjiaCellLayer::Updata));
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime," %02ld:%02ld:%02ld",m_shangjiatimess/3600, m_shangjiatimess%3600/60,m_shangjiatimess%60);
    m_shangjiatimeLabel->setString(mtime);
}

void AuctionSahngjiaCellLayer::requestAuctionsahngjiaListMsg(int lastMarketGoodsId)//请求上架中列表信息
{
    AuctionShangjiaMsg* msg = new AuctionShangjiaMsg(lastMarketGoodsId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void AuctionSahngjiaCellLayer::onTipsStateMsg(EventCustom* msg)
{
    __Bool* inter = (__Bool*)msg->getUserData();
    istips = inter->getValue();
}
void AuctionSahngjiaCellLayer::addEventListener()
{
    this->addUserMsg(CUSTOM_MARKER_FINDTIPS, CC_CALLBACK_1(AuctionSahngjiaCellLayer::onTipsStateMsg, this));
}
void AuctionSahngjiaCellLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
