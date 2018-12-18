//
//  MessageList_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/23.
//
//

#include "MessageList_Layer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "MessageNotifyNode.h"
MessageList_Layer::MessageList_Layer()
:TAG_TABLEVIEW(1)
,messageList(NULL)
,isMoveing(false)
{
    messageList = new vector<YVMessagePtr>();
}
MessageList_Layer::~MessageList_Layer()
{
    CC_SAFE_DELETE(messageList);
    messageList = NULL;
}

void MessageList_Layer::onExit()
{
    BaseLayer::onExit();
}
void MessageList_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void MessageList_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
}
void MessageList_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->setClickEnabled(true);
    this->m_eventDispatcher->setSwallowTouches(false);
}
bool MessageList_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
       
        setWorldMsg();
        this->initTableView();
        bref = true;
    } while (false);
    return bref;
}
void MessageList_Layer::setWorldMsg()
{
    YVMessagePtr msg = NULL;
    YVMessageListPtr msgList = YVPlatform::getSingletonPtr()->getCacheChannalChatData(kChatChannel_World);
    if (msgList != NULL)
    {
        std::vector<YVMessagePtr> list = msgList->getMessageList();
        if(list.size())
        {
            msg = msgList->getMessageList().at(msgList->getMessageList().size()-1);
        }
    }
    else
    {
        msg = new _YVTextMessage("......");
        msg->recvId = kChatChannel_World;
        msg->sendId = kChatChannel_World;
        msg->state = YVMessageStatusSending;
      
        
    }
     messageList->push_back(msg);
}
MessageList_Layer* MessageList_Layer::create(int cardId)
{
    MessageList_Layer* layer = new MessageList_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void MessageList_Layer::createLayer()
{
    
}
//--------------------------------列表部分-------------------------------------------------------//
void MessageList_Layer::initTableView()
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
    
//    Node* node = _tableView->cellAtIndex(0)->getChildByTag(0);
//    onMsgItemClick(node);
}
TableViewCell* MessageList_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
//    int channel = idx == 0 ? kChatChannel_World : kChatChannel_Private;
    MessageNotifyNode* node =  MessageNotifyNode::create(messageList->at(idx),CC_CALLBACK_1(MessageList_Layer::onMsgItemClick, this));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node,0,idx);
    return cell;
}
void MessageList_Layer::onMsgItemClick(Ref* item)
{
    if(isMoveing)
    {
        isMoveing = false;
        return;
    }
    Node* node = (Node*)item;
    this->broadMsg(CUSTOM_CHAT_MESSAGE_CLICK,__Integer::create(node->getTag()));
}
//列表大小
Size MessageList_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
        Sprite* headBox=Sprite::create(IMG_CHAT_CELLBG);
        cellSize = headBox->getContentSize();
    }
   
    return cellSize;
}
//获取view的长度
ssize_t MessageList_Layer::numberOfCellsInTableView(TableView *table)
{
    return messageList->size();
}

//点击cell事件
void MessageList_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    
}
void MessageList_Layer::scrollViewDidScroll(ScrollView* view)
{
    isMoveing = true;
}
void MessageList_Layer::addEventListener()
{
    

}
void MessageList_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
bool MessageList_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    return true;
}
void MessageList_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().y > 20 * GlobalInfo::getInstance()->screenScaleX)
    {
        isMoveing = true;
    }
}
void MessageList_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
}