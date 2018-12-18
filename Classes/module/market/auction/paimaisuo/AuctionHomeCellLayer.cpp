//
//  AuctionHomeCellLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#include "AuctionHomeCellLayer.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../common/TouchSprite/Button.h"

#include "AuctionSureBuyLayer.h"
#include "../../marketData/auctionData/AuctionHomeDataManager.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../tips/TipsLayer.h"
AuctionHomeCellLayer::AuctionHomeCellLayer()
:TAG_TIME(10)
,timess(1)
,timeLabel(NULL)
{
    
}

AuctionHomeCellLayer::~ AuctionHomeCellLayer()
{

}


bool AuctionHomeCellLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        CellBackGround(idx);
        bref = true;
    } while (false);
    return bref;
}

AuctionHomeCellLayer* AuctionHomeCellLayer::create(int idx)
{
    AuctionHomeCellLayer* list = new AuctionHomeCellLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void AuctionHomeCellLayer::onEnter()
{
    BaseLayer::onEnter();
}
void AuctionHomeCellLayer::onExit()
{
    BaseLayer::onExit();
}
void AuctionHomeCellLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void AuctionHomeCellLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void AuctionHomeCellLayer::CellBackGround(int idx)
{
    if(idx >= AuctionHomeDataManager::getInstance()->homeList->size())
    {
        return;
    }
    AuctionHomeData* data = AuctionHomeDataManager::getInstance()->homeList->at(idx);
    

    Sprite* layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    this->setContentSize(layerBg->getContentSize());
    this->addChild(layerBg,-1,idx);
    
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
    head->setSwallowsTouches(true);
    head->addTouchBegainCallBack(this, callfuncN_selector(AuctionHomeCellLayer::onHeroHeadClick));
    layerBg->addChild(head,2);
    
    
    //名字
    Sprite* namebg = Sprite::create(IMG_MARKET_MARKETSHOP_DAOJUBG);
    namebg->setAnchorPoint(Point::ZERO);
    namebg->setPosition(150,110);
    layerBg->addChild(namebg,2);
    string nameStr = data->itemName;
    Label* nameLabel = PublicShowUI::getLabel(nameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(10,2);
    namebg->addChild(nameLabel,1);
    
    
    //价格
    Sprite* jiage = Sprite::create(IMG_MARKET_AUCTION_JIAGE);
    jiage->setAnchorPoint(Point::ZERO);
    jiage->setPosition(150,35);
    layerBg->addChild(jiage,2);
    string priceStr = StringUtils::format("%d",data->price);
    Label* pricelabel = PublicShowUI::getLabel(priceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    pricelabel->setAnchorPoint(Point::ZERO);;
    pricelabel->setPosition(210,87);
    layerBg->addChild(pricelabel,2);
    //元宝
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.6);
    gold->setPosition(pricelabel->getPositionX()+pricelabel->getContentSize().width+5,pricelabel->getPositionY()-2);
    layerBg->addChild(gold,2);
   //数量
    string countStr = StringUtils::format("%d个",data->sellCount);
    Label* countLabel = PublicShowUI::getLabel(countStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    countLabel->setAnchorPoint(Point::ZERO);;
    countLabel->setPosition(210,60);
    layerBg->addChild(countLabel,2);
    
    //剩余时间
    timess = data->remainingTimes;
    string recuittime=StringUtils::format("%02ld:%02ld:%02ld",timess/3600, timess%3600/60,timess%60);
    timeLabel = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),20,false,false);
    timeLabel->setAnchorPoint(Point::ZERO);
    layerBg->addChild(timeLabel,2);
    timeLabel->setTag(TAG_TIME);
    timeLabel->setPosition(230,35);
    this->schedule(schedule_selector(AuctionHomeCellLayer::Updata),1);
    
    //出售人
    Sprite* sellPeo = Sprite::create(IMG_MARKET_AUCTION_SELLPEOPLE);
    sellPeo->setAnchorPoint(Point::ZERO);
    sellPeo->setPosition(150,10);
    layerBg->addChild(sellPeo,2);
    
    Label* sellnameLabel = PublicShowUI::getLabel(data->sellRoleName.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    sellnameLabel->setAnchorPoint(Point::ZERO);
    sellnameLabel->setPosition(220,10);
    layerBg->addChild(sellnameLabel,2);
    
    //购买按钮
    Sprite* buyBg = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyBg->setAnchorPoint(Point::ZERO);
    buyBg->setPosition(layerBg->getContentSize().width-buyBg->getContentSize().width-10,60);
    layerBg->addChild(buyBg,1);
    Button* beginxunfangSpr=Button::create(IMG_PUBLIC_LABEL_BUYWORD, IMG_PUBLIC_LABEL_BUYWORD, CC_CALLBACK_1(AuctionHomeCellLayer::onClick, this));
    beginxunfangSpr->setAnchorPoint(Point::ZERO);
    beginxunfangSpr->setPosition(Point::ZERO);
    buyBg->addChild(beginxunfangSpr,1,idx);
    
    
}
void AuctionHomeCellLayer::onClick(Ref* psender)//点击购买
{
    //    log("%d",psender->getTag());
    Node* target = (Node*)psender;
    AuctionSureBuyLayer::show(target->getTag());
}
void AuctionHomeCellLayer::onHeroHeadClick(Node* psender)//点击头像
{
    AuctionHomeData* data = AuctionHomeDataManager::getInstance()->homeList->at(psender->getTag());
    TipsLayer::show(data->itemType,data->itemId, data->sellCount);
    
//    log("%d",psender->getTag());
//    AuctionSureBuyLayer::show(psender->getTag());
}
void AuctionHomeCellLayer::oncellClick(Ref* psender)
{
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    AuctionSureBuyLayer::show(target->getTag());
}
void AuctionHomeCellLayer::Updata(float delta)
{
    timess -= 1;
    if (timess <= 0) {
        timess =0;
        log("%ld",timess);
        unschedule(schedule_selector(AuctionHomeCellLayer::Updata));
    }
    char*mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime," %02ld:%02ld:%02ld",timess/3600, timess%3600/60,timess%60);
    timeLabel->setString(mtime);
}
