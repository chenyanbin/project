//
//  ChatItem.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/25.
//
//

#include "ChatItem.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../YVSDK/YVPlatform.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../common/StringUtil.h"

unsigned long tempvoiceID;
unsigned long voiceID;

ChatItem::ChatItem()
:m_data(NULL)
,userinfo(NULL)
,TAG_BG(0)
,TAG_HEAD(1)
,TAG_VOICEBTN(2)
,TAG_TEXT(3)
,TAG_SENDING(4)
,m_richText(NULL)
,m_Message(NULL)
,m_isVoiceMssage(false)
,m_voiceText("")
,m_voicePath(NULL)
,redDot(NULL)
,sendingSpr(NULL)
,isSound(false)
,sx(1)
{
    
}
ChatItem::~ChatItem()
{
    m_data = NULL;
    userinfo = NULL;
    m_richText = NULL;
    redDot = NULL;
}
bool ChatItem::init(YVMessagePtr data)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
      
        sx = GlobalInfo::getInstance()->screenScaleX;
        this->setContentSize(Size(600 * sx ,110 * sx));
        setChatMsg(data);
      
        bref = true;
    } while (false);
    return bref;
}
ChatItem* ChatItem::create(YVMessagePtr data)
{
    ChatItem* item = new ChatItem();
    if(item && item->init(data))
    {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    item = NULL;
    return item;
}
void ChatItem::onExit()
{
    BaseLayer::onExit();
}
void ChatItem::onEnter()
{
    BaseLayer::onEnter();
    
}
void ChatItem::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->delFinishPlayListern(this);
    platform->delDownLoadFileListern(this);
}
void ChatItem::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    if(this->m_isVoiceMssage)
    {
        DelayTime* delay = DelayTime::create(1);
        CallFunc* callFun = CallFunc::create(CC_CALLBACK_0(ChatItem::downLoadVoiceFile, this));
        this->runAction(Sequence::create(delay,callFun, NULL));
        
       
    }
    

}
void ChatItem::setContent()
{
    //头像
    string ext=m_data->ext;
//
    vector<string> ret=StringUtil::split(ext,",");
    int headId=atoi(ret[0].c_str());
    DictHero* data=DictHeroManager::getInstance()->getData(headId);
    Node* node = NULL;
    if (!data) {
        node = PublicShowUI::getAvatarHead("caopi", 0, 0);
    }else
    {
        node = PublicShowUI::getAvatarHead(data->resource.c_str(), 0, 0);
    }
    //名字
    Label* nameLabel=NULL;
    if (ret.size()>1) {
        nameLabel = PublicShowUI::getLabel(ret[1].c_str(),Color3B::BLACK,18,false,false);
        nameLabel->setAnchorPoint(Point::ZERO);
        node->addChild(nameLabel,2);
    }
    
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        node->setPosition(this->getContentSize().width-node->getContentSize().width*sx,0);
        if (nameLabel) {
            nameLabel->setPosition(-nameLabel->getContentSize().width-5,node->getContentSize().height-nameLabel->getContentSize().height);
        }
    }else
    {
        node->setPosition(0, 0);
        if (nameLabel) {
            nameLabel->setPosition(node->getContentSize().width+5,node->getContentSize().height-nameLabel->getContentSize().height);
        }
    }
    node->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(node);
    this->addChild(node,1,TAG_HEAD);
    
    if(m_data->state == YVMessageStatusSending)
    {
        setSending();
    }
    else
    {
        if(this->getChildByTag(TAG_SENDING))
        {
            this->removeChildByTag(TAG_SENDING);
        }
        initMessageContent(m_data,false);
    }
    
}
void ChatItem::initMessageContent(YVSDK::YVMessagePtr message, bool flag)
{
    m_isVoiceMssage = false;
    switch (message->type)
    {
        case YVMessageTypeText:
        {
            YVTextMessagePtr msg = message;
            initTextMessage(msg->text);
            break;
        }
        case YVMessageTypeImage:
        {
            YVImageMessagePtr msg = message;
            initPicMessage(msg);
            break;
        }
        case YVMessageTypeAudio:
        {
            YVVoiceMessagePtr msg = message;
            initVoiceMessage(msg, flag);
            break;
        }
    }
}
void ChatItem::setSending()
{
    Sprite* sendSpr = Sprite::create(IMG_CHAT_SENDING);
    sendSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(sendSpr);
    
    Node* head = this->getChildByTag(TAG_HEAD);
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        
        sendSpr->setPosition(head->getPositionX()- head->getContentSize().width - sendSpr->getContentSize().width, (head->getContentSize().height - sendSpr->getContentSize().height)/2);
        
    }else
    {
        sendSpr->setPosition(head->getContentSize().width, (head->getContentSize().height - sendSpr->getContentSize().height)/2);
    }
    
    this->addChild(sendSpr,4,TAG_SENDING);
}
void ChatItem::initTextMessage(std::string& te)
{
    
    Node* head = this->getChildByTag(TAG_HEAD);
    
    Size size = this->getContentSize();
    Label* pLabel = PublicShowUI::getLabel(te.c_str(),Color3B::BLACK,20,false,false);
    pLabel->setAnchorPoint(Point::ZERO);
    pLabel->setMaxLineWidth(400*sx);
    pLabel->setLineBreakWithoutSpace(true);
    
    
    Size extenSize = Size(pLabel->getContentSize().width+40 * sx,pLabel->getContentSize().height+30 * sx);
    //判断头像高还是文本高
    int tempY=extenSize.height+30*sx-head->getContentSize().height;
    int spY=0;
//    log("te=======================================================%s",te.c_str());
//    log("extenSize======================%f",pLabel->getContentSize().height);
//    log("head->getContentSize().height============================,%f",head->getContentSize().height);
    if (tempY > 0) {
//        log("tempY============================,%d",tempY);
        head->setPositionY(tempY);
        size.height=tempY+head->getContentSize().height+20*sx;
        this->setContentSize(size);
        
    }else
    {
        spY=head->getPositionY() + head->getContentSize().height - extenSize.height - 30 * sx;
    }
    Scale9Sprite* sp =NULL;
    //判断自己说话还是对方说话
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        sp = Scale9Sprite::create(IMG_CHAT_ITEM_GREEN_BG);
        sp->setContentSize(extenSize);
        sp->setPosition(head->getPositionX() - sp->getContentSize().width - 3*sx,spY);
    }else
    {
        sp = Scale9Sprite::create(IMG_CHAT_ITEM_WHITE_BG);
        sp->setContentSize(extenSize);
        sp->setPosition(head->getPositionX() + head->getContentSize().width + 3 *sx,spY);
    }
    
    sp->setAnchorPoint(Point::ZERO);
    sp->addChild(pLabel);
    pLabel->setPosition(20,15);
    this->addChild(sp, 1);
}
void ChatItem::initVoiceMessage(YVSDK::YVVoiceMessagePtr message,bool flag)
{
    Node* head = this->getChildByTag(TAG_HEAD);
    m_isVoiceMssage = true;
    m_Message = message;
   
    TouchSprite* voiceButton = TouchSprite::createWithPic(IMG_CHAT_PLAYSOUND, this, callfuncN_selector(ChatItem::playSound));
    voiceButton->setVisible(false);
    voiceButton->isButtonMode = true;
    voiceButton->setAnchorPoint(Point::ZERO);

    char num[12] = { 0 };
    int timeNum = ceil(message->voiceTimes / 1000.0f);
    sprintf((char*)num, "%d", timeNum);
    strcat(num, "\"");
    Label* timeLabel = PublicShowUI::getLabel(num,Color3B::BLACK,18,false,false);
    timeLabel->setAnchorPoint(Point::ZERO);
    timeLabel->setPosition(voiceButton->getContentSize().width, voiceButton->getContentSize().height - timeLabel->getContentSize().height);
    this->addChild(timeLabel,2);
    
    
    //红点
    if(message->playState && !isSendMessage(message))
    {
        redDot = Sprite::create(IMG_CHAT_REDDOT);
        redDot->setAnchorPoint(Point::ZERO);
        this->addChild(redDot,3);
        redDot->setPosition(timeLabel->getPositionX() + timeLabel->getContentSize().width, timeLabel->getPositionY());
    }
    PublicShowUI::setTargetScale(voiceButton);
    m_voiceText = message->attach;
    
//    文本框
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    Size size = this->getContentSize();
    Label* pLabel = PublicShowUI::getLabel(m_voiceText.c_str(),Color3B::BLACK,20,false,true);
    pLabel->setAnchorPoint(Point::ZERO);
    pLabel->setMaxLineWidth(size.width * .65);
    
    
    Size extenSize = Size(pLabel->getContentSize().width+40 * sx,pLabel->getContentSize().height+voiceButton->getContentSize().height+30 * sx);
    //判断头像高还是文本高
    int tempY=extenSize.height+30*sx-head->getContentSize().height;
    int spY=0;
    if (tempY > 0) {
        head->setPositionY(tempY);
        size.height=extenSize.height+30*sx;
        this->setContentSize(size);
    }else
    {
        spY=head->getPositionY() + head->getContentSize().height - extenSize.height - 30 * sx;
    }
    Scale9Sprite* sp =NULL;
    //判断自己说话还是对方说话
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        sp = Scale9Sprite::create(IMG_CHAT_ITEM_GREEN_BG);
        sp->setContentSize(extenSize);
        sp->setPosition(head->getPositionX() - sp->getContentSize().width - 3*sx,spY);
    }else
    {
        sp = Scale9Sprite::create(IMG_CHAT_ITEM_WHITE_BG);
        sp->setContentSize(extenSize);
        sp->setPosition(head->getPositionX() + head->getContentSize().width + 3 *sx,spY);
    }
    
    sp->setAnchorPoint(Point::ZERO);
    sp->addChild(pLabel);
    pLabel->setPosition(20,15);
    this->addChild(sp, 1);
    
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        
        voiceButton->setPosition(sp->getPositionX() + sp->getContentSize().width-5,sp->getPositionY()+sp->getContentSize().height-voiceButton->getContentSize().height-5*sx);
        voiceButton->setScaleX(-1);
    }else
    {
        voiceButton->setPosition(sp->getPositionX()+5,sp->getPositionY()+sp->getContentSize().height-voiceButton->getContentSize().height-5*sx);
    }
    this->addChild(voiceButton,3,TAG_VOICEBTN);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    
    if (m_data->sendId==GlobalInfo::getInstance()->gameRole->yayaId) {
        if (redDot) {
            redDot->setPosition(timeLabel->getPositionX() + timeLabel->getContentSize().width, timeLabel->getPositionY());
        }
        timeLabel->setPosition(voiceButton->getPositionX() - timeLabel->getContentSize().width - voiceButton->getContentSize().width -5*sx, voiceButton->getPositionY() + voiceButton->getContentSize().height - timeLabel->getContentSize().height);
        
    }else
    {
        if (redDot) {
            redDot->setPosition(timeLabel->getPositionX() - timeLabel->getContentSize().width - redDot->getContentSize().width, timeLabel->getPositionY());
        }
        timeLabel->setPosition(voiceButton->getPositionX()+timeLabel->getContentSize().width+5*sx, voiceButton->getPositionY() + voiceButton->getContentSize().height - timeLabel->getContentSize().height);
    }
    this->addChild(timeLabel,2);
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
     m_voicePath =  message->voicePath;
    if (m_voicePath != NULL && (m_voicePath->getState() == BothExistState || m_voicePath->getState() == OnlyLocalState) )
    {
        voiceButton->setVisible(true);
    }
    else
    {

    }
   

}
void ChatItem::setChatMsg(YVMessagePtr data)
{
    m_data = data;
    userinfo = YVPlatform::getSingletonPtr()->getUInfoById(m_data->sendId);
    this->removeAllChildren();
    this->setContent();
}
YVMessagePtr ChatItem::getChatMessage()
{
    return m_data;
}
void ChatItem::downLoadVoiceFile()
{
    
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    
    platform->addDownLoadFileListern(this);
    platform->downLoadFile(m_voicePath);
}
void ChatItem::playSound(Node* pSender)
{
    voiceID = m_voicePath->getPathId();
    if (voiceID != tempvoiceID)
    {
        tempvoiceID = voiceID;
        playVoice();
  
    }
    else
    {
        tempvoiceID = -1;
    }
}
void ChatItem::playVoice()
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    
    if(!platform->playRecord(m_voicePath))
    {
        return;
    }
     Node* voiceButton = this->getChildByTag(TAG_VOICEBTN);
    voiceButton->setVisible(false);
   
    platform->addFinishPlayListern(this);
}
void ChatItem::initPicMessage(YVSDK::YVImageMessagePtr)
{
    
}
bool  ChatItem::isSendMessage(YVMessagePtr base)
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    if (platform->getLoginUserInfo()->userid == base->sendId)
        return true;
    
    return false;
}
void ChatItem::onDownLoadFileListern(YVSDK::YVFilePathPtr path)
{
    if (path->getState() == DownLoadErroSate)
    {
        CCLOG("download Error:%s", path->getLocalPath().c_str());
        return;
    }

    if (m_voicePath != NULL && m_voicePath->getPathId() == path->getPathId())
    {
        Node* voiceButton = this->getChildByTag(TAG_VOICEBTN);
        if (voiceButton != NULL)
        {
            voiceButton->setVisible(true);
        }
       
    }
 
}

void ChatItem::onUpdateUserInfoListern(YVSDK::YVUInfoPtr info)
{
    if (userinfo != NULL && userinfo->userid == info->userid)
    {
        YVPlatform* platform = YVPlatform::getSingletonPtr();
        platform->delUpdateUserInfoListern(this);
   
    }
}

void ChatItem::onFinishPlayListern(YVSDK::StartPlayVoiceRespond* r)
{
    YVPlatform::getSingletonPtr()->delFinishPlayListern(this);
    m_data->playState = 0;
    Node* voiceButton = this->getChildByTag(TAG_VOICEBTN);
    voiceButton->setVisible(true);
    if(redDot && redDot->getParent())
    {
        redDot->removeFromParent();
        redDot = NULL;
    }
}
