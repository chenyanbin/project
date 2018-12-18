//
//  PowerLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/16.
//
//

#include "PowerLayer.hpp"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../Signin_Scene.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../common/commonEffect/CommonEffect.h"
#include "../../../../common/Dialog/Dialog.h"

#include "../../../../message/Decoding/signin/SigninPowerMsg.hpp"
#include "../../../../message/Decoding/signin/SigninPowerPageMsg.hpp"

#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/Protocal.h"
#include "../moneyDrawing/MoneyDrawingDataManager.h"
#include "../moneyDrawing/MoneyDrawingGiftLayer.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../../common/TimeUtil.h"
PowerLayer::PowerLayer()
:sx(1)
,TAG_RECEIVEBTN(1)
,TAG_POWERLABEL(2)
,m_status(0)
,m_nowTime(0)
,m_isReceive(false)
,powecount(1)
{
    
}
PowerLayer::~PowerLayer()
{
    
}

void PowerLayer::onExit()
{
    BaseLayer::onExit();
}
void PowerLayer::onEnter()
{
    BaseLayer::onEnter();
}
void PowerLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void PowerLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestPowerPageMsg();
}
bool PowerLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        //        this->setBackground(IMG_SIGNIN_LUXURY_LABEL2);
        this->createLayer();
        this->isAbleGuiding = true;
        bref = true;
    } while (false);
    return bref;
}
PowerLayer* PowerLayer::create()
{
    PowerLayer* layer = new PowerLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void PowerLayer::createLayer()
{
    Sprite* bg=Sprite::create(IMG_SIGNIN_POWERBG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg,true,true);
    bg->setTag(TAG_BG);
    this->addChild(bg);
    
    Sprite* bgWord=Sprite::create(IMG_SIGNIN_POWERWORD);
    bgWord->setAnchorPoint(Point::ZERO);
    bgWord->setPosition(50,bg->getContentSize().height/sx-bgWord->getContentSize().height - 50);
    bg->addChild(bgWord);
    
    
}
void PowerLayer::setReceiveMessage(int _status,long _nowTime)
{
    
    long long nowAllSec = _nowTime/1000;
    
    struct tm *l=TimeUtil::getDateByTimestamp(nowAllSec);//localtime(&nowAllSec);
    int now_hour = l->tm_hour;
    
    int power = 0;
    if (_status == 1)//可领取
    {
        power = powecount;
        
        //领取按钮
        Button* btn = Button::create(IMG_BUTTON_BIGYELLOW, IMG_BUTTON_BIGYELLOW, CC_CALLBACK_1(PowerLayer::onPersonClick, this));
        btn->setAnchorPoint(Point::ZERO);
        PublicShowUI::setDot(btn,Point::ZERO,false,DictFunctionEnumLucky);
        PublicShowUI::setTargetScale(btn);
        btn->setPosition(VisibleRect::center().x- btn->getContentSize().width/2,150*sx);
        this->addChild(btn,2,TAG_NOLINQU);
        Sprite* spr = Sprite::create(IMG_BUTTON_BIGLINGQU);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,5);
    }else if( _status == 2)//时间未到
    {
        Button* btn = Button::create(IMG_BUTTON_BIGYELLOW, IMG_BUTTON_BIGYELLOW, CC_CALLBACK_1(PowerLayer::onPersonClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPartEnabled(false);
        PublicShowUI::setTargetScale(btn);
        btn->setPosition(VisibleRect::center().x- btn->getContentSize().width/2,100*sx);
        this->addChild(btn,2,TAG_UNTIME);
        Sprite* spr = Sprite::create(IMG_BUTTON_BIGLINGQU);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,5);
    }else if (_status == 3)//领取过了
    {
        Button* btn = Button::create(IMG_BUTTON_BIGYELLOW, IMG_BUTTON_BIGYELLOW, CC_CALLBACK_1(PowerLayer::onPersonClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPartEnabled(false);
        PublicShowUI::setTargetScale(btn);
        btn->setPosition(VisibleRect::center().x- btn->getContentSize().width/2,150*sx);
        this->addChild(btn,2,TAG_SUCCEEDLINQU);
        Sprite* spr = Sprite::create(IMG_BUTTON_BIGLINGQU);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,5);
    }
    //体力值
    string powerstr = StringUtils::format("%d",power);
    Label* powerstrlabel = (Label*)this->getChildByTag(TAG_POWERLABEL);
    if(powerstrlabel)
    {
        powerstrlabel->setString(powerstr);
    }
    else
    {
        powerstrlabel = PublicShowUI::getLabel(powerstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),30,false,false);
        powerstrlabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(powerstrlabel);
        powerstrlabel->setPosition( VisibleRect::center().x + 110*sx,103*sx);
        this->addChild(powerstrlabel,3,TAG_POWERLABEL);
    }
    
    //领取时间
    string firstTime = "12:00 - 14:00";
    Label* firstTimelabel = NULL;
    string secondtTime = "18:00 - 20:00";
    Label* secondtTimelabel = NULL;
    string thirdTime = "21:00 - 23:00";
    Label* thirdTimelabel = NULL;
    
    if (m_isReceive == true) {
        return;
    }
    Sprite* timeBg = Sprite::create(IMG_SIGNIN_TIMEBG);
    timeBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(timeBg);
    timeBg->setPosition(100*sx,30*sx);
    this->addChild(timeBg,2);
    
    if(now_hour>=12 && now_hour < 14)
    {
        firstTimelabel = PublicShowUI::getLabel(firstTime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),22,false,false);
        secondtTimelabel = PublicShowUI::getLabel(secondtTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        thirdTimelabel = PublicShowUI::getLabel(thirdTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    }else if (now_hour>=18 && now_hour < 20)
    {
        firstTimelabel = PublicShowUI::getLabel(firstTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        secondtTimelabel = PublicShowUI::getLabel(secondtTime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),22,false,false);
        thirdTimelabel = PublicShowUI::getLabel(thirdTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    }else if (now_hour>=21 && now_hour < 23)
    {
        firstTimelabel = PublicShowUI::getLabel(firstTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        secondtTimelabel = PublicShowUI::getLabel(secondtTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        thirdTimelabel = PublicShowUI::getLabel(thirdTime.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),22,false,false);
    }else
    {
        
        firstTimelabel = PublicShowUI::getLabel(firstTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        secondtTimelabel = PublicShowUI::getLabel(secondtTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
        thirdTimelabel = PublicShowUI::getLabel(thirdTime.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),22,false,false);
    }
    firstTimelabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(firstTimelabel);
    firstTimelabel->setPosition(160,5);
    timeBg->addChild(firstTimelabel,3);
    
    secondtTimelabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(secondtTimelabel);
    secondtTimelabel->setPosition(firstTimelabel->getPositionX()+firstTimelabel->getContentSize().width+30,firstTimelabel->getPositionY());
    timeBg->addChild(secondtTimelabel,3);
    
    thirdTimelabel->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(thirdTimelabel);
    thirdTimelabel->setPosition(secondtTimelabel->getPositionX()+secondtTimelabel->getContentSize().width+30,secondtTimelabel->getPositionY());
    timeBg->addChild(thirdTimelabel,3);
    
    //体力图标
    Sprite* powerSpr=Sprite::create(IMG_ICON_PUBLIC_POWER);
    powerSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(powerSpr);
    powerSpr->setPosition( VisibleRect::center().x + 60*sx,100*sx);
    this->addChild(powerSpr);
    
}
void PowerLayer::onPersonClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    switch (tag)
    {
        case TAG_NOLINQU:
            requestPowerMsg();
            break;
        case TAG_UNTIME:
            NoticeManager::getInstance()->showNotice("时间未到");
            break;
        case TAG_SUCCEEDLINQU:
            NoticeManager::getInstance()->showNotice("本时间段已成功领取，请下个时间到在领");
            break;
        default:
            break;
    }
    
}
//--------------------------------------------连接服务器----------------------------------------------------------//

void PowerLayer::requestPowerPageMsg()//请求体力页
{
    Dialog::showServerLoading();
    SigninPowerPageMsg* msg = new SigninPowerPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void PowerLayer::requestPowerMsg()//请求获取体力
{
    Dialog::showServerLoading();
    SigninPowerMsg* msg = new SigninPowerMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void PowerLayer::onPowerMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_ACCOUNT_ReceivePowerPageResp)
    {
        if(message->state)//返回成功
        {
            m_status = message->byteStream->getByte();
            m_nowTime = message->byteStream->getLong();
            powecount = message->byteStream->getInt();
            log("%ld,",m_nowTime);
            setReceiveMessage(m_status,m_nowTime);
        }
    }
    else if (message->messageID == SCENSE_CLIENT_ACCOUNT_ReceivePowerResp)
    {
        if(message->state)//返回成功
        {
            m_isReceive = true;
            m_status = 3;
            Button* btn = (Button*)this->getChildByTag(TAG_NOLINQU);
            btn->removeFromParent();
            setReceiveMessage(m_status,m_nowTime);
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumBanquet));
        }
    }
}
void PowerLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_ReceivePowerPageResp).c_str(), CC_CALLBACK_1(PowerLayer::onPowerMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_ReceivePowerResp).c_str(), CC_CALLBACK_1(PowerLayer::onPowerMsgProcess, this));
}
void PowerLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}