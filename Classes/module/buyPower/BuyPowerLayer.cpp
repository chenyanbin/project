//
//  BuyPowerLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/11.
//
//

#include "BuyPowerLayer.hpp"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/buypowerModule/BuyPowerMsg.hpp"
#include "../../message/Decoding/buypowerModule/BuyPowerPageMsg.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
#include "../../common/StringUtil.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../goRecharge/GoRecharge.hpp"
BuyPowerLayer::BuyPowerLayer()
:m_gold(1)
{
}
BuyPowerLayer::~ BuyPowerLayer()
{
    
}
bool BuyPowerLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_DIALOG_BG1,Point::ZERO,true);
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
        this->isAnimation = true;

        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}
BuyPowerLayer* BuyPowerLayer::create()
{
    BuyPowerLayer* layer= new BuyPowerLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void BuyPowerLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    BuyPowerLayer* layer = BuyPowerLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_TWOLAYER_ZORDER);
}

void BuyPowerLayer::onEnter()
{
    BaseLayer::onEnter();
}
void BuyPowerLayer::onExit()
{
    BaseLayer::onExit();
}
void BuyPowerLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    this->requestBuyPowerPageMsg();
    
}
void BuyPowerLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void BuyPowerLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void BuyPowerLayer::onSetContent(int gold,int count,int power)
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    if (GlobalInfo::getInstance()->bodyPower<=800) {
        DictTips* data = DictTipsManager::getInstance()->getData(6001002);
        if (data) {
            string str = data->desc;
            string oldStr = "#%d#";
            int arr[3] = {gold,power,count};
            for(int i=1; i<=3;i ++)
            {
                oldStr = StringUtils::format("#%d#",i);
                str = StringUtil::replace(str, oldStr, StringUtils::format("%d",arr[i-1]));
            }
            str = StringUtil::replace(str, "<br>", "\n    ");
            Label* label = PublicShowUI::getLabelNumber(str.c_str(), PublicShowUI::getColor3b(COLOR_BROWN_WHITE), 22, false, false);
            label->setAnchorPoint(Point::ZERO);
            label->setPosition((layer->getContentSize().width/sx-label->getContentSize().width)/2,layer->getContentSize().height/sx/2+30);
            layer->addChild(label);
        }
        
    }else
    {
        DictTips* data = DictTipsManager::getInstance()->getData(6001003);
        if (data) {
            string str = data->desc;
            Label* label = PublicShowUI::getLabelNumber(str.c_str(), PublicShowUI::getColor3b(COLOR_BROWN_WHITE), 22, false, false);
            label->setAnchorPoint(Point::ZERO);
            label->setPosition(layer->getContentSize().width/2-label->getContentSize().width/2,layer->getContentSize().height/2+30);
            layer->addChild(label);
        }
        
    }
}

void BuyPowerLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(BuyPowerLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(BuyPowerLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void BuyPowerLayer::onSureBuyClick(Ref* psender)
{
    if(GlobalInfo::getInstance()->bodyPower <= 800)
    {
        if (m_gold>GlobalInfo::getInstance()->userGold) {
            GoRecharge::show();
            return;
        }
        requestBuyPowerMsg();
    }else{
        this->removeFromParent();
    }
}

void BuyPowerLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}

/*-------------------------------------------------------------连接服务器---------------------------------------------------*/
void BuyPowerLayer::requestBuyPowerPageMsg()//请求购买体力页
{
    Dialog::showServerLoading();
    BuyPowerPageMsg* msg = new BuyPowerPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void BuyPowerLayer::requestBuyPowerMsg()//请求购买体力页
{
    Dialog::showServerLoading();
    BuyPowerMsg* msg = new BuyPowerMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void BuyPowerLayer::onBuyPowerMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_ACCOUNT_BuyPowerPageResp)
    {
        if(message->state)//返回成功
        {
            int gold = message->byteStream->getInt();
            m_gold = gold;
            int count = message->byteStream->getInt();
            int power = message->byteStream->getInt();
            onSetContent(gold,count,power);
        }
    }
    else if(message->messageID == SCENSE_CLIENT_ACCOUNT_BuyPowerResp)
    {
        if(message->state)//返回成功
        {
            this->removeFromParent();
        }
    }
}
void BuyPowerLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_BuyPowerPageResp).c_str(), CC_CALLBACK_1(BuyPowerLayer::onBuyPowerMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_BuyPowerResp).c_str(), CC_CALLBACK_1(BuyPowerLayer::onBuyPowerMsgProcess, this));
}
