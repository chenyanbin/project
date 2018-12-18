//
//  FindFriendList_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/11/24.
//
//

#include "FindFriendList_Layer.h"
#include "MessageItem.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/chat/FindFriendListMsg.h"

FindFriendList_Layer::FindFriendList_Layer()
:TAG_TABLEVIEW(1)
,listData(NULL)
{
    listData=new Vector<MessageData*>();
}
FindFriendList_Layer::~FindFriendList_Layer()
{
    CC_SAFE_DELETE(listData);
    listData = NULL;

}

void FindFriendList_Layer::onExit()
{
    BaseLayer::onExit();
}
void FindFriendList_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void FindFriendList_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    
}
void FindFriendList_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestFindFriendListMsg();
    
}
bool FindFriendList_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        bref = true;
    } while (false);
    return bref;
}
FindFriendList_Layer* FindFriendList_Layer::create()
{
    FindFriendList_Layer* layer = new FindFriendList_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}

void FindFriendList_Layer::createLayer()
{
    
}
//--------------------------------列表部分-------------------------------------------------------//
void FindFriendList_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
 
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
TableViewCell* FindFriendList_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    MessageItem* item=MessageItem::create(listData->at(idx));
    item->setAnchorPoint(Point::ZERO);
    cell->addChild(item);
    return cell;
}

//列表大小
Size FindFriendList_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* headBox=Sprite::create(IMG_CHAT_CELLBG);
    cellSize.height=headBox->getContentSize().height;
    cellSize.width=headBox->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t FindFriendList_Layer::numberOfCellsInTableView(TableView *table)
{
    int count = (int)listData->size();
    return count;
    
}

//点击cell事件
void FindFriendList_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void FindFriendList_Layer::scrollViewDidScroll(ScrollView* view)
{
    
}
//后台协议部分
void FindFriendList_Layer::requestFindFriendListMsg(string name)
{
    FindFriendListMsg* msg = new FindFriendListMsg(name);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FindFriendList_Layer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendSearchRoleResp)
    {
        listData->clear();
        int len=message->byteStream->getByte();
        for (int i=0; i<len; i++) {
            MessageData* data=new MessageData();
            long id=message->byteStream->getLong();
            data->roleId=id;
            data->userid=PublicShowUI::numberToString(id);
            
            data->nickName=message->byteStream->getUTF8();
            if (data->nickName=="") {
                data->nickName=PublicShowUI::numberToString(id);
            }
            data->level=message->byteStream->getInt();
            data->combat=message->byteStream->getInt();
            data->headId=message->byteStream->getInt();
            data->status=message->byteStream->getByte();
            listData->pushBack(data);
        }
        this->initTableView();
    }
}
void FindFriendList_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendSearchRoleResp).c_str(), CC_CALLBACK_1(FindFriendList_Layer::onMsgProcess, this));
}
void FindFriendList_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}