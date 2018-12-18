//
//  FriendApplyList_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#include "FriendApplyList_Layer.h"
#include "FriendApplyNode.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/chat/FriendApplyMsg.h"
#include "../../../protocol/UserCustomEvent.h"

FriendApplyList_Layer::FriendApplyList_Layer()
:TAG_TABLEVIEW(1)
{
    m_list=new Vector<MessageData*>();
}
FriendApplyList_Layer::~FriendApplyList_Layer()
{
    CC_SAFE_DELETE(m_list);
}

void FriendApplyList_Layer::onExit()
{
    BaseLayer::onExit();
}
void FriendApplyList_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void FriendApplyList_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FriendApplyList_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestApplyListMsg();
}
bool FriendApplyList_Layer::init(int cardId)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        bref = true;
    } while (false);
    return bref;
}
FriendApplyList_Layer* FriendApplyList_Layer::create(int cardId)
{
    FriendApplyList_Layer* layer = new FriendApplyList_Layer();
    if(layer && layer->init(cardId))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void FriendApplyList_Layer::createLayer()
{
}
//--------------------------------列表部分-------------------------------------------------------//
void FriendApplyList_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
//        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
//        _tableView->setContentOffset(cp);
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
TableViewCell* FriendApplyList_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    FriendApplyNode* node = FriendApplyNode::create(m_list->at(idx));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    return cell;
}

//列表大小
Size FriendApplyList_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* headBox=Sprite::create(IMG_CHAT_CELLBG);
    cellSize.height=headBox->getContentSize().height;
    cellSize.width=headBox->getContentSize().width-10;
    return cellSize;
}
//获取view的长度
ssize_t FriendApplyList_Layer::numberOfCellsInTableView(TableView *table)
{
    int count = (int)m_list->size();
    return count;
    
}

//点击cell事件
void FriendApplyList_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void FriendApplyList_Layer::scrollViewDidScroll(ScrollView* view)
{
    
}

//后台协议部分
void FriendApplyList_Layer::requestApplyListMsg(EventCustom* evt)
{
    FriendApplyMsg* msg = new FriendApplyMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void FriendApplyList_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendAddAskPageResp)
    {
        m_list->clear();
        int len=message->byteStream->getByte();
        for (int i=0; i<len; i++) {
            MessageData* data=new MessageData();
            long id=message->byteStream->getLong();
            data->userid=PublicShowUI::numberToString(id);
            
            data->nickName=message->byteStream->getUTF8();
            data->level=message->byteStream->getInt();
            data->combat=message->byteStream->getInt();
            data->headId=message->byteStream->getInt();
            m_list->pushBack(data);
        }
        this->initTableView();
    }
}
void FriendApplyList_Layer::addEventListener()
{
    addUserMsg(CUSTOM_REFRESH_APPLY,CC_CALLBACK_1(FriendApplyList_Layer::requestApplyListMsg, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendAddAskPageResp).c_str(), CC_CALLBACK_1(FriendApplyList_Layer::onMsgProcess, this));
}
void FriendApplyList_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}