//
//  ServerListLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/16.
//
//

#include "ServerListLayer.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../common/TouchSprite/Button.h"
#include "../userLogin/UserLoginLayer.h"
#include "../LoginLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "EnterGameLayer.h"
#include "ServerAllListLayer.hpp"
ServerListLayer::ServerListLayer()
:serverList(NULL)
,recentList(NULL)
,PAGENUM(12)
,DISPLAY_COUNT(6)
,curSelectedItem(NULL)
,TAG_SERVERLIST(1)
,TAG_LASTLOGIN(2)
,TAG_TABLEVIEW(3)
,TAG_ALLLIST(4)
,TAG_LABEL(5)
,m_nowSelectedData(NULL)
{
    
}
ServerListLayer::~ServerListLayer()
{
    serverList = NULL;
    curSelectedItem = NULL;
    m_nowSelectedData = NULL;
    recentList = NULL;
}
bool ServerListLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
     
        setBg();
        isShowGrayBg = true;
        this->isClickClose = true;
        setTitle();
        
        bref = true;
    } while (false);
    return bref;
}
ServerListLayer* ServerListLayer::create()
{
    ServerListLayer* layer = new ServerListLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ServerListLayer::show()
{
    ServerListLayer* layer = ServerListLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer);
}
void ServerListLayer::setBg()
{
    Sprite* bg = Sprite::create(IMG_SERVERLIST_BG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg);
    this->setContentSize(bg->getContentSize());
    this->addChild(bg,0,TAG_BG);
}

void ServerListLayer::onEnter()
{
    BaseLayer::onEnter();
    
  
    serverList = ServerListDataManager::getInstance()->getRecentList();
    recentList = ServerListDataManager::getInstance()->getServerList();
    setServerTableView();
    setLastLoginBtn();
    

    this->setClickEnabled(true);
}
void ServerListLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void ServerListLayer::setLastLoginBtn()
{
//    tableView->setPositionX(50 * sx);
//    tableView->setPositionY(220 * sx);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    MenuItemImage* lastBtn = MenuItemImage::create(IMG_SERVERLIST_LASTBTN, IMG_SERVERLIST_LASTBTN1, CC_CALLBACK_1(ServerListLayer::onLastBtnClick, this));
    lastBtn->setAnchorPoint(Point::ZERO);
    Menu* menu = Menu::create(lastBtn,NULL);
    menu->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(menu);
    menu->setPosition(30* sx , this->getContentSize().height - 100 * sx);
    this->addChild(menu,3,TAG_LASTLOGIN);
 
    if(serverList->size() <= 0)
    {
        serverList = ServerListDataManager::getInstance()->getServerList();
        TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
        tableCellTouched(tableView,tableView->cellAtIndex(0));
       
    }
    else
    {
        onLastBtnClick(lastBtn);
    }
   
}
void ServerListLayer::onLastBtnClick(Ref* pSender)
{
    MenuItemImage* lastBtn = (MenuItemImage*)pSender;
    serverList = NULL;
    serverList = ServerListDataManager::getInstance()->getRecentList();
    if(curSelectedItem != NULL && curSelectedItem->getReferenceCount() > 0 && curSelectedItem->getParent())
    {
        curSelectedItem->unselected();
    }
    curSelectedItem = lastBtn;
    curSelectedItem->selected();
    this->showServerList(0);
    this->showAllServerList(0);
}
void ServerListLayer::setTitle()
{
    Sprite* title = Sprite::create(IMG_SERVERLIST_TITLE);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition((this->getContentSize().width - title->getContentSize().width)/2 + 30 *GlobalInfo::getInstance()->screenScaleX, this->getContentSize().height - title->getContentSize().height - 10 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(title,4);
}
//void ServerListLayer::onReloginClick(Ref* pSender)
//{
//    EnterGameLayer::show();
//    this->removeFromParent();
//    
//    
//}
//void ServerListLayer::onConfirmClick(Ref* pSender)
//{
//    if(!m_nowSelectedData)
//    {
//        NoticeManager::getInstance()->showNotice("请选择服务器");
//        return;
//    }
//    ServerListDataManager::getInstance()->_nowServerData = m_nowSelectedData;
//    GlobalInfo::getInstance()->addressIP = m_nowSelectedData->IP;
//    GlobalInfo::getInstance()->port = m_nowSelectedData->port;
//   
//    onReloginClick(NULL);
//}
//void ServerListLayer::setConfirmBtn()
//{
//    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Button* reLogin = Button::create(IMG_SERVERLIST_CONFIRM, "", CC_CALLBACK_1(ServerListLayer::onConfirmClick, this));
//    reLogin->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(reLogin);
//    reLogin->setPosition(this->getContentSize().width - reLogin->getContentSize().width - 60 * sx, 30 * sx);
//    this->addChild(reLogin);
//}
void ServerListLayer::setServerTableView()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size size = cellSizeForTable(NULL);
    size.height = DISPLAY_COUNT * size.height;
    TableView* tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setPositionX(30 * sx);
    tableView->setPositionY(90 * sx);
//    tableView->reloadData();
    this->addChild(tableView,2,TAG_TABLEVIEW);

}
void ServerListLayer::showServerList(int index)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    
    Menu* menu = (Menu*)this->getChildByTag(TAG_SERVERLIST);
    if(menu)
    {
        menu->removeFromParent();
    }
    Menu* menu1 = (Menu*)this->getChildByTag(TAG_ALLLIST);
    if(menu1)
    {
        menu1->removeFromParent();
        this->removeChildByTag(TAG_LABEL);
    }
    
    menu = Menu::create();
    menu->setAnchorPoint(Point::ZERO);
    menu->setPosition(320 * sx, 423 * sx);
    this->addChild(menu,4,TAG_SERVERLIST);
    
    
    MenuItem* itemLabel = NULL;
    Node* node = NULL;
    ssize_t size = this->serverList->size();
    int startIndex = index * PAGENUM;
    int nowIndex = 0;
    for(int i = startIndex; i < startIndex + PAGENUM; i++)
    {
        if(i >= size)
        {
            break;
        }
        node = getServerNode(this->serverList->at(i));
        nowIndex = i - startIndex;
        itemLabel  = MenuItemLabel::create(node, CC_CALLBACK_1(ServerListLayer::onSelectedServer, this));
        itemLabel->setPosition((nowIndex % 2) * (itemLabel->getContentSize().width + 40), -(nowIndex / 2 * (itemLabel->getContentSize().height + 15)));
        menu->addChild(itemLabel,nowIndex,i);
    }
   
    if(itemLabel)
    {
        Size contentSize ;
        contentSize.width = itemLabel->getPositionX() + itemLabel->getContentSize().width;
        contentSize.height = abs(itemLabel->getPositionY());
        menu->setContentSize(contentSize);
        PublicShowUI::setTargetScale(menu);
    }
   
}
void ServerListLayer::showAllServerList(int index)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    //tittle
    int height = 350*sx;
    Menu* menuone = (Menu*)this->getChildByTag(TAG_SERVERLIST);
    if(menuone)
    {
        height = menuone->getPositionY();
    }
    Sprite* spr = Sprite::create(IMG_SERVERALLLIST_TITLE);
    spr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(spr);
    spr->setPosition((this->getContentSize().width - spr->getContentSize().width)/2 + 30*GlobalInfo::getInstance()->screenScaleX, height - spr->getContentSize().height-20*sx);
    this->addChild(spr,3,TAG_LABEL);
    
//    ServerAllListLayer* layer = ServerAllListLayer::create();
//    layer->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(layer);
//    layer->setPosition(350*sx,0);
//    this->addChild(layer,3,TAG_ALLLIST);
//    
    Menu* menu = Menu::create();
    menu->setAnchorPoint(Point::ZERO);
    
    
    
    MenuItem* itemLabel = NULL;
    Node* node = NULL;
    ssize_t size = this->recentList->size();
    int startIndex = index * PAGENUM;
    int nowIndex = 0;
    for(int i = startIndex; i < 10; i++)
    {
        if(i >= size)
        {
            break;
        }
        node = getServerNode(this->recentList->at(i));
        nowIndex = i - startIndex;
        itemLabel  = MenuItemLabel::create(node, CC_CALLBACK_1(ServerListLayer::onAllSelectedServer, this));
        itemLabel->setPosition((nowIndex % 2) * (itemLabel->getContentSize().width + 40), -(nowIndex / 2 * (itemLabel->getContentSize().height + 15)));
        menu->addChild(itemLabel,nowIndex,i);
    }
    
    if(itemLabel)
    {
        Size contentSize ;
        contentSize.width = itemLabel->getPositionX() + itemLabel->getContentSize().width;
        contentSize.height = abs(itemLabel->getPositionY());
        menu->setContentSize(contentSize);
        PublicShowUI::setTargetScale(menu);
    }
    
    menu->setPosition(320 * sx, spr->getPositionY() - menu->getContentSize().height-20*sx );
    this->addChild(menu,4,TAG_ALLLIST);
    
}
void ServerListLayer::onAllSelectedServer(Ref* pSender)
{
    int index = ((Node*)pSender)->getTag();
    
    m_nowSelectedData = recentList->at(index);
    
    setNowSelect();
}

void ServerListLayer::onSelectedServer(Ref* pSender)
{
    int index = ((Node*)pSender)->getTag();
   
    m_nowSelectedData = serverList->at(index);
    
    setNowSelect();
}
Node* ServerListLayer::getServerNode(ServerListData* data)
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
    //    itemImage->setNormalImage(Sprite::createWithSpriteFrameName(IMG_SERVERLIST_ITEMBG1));
    //    itemImage->setSelectedImage(Sprite::createWithSpriteFrameName(IMG_SERVERLIST_ITEMBG2));
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
Node* ServerListLayer::getNode(int index)
{
    log("index ==%d",index);
//     ServerListData* data = serverList->at(index);
    MenuItemImage* itemImage = MenuItemImage::create(IMG_SERVERLIST_AREAITEM,IMG_SERVERLIST_AREAITEM1);
//    itemImage->setNormalImage(Sprite::createWithSpriteFrameName(IMG_SERVERLIST_ITEMBG1));
//    itemImage->setSelectedImage(Sprite::createWithSpriteFrameName(IMG_SERVERLIST_ITEMBG2));
    itemImage->setAnchorPoint(Point::ZERO);
    string str = PublicShowUI::numberToString(index * PAGENUM + 1) + " - " + PublicShowUI::numberToString(index * PAGENUM + PAGENUM) + " 服";
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),20,false,false);
    itemImage->addChild(label);
    label->setPosition(itemImage->getContentSize().width/2, itemImage->getContentSize().height/2);
    PublicShowUI::setTargetScale(itemImage);
    
    return itemImage;
}

void ServerListLayer::setNowSelect()
{

    if(!m_nowSelectedData)
    {
        return;
    }
    ServerListDataManager::getInstance()->_nowServerData = m_nowSelectedData;
    this->backScene();
  
//    string str = "已选择   " + m_nowSelectedData->serverName;;
//    Label* label = (Label*)this->getChildByTag(TAG_NOWSELECT);
//    if(label)
//    {
//        label->setString(str.c_str());
//    }
//    else
//    {
//        label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_WHITE),18,false,true);
//        label->setAnchorPoint(Point::ZERO);
//        label->setPosition((this->getContentSize().width - label->getContentSize().width)/2, 35 * GlobalInfo::getInstance()->screenScaleX);
//        this->addChild(label,4,TAG_NOWSELECT);
//
//    }
}
Size ServerListLayer::cellSizeForTable(TableView *table)
{
    if(cellSize.width == 0)
    {
        cellSize = Sprite::create(IMG_SERVERLIST_AREAITEM)->getContentSize();
        cellSize.width *= GlobalInfo::getInstance()->screenScaleX;
        cellSize.height *= GlobalInfo::getInstance()->screenScaleX;
        cellSize.height += 5 * GlobalInfo::getInstance()->screenScaleX;
    }
    return cellSize;
}
TableViewCell* ServerListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = this->getNode(idx);
    cell->addChild(node, 0,0);
    cell->setTag(idx);
    return cell;
}
ssize_t ServerListLayer::numberOfCellsInTableView(TableView *table)
{
    return ceil((double)ServerListDataManager::getInstance()->getServerList()->size()/PAGENUM);
}
void ServerListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    if(!cell)
    {
        return;
    }
    serverList = NULL;
    serverList = ServerListDataManager::getInstance()->getServerList();
    MenuItemImage* itemLabel = (MenuItemImage*)cell->getChildByTag(0);
    if(curSelectedItem != NULL && curSelectedItem->getReferenceCount() > 0 && curSelectedItem->getParent())
    {
        curSelectedItem->unselected();
    }
    curSelectedItem = itemLabel;
    curSelectedItem->selected();
    this->showServerList(cell->getTag());
}
void ServerListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}
void ServerListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}
void ServerListLayer::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    MenuItemImage* itemLabel = (MenuItemImage*)cell->getChildByTag(0);
    if(itemLabel == this->curSelectedItem)
    {
        curSelectedItem->unselected();
        curSelectedItem = NULL;
    }
}
void ServerListLayer::backScene()
{
    EnterGameLayer::show();
    BaseLayer::backScene();
}