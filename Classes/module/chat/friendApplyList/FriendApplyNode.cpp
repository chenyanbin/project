//
//  FriendApplyNode.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/1.
//
//

#include "FriendApplyNode.h"
#include "../data/MessageData.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/TimeUtil.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"

#include "../../../message/Decoding/chat/FriendRefuseMsg.h"
#include "../../../message/Decoding/chat/FriendAgreeMsg.h"
FriendApplyNode::FriendApplyNode()
:m_data(NULL)
,cellNode(NULL)
,cellBg2(NULL)
,TAG_BG(0)
,TAG_NICKNAME(1)
,TAG_AGREE(2)
,TAG_REFUSE(3)
{
    
}
FriendApplyNode::~FriendApplyNode()
{
    m_data = NULL;
}
bool FriendApplyNode::init(MessageData* data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        m_data=data;
        setBg();
        bref = true;
    } while (false);
    return bref;
}
FriendApplyNode* FriendApplyNode::create(MessageData* data)
{
    FriendApplyNode* item = new FriendApplyNode();
    if(item && item->init(data))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    item = NULL;
    return item;
}
void FriendApplyNode::setBg()
{
    Sprite*  bg = Sprite::create(IMG_CHAT_CELLBG);
    this->setContentSize(bg->getContentSize());
}
void FriendApplyNode::onItemClick(Node* item)
{
    
}
void FriendApplyNode::onExit()
{
    BaseLayer::onExit();
}
void FriendApplyNode::onEnter()
{
    BaseLayer::onEnter();
}
void FriendApplyNode::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FriendApplyNode::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setContent();
}
void FriendApplyNode::setContent()
{
//    float sx = 1;//GlobalInfo::getInstance()->screenScaleX;
    
//    cellNode=Node::create();
//    cellNode->setContentSize(this->getContentSize());
//    cellNode->setAnchorPoint(Point::ZERO);
//    this->addChild(cellNode);
    
//    Layer * containlayer = Layer::create();
    
    cellNode=Sprite::create(IMG_CHAT_CELLBG);
    cellNode->setAnchorPoint(Point::ZERO);
    this->addChild(cellNode);
    
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
    head->setAnchorPoint(Point::ZERO);
    head->setScale(0.7);
    head->setContentSize(head->getContentSize()*0.7);
    head->setPosition(15, (this->getContentSize().height - head->getContentSize().height)/2);
    cellNode->addChild(head,1);
    
    str=m_data->nickName;
    
    Label* nickName = PublicShowUI::getLabel(str.c_str(),Color3B::WHITE,20,false,false);
    nickName->setAnchorPoint(Point::ZERO);
    cellNode->addChild(nickName,2);
    nickName->setPosition(head->getPositionX() + head->getContentSize().width + 20 ,this->getContentSize().height - nickName->getContentSize().height - 3 );
    
    Sprite* levelSpr = Sprite::create(IMG_CHAT_LV);
    levelSpr->setAnchorPoint(Point::ZERO);
    levelSpr->setPosition(nickName->getPositionX()-10, nickName->getPositionY() - levelSpr->getContentSize().height);
    cellNode->addChild(levelSpr,3);
    string valueStr = PublicShowUI::numberToBigNumString(m_data->level);
    Label* valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, levelSpr->getContentSize().height / 2);
    levelSpr->addChild(valueLabel);
    
    
    Sprite* combatPower=Sprite::create(IMG_PUBLIC_MILITARY);
    combatPower->setAnchorPoint(Point::ZERO);
    combatPower->setPosition(levelSpr->getPositionX(), levelSpr->getPositionY() - combatPower->getContentSize().height-5);
    cellNode->addChild(combatPower,4);
    
    valueStr = PublicShowUI::numberToBigNumString(m_data->combat);
    valueLabel = PublicShowUI::getLabel(valueStr.c_str(),Color3B::WHITE,18,false,false);
    valueLabel->setAnchorPoint(Point(0,.5));
    valueLabel->setPosition(80, combatPower->getContentSize().height / 2);
    combatPower->addChild(valueLabel);
    
    //同意
    Button* agreeBtn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(FriendApplyNode::onBtnClick, this));
//    Sprite* agreeBtn=Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    agreeBtn->setAnchorPoint(Point::ZERO);
    agreeBtn->setPosition(cellNode->getContentSize().width-agreeBtn->getContentSize().width-16,cellNode->getContentSize().height-agreeBtn->getContentSize().height-2);
    cellNode->addChild(agreeBtn,5,TAG_AGREE);
    
    Sprite* agreeLabel=Sprite::create(IMG_CHAT_LABEL_AGREE);
    agreeLabel->setAnchorPoint(Point::ZERO);
    agreeLabel->setPosition((agreeBtn->getContentSize().width-agreeLabel->getContentSize().width)/2,(agreeBtn->getContentSize().height-agreeLabel->getContentSize().height)/2);
    agreeBtn->addChild(agreeLabel,2);
    
    //拒绝
    Button* refuseBtn=Button::create(IMG_PUBLIC_BUTTON_TWO_RED, "", CC_CALLBACK_1(FriendApplyNode::onBtnClick, this));
    refuseBtn->setAnchorPoint(Point::ZERO);
    refuseBtn->setPosition(agreeBtn->getPositionX(),2);
    cellNode->addChild(refuseBtn,5,TAG_REFUSE);
    
    Sprite* refuseLabel=Sprite::create(IMG_CHAT_LABEL_REJECT);
    refuseLabel->setAnchorPoint(Point::ZERO);
    refuseLabel->setPosition((refuseBtn->getContentSize().width-refuseLabel->getContentSize().width)/2,(refuseBtn->getContentSize().height-refuseLabel->getContentSize().height)/2);
    refuseBtn->addChild(refuseLabel,2);
    //
}
void FriendApplyNode::onStatusApply(Node* psender)
{
    MoveTo* move=MoveTo::create(0.2, Point(-cellNode->getContentSize().width, 0));
    if (cellNode) {
        cellNode->runAction(move);
    }
    
    MoveTo* move2=MoveTo::create(0.2, Point(0, 0));
    if (cellBg2) {
        cellBg2->runAction(move2);
    }
}
void FriendApplyNode::onStatusApplyEnabled(Node* psender)
{
    MoveTo* move=MoveTo::create(0.2, Point(0, 0));
    if (cellNode) {
        cellNode->runAction(move);
    }
    
    if (cellBg2) {
        MoveTo* move2=MoveTo::create(0.2, Point(cellNode->getContentSize().width, 0));
        cellBg2->runAction(move2);
    }
}
void FriendApplyNode::onBtnClick(Ref* psender)
{
    Node* node = (Node*)psender;
    int tag=node->getTag();
    if (tag == TAG_REFUSE) {
        
        this->requestRefuseMsg();
        
    }else if (tag == TAG_AGREE)
    {
        this->requestAgreeMsg();
    }
}
void FriendApplyNode::scrollViewDidScroll(ScrollView* view)
{
    
}

void FriendApplyNode::scrollViewDidZoom(ScrollView* view)
{
    
}

void FriendApplyNode::requestRefuseMsg()
{
    long userId=atol(m_data->userid.c_str());
    FriendRefuseMsg* msg = new FriendRefuseMsg(userId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void FriendApplyNode::requestAgreeMsg()
{
    long userId=atol(m_data->userid.c_str());
    FriendAgreeMsg* msg = new FriendAgreeMsg(userId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FriendApplyNode::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendAddAgreeResp)
    {
        this->broadMsg(CUSTOM_REFRESH_APPLY,NULL);
    }else if(message->messageID == SCENSE_CLIENT_FRIEND_FriendAddRefuseResp)
    {
        this->broadMsg(CUSTOM_REFRESH_APPLY,NULL);
    }
}
void FriendApplyNode::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendAddAgreeResp).c_str(), CC_CALLBACK_1(FriendApplyNode::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendAddRefuseResp).c_str(), CC_CALLBACK_1(FriendApplyNode::onMsgProcess, this));
}
void FriendApplyNode::removeEventListener()
{
    BaseLayer::removeEventListener();
}