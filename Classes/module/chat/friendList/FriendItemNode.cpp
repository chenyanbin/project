//
//  FriendItemNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/1.
//
//

#include "FriendItemNode.h"
#include "../data/MessageData.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/TimeUtil.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../protocol/UserCustomEvent.h"
//#include "../../../net/NetworkDataProcessing.h"
FriendItemNode::FriendItemNode()
:m_data(NULL)
,friendData(NULL)
,TAG_BG(0)
,TAG_NICKNAME(1)
,sx(1)

{
    
}
FriendItemNode::~FriendItemNode()
{
    m_data = NULL;
}
bool FriendItemNode::init(MessageData* data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        friendData=data;
        setBg();
        bref = true;
    } while (false);
    return bref;
}
FriendItemNode* FriendItemNode::create(MessageData* data)
{
    FriendItemNode* item = new FriendItemNode();
    if(item && item->init(data))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    item = NULL;
    return item;
}
void FriendItemNode::setBg()
{
    TouchSprite*  bg = TouchSprite::createWithPic(IMG_CHAT_CELLBG, this, callfuncN_selector(FriendItemNode::onItemClick));
    bg->setSwallowTouches(false);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    
    this->setContentSize(bg->getContentSize());
}
void FriendItemNode::onItemClick(Node* item)
{
    this->broadMsg(CUSTOM_CHAT_FRIEND_CLICK,__Integer::create(friendData->yayaId));
}
void FriendItemNode::onExit()
{
    BaseLayer::onExit();
}
void FriendItemNode::onEnter()
{
    BaseLayer::onEnter();
}
void FriendItemNode::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FriendItemNode::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setContent();
}
void FriendItemNode::setContent()
{
    DictHero*data= DictHeroManager::getInstance()->getData(friendData->headId);
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
    str=friendData->nickName;
    if (str=="") {
        str=friendData->userid;
    }
    Label* nickName = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,20,false,false);
    nickName->setAnchorPoint(Point::ZERO);
    this->addChild(nickName,2);
    nickName->setPosition(head->getPositionX() + head->getContentSize().width + 20 ,this->getContentSize().height - nickName->getContentSize().height - 3 );
    
    Sprite* levelSpr = Sprite::create(IMG_CHAT_LV);
    levelSpr->setAnchorPoint(Point::ZERO);
    levelSpr->setPosition(nickName->getPositionX()-10, nickName->getPositionY() - levelSpr->getContentSize().height);
    this->addChild(levelSpr,3);
    string valueStr = PublicShowUI::numberToBigNumString(friendData->level);
    Label* valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, levelSpr->getContentSize().height / 2);
    levelSpr->addChild(valueLabel);
    
    
    Sprite* combatPower=Sprite::create(IMG_PUBLIC_MILITARY);
    combatPower->setAnchorPoint(Point::ZERO);
    combatPower->setPosition(levelSpr->getPositionX(), levelSpr->getPositionY() - combatPower->getContentSize().height-5);
    this->addChild(combatPower,4);
    
    valueStr = PublicShowUI::numberToBigNumString(friendData->combat);
    valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, combatPower->getContentSize().height / 2);
    combatPower->addChild(valueLabel);
    
    
    Button* btn=Button::create(IMG_CHAT_MENU, "", CC_CALLBACK_1(FriendItemNode::onBtnClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(this->getContentSize().width-btn->getContentSize().width-20,15);
    this->addChild(btn,4);

}
void FriendItemNode::onBtnClick(Ref* psender)
{    
    this->broadMsg(CUSTOM_DELETE_FRIEND,__String::create(friendData->userid));
}