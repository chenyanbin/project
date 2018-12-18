//
//  MessageItem.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/24.
//
//

#include "MessageItem.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/customButton/CustomButton.hpp"
#include "../../../YVSDK/YVPlatform.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../message/Decoding/chat/AddFriendMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"
using namespace YVSDK;
MessageItem::MessageItem()
:m_data(NULL)
,TAG_BG(0)

{
    
}
MessageItem::~MessageItem()
{
    CC_SAFE_RELEASE_NULL(m_data);
}
bool MessageItem::init(MessageData* data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_data = data;
        CC_SAFE_RETAIN(m_data);
        setBg();
        bref = true;
    } while (false);
    return bref;
}
MessageItem* MessageItem::create(MessageData* data)
{
    MessageItem* item = new MessageItem();
    if(item && item->init(data))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    item = NULL;
    return item;
}
void MessageItem::setBg()
{
    Sprite* bg = Sprite::create(IMG_CHAT_CELLBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);

    this->setContentSize(bg->getContentSize());
}
void MessageItem::onExit()
{
    BaseLayer::onExit();
}
void MessageItem::onEnter()
{
    BaseLayer::onEnter();
}
void MessageItem::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void MessageItem::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setContent();
}
void MessageItem::setContent()
{
    float sx = 1;//GlobalInfo::getInstance()->screenScaleX;
    DictHero*data= DictHeroManager::getInstance()->getData(m_data->headId);
    string str="";
    if (data) {
        str=data->headResource;
    }else
    {
        str="caopi";
    }
    const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, str.c_str());
    
    UserEquipLayer* head=UserEquipLayer::create(imgPath,1,false);
    //    Node* node = PublicShowUI::getAvatarHead(str.c_str(), 0, 0);
    head->setAnchorPoint(Point::ZERO);
    head->setScale(0.7);
    head->setContentSize(head->getContentSize()*0.7);
    head->setPosition(5, (this->getContentSize().height - head->getContentSize().height)/2);
    
    this->addChild(head,1);
    str=m_data->nickName;
    
    Label* nickName = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,20,false,false);
    nickName->setAnchorPoint(Point::ZERO);
    this->addChild(nickName,2);
    nickName->setPosition(head->getPositionX() + head->getContentSize().width + 20 ,this->getContentSize().height - nickName->getContentSize().height - 3 );
    
    Sprite* levelSpr = Sprite::create(IMG_CHAT_LV);
    levelSpr->setAnchorPoint(Point::ZERO);
    levelSpr->setPosition(nickName->getPositionX()-10, nickName->getPositionY() - levelSpr->getContentSize().height);
    this->addChild(levelSpr,3);
    string valueStr = PublicShowUI::numberToBigNumString(m_data->level);
    Label* valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, levelSpr->getContentSize().height / 2);
    levelSpr->addChild(valueLabel);
    
    
    Sprite* combatPower=Sprite::create(IMG_PUBLIC_MILITARY);
    combatPower->setAnchorPoint(Point::ZERO);
    combatPower->setPosition(levelSpr->getPositionX(), levelSpr->getPositionY() - combatPower->getContentSize().height-5);
    this->addChild(combatPower,4);
    
    valueStr = PublicShowUI::numberToBigNumString(m_data->combat);
    valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, combatPower->getContentSize().height / 2);
    combatPower->addChild(valueLabel);

//    CustomButton*  touchSprite = TouchSprite::createWithPic(IMG_PUBLIC_BUTTON_TWO_RED, this, callfuncN_selector(MessageItem::onAddFriendClick));
    CustomButton* touchSprite = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(MessageItem::onAddFriendClick, this));
    
    if(touchSprite)
    {
           touchSprite->setAnchorPoint(Point::ZERO);
        touchSprite->addTitle(IMG_BUTTON_REQUESTTITLE, IMG_BUTTON_REQUESTTITLE);
     
        touchSprite->setPosition(this->getContentSize().width - touchSprite->getContentSize().width - 15 * sx, 15 * sx);
        this->addChild(touchSprite,4);
    }
}
//后台协议部分
void MessageItem::onAddFriendClick(Ref* pSender)
{
    CustomButton* touchSprite = (CustomButton*)pSender;
    touchSprite->setEnabled(false);
    long userId= atol(m_data->userid.c_str());
    AddFriendMsg* msg = new AddFriendMsg(userId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void MessageItem::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendAddResp)
    {
        log("申请好友成功");
    }
}
void MessageItem::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendAddResp).c_str(), CC_CALLBACK_1(MessageItem::onMsgProcess, this));
}
void MessageItem::removeEventListener()
{
    BaseLayer::removeEventListener();
}

