//
//  RankAddFriendLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/2/1.
//
//

#include "RankAddFriendLayer.hpp"
#include "../../common/TouchSprite/Button.h"
#include "../../commonData/dictData/DictSkill/DictSkillManager.h"
#include "../../message/Decoding/chat/AddFriendMsg.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../protocol/Protocal.h"
#include "../../common/noticeManager/NoticeManager.h"
RankAddFriendLayer::RankAddFriendLayer()
:sx(0)
,m_roleId(0)
,m_heroName("")
{
    
}
RankAddFriendLayer::~ RankAddFriendLayer()
{
    
}
void RankAddFriendLayer::onExit()
{
    BaseLayer::onExit();
}
void RankAddFriendLayer::onEnter()
{
    BaseLayer::onEnter();
}
void RankAddFriendLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void RankAddFriendLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool RankAddFriendLayer::init(long heriId, string heroName)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        m_roleId = heriId;
        m_heroName = heroName;
        this->setBackground(IMG_DIALOG_BG);
        this->isAnimation = false;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
RankAddFriendLayer* RankAddFriendLayer::create(long heriId, string heroName)
{
    RankAddFriendLayer* layer = new RankAddFriendLayer();
    if(layer && layer->init(heriId, heroName))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void RankAddFriendLayer::show(long heriId, string heroName )
{
    RankAddFriendLayer* layer = RankAddFriendLayer::create(heriId, heroName);
    if(layer)
    {
        Scene* scene = Director::getInstance()->getRunningScene();
        layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
        scene->addChild(layer,SCENE_LAYER_ZORDER);
    }
}
void RankAddFriendLayer::createLayer()
{
    
    string desc = "是否添加"+ m_heroName + "为好友？";
    Label* addlabel = PublicShowUI::getLabel(desc.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),22,false,false);
    addlabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(addlabel);
    addlabel->setPosition(this->getContentSize().width/2-addlabel->getContentSize().width/2,220*sx);
    this->addChild(addlabel,3);
    
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,70*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(RankAddFriendLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,70*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(RankAddFriendLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void RankAddFriendLayer::onSureBuyClick(Ref* psender)
{
    onAddFriendClick(m_roleId);
}

void RankAddFriendLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void RankAddFriendLayer::onAddFriendClick(long userId)
{
    
    AddFriendMsg* msg = new AddFriendMsg(userId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void RankAddFriendLayer::onaddfriendProcess(EventCustom* msg)
{

    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendAddResp)
    {
        if(message->state)//返回成功
        {
            this->removeFromParent();
            NoticeManager::getInstance()->showNotice("添加好友请求发送成功");
        }
    }

}

void RankAddFriendLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendAddResp).c_str(), CC_CALLBACK_1(RankAddFriendLayer::onaddfriendProcess, this));

}
void RankAddFriendLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}