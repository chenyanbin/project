//
//  FriendChatCont_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 16/1/6.
//
//

#include "FriendChatCont_Layer.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../common/TouchSprite/Button.h"
#include "../data/MessageData.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/StringUtil.h"
FriendChatCont_Layer::FriendChatCont_Layer()
:messageList(NULL)
,TAG_TABLEVIEW(1)
,TAG_VOICEBTN(2)
,TAG_INPUTEDIT(3)
,uinfo(NULL)
,m_chatWithUid(-1)
,indexTemp (0)
,m_recordingTime(0)
{
    messageList = new vector<YVMessagePtr>();
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->addUpdateUserInfoListern(this);
    platform->addFriendChatListern(this);
    platform->addFriendHistoryChatListern(this);
    platform->addFriendChatStateListern(this);
}
FriendChatCont_Layer::~FriendChatCont_Layer()
{
    CC_SAFE_DELETE(messageList);
    messageList = NULL;
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->delUpdateUserInfoListern(this);
    platform->delFriendChatListern(this);
    platform->delFriendHistoryChatListern(this);
    platform->delFriendChatStateListern(this);
}

void FriendChatCont_Layer::onExit()
{
    BaseLayer::onExit();
  
}
void FriendChatCont_Layer::onEnter()
{
    BaseLayer::onEnter();
   
}
void FriendChatCont_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
   
}
void FriendChatCont_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    setVoiceInputModeBtn();
    this->setChatUid();
}
bool FriendChatCont_Layer::init(int _YaYaId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_chatWithUid = _YaYaId;
        this->createLayer();
//        platform->addGetCpuUserListern(this);
        
        bref = true;
    } while (false);
    return bref;
}

FriendChatCont_Layer* FriendChatCont_Layer::create(int _YaYaId)
{
    FriendChatCont_Layer* layer = new FriendChatCont_Layer();
    if(layer && layer->init(_YaYaId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void FriendChatCont_Layer::createLayer()
{
    TouchSprite* bg = TouchSprite::createWithPic(IMG_CHAT_CHATBG,this,NULL);
    //    Sprite* bg=Sprite::create(IMG_CHAT_CHATBG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg);
    this->addChild(bg);
    this->setContentSize(bg->getContentSize());
}

//--------------------------------列表部分-------------------------------------------------------//
void FriendChatCont_Layer::initTableView()
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
    this->setContentSize(_size);
    _tableView->setContentOffset(_tableView->maxContainerOffset());
}
TableViewCell* FriendChatCont_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size FriendChatCont_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    ChatItem* chatItem = ChatItem::create(messageList->at(idx));
    
    cellSize = chatItem->getContentSize();
    return cellSize;
}
//获取view的长度
ssize_t FriendChatCont_Layer::numberOfCellsInTableView(TableView *table)
{
    return messageList->size();
}

//点击cell事件
void FriendChatCont_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void FriendChatCont_Layer::scrollViewDidScroll(ScrollView* view)
{
    
}
void FriendChatCont_Layer::addEventListener()
{
    
    
}
void FriendChatCont_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//-------------------------YYSDK部分---------------------------------------------//
void FriendChatCont_Layer::setChatUid()
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    uinfo = YVPlatform::getSingletonPtr()->getUInfoById(m_chatWithUid);
    if (uinfo != NULL)
    {
        std::string str = "name: ";
        str.append(uinfo->nickname);
        str.append(",uid:");
        
        std::string str2;
        char car[40] = {};
        sprintf(car, "%d", uinfo->userid);
        str.append(car);
        YVPlatform::getSingletonPtr()->setChatNodeUid(uinfo->userid);
    }
    //根据缓存数据恢复聊天数据
    YVMessageListPtr msgList = platform->getFriendChatListById(m_chatWithUid);
    //没有数据，获取点历史消息
    if (msgList == NULL  || msgList->getMessageList().size() == 0)
    {
        getBeforeMsg();
        return;
    }
    //从缓存里恢复数据
    
    messageList->clear();
    std::vector<YVMessagePtr>&  msgs = msgList->getMessageList();
    for (auto it = msgs.begin(); it != msgs.end(); ++it)
    {
        YVMessagePtr msg = *it;
        msg->playState = 0;
        messageList->push_back(msg);
    }
    initTableView();
}

int FriendChatCont_Layer::getHistoryIndex()
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    YVMessageListPtr msgList = platform->getFriendChatListById(m_chatWithUid);
    uint32 index = 0;
    if (msgList != NULL  && msgList->getMessageList().size() != 0)
    {
        for (auto msg : msgList->getMessageList())
        {
            if (index == 0)
            {
                index = msg->index;
            }
            if (index > msg->index)
            {
                index = msg->index;
            }
        }
    }
    return index - 1;
}
void FriendChatCont_Layer::getBeforeMsg()
{
    int index = 0;
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    YVMessageListPtr msgList = platform->getFriendChatListById(m_chatWithUid);
    if (msgList != NULL  && msgList->getMessageList().size() != 0)
    {
        YVMessagePtr msg;
        if(indexTemp == 0)
        {
            msg = msgList->getMessageList().back();
            indexTemp = msg->index;
            index = getHistoryIndex();
        } else {
            index = getHistoryIndex();
        }
        if (index <= 0)
            index = -1;
    }
    
    platform->getFriendChatHistoryData(m_chatWithUid, index);
}

//监听到有好友消息
void FriendChatCont_Layer::onFriendChatListern(YVSDK::YVMessagePtr msg)
{
    log(" onFriendChatListern onFriendChatListern onFriendChatListern m_chatWithUid=%d,msg->sendId=%d",m_chatWithUid,msg->sendId);
    if(m_chatWithUid != msg->sendId)   //  是在同一个好友界面
    {
        return;
    }
    
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    //发云确认消息
    platform->sendConfirmMsg(msg->index, msg->source);
    
    //排除自己的id
    int uid = YVPlatform::getSingletonPtr()->getLoginUserInfo()->userid;
    if (uid == msg->sendId)
    {
        
        return;
    }
    this->addContextItem(msg);
//    m_voiceList->insertObject(item, 0);
}
//查询到有新消息处理
void FriendChatCont_Layer::addContextItem(YVSDK::YVMessagePtr msg)
{
    if(messageList->size() > MAXMSG)
    {
        messageList->erase(messageList->begin());
    }
    messageList->push_back(msg);
    initTableView();
}
//监听到好友消息已读未读
void FriendChatCont_Layer::onFriendChatStateListern(YVSDK::YVMessagePtr msg)
{
    log(" onFriendChatStateListern onFriendChatStateListern onFriendChatStateListernmsg->recvId  = %d,m_chatWithUid=%d",msg->recvId ,m_chatWithUid);
    if (msg->recvId != m_chatWithUid) return;
    
//
    ChatItem* item = getItemByMsg(msg);
    
    if (item != NULL)
    {
        item->setChatMsg(msg);
    }
    else
    {
        this->addContextItem(msg);
    }
}
ChatItem* FriendChatCont_Layer::getItemByMsg(YVSDK::YVMessagePtr msg)
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
//历史聊天记录
void FriendChatCont_Layer::onFriendHistoryChatListern(YVSDK::YVMessageListPtr msgList)
{
    messageList->clear();
    std::vector<YVMessagePtr>&  msgs = msgList->getMessageList();
    for (auto it = msgs.begin(); it != msgs.end(); ++it)
    {
        YVMessagePtr msg = *it;
        msg->playState = 0;
        messageList->push_back(msg);
    }
    initTableView();
}

void FriendChatCont_Layer::onUpdateUserInfoListern(YVSDK::YVUInfoPtr uinfo)
{
    if (uinfo->userid != m_chatWithUid) return;
//    YVPlatform* platform = YVPlatform::getSingletonPtr();
//    platform->delUpdateUserInfoListern(this);
//    setTitle(uinfo->nickname);
}

//语音

void FriendChatCont_Layer::setVoiceInputModeBtn()
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
    
    TouchSprite* voiceBtn = TouchSprite::createWithPic(IMG_CHAT_SAY, this, callfuncN_selector(FriendChatCont_Layer::onVoiceBtnUp));
    voiceNode->addChild(voiceBtn,0);
    voiceBtn->addTouchBegainCallBack(this, callfuncN_selector(FriendChatCont_Layer::onVoiceBtnDown));
    voiceBtn->onRelesaseOutCallBack=CC_CALLBACK_1(FriendChatCont_Layer::onRelesaseOutUp, this);
    PublicShowUI::setTargetScale(voiceBtn,false,false);
    voiceBtn->isButtonMode = true;
    
    Size size = voiceBtn->getContentSize() * GlobalInfo::getInstance()->screenScaleX;
    TouchSprite* keyboard = TouchSprite::createWithPic(IMG_CHAT_KEYBOARD,this,callfuncN_selector(FriendChatCont_Layer::onKeybordClick));
    
    keyboard->isButtonMode = true;
    PublicShowUI::setTargetScale(keyboard,false,false);
    keyboard->setPosition(voiceBtn->getPositionX() + size.width / 2 + keyboard->getContentSize().width * sx/2 + 5 * sx,voiceBtn->getPositionY());
    
    voiceNode->addChild(keyboard,1);
    
    
    voiceNode->setPosition(this->getContentSize().width/2 - keyboard->getContentSize().width/2, voiceBtn->getContentSize().height * GlobalInfo::getInstance()->screenScaleX /2 + 10 * GlobalInfo::getInstance()->screenScaleX);
    
    this->addChild(voiceNode,3,TAG_VOICEBTN);
    
}
void FriendChatCont_Layer::onSoundBtnClick(Node* pSender)
{
    Node* inputNode = this->getChildByTag(TAG_INPUTEDIT);
    if(inputNode)
    {
        inputNode->removeFromParent();
    }
    this->setVoiceInputModeBtn();
}
void FriendChatCont_Layer::onVoiceBtnPress(Node* pSender)
{
    m_recordingTime = RECORDTIME;
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    
    platform->stopPlay();
    
    
    platform->startRecord();
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(FriendChatCont_Layer::recordingTimeUpdate), this, 0, false);
    
}

void FriendChatCont_Layer::onRelesaseOutUp(Ref* psender)
{
    sendVoice(false);
}
void FriendChatCont_Layer::onVoiceBtnUp(Node* pSender)
{
    sendVoice(false);
}
void FriendChatCont_Layer::onVoiceBtnDown(Node* pSender)
{
    sendVoice(true);
}
void FriendChatCont_Layer::onKeybordClick(Node* pSender)
{
    Node* voiceNode = this->getChildByTag(TAG_VOICEBTN);
    if(voiceNode)
    {
        voiceNode->removeFromParent();
    }
    this->setInputModeBtn();
}

void FriendChatCont_Layer::sendVoice(bool isSend)
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    if (isSend) {
//        m_recordingTime=RECORDTIME;
        m_recordingTime = RECORDTIME;
        YVPlatform* platform = YVPlatform::getSingletonPtr();
        
        platform->stopPlay();
        
        
        platform->startRecord();
        
        Director::getInstance()->getScheduler()->schedule(schedule_selector(FriendChatCont_Layer::recordingTimeUpdate), this, 0,  false);
    }else
    {
        platform->addStopRecordListern(this);
        platform->stopRecord();
    }
//    m_isSendVoice = isSend;
}

void FriendChatCont_Layer::onStopRecordListern(YVSDK::RecordStopNotify* r)
{
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(FriendChatCont_Layer::recordingTimeUpdate), this);
    //πÿ±’ªÿ µ˜
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    platform->delStopRecordListern(this);
    
    log("m_recordingTime=====================%f",m_recordingTime);
    
    if ((RECORDTIME - m_recordingTime) < 0.01)
    {
        NoticeManager::getInstance()->showNotice("录音时间太短");
        return;
    }
    
    
    m_recordingTime = r->time;
    
    this->sendFriendVoice(r->strfilepath, m_recordingTime);
}
//最大60秒
void FriendChatCont_Layer::recordingTimeUpdate(float dt)
{
    
    m_recordingTime -= dt;
    std::stringstream ss;
    std::string str;
    ss << (int)ceil(m_recordingTime);
    ss >> str;
    log("m_recordingTime=====================%f",m_recordingTime);
    
    const float EPSINON = 0.000001;
    if (m_recordingTime <= EPSINON)
    {
        sendVoice(true);
    }
    
}
void FriendChatCont_Layer::sendFriendVoice(YVSDK::YVFilePathPtr voicePath, float voiceTime)
{
    YVPlatform* platform = YVPlatform::getSingletonPtr();
    string ext =GlobalInfo::getInstance()->gameRole->headID+","+GlobalInfo::getInstance()->gameRole->name;
    platform->sendFriendVoice(m_chatWithUid, voicePath, voiceTime,ext);
    
    //    m_isSendVoice = false;
}
//文本聊天
void FriendChatCont_Layer::setInputModeBtn()
{
    Node* inputNode = this->getChildByTag(TAG_INPUTEDIT);
    if(inputNode)
    {
        inputNode->setVisible(true);
        return;
    }
    inputNode = Node::create();
    
    
    TouchSprite* voiceBtn = TouchSprite::createWithPic(IMG_CHAT_SOUNDBTN,this,callfuncN_selector(FriendChatCont_Layer::onSoundBtnClick));
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
    
    
    TouchSprite* sendBtn = TouchSprite::createWithPic(IMG_PUBLIC_BUTTON_TWO_RED, this, callfuncN_selector(FriendChatCont_Layer::onTextSendClick));
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
void FriendChatCont_Layer::onTextSendClick(Node* pSender)
{
    Node* node = this->getChildByTag(TAG_INPUTEDIT);
    if(node)
    {
        EditBox* box = (EditBox*)node->getChildByTag(TAG_INPUTEDIT);
        string text = box->getText();
        string ext =GlobalInfo::getInstance()->gameRole->headID+","+GlobalInfo::getInstance()->gameRole->name;
        if (text!="") {
            YVPlatform* platform = YVPlatform::getSingletonPtr();
            platform->sendFriendText(m_chatWithUid, text,ext);
            box->setText("");
        }
    }
    
}

//-------------------------以上YY部分---------------------------------------------//
//-------------------------输入框部分---------------------------------------------//
void FriendChatCont_Layer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void FriendChatCont_Layer::editBoxEditingDidEnd(EditBox* editBox)
{
    
}
void FriendChatCont_Layer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}
void FriendChatCont_Layer::editBoxReturn(EditBox* editBox)
{
    
}
//-------------------------以上输入框部分---------------------------------------------//