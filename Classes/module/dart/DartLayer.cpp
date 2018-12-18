//
//  DartLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/7.
//
//

#include "DartLayer.hpp"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/dart/DartMsg.hpp"
#include "../../message/Decoding/dart/DartPageMsg.hpp"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/dictData/DictTips/DictTipsManager.h"
#include "../../common/StringUtil.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../goRecharge/GoRecharge.hpp"
DartLayer::DartLayer()
:TAG_NODE(10)
,m_allCount(1)
,coustGold(1)
{
}
DartLayer::~ DartLayer()
{
   
}
bool DartLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_DARK_DARKBG,Point::ZERO,false);
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
//
        onSetButton();
        bref = true;
    } while (false);
    return bref;
}
DartLayer* DartLayer::create()
{
    DartLayer* layer= new DartLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void DartLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    DartLayer* layer = DartLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,SCENE_LAYER_ZORDER + 1);
}

void DartLayer::onEnter()
{
    BaseLayer::onEnter();
}
void DartLayer::onExit()
{
    BaseLayer::onExit();
}
void DartLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    requestDarPagetMsg();
    
}
void DartLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGrabButton);
}

void DartLayer::onSetButton()
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);

    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(DartLayer::onclick, this));
    btn->setAnchorPoint(Point::ZERO);
    layer->addChild(btn,1);
    btn->setPosition(this->getContentSize().width/2-btn->getContentSize().width/2,50);
   
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumGrabButton, btn);
    Sprite* btnSpr = Sprite::create(IMG_DARK_DARKROBWORD);
    btnSpr->setAnchorPoint(Point::ZERO);
    btn->addChild(btnSpr,4);

}

void DartLayer::onSetContent(int count,int allCount,int glod)
{
    coustGold = glod;
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
   
    layer->removeChildByTag(TAG_NODE);
    
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);

    string str = StringUtils::format("抢夺次数：%d/%d   花费 %d ",allCount-count,allCount,glod);
    Label* label = PublicShowUI::getLabelNumber(str.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE), 22, false, false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(Point::ZERO);
    node->addChild(label,1);
    
    Sprite* spr = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    spr->setAnchorPoint(Point(0,0.2));
    spr->setPosition(label->getPositionX() + label->getContentSize().width,label->getPositionY());
    node->addChild(spr);
    
    Size size = label->getContentSize();
    size.width = spr->getPositionX() + spr->getContentSize().width;
    node->setContentSize(size);
    
    node->setPosition(350 - node->getContentSize().width/2,20);
    layer->addChild(node,2,TAG_NODE);
}
void DartLayer::onclick(Ref* psender)
{
    
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGrabButton);
    if (coustGold>GlobalInfo::getInstance()->userGold) {
        GoRecharge::show();
        return;
    }
    requestDarMsg();
}
void DartLayer::setBoom(int multiple)
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    //特效
    CommonEffect* commonEffect = CommonEffect::create("jiebiaodonghua");
    commonEffect->setAnchorPoint(Point::ZERO);
//    commonEffect->isAutoStop;
    commonEffect->setPosition(350 - commonEffect->getContentSize().width/2,300-commonEffect->getContentSize().height/2);
    layer->addChild(commonEffect,30);
    
    DelayTime* delaycommonEffect = DelayTime::create(1);
    RemoveSelf* removecommonEffect = RemoveSelf::create();
    commonEffect->runAction(Sequence::create(delaycommonEffect, removecommonEffect,NULL));
    
    //暴击
    if (multiple>1) {
        Sprite* critSpr = Sprite::create(IMG_BATTLE_CRIT);
        critSpr->setScale(.1);
        critSpr->setPosition(320 , 300);
        layer->addChild(critSpr,int(layer->getChildrenCount() + 1));
        
        string str = StringUtils::format("%d倍",multiple);
        Label* label = PublicShowUI::getLabelNumber(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT), 80, false, false);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(critSpr->getContentSize().width,0);
        critSpr->addChild(label,1);
        
        ScaleTo* scaleTo = ScaleTo::create(.05, 1.5);
        ScaleTo* scaleTo2 = ScaleTo::create(.08, 1);
        DelayTime* delay = DelayTime::create(.5);
        RemoveSelf* remove = RemoveSelf::create();
        critSpr->runAction(Sequence::create(scaleTo,scaleTo2,delay, remove,NULL));
    }
    
}
/*-------------------------------------------------------------连接服务器---------------------------------------------------*/
void DartLayer::requestDarPagetMsg()
{
    Dialog::showServerLoading();
    DartPageMsg* msg = new DartPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void DartLayer::requestDarMsg()
{
    Dialog::showServerLoading();
    DartMsg* msg = new DartMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void DartLayer::onDartPageMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_Gemstone_GemstonePageResp)
    {
        if(message->state)//返回成功
        {
            int count = message->byteStream->getByte();
            m_allCount = message->byteStream->getByte();
            int gold = message->byteStream->getInt();
            onSetContent(count,m_allCount,gold);
        }
    }
    else if(message->messageID == SCENSE_CLIENT_Gemstone_GemstoneGrabResp)
    {
        if(message->state)//返回成功
        {
            int count = message->byteStream->getByte();
            int gold = message->byteStream->getInt();
            int boomAttact = message->byteStream->getInt();
            
            onSetContent(count,m_allCount,gold);
            setBoom(boomAttact);
        }
    }

}
void DartLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_Gemstone_GemstonePageResp).c_str(), CC_CALLBACK_1(DartLayer::onDartPageMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_Gemstone_GemstoneGrabResp).c_str(), CC_CALLBACK_1(DartLayer::onDartPageMsgProcess, this));
}
void DartLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
