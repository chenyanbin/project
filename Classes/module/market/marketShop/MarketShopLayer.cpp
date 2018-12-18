//
//  MarketShopLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/27.
//
//

#include "MarketShopLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/market/shop/ShopPageListMsg/ShopPageListMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../marketData/ShopPageListDataManager.h"
#include "MarketPurchaseLayer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../tips/TipsLayer.h"
MarketShopLayer::MarketShopLayer()
:listBg(NULL)
,_tableView(NULL)
,m_todayBuyCount(1)
,m_maxBuyCount(1)
,TAG_TABLEVIEW(10)
,m_selectedIndex(1)
,isMoveing(false)
{
    
}

MarketShopLayer::~MarketShopLayer()
{
    ShopPageListDataManager::getInstance()->destroyInstance();
}

bool MarketShopLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
        bref = true;
    } while (false);
    return bref;
}

MarketShopLayer* MarketShopLayer::create()
{
    MarketShopLayer* list = new MarketShopLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketShopLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketShopLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketShopLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestListMsg();
}
void MarketShopLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MarketShopLayer::setBackGround()
{
   
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,5);
    this->setContentSize(listBg->getContentSize());
    
//    Sprite* listbgbox = Sprite::create(IMG_MARKET_AUCTION_CELLBGBOX);
//    if(listbgbox)
//    {
//        listbgbox->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(listbgbox);
//        listbgbox->setPosition(Point::ZERO);
//        this->addChild(listbgbox,10);
//    }
    
}
void MarketShopLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }

    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height * 3 - 50;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32,55);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
    
    
}
Sprite* MarketShopLayer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    if(idx >= ShopPageListDataManager::getInstance()->shopList->size())
    {
        return NULL;
    }

    ShopPageListData* data = ShopPageListDataManager::getInstance()->shopList->at(idx);
     
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    head->setTag(idx);
    head->addTouchBegainCallBack(this, callfuncN_selector(MarketShopLayer::onshopitemClick));
    head->setPosition(22,26);
    layerBg->addChild(head,1);
    
    //道具名称背景
    Sprite* namebg = Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    namebg->setAnchorPoint(Point::ZERO);
    namebg->setPosition(150,110);
    layerBg->addChild(namebg,1);
    string sellnameStr = data->itemName;
    Label* sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    sellnameLabel->setAnchorPoint(Point::ZERO );
    sellnameLabel->setPosition(10,2);
    namebg->addChild(sellnameLabel,4);
    
    //原价
    int oleCount = data->gold;
    string oleCountStr = StringUtils::format("原价 %d",oleCount);;
    Label* oleCountLabel = PublicShowUI::getLabel(oleCountStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    oleCountLabel->setAnchorPoint(Point::ZERO);
    oleCountLabel->setPosition(150,80);
    layerBg->addChild(oleCountLabel,2);
    Sprite* olegold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    olegold->setAnchorPoint(Point::ZERO);
    olegold->setScale(0.5);
    olegold->setPosition(oleCountLabel->getPositionX()+oleCountLabel->getContentSize().width,oleCountLabel->getPositionY()-2);
    layerBg->addChild(olegold,2);
    Sprite* lineSpr = Sprite::create(IMG_MARKET_MARKETSHOP_REMOVELINE);
    lineSpr->setAnchorPoint(Point::ZERO);
    lineSpr->setPosition(oleCountLabel->getPositionX()-5,oleCountLabel->getPositionY()+oleCountLabel->getContentSize().height/2-lineSpr->getContentSize().height/2);
    layerBg->addChild(lineSpr,3);
    
    //限时折扣
    int money = data->goldnow;
    string moneyStr = StringUtils::format("限时折扣 %d",money);
    Label* moneyLabel = PublicShowUI::getLabel(moneyStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    moneyLabel->setAnchorPoint(Point::ZERO);
    moneyLabel->setPosition(150,45);
    layerBg->addChild(moneyLabel,4);
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.5);
    gold->setPosition(moneyLabel->getPositionX()+moneyLabel->getContentSize().width,moneyLabel->getPositionY()-2);
    layerBg->addChild(gold,2);

    //购买按钮
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MarketShopLayer::onClick, this));
    btn->setAnchorPoint(Point::ZERO);
    btn->setPosition(layerBg->getContentSize().width-btn->getContentSize().width-10,60);
    layerBg->addChild(btn,1,idx);
    Sprite* sprword = Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
    sprword->setAnchorPoint(Point::ZERO);
    sprword->setPosition(Point::ZERO);
    btn->addChild(sprword,4);
    
    //购买次数
    if (data->todayBuyCount < data->maxBuyCount) {
        int times = data->maxBuyCount - data->todayBuyCount;
        string shopTimesStr = StringUtils::format("今日可购买个数:%d",times);;
        Label* shopTimesLabel = PublicShowUI::getLabel(shopTimesStr.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),15,false,false);
        shopTimesLabel->setAnchorPoint(Point::ZERO);
        shopTimesLabel->setPosition(150,20);
        layerBg->addChild(shopTimesLabel,2);
    }else
    {
        btn->setEnabled(false);
        btn->setVisible(false);
        string shopTimesStr = "已达购买上限";;
        Label* shopTimesLabel = PublicShowUI::getLabel(shopTimesStr.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),15,false,false);
        shopTimesLabel->setAnchorPoint(Point::ZERO);
        shopTimesLabel->setPosition(150,20);
        layerBg->addChild(shopTimesLabel,2);
        
        Sprite* sellout = Sprite::create(IMG_PUBLIC_LABEL_SHOP_SELLOUT);
        sellout->setAnchorPoint(Point::ZERO);
        layerBg->addChild(sellout,5);
        sellout->setPosition(layerBg->getContentSize().width-btn->getContentSize().width-30,30);
    }

    
    return layerBg;
}
void MarketShopLayer::onshopitemClick(Node* pSender)
{
    
    if(isMoveing)
    {
        return;
    }
    ShopPageListData* data = ShopPageListDataManager::getInstance()->shopList->at(pSender->getTag());
    TipsLayer::show(data->itemType,data->itemId, 0);
}
//购买
void MarketShopLayer::onClick(Ref* psender)
{
    Node* target = (Node*)psender;
    MarketPurchaseLayer::show(target->getTag());
    m_selectedIndex = target->getTag();
}


TableViewCell* MarketShopLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++) {
        int tag=(int)idx*2+i;
        Sprite* list = singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX(420*i);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    
    return cell;
}

//列表大小
Size MarketShopLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width *2+10;
    return cellSize;
}
//获取view的长度
ssize_t MarketShopLayer::numberOfCellsInTableView(TableView *table)
{

    int allPage = ceil(double(ShopPageListDataManager::getInstance()->shopList->size()) / 2);
    return allPage;
}
//点击cell事件
void MarketShopLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
    isMoveing = false;
}

void MarketShopLayer::onUpdataCell(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    int buycount = inter->getValue();
    ShopPageListData* data = ShopPageListDataManager::getInstance()->shopList->at(m_selectedIndex);
    data->todayBuyCount += buycount;
    data->ownCount += buycount;
    int idx = ceil(double(m_selectedIndex/2));
    _tableView->updateCellAtIndex(idx);
}
void MarketShopLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
/******------------------------------------访问服务器------------------------------*************/
void MarketShopLayer::requestListMsg()//请求列表信息
{
    Dialog::showServerLoading();
    ShopPageListMsg* msg = new ShopPageListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketShopLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    ShopPageListDataManager::getInstance()->clearshopList();
    if(message->messageID == SCENSE_CLIENT_SHOP_ShopPageResp)
    {
        if(message->state)//返回成功
        {
            short itemSize = message->byteStream->getShort();
            for (int i = 0; i < itemSize; i ++) {
                ShopPageListData* data = new ShopPageListData;
                data->autorelease();
                data->shopId = message->byteStream->getInt();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemName = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->desc = message->byteStream->getUTF8();
                data->gold = message->byteStream->getInt();
                data->goldnow = message->byteStream->getInt();
                data->todayBuyCount = message->byteStream->getInt();
                data->maxBuyCount = message->byteStream->getInt();
                data->ownCount = message->byteStream->getInt();
                ShopPageListDataManager::getInstance()->addData(data);
            }
            this->createTableView();
        }
    }
    
}

void MarketShopLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SHOP_ShopPageResp).c_str(), CC_CALLBACK_1(MarketShopLayer::onMsgProcess, this));
    this->addUserMsg(CUSTOM_MARKER_UPDATASHOP, CC_CALLBACK_1(MarketShopLayer::onUpdataCell, this));
}
void MarketShopLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
