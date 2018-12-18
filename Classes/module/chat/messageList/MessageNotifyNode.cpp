//
//  MessageNotifyNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/30.
//
//
#include "MessageNotifyNode.h"
#include "../data/MessageData.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/TimeUtil.h"
MessageNotifyNode::MessageNotifyNode()
:m_data(NULL)
,TAG_BG(0)
,TAG_NICKNAME(1)
,userinfo(NULL)
,m_callBack(NULL)
{
    
}
MessageNotifyNode::~MessageNotifyNode()
{
    m_data = NULL;
}
bool MessageNotifyNode::init(YVMessagePtr data,ccMenuCallback callBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        m_data = data;
        m_callBack = callBack;
        userinfo = YVPlatform::getSingletonPtr()->getUInfoById(m_data->sendId);
        
        setBg();
        bref = true;
    } while (false);
    return bref;
}
MessageNotifyNode* MessageNotifyNode::create(YVMessagePtr data,ccMenuCallback callBack)
{
    MessageNotifyNode* item = new MessageNotifyNode();
    if(item && item->init(data,callBack))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    item = NULL;
    return item;
}
void MessageNotifyNode::setBg()
{
    TouchSprite*  bg = TouchSprite::createWithPic(IMG_CHAT_CELLBG, this, callfuncN_selector(MessageNotifyNode::onItemClick));
    bg->setSwallowTouches(false);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
    this->setContentSize(bg->getContentSize());
}
void MessageNotifyNode::onItemClick(Node* item)
{
    if(m_callBack)
    {
        m_callBack(this);
    }
}
void MessageNotifyNode::onExit()
{
    Node::onExit();
}
void MessageNotifyNode::onEnter()
{
    Node::onEnter();
}
void MessageNotifyNode::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
}
void MessageNotifyNode::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    setContent();
}
void MessageNotifyNode::setContent()
{
   
    Node* node = PublicShowUI::getAvatarHead("caopi", 0, 0);
    node->setAnchorPoint(Point::ZERO);
    
    node->setPosition(5, (this->getContentSize().height - node->getContentSize().height)/2);
    this->addChild(node,1);
    Label* nickName = NULL;//PublicShowUI::getLabel(m_data->us.c_str(),Color3B::WHITE,20,false,false);
    if(m_data->recvId == kChatChannel_World)
    {
        nickName = PublicShowUI::getLabel("世界",Color3B::WHITE,20,false,false);
    }
    else
    {
        nickName = PublicShowUI::getLabel("顾超",Color3B::WHITE,20,false,false);
    }
    nickName->setAnchorPoint(Point::ZERO);
    this->addChild(nickName,2,TAG_NICKNAME);
    nickName->setPosition(node->getPositionX() + node->getContentSize().width + 10 ,this->getContentSize().height - nickName->getContentSize().height - 3);
    
    setMsgContent();
    setTime();
    
  }
void MessageNotifyNode::setMsgContent()
{
    Node* nickLabel = this->getChildByTag(TAG_NICKNAME);
    string str = ".......";
    if(m_data->type == YVMessageTypeText)
    {
        str = ((YVTextMessagePtr)m_data)->text;
    }
    else if(m_data->type == YVMessageTypeAudio)
    {
       str = ((YVVoiceMessagePtr)m_data)->attach;
    }
    str = str.substr(0,15);
    str = userinfo != NULL ? userinfo->nickname + ":" + str : str;
    Label* msgLabel = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,20,false,false);
    msgLabel->setAnchorPoint(Point::ZERO);
    this->addChild(msgLabel,3);
    msgLabel->setPosition(nickLabel->getPositionX(),5);
}
void MessageNotifyNode::setTime()
{
    string str = "N周前";
    long timeStamp = time(0) - m_data->getTimeStamp();//单位是秒
    if(timeStamp < 60 )//1 分钟
    {
        str = "刚刚";
    }
    else if(timeStamp < 60 * 60 )//60分钟
    {
        str = "N分钟前";
    }
    else if(timeStamp < 24 * 60 * 60 )//1天
    {
        str = "N小时前";
    }
    else if(timeStamp < 7 * 24 * 60 * 60)
    {
        str = "N天前";
    }
    Label* timeLabel = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,20,false,false);
    timeLabel->setAnchorPoint(Point::ZERO);
    this->addChild(timeLabel,3);
    timeLabel->setPosition(this->getContentSize().width - timeLabel->getContentSize().width - 10,5);
}