//
//  FindAccelerationLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//  加速寻访弹出层

#include "FindAccelerationLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/findSpeedMsg/FindSpeedMsg.h"
#include "../marketData/marketFindDataManager.h"
#include "../../../message/Decoding/market/marketFindMsg/MarketFindPageMsg.h"
FindAccelerationLayer::FindAccelerationLayer()
:m_nowcount(1)
,TAG_COUNT(2)
,TAG_ALLCOUNT(3)
,m_idx(0)
,m_owngold(1100)
{
    
}

FindAccelerationLayer::~FindAccelerationLayer()
{
}


bool FindAccelerationLayer::init(int idx)
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
        setUiSpr();
        
        setSureBuyBtn();
        
        bref = true;
    } while (false);
    return bref;
}

FindAccelerationLayer* FindAccelerationLayer::create(int idx)
{
    FindAccelerationLayer* list = new FindAccelerationLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void FindAccelerationLayer::show(int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    FindAccelerationLayer* layer = FindAccelerationLayer::create(idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void FindAccelerationLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FindAccelerationLayer::onExit()
{
    BaseLayer::onExit();
}
void FindAccelerationLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void FindAccelerationLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void FindAccelerationLayer::setUiSpr()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    //道具名称背景
    Sprite* namebg = Sprite::create(IMG_MARKET_MARKETFIND_SHIFOUJIASU);
    namebg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(namebg);
    namebg->setScale(2.0);
    namebg->setPosition(this->getContentSize().width/2-namebg->getContentSize().width/2+10*sx ,this->getContentSize().height/2+namebg->getContentSize().height/2-30*sx );
//    this->addChild(namebg,1);
    
    string renwuWord1= "是否加速寻访？";
    Label* renwuLabel1 = PublicShowUI::getLabel(renwuWord1.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    renwuLabel1->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel1);
    renwuLabel1->setPosition(this->getContentSize().width/2-renwuLabel1->getContentSize().width/2 ,this->getContentSize().height-renwuLabel1->getContentSize().height/2-70*sx);
    this->addChild(renwuLabel1,2);
    
    int goldmoney = marketFindDataManager::getInstance()->findList->at(m_idx)->fastGold;
    string militaryStr = StringUtils::format("花费：%d",goldmoney);
    Label* militaryLabel = PublicShowUI::getLabel(militaryStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),22,false,false);
    militaryLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(militaryLabel);
    militaryLabel->setPosition(this->getContentSize().width/2-militaryLabel->getContentSize().width/2 -30*sx ,this->getContentSize().height/2-militaryLabel->getContentSize().height/2+20*sx);
    this->addChild(militaryLabel,2);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setScale(0.8*sx);
    gold->setPosition(militaryLabel->getPositionX()+militaryLabel->getContentSize().width+5*sx,militaryLabel->getPositionY()-5*sx);
    this->addChild(gold,1);
    
}

void FindAccelerationLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(FindAccelerationLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(FindAccelerationLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void FindAccelerationLayer::onSureBuyClick(Ref* psender)
{
  
    int needgold = marketFindDataManager::getInstance()->findList->at(m_idx)->fastGold;
    requestAccelerMsg(marketFindDataManager::getInstance()->findList->at(m_idx)->findId);

    
}

void FindAccelerationLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/**************服务器*****************/
void FindAccelerationLayer::requestAccelerMsg(int findId)//请求加速寻访
{
    FindSpeedMsg* msg = new FindSpeedMsg(findId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindAccelerationLayer::onAccelerMsgProcess(EventCustom* msg)//获取加速寻访成功返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_FIND_FindSpeedUpResp)
    {
        if(message->state)//返回成功
        {
            log("确认加速");
            this->removeFromParent();
            broadMsg(CUSTOM_MARKER_SUREJAISU,__Integer::create(m_idx));
        }
      
    }
}
void FindAccelerationLayer::addEventListener()
{
    
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIND_FindSpeedUpResp).c_str(), CC_CALLBACK_1(FindAccelerationLayer::onAccelerMsgProcess, this));
}
void FindAccelerationLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
