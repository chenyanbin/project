//
//  BuyTimeLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//

#include "BuyTimeLayer.hpp"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../../message/Decoding/arena/FindUserMessageMsg.hpp"
#include "../../../common/Dialog/Dialog.h"
#include "../arenaData/RoleMessageDataManager.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../message/Decoding/arena/BuyTimeMsg.hpp"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/noticeManager/NoticeManager.h"
BuyTimeLayer::BuyTimeLayer()
:m_buytype(1)
,m_glod(1)
,m_times(1)
{
    
}

BuyTimeLayer::~BuyTimeLayer()
{
    
}


bool BuyTimeLayer::init(int buytype,int glod,int time)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_buytype = buytype;
        m_glod = glod;
        m_times = time;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setBgLayer();
        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}

BuyTimeLayer* BuyTimeLayer::create(int buytype,int glod,int time)
{
    BuyTimeLayer* list = new BuyTimeLayer();
    if(list && list->init(buytype,glod,time))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void BuyTimeLayer::show(int buytype,int glod,int time)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    BuyTimeLayer* layer = BuyTimeLayer::create(buytype,glod,time);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void BuyTimeLayer::onEnter()
{
    BaseLayer::onEnter();
}
void BuyTimeLayer::onExit()
{
    BaseLayer::onExit();
}
void BuyTimeLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void BuyTimeLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void BuyTimeLayer::setBgLayer()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    if (m_buytype == 1)//购买挑战次数
    {
        Sprite* spr = Sprite::create(IMG_ARENALIST_TIMES);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition((layerbg->getContentSize().width/sx - spr->getContentSize().width)/2, (layerbg->getContentSize().height/sx - spr->getContentSize().height)/2+50);
        layerbg->addChild(spr,1);
        
        string str = PublicShowUI::numberToString(m_glod);
        Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),28,false,false);
        label->setAnchorPoint(Point::ZERO);
        layerbg->addChild(label,3);
        label->setPosition(197,220);
        
        str = PublicShowUI::numberToString(m_times);
        Label* timelabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),28,false,false);
        timelabel->setAnchorPoint(Point::ZERO);
        layerbg->addChild(timelabel,3);
        timelabel->setPosition(375,164);
    }
    else if(m_buytype == 2)//购买挑战时间
    {
        Sprite* spr = Sprite::create(IMG_ARENALIST_GLOD);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition((layerbg->getContentSize().width/sx - spr->getContentSize().width)/2, (layerbg->getContentSize().height/sx - spr->getContentSize().height)/2+50);
        layerbg->addChild(spr,1);
        
        string str = PublicShowUI::numberToString(m_glod);
        Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_ORANGE_YELLOW),28,false,false);
        label->setAnchorPoint(Point::ZERO);
        layerbg->addChild(label,3);
        label->setPosition(230,175);
 
    }
    
}
void BuyTimeLayer::setSureBuyBtn()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_PUBLIC_LABEL_BUYWORD, IMG_PUBLIC_LABEL_BUYWORD, CC_CALLBACK_1(BuyTimeLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(BuyTimeLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
}
void BuyTimeLayer::onSureBuyClick(Ref* psender)
{
    if (m_buytype == 1 && m_times == 0) {
        NoticeManager::getInstance()->showNotice("次数用尽，请充值vip");
        return;
    }
    requestBuyTimeMsg(m_buytype);
}
void BuyTimeLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/**************-------------------------------------  ---------服务器---------  ------------------------------------*****************/
void BuyTimeLayer::requestBuyTimeMsg(int buyType)
{
    Dialog::showServerLoading();
    BuyTimeMsg* msg = new BuyTimeMsg(buyType);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void BuyTimeLayer::onBuyTimeMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    RoleMessageDataManager::getInstance()->destroyInstance();
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaBuyResp)
    {
        if(message->state)//返回成功
        {
            broadMsg(CUSTOM_ARENA_FIGHT_SUCCEED);
            this->removeFromParent();
        
        }
    }
}
void BuyTimeLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaBuyResp).c_str(), CC_CALLBACK_1(BuyTimeLayer::onBuyTimeMsgProcess, this));
}
void BuyTimeLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
