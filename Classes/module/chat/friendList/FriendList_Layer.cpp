//
//  FriendList_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#include "FriendList_Layer.h"
#include "FriendItemNode.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/chat/ChatFriendsListMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../message/Decoding/chat/DeleteFriendMsg.h"

FriendList_Layer::FriendList_Layer()
:TAG_TABLEVIEW(1)
,userId("")
{
    m_list=new Vector<MessageData*>();
}
FriendList_Layer::~FriendList_Layer()
{
    CC_SAFE_DELETE(m_list);
}

void FriendList_Layer::onExit()
{
    BaseLayer::onExit();
}
void FriendList_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void FriendList_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FriendList_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestFriendListMsg();
}
bool FriendList_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        bref = true;
    } while (false);
    return bref;
}
FriendList_Layer* FriendList_Layer::create(int cardId)
{
    FriendList_Layer* layer = new FriendList_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void FriendList_Layer::createLayer()
{
}
//--------------------------------列表部分-------------------------------------------------------//
void FriendList_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*4;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    this->setContentSize(_size);
    
}
TableViewCell* FriendList_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    FriendItemNode* node = FriendItemNode::create(m_list->at(idx));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    return cell;
}

//列表大小
Size FriendList_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* headBox=Sprite::create(IMG_CHAT_CELLBG);
    cellSize.height=headBox->getContentSize().height;
    cellSize.width=headBox->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t FriendList_Layer::numberOfCellsInTableView(TableView *table)
{
    int count = (int)m_list->size();
    return count;
}

//点击cell事件
void FriendList_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
//    int idx=(int)cell->getIdx();
//    int id=m_list->at(idx)->yayaId;
//    this->broadMsg(CUSTOM_CHAT_FRIEND_CLICK,__Integer::create(id));
}
void FriendList_Layer::scrollViewDidScroll(ScrollView* view)
{
    
}

void FriendList_Layer::deleteNotice(EventCustom* msg)
{
    __String* _userId = (__String*)msg->getUserData();
    userId = _userId->getCString();
    
    
    string name="";
    for (MessageData* data : *m_list) {
        if (data->userid.c_str()==userId) {
            name=data->nickName;
            break;
        }
    }
    
    /*Sprite* item = Sprite::create();
    item->setAnchorPoint(Point::ZERO);
    Label* label = Label::createWithTTF("您即将删除你的好友","fonts/YABold.ttf",18);
    label->setAnchorPoint(Point::ZERO);
    label->setColor(PublicShowUI::getColor3b(0xBDF8E1));
    item->addChild(label);
    Size size = label->getContentSize();
    
    Label* valueLabel = Label::createWithTTF(name,"fonts/YABold.ttf",18);
    valueLabel->setAnchorPoint(Point::ZERO);
    valueLabel->setColor(PublicShowUI::getColor3b(0xF99DAB));
    valueLabel->setPositionX(label->getContentSize().width +1);
    item->addChild(valueLabel);
    
    Label* label2 = Label::createWithTTF("删除后您也将从对方好友列表中消失是否确定删除？", "fonts/YABold.ttf", 18);
    label2->setAnchorPoint(Point::ZERO);
    label2->setColor(PublicShowUI::getColor3b(0xBDF8E1));
    label2->setPositionX(valueLabel->getContentSize().width +1);
    item->addChild(label2);
    
    size.width = label2->getPositionX() + label2->getContentSize().width;
    item->setContentSize(size);*/

    
    string cont="您即将删除你的好友"+name+"删除后您也将从对方好友列表中消失是否确定删除？";
    Dialog::show(cont.c_str(),"提示",2,this,callfuncN_selector(FriendList_Layer::requestDeleteFriendMsg));
}
//删除好友
void FriendList_Layer::removeFriend()
{
    int index = this->getIndexByUserId(userId);
    if(index >= 0)
    {
        m_list->erase(index);
    }
    this->initTableView();
}

//添加好友
void FriendList_Layer::addFriend(EventCustom* msg)
{
    
}
//接收好友消息
void FriendList_Layer::addFriendMessage()
{
    
}
//好友消息排序
void FriendList_Layer::sortList()
{
    
}
//查找好友
int FriendList_Layer::getIndexByUserId(string id)
{
    int len = (int)m_list->size();
    for(int i = 0; i < len; i++)
    {
        if(m_list->at(i)->userid == id)
        {
            return i;
        }
    }
    return -1;
}
//协议接口部分
void FriendList_Layer::requestDeleteFriendMsg(Node* sp)
{
    int tag=sp->getTag();
    if (tag==1) {
        long tempId=atol(userId.c_str());
        DeleteFriendMsg* msg = new DeleteFriendMsg(tempId);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
    
}
void FriendList_Layer::requestFriendListMsg()
{
    ChatFriendsListMsg* msg = new ChatFriendsListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void FriendList_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendMyPageResp)
    {
        m_list->clear();
        int len=message->byteStream->getByte();
        for (int i=0; i<len; i++) {
            MessageData* data=new MessageData();
            long long id=message->byteStream->getLong();
            data->userid=PublicShowUI::numberToString(id);
            data->yayaId=message->byteStream->getInt();
            log("data->yayaId==================%d",data->yayaId);
            data->nickName=message->byteStream->getUTF8();
            log("data->nickName==================%s",data->nickName.c_str());
            data->level=message->byteStream->getInt();
            data->combat=message->byteStream->getInt();
            data->headId=message->byteStream->getInt();
            data->status=message->byteStream->getByte();
            m_list->pushBack(data);
        }
        this->initTableView();
    }else if (message->messageID == SCENSE_CLIENT_FRIEND_FriendDelResp)
    {
        this->removeFriend();
    }
}
void FriendList_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendMyPageResp).c_str(), CC_CALLBACK_1(FriendList_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendDelResp).c_str(), CC_CALLBACK_1(FriendList_Layer::onMsgProcess, this));
    this->addUserMsg(CUSTOM_DELETE_FRIEND,CC_CALLBACK_1(FriendList_Layer::deleteNotice, this));
}
void FriendList_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}