//
//  ServerAllListLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/5/5.
//
//

#include "ServerAllListLayer.hpp"
#include "EnterGameLayer.h"
ServerAllListLayer::ServerAllListLayer()
:TAG_TABLEVIEW(1)
,viewNode(NULL)
,recentList(NULL)
{
    
}
ServerAllListLayer::~ServerAllListLayer()
{
    recentList = NULL;
}
bool ServerAllListLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        Size size;
        recentList = ServerListDataManager::getInstance()->getServerList();
//        size.width = 400;
//        size.height = 400;
//        this->setContentSize(size);
        initView();
        initTableView();
        
        bref = true;
    } while (false);
    return bref;
}
ServerAllListLayer* ServerAllListLayer::create()
{
    ServerAllListLayer* layer = new ServerAllListLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ServerAllListLayer::onEnter()
{
    
}
void ServerAllListLayer::onExit()
{
    
}
//--------------------------------列表部分-------------------------------------------------------//
void ServerAllListLayer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    //
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=100;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(0,0);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    this->setContentSize(_tableView->getContentSize());
}
Node* ServerAllListLayer::initView()
{
    viewNode=Node::create();
    viewNode->setAnchorPoint(Point::ZERO);
    
    
    Menu* menu = Menu::create();
    menu->setAnchorPoint(Point::ZERO);
    

    MenuItem* itemLabel = NULL;
    Node* node = NULL;
    ssize_t size = this->recentList->size();
    for(int i = 0; i < size; i++)
    {
      
        node = getServerNode(this->recentList->at(i));
        itemLabel  = MenuItemLabel::create(node, CC_CALLBACK_1(ServerAllListLayer::onAllSelectedServer, this));
        itemLabel->setPosition((i % 2) * (itemLabel->getContentSize().width + 40), -(i / 2 * (itemLabel->getContentSize().height + 15)));
        menu->addChild(itemLabel,3,i);
    }
    
    if(itemLabel)
    {
        Size contentSize ;
        contentSize.width = itemLabel->getPositionX() + itemLabel->getContentSize().width;
        contentSize.height = abs(itemLabel->getPositionY());
        menu->setContentSize(contentSize);
    }
    viewNode->addChild(menu,4);
    viewNode->setContentSize(menu->getContentSize());
    
    return viewNode;
}
Node* ServerAllListLayer::getServerNode(ServerListData* data)
{
    
    Sprite* stateNode = NULL;
    switch (data->state) {
        case ServerListData::STATE_NORMAL:
            stateNode = Sprite::create(IMG_SERVERLIST_SMOOTH);
            break;
        case ServerListData::STATE_FIX:
            stateNode = Sprite::create(IMG_SERVERLIST_MAINTAIN);
            break;
        case ServerListData::STATE_NEW:
            stateNode = Sprite::create(IMG_SERVERLIST_SMOOTH);
            break;
        case ServerListData::STATE_STOP:
            stateNode = Sprite::create(IMG_SERVERLIST_MAINTAIN);
            break;
        default:
            break;
    }
    stateNode->setAnchorPoint(Point::ZERO);
    MenuItemImage* itemImage = MenuItemImage::create(IMG_SERVERLIST_ITEMBG1,IMG_SERVERLIST_ITEMBG1);
    itemImage->setAnchorPoint(Point::ZERO);
    stateNode->setPosition(5, (itemImage->getContentSize().height - stateNode->getContentSize().height)/2);
    itemImage->addChild(stateNode);
    Label* label = PublicShowUI::getLabel(data->serverName.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),16,false,false);
    itemImage->addChild(label);
    label->setPosition(itemImage->getContentSize().width/2, itemImage->getContentSize().height/2);
    itemImage->setScale(1.2);
    itemImage->setContentSize(itemImage->getContentSize() * 1.2);
    return itemImage;
}
void ServerAllListLayer::onAllSelectedServer(Ref* pSender)
{
    int index = ((Node*)pSender)->getTag();
    
    ServerListDataManager::getInstance()->_nowServerData = recentList->at(index);
    EnterGameLayer::show();
    BaseLayer::backScene();
}
TableViewCell* ServerAllListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    if (idx == 0) {
        
        cell->addChild(viewNode);
    }
    
    
    return cell;
}

//列表大小
Size ServerAllListLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    if (idx==0) {
        cellSize=viewNode->getContentSize();
    }else
    {
        cellSize=Point::ZERO;
    }
    return cellSize;
}
//获取view的长度
ssize_t ServerAllListLayer::numberOfCellsInTableView(TableView *table)
{
    return 2;
}
//点击cell事件
void ServerAllListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}


