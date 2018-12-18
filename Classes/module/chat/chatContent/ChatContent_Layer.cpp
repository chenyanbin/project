//
//  ChatContent_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/25.
//
//
#include "../../../common/noticeManager/NoticeManager.h"
#include "ChatContent_Layer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../data/MessageData.h"
ChatContent_Layer::ChatContent_Layer()
:TAG_TABLEVIEW(1)
,TAG_VOICEBTN(2)
,TAG_INPUTEDIT(3)
,m_channel(0)
,m_recordingTime(59)
,messageList(NULL)
,m_isSendVoice(false)
{
    messageList = new vector<YVMessagePtr>();
}
ChatContent_Layer::~ChatContent_Layer()
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->delChannelChatListern(this);
    platform->delChannelHistoryChatListern(this);
    platform->delChannelChatStateListern(this);
    platform->delChannalloginListern(this);
    platform->delStopRecordListern(this);
    CC_SAFE_DELETE(messageList);
    messageList = NULL;
}

void ChatContent_Layer::onExit()
{
    BaseLayer::onExit();
}
void ChatContent_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void ChatContent_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void ChatContent_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setVoiceInputModeBtn();
    
}
bool ChatContent_Layer::init(int _channel)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_channel = _channel;
//        this->setBackground(IMG_CHAT_CHATBG);
        
        YVPlatform* platform = YVPlatform::getSingletonPtr();
        platform->addStopRecordListern(this);
        platform->addChannelChatListern(this);
        platform->addChannelHistoryChatListern(this);
        platform->addChannelChatStateListern(this);
        platform->addChannalloginListern(this);
        
        this->createLayer();
        //数据初使化
        YVMessageListPtr msgList = platform->getCacheChannalChatData(0);
        if (msgList != NULL)
        {
            std::vector<YVMessagePtr>&  msgs = msgList->getMessageList();
            for (auto it = msgs.begin(); it != msgs.end(); ++it)
            {
                messageList->push_back( *it);
            }
            initTableView();
        }
        else
        {
            getChannalHistoryD();
        }
        bool bnewMessage = UserDefault::getInstance()->getBoolForKey("hasNewMessageInChatChannel", false);
        YVPlatform * p = YVPlatform::getSingletonPtr();
        p->setNewMessageChatChannel(bnewMessage);
        bref = true;
    } while (false);
    return bref;
}
void ChatContent_Layer::getChannalHistoryD()
{
    Director::getInstance()->getScheduler()->schedule(schedule_selector(ChatContent_Layer::getChannalHistory), this, 0.05, 0.5, 0, false);
}
void ChatContent_Layer::getChannalHistory(float dt)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(ChatContent_Layer::getChannalHistory), this);

    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->getChannalHistoryData(m_channel, 0);
}

ChatContent_Layer* ChatContent_Layer::create(int _channel)
{
    ChatContent_Layer* layer = new ChatContent_Layer();
    if(layer && layer->init(_channel))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void ChatContent_Layer::createLayer()
{
    TouchSprite* bg = TouchSprite::createWithPic(IMG_CHAT_CHATBG,this,NULL);
//    Sprite* bg=Sprite::create(IMG_CHAT_CHATBG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg);
    this->addChild(bg);
    this->setContentSize(bg->getContentSize());
}
void ChatContent_Layer::setVoiceInputModeBtn()
{
    Node* voiceNode = this->getChildByTag(TAG_VOICEBTN);
    if(voiceNode)
    {
        voiceNode->setVisible(true);
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    voiceNode = Node::create();
    voiceNode->setAnchorPoint(Point::ZERO);
    
    TouchSprite* voiceBtn = TouchSprite::createWithPic(IMG_CHAT_SAY, this, callfuncN_selector(ChatContent_Layer::onVoiceBtnClick));
    voiceNode->addChild(voiceBtn,0);
    voiceBtn->onRelesaseOutCallBack=CC_CALLBACK_1(ChatContent_Layer::onRelesaseOutUp, this);
    
    PublicShowUI::setTargetScale(voiceBtn,false,false);
    voiceBtn->isButtonMode = true;
    voiceBtn->addTouchBegainCallBack(this, callfuncN_selector(ChatContent_Layer::onVoiceBtnPress));
    
    
    Size size = voiceBtn->getContentSize() * GlobalInfo::getInstance()->screenScaleX;
    TouchSprite* keyboard = TouchSprite::createWithPic(IMG_CHAT_KEYBOARD,this,callfuncN_selector(ChatContent_Layer::onKeybordClick));
   
    keyboard->isButtonMode = true;
    PublicShowUI::setTargetScale(keyboard,false,false);
    keyboard->setPosition(voiceBtn->getPositionX() + size.width / 2 + keyboard->getContentSize().width * sx/2 + 5 * sx,voiceBtn->getPositionY());
    
     voiceNode->addChild(keyboard,1);
    
   
    voiceNode->setPosition(this->getContentSize().width/2 - keyboard->getContentSize().width/2, voiceBtn->getContentSize().height * GlobalInfo::getInstance()->screenScaleX /2 + 10 * GlobalInfo::getInstance()->screenScaleX);
    
    this->addChild(voiceNode,3,TAG_VOICEBTN);
    
}
void ChatContent_Layer::onKeybordClick(Node* pSender)
{
    Node* voiceNode = this->getChildByTag(TAG_VOICEBTN);
    if(voiceNode)
    {
        voiceNode->removeFromParent();
    }
    setInputModeBtn();
}
void ChatContent_Layer::onVoiceBtnClick(Node* pSender)
{
    sendVoice(true);
}
void ChatContent_Layer::onRelesaseOutUp(Ref* psender)
{
    sendVoice(true);
}
void ChatContent_Layer::onVoiceBtnPress(Node* pSender)
{
    m_recordingTime = RECORDTIME;
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    
    platform->stopPlay();

    
    platform->startRecord();

    Director::getInstance()->getScheduler()->schedule(schedule_selector(ChatContent_Layer::recordingTimeUpdate), this, 0, false);
    
}
void ChatContent_Layer::recordingTimeUpdate(float dt)
{
 
    m_recordingTime -= dt;
    std::stringstream ss;
    std::string str;
    ss << (int)ceil(m_recordingTime);
    ss >> str;
    const float EPSINON = 0.000001;
    if (m_recordingTime <= EPSINON)
    {
        sendVoice(true);
    }

}
void ChatContent_Layer::sendVoice(bool isSend)
{
    log("m_recordingTime endendendendend====================================%f",m_recordingTime);
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->addStopRecordListern(this);
    platform->stopRecord();
    m_isSendVoice = isSend;
}
void ChatContent_Layer::sendChannalVoice(YVSDK::YVFilePathPtr voicePath, float voiceTime)
{
    YVPlatform* platform= YVPlatform::getSingletonPtr();
    string ext =GlobalInfo::getInstance()->gameRole->headID+","+GlobalInfo::getInstance()->gameRole->name;
    platform->sendChannalVoice(kChatChannel_World, voicePath, voiceTime,ext);
    m_isSendVoice = false;
}
void ChatContent_Layer::setInputModeBtn()
{
    Node* inputNode = this->getChildByTag(TAG_INPUTEDIT);
    if(inputNode)
    {
        inputNode->setVisible(true);
        return;
    }
    inputNode = Node::create();
   
    
    TouchSprite* voiceBtn = TouchSprite::createWithPic(IMG_CHAT_SOUNDBTN,this,callfuncN_selector(ChatContent_Layer::onSoundBtnClick));
    voiceBtn->setAnchorPoint(Point::ZERO);
    voiceBtn->isButtonMode = true;
    PublicShowUI::setTargetScale(voiceBtn,false,false);
    voiceBtn->setPosition(0 ,0);
    inputNode->addChild(voiceBtn,1);
    
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Scale9Sprite* spr = Scale9Sprite::create(IMG_CHAT_INPUTBOX);
    Size size = spr->getContentSize() * sx;
    EditBox* editbox = EditBox::create(size, spr);
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setText("");
    editbox->setDelegate(this);
    editbox->setPosition(Point(voiceBtn->getContentSize().width * sx,0));
    inputNode->addChild(editbox,2,TAG_INPUTEDIT);

    
    TouchSprite* sendBtn = TouchSprite::createWithPic(IMG_PUBLIC_BUTTON_TWO_RED, this, callfuncN_selector(ChatContent_Layer::onTextSendClick));
    sendBtn->setAnchorPoint(Point::ZERO);
    Label* label = PublicShowUI::getLabel("发送",Color3B::WHITE,18,false,false);
    label->setPosition(sendBtn->getContentSize().width/2, sendBtn->getContentSize().height/2);
    sendBtn->addChild(label);
    
    PublicShowUI::setTargetScale(sendBtn,false,false);
    sendBtn->setPosition(editbox->getPositionX() + size.width, editbox->getPositionY());
    inputNode->addChild(sendBtn,3);
    
    size.width = sendBtn->getPositionX() + sendBtn->getContentSize().width * sx;
    inputNode->setPositionX((this->getContentSize().width - size.width)/2);
    inputNode->setPositionY(10 * sx);
    
    
    this->addChild(inputNode,4,TAG_INPUTEDIT);
}
void ChatContent_Layer::onTextSendClick(Node* pSender)
{
    if(YVPlatform::getSingletonPtr()->getLoginUserInfo() == NULL)
    {
        NoticeManager::getInstance()->showNotice("聊天异常！");
        return;
    }
    Node* node = this->getChildByTag(TAG_INPUTEDIT);
    if(node)
    {
        EditBox* box = (EditBox*)node->getChildByTag(TAG_INPUTEDIT);
        string text = box->getText();
        if (text!="") {
            string ext =GlobalInfo::getInstance()->gameRole->headID+","+GlobalInfo::getInstance()->gameRole->name;
            YVPlatform::getSingletonPtr()->sendChannalText(kChatChannel_World, text,ext);
        }
        box->setText("");
    }
    
}
void ChatContent_Layer::onSoundBtnClick(Node* pSender)
{
    if(YVPlatform::getSingletonPtr()->getLoginUserInfo() == NULL)
    {
        NoticeManager::getInstance()->showNotice("聊天异常！");
        return;
    }
    Node* inputNode = this->getChildByTag(TAG_INPUTEDIT);
    if(inputNode)
    {
        inputNode->removeFromParent();
    }
    this->setVoiceInputModeBtn();
}
//--------------------------------列表部分-------------------------------------------------------//
void ChatContent_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        _tableView->reloadData();
        _tableView->setContentOffset(_tableView->maxContainerOffset());
        return;
    }
    Size _size= this->getContentSize();
    _size.height *= .7;
   
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
  
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 30 * GlobalInfo::getInstance()->screenScaleX));
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    _tableView->setPositionX(10 * GlobalInfo::getInstance()->screenScaleX);
    _tableView->setPositionY(100 * GlobalInfo::getInstance()->screenScaleX);
//    this->setContentSize(_size);
    _tableView->setContentOffset(_tableView->maxContainerOffset());
}
TableViewCell* ChatContent_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    ChatItem* chatItem = ChatItem::create(messageList->at(idx));
    chatItem->setAnchorPoint(Point::ZERO);
    cell->addChild(chatItem,1,1);
    return cell;
}

//列表大小
Size ChatContent_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
        ChatItem* chatItem = ChatItem::create(messageList->at(idx));
        cellSize = chatItem->getContentSize();
    }
    
    return cellSize;
}
//获取view的长度
ssize_t ChatContent_Layer::numberOfCellsInTableView(TableView *table)
{
    return messageList->size();
}

//点击cell事件
void ChatContent_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void ChatContent_Layer::scrollViewDidScroll(ScrollView* view)
{
    
}
void ChatContent_Layer::addEventListener()
{
    
    
}
void ChatContent_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void ChatContent_Layer::onStopRecordListern(YVSDK::RecordStopNotify* r)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(ChatContent_Layer::recordingTimeUpdate), this);
    //πÿ±’ªÿ µ˜
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->delStopRecordListern(this);
    
    
    if (!m_isSendVoice)
    {
        return;
    }
    if ((RECORDTIME - m_recordingTime) < 0.01)
    {
        NoticeManager::getInstance()->showNotice("录音时间太短");
        return;
    }
    
    
    m_recordingTime = r->time;
    
    sendChannalVoice(r->strfilepath, m_recordingTime);
}

void ChatContent_Layer::onChannelChatListern(YVSDK::YVMessagePtr msg)
{

    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(!tableView)
    {
        return;
    }
    YVPlatform* p = YVPlatform::getSingletonPtr();
    if (p->getIsInChatChannel() == false)
    {
        
        p->setNewMessageChatChannel(true);
        UserDefault::getInstance()->setBoolForKey("hasNewMessageInChatChannel", true);
    }
    else
    {
       
        p->setNewMessageChatChannel(false);
        UserDefault::getInstance()->setBoolForKey("hasNewMessageInChatChannel", false);
    }

    ChatItem* item = getItemByMsg(msg);
    if (item == NULL)
    {
        msg->playState = 1;

        addContextItem(msg);
       
    }
    else
    {
        if (msg->state == YVMessageStatusSending)
        {
            item->setChatMsg(msg);
        }
        if (msg->state == YVMessageStatusSendingFailed)
        {
            NoticeManager::getInstance()->showNotice("消息发送失败");
        }
    }
    
}
ChatItem* ChatContent_Layer::getItemByMsg(YVSDK::YVMessagePtr msg)
{
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(!tableView)
    {
        return NULL;
    }
    TableViewCell* cell = NULL;
    ssize_t len = this->numberOfCellsInTableView(tableView);
    ChatItem* chatItem = NULL;
    for(int i = 0; i  < len; i++)
    {
        cell = tableView->cellAtIndex(i);
        if(cell)
        {
            chatItem = (ChatItem*)cell->getChildByTag(1);
            if (chatItem != NULL)
            {
                YVSDK::YVMessagePtr msgt = chatItem->getChatMessage();
                if (msgt != NULL && msgt->id == msg->id)
                {
                    return chatItem;
                }
                
            }
        }
        
    }
    
   
    return NULL;
}

void ChatContent_Layer::addContextItem(YVMessagePtr msg)
{
    if(messageList->size() > MAXMSG)
    {
        messageList->erase(messageList->begin());
    }
    messageList->push_back(msg);
    initTableView();
   
}
void ChatContent_Layer::onChannelHistoryChatListern(YVSDK::YVMessageListPtr msgList)
{
    log("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
    if (msgList->getChatWithID() != 0) return;
    messageList->clear();
    std::vector<YVMessagePtr>&  msgs = msgList->getMessageList();
    for (auto it = msgs.begin(); it != msgs.end(); ++it)
    {
        YVMessagePtr msg = *it;
        msg->playState = 0;
        if (msg->ext!="") {
            messageList->push_back(msg);
        }
        
    }
    initTableView();
}

void ChatContent_Layer::onChannelChatStateListern(YVSDK::YVMessagePtr msg)
{
    ChatItem* item = getItemByMsg(msg);
   
    if (item != NULL)
    {
        item->setChatMsg(msg);
    }
}
void ChatContent_Layer::onModChannelIdListern(YVSDK::ModChannelIdRespond* r)
{
    log("sldfjlsd");
}
void ChatContent_Layer::onChannalloginListern(YVSDK::ChanngelLonginRespond* r)
{
    log("login ======================================登陆成功");
//    YVPlatform* platform = YVPlatform::getSingletonPtr();
    
}


void ChatContent_Layer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void ChatContent_Layer::editBoxEditingDidEnd(EditBox* editBox)
{
    
}
void ChatContent_Layer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}
void ChatContent_Layer::editBoxReturn(EditBox* editBox)
{
    
}