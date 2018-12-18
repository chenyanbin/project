//
//  StageBattleBox.cpp
//  FightPass
//
//  Created by zhangbin on 16/3/23.
//
//

#include "StageBattleBox.hpp"
#include "../../message/Decoding/stage/RequestStageBoxMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../protocol/Protocal.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
StageBattleBox::StageBattleBox()
:m_boxData(NULL)
,TAG_BOX(1)
,TAG_LEFTSTAR(2)
{
    
}
StageBattleBox::~StageBattleBox()
{

    m_boxData = NULL;
}

bool StageBattleBox::init(BattleBox* boxData)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        m_boxData = boxData;
        Sprite* bg = Sprite::create(IMG_STAGEBATTLEINFO_BOXBG);
        bg->setAnchorPoint(Point::ZERO);
        this->addChild(bg, 0, TAG_BG);
        this->setContentSize(bg->getContentSize());
        updateBox();
        bref = true;
    } while (false);
    return bref;
}

StageBattleBox* StageBattleBox::create(BattleBox* boxData)
{
    StageBattleBox* layer = new StageBattleBox();
    if(layer && layer->init(boxData))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void StageBattleBox::updateBox()
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
        
        box = TouchSprite::createWithPic(IMG_PUBLIC_BOXOPEN,this,callfuncN_selector(StageBattleBox::setOpenBox));
        box->setPosition(bg->getContentSize().width/2 - 25,bg->getContentSize().height/2 - 30);
    }
    else
    {
        box = TouchSprite::createWithPic(IMG_PUBLIC_BOXCLOSE,this,callfuncN_selector(StageBattleBox::setOpenBox));
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
    
    if(m_boxData->canOpenBoxId)
    {
        PublicShowUI::setTargetSwing(box);
    }
    
}

void StageBattleBox::setOpenBox(Node* psender)
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
    CommonEffect* commonEffect = CommonEffect::create("baoxiangdonghua",false,true,CC_CALLBACK_0(StageBattleBox::onEffectFinised, this,m_boxData->canOpenBoxId));
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    PublicShowUI::setTargetScale(commonEffect);
    Scene* scene = Director::getInstance()->getRunningScene();
    commonEffect->setPosition(VisibleRect::center());
    scene->addChild(commonEffect,SCENE_LAYER_ZORDER);
    
    
    
}
void StageBattleBox::onEffectFinised(int boxID)
{
    RequestStageBoxMsg* msg = new RequestStageBoxMsg(m_boxData->canOpenBoxId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void StageBattleBox::onMsgProcess(EventCustom* msg)
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
void StageBattleBox::onEnter()
{
    BaseLayer::onEnter();
}
void StageBattleBox::onExit()
{
    BaseLayer::onExit();
    
}
void StageBattleBox::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BATTLE_StageOpenBoxResp).c_str(), CC_CALLBACK_1(StageBattleBox::onMsgProcess, this));
}
void StageBattleBox::removeEventListener()
{
    BaseLayer::removeEventListener();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumChestButton);
}
