//
//  SweepBoxLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/7/15.
//
//

#include "SweepBoxLayer.h"
#include "../../message/Decoding/stage/RequestStageBoxMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../protocol/Protocal.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
SweepBoxLayer::SweepBoxLayer()
:m_boxData(NULL)
,TAG_BOX(1)
,TAG_LEFTSTAR(2)
{
    
}
SweepBoxLayer::~SweepBoxLayer()
{
    log("~StageLayer ~StageLayer");
    m_boxData = NULL;
}

bool SweepBoxLayer::init(BattleBoxData* boxData)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        m_boxData = boxData;
        Sprite* bg = Sprite::create(IMG_SWEEP_STARBG);
        bg->setAnchorPoint(Point::ZERO);
        this->addChild(bg, 0, TAG_BG);
        this->setContentSize(bg->getContentSize());
        updateBox();
        bref = true;
    } while (false);
    return bref;
}

SweepBoxLayer* SweepBoxLayer::create(BattleBoxData* boxData)
{
    SweepBoxLayer* layer = new SweepBoxLayer();
    if(layer && layer->init(boxData))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void SweepBoxLayer::updateBox()
{
    if(this->getChildByTag(TAG_BOX))
    {
        this->removeChildByTag(TAG_BOX);
        this->removeChildByTag(TAG_LEFTSTAR);
    }
    Node* bg = this->getChildByTag(TAG_BG);
    Sprite* box = NULL;
    
    if(m_boxData->curStarCount > 0 && m_boxData->canOpenBoxId == 0)
    {
 
        box = TouchSprite::createWithPic(IMG_PUBLIC_BOXOPEN,this,callfuncN_selector(SweepBoxLayer::setOpenBox));
        box->setPosition(bg->getContentSize().width/2 - 25,bg->getContentSize().height/2 - 30);
    }
    else
    {
        box = TouchSprite::createWithPic(IMG_PUBLIC_BOXCLOSE,this,callfuncN_selector(SweepBoxLayer::setOpenBox));
        ((TouchSprite*)box)->setSwallowTouches(true);
        ((TouchSprite*)box)->isButtonMode = true;
        box->setPosition(bg->getContentSize().width/2 - 15,bg->getContentSize().height/2 - 10);
    }
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumChestButton, box);
    box->setScale(.5);
    box->setContentSize(box->getContentSize() * .5);
    box->setAnchorPoint(Point(0.5,0.5));
    this->addChild(box,1,TAG_BOX);

    
    string countStr= PublicShowUI::numberToString(m_boxData->curStarCount) + "/" + PublicShowUI::numberToString(m_boxData->starCountMax);
    Label* countLabel = PublicShowUI::getLabel(countStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWM_WRITE),20,false,false);
    countLabel->setAnchorPoint(Point::ZERO);
    countLabel->setPosition(40,bg->getContentSize().height - countLabel->getContentSize().height - 10);
    this->addChild(countLabel,4);
    
//    Sprite* leftStarSpr = Sprite::create(IMG_SWEEP_STAR);
//    leftStarSpr->setAnchorPoint(Point::ZERO);
//    leftStarSpr->setPosition(box->getPositionX()+box->getContentSize().width/2-leftStarSpr->getContentSize().width-13,box->getContentSize().height-90);
//    this->addChild(leftStarSpr,2,TAG_LEFTSTAR);
//    
//    string leftCountStr = PublicShowUI::numberToString(m_boxData->canOpenCount);
//    Label* powerLabel = PublicShowUI::getLabel(leftCountStr.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_BLACK),20,false,false);
//    powerLabel->setAnchorPoint(Point::ZERO);
//    powerLabel->setPosition(leftStarSpr->getContentSize().width/2-5,leftStarSpr->getContentSize().height/2-12);
//    leftStarSpr->addChild(powerLabel);
    
   if(m_boxData->canOpenBoxId)
   {
       PublicShowUI::setTargetSwing(box);
   }
    
}

void SweepBoxLayer::setOpenBox(Node* psender)
{
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumChestButton);
    if(m_boxData->curStarCount > 0 && m_boxData->canOpenBoxId == 0)
    {
        return;
    }

    if(!m_boxData->canOpenBoxId)
    {
        return;
    }
     Dialog::showServerLoading(3);
    CommonEffect* commonEffect = CommonEffect::create("baoxiangdonghua",false,true,CC_CALLBACK_0(SweepBoxLayer::onEffectFinised, this,m_boxData->canOpenBoxId));
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(commonEffect);
    Scene* scene = Director::getInstance()->getRunningScene();
    commonEffect->setPosition(VisibleRect::center());
    scene->addChild(commonEffect,SCENE_LAYER_ZORDER);
    
   
    
}
void SweepBoxLayer::onEffectFinised(int boxID)
{
    RequestStageBoxMsg* msg = new RequestStageBoxMsg(m_boxData->canOpenBoxId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void SweepBoxLayer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(!message->state)
    {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_BATTLE_StageOpenBoxResp)
    {
        int canOpenCount = message->byteStream->get();
        int canOpenBoxId = message->byteStream->getInt();
        this->m_boxData->canOpenCount = canOpenCount;
        this->m_boxData->canOpenBoxId = canOpenBoxId;
        this->updateBox();
//        NoticeManager::getInstance()->showNotice("领取成功",NoticeManager::COLOR_GREEN);
    }
}
void SweepBoxLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SweepBoxLayer::onExit()
{
    BaseLayer::onExit();
    
}
void SweepBoxLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_StageOpenBoxResp).c_str(), CC_CALLBACK_1(SweepBoxLayer::onMsgProcess, this));
}
void SweepBoxLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumChestButton);
}
