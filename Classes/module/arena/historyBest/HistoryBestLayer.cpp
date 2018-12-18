//
//  HistoryBestLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/5.
//
//

#include "HistoryBestLayer.hpp"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../message/Decoding/arena/ArenaRewardMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/PublicShowUI.h"
HistoryBestLayer::HistoryBestLayer()
:m_nowOrder(0)
,m_historyOrder(0)
,m_goldPrize(0)
,m_changeValue(0)
,TAG_CONTENT(1)
{
    
}
HistoryBestLayer::~HistoryBestLayer()
{
    
}
bool HistoryBestLayer::init(int nowOrder,int historyOrder,int goldPrize)
{
    m_nowOrder = nowOrder;
    m_historyOrder = historyOrder;
    m_goldPrize = goldPrize;
    
    setBackground(IMG_DIALOG_BG,Point::ZERO,false);
    
    Sprite* contentSpr = Sprite::create(IMG_ARENA_HISTORYBEST_CONTENT);
    contentSpr->setAnchorPoint(Point::ZERO);
    contentSpr->setPosition((this->getContentSize().width - contentSpr->getContentSize().width)/2, (this->getContentSize().height - contentSpr->getContentSize().height)/2);
    this->addChild(contentSpr,1,TAG_CONTENT);
    
    Sprite* title = Sprite::create(IMG_ARENA_HISTORYBEST_WORD);
    title->setPosition(this->getContentSize().width/2, this->getContentSize().height);
    this->addChild(title,2);

    
    
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(HistoryBestLayer::onConfirmClick, this));
    btn->setPosition(this->getContentSize().width/2, btn->getContentSize().height/2 + 15);
    btn->addTitle(IMG_BUTTON_CONFIRM_LABEL,IMG_BUTTON_CONFIRM_LABEL);
    this->addChild(btn,3);
    

    this->setClickEnabled(true);
    return true;
}
void HistoryBestLayer::onConfirmClick(Ref* pSender)
{
   
    
    NoticeManager::getInstance()->showNotice("奖励已通过邮件发送",NoticeManager::COLOR_GREEN);
    this->removeFromParent();
    
}
void HistoryBestLayer::onEnter()
{
    BaseLayer::onEnter();
}
void HistoryBestLayer::onExit()
{
    BaseLayer::onExit();
}
void HistoryBestLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void HistoryBestLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    ArenaRewardMsg* msg = new ArenaRewardMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void HistoryBestLayer::onMsgProcess(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_ARENA_ArenaRewardResp)
    {
//        historyHighestRank	历史最高排名	int	Y
//        currentRank	当前排名	int	Y
//        reward	奖励	int	Y
//        upOrDown	名次变化情况	int
        this->m_historyOrder = msg->byteStream->getInt();
        this->m_nowOrder = msg->byteStream->getInt();
        this->m_goldPrize = msg->byteStream->getInt();
        this->m_changeValue = msg->byteStream->getInt();
        this->setContent();
    }
}
void HistoryBestLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaRewardResp).c_str(), CC_CALLBACK_1(HistoryBestLayer::onMsgProcess, this));
}
void HistoryBestLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
HistoryBestLayer* HistoryBestLayer::create(int nowOrder,int historyOrder,int goldPrize)
{
    HistoryBestLayer* layer = new HistoryBestLayer();
    if(layer && layer->init(nowOrder, historyOrder, goldPrize))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_FREE(layer);
    layer = NULL;
    return layer;
}
void HistoryBestLayer::setContent()
{
    Node* contentSpr = this->getChildByTag(TAG_CONTENT);
    
    //q金币奖励
    Sprite* goldSpr = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    goldSpr->setAnchorPoint(Point::ZERO);
    contentSpr->addChild(goldSpr);
    
    string str = PublicShowUI::numberToString(this->m_goldPrize);
    Label* goldLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    goldLabel->setAnchorPoint(Point::ZERO);
    goldLabel->setPosition(goldSpr->getContentSize().width, 0);
    goldSpr->addChild(goldLabel);
    goldSpr->setPosition(100, 0);
    
    //当前排名
    str = PublicShowUI::numberToString(this->m_nowOrder);
    Label* nowLabel = PublicShowUI::getLabel(str.c_str(),Color3B::RED,24,false,false);
    nowLabel->setAnchorPoint(Point::ZERO);
    nowLabel->setPosition(100, goldLabel->getPositionY() + goldLabel->getContentSize().height + 20);
    contentSpr->addChild(nowLabel);
    
    Sprite* arrow = NULL;
    int changeValue = this->m_changeValue;

    if(changeValue> 0)
    {
        arrow = Sprite::create(IMG_GENERALS_EXPERIENCE_ARROW);
        arrow->setAnchorPoint(Point(0.5,0.5));
        arrow->setRotation(-90);
    
        str = "[    " + PublicShowUI::numberToString(changeValue) + "]";
    }
    else if(changeValue < 0)
    {
        str = "[下降" + PublicShowUI::numberToString(changeValue) + "]";
    }
    else
    {
        str = "[排名未变]";
    }
    
    Label* changeLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WHITE_YELLOW),24,false,false);
    changeLabel->setAnchorPoint(Point::ZERO);
    changeLabel->setPosition(nowLabel->getPositionX() + nowLabel->getContentSize().width, nowLabel->getPositionY());
    contentSpr->addChild(changeLabel);
    if(arrow)
    {
        arrow->setPosition(changeLabel->getPositionX() + arrow->getContentSize().width/2 + 10, changeLabel->getPositionY() + arrow->getContentSize().height/2 + 10);
        contentSpr->addChild(arrow);
    }
    
    
    //历史排名
    Node* historyLabel = PublicShowUI::getNumbers(m_historyOrder,IMG_PUBLIC_NUMBER2);
    historyLabel->setScale(.4);
    historyLabel->setAnchorPoint(Point::ZERO);
    historyLabel->setPosition(140, nowLabel->getPositionY() + nowLabel->getContentSize().height + 13);
    contentSpr->addChild(historyLabel);
    
    
}
