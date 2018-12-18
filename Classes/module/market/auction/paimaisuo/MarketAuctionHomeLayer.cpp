//
//  MarketAuctionHomeLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//

#include "MarketAuctionHomeLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "AuctionSureBuyLayer.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../../message/Decoding/market/paimai/paimaiHomeMsg/AuctionHomeMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../marketData/auctionData/AuctionHomeDataManager.h"
#include "AuctionHomeCellLayer.h"
#include "../../../../common/noticeManager/NoticeManager.h"
MarketAuctionHomeLayer::MarketAuctionHomeLayer()
:listBg(NULL)
,now_count(2)
,_tableView(NULL)
,m_homeList(NULL)
,TAG_TIME(10)
,timess(1)
,isMoveing(false)
,isDownPoint(Point::ZERO)
,m_isrearch(false)
,m_isscroll(true)
{
    
}

MarketAuctionHomeLayer::~MarketAuctionHomeLayer()
{
    AuctionHomeDataManager::destroyInstance();
    m_homeList = NULL;
}

bool MarketAuctionHomeLayer::init()
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

MarketAuctionHomeLayer* MarketAuctionHomeLayer::create()
{
    MarketAuctionHomeLayer* list = new MarketAuctionHomeLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketAuctionHomeLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketAuctionHomeLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketAuctionHomeLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestAuctionHomeListMsg("",0);
}
void MarketAuctionHomeLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MarketAuctionHomeLayer::setBackGround()
{
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
 
}
void MarketAuctionHomeLayer::setTableViewDelegate()
{
    _tableView->setDelegate(this);
}
void MarketAuctionHomeLayer::createTableView()
{
    if(_tableView)
    {
        if (m_isrearch) {
            _tableView->reloadData();
            return;
        }
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->getContainer()->stopAllActions();
        _tableView->stopAllActions();
        cp.y = 0;
        _tableView->setContentOffsetInDuration(cp, 0);
        DelayTime* delay = DelayTime::create(.8);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketAuctionHomeLayer::setTableViewDelegate, this));
        _tableView->runAction(Sequence::create(delay,callBack, NULL));
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-5;
    _tableView =TableView::create(this,_size);
   
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0,0));
    _tableView->setPosition(30,43);
    listBg->addChild(_tableView,2);
     _tableView->setDelegate(this);

}

TableViewCell* MarketAuctionHomeLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        AuctionHomeCellLayer* list = AuctionHomeCellLayer::create(tag);
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
Size MarketAuctionHomeLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
        Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
        cellSize = temp->getContentSize();
        cellSize.height += 3.5;
        cellSize.width = temp->getContentSize().width *2+10;
    }
    return cellSize;
}
//获取view的长度
ssize_t MarketAuctionHomeLayer::numberOfCellsInTableView(TableView *table)
{
//    int allPage = ceil(double(m_homeList->size()) / 2);
//    if (AuctionHomeDataManager::getInstance()->homeList->size() == 1) {
//        allPage = 1;
//    }
//    return allPage;
    
    int allPage = ceil(double(m_homeList->size()) / 2);
    if(allPage<3)
        allPage = 3;
    return allPage;
}
//点击cell事件
void MarketAuctionHomeLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{

}
void MarketAuctionHomeLayer::updataAuctuon(EventCustom* msg)
{
    if(m_isrearch){
        requestAuctionHomeListMsg("",0);
    }else{
        __Integer* inter = (__Integer*)msg->getUserData();
        int idx = inter->getValue();
        AuctionHomeDataManager::getInstance()->homeList->erase(idx);
        _tableView->reloadData();
    }
    
    
    
}
void MarketAuctionHomeLayer::scrollViewDidScroll(ScrollView* view)
{

    if (!m_isscroll) {
        return;
    }
    if(this->_tableView ->getContentOffset().y > cellSize.height / 2)
    {
        if (m_isrearch)
        {
            m_isrearch = false;
            requestAuctionHomeListMsg("",0);
        }
        else
        {
            this->_tableView->setDelegate(NULL);
            log("%d",this->m_homeList->at(m_homeList->size()-1)->sellId);
            requestAuctionHomeListMsg("",this->m_homeList->at(m_homeList->size()-1)->sellId);
        }
    }
    return;
}
bool MarketAuctionHomeLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void MarketAuctionHomeLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
}
void MarketAuctionHomeLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    BaseLayer::onTouchEnded(touch, unused_event);
}

void MarketAuctionHomeLayer::setOnSerch(EventCustom* msg)
{
    __String* str = (__String*)msg->getUserData();
    const char* name = str->getCString();
    m_isrearch = true;
    long s=strlen(name);
    log("%ld",s);
    if (s <= 0) {
        NoticeManager::getInstance()->showNotice("请输入搜索物品名称");
    }else{
        requestAuctionHomeListMsg(name,0);

    }
}
/******------------------------------------访问服务器------------------------------*************/

void MarketAuctionHomeLayer::requestAuctionHomeListMsg(const char* itemName,int lastSellId)//请求拍卖所列表信息
{
    Dialog::showServerLoading(.2);
    AuctionHomeMsg* msg = new AuctionHomeMsg(itemName,lastSellId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketAuctionHomeLayer::onAuctionHomeMsg(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    m_isscroll = true;
    if (m_isrearch) {
        m_isscroll = false;
//        AuctionHomeDataManager::getInstance()->clearAuctionHomeList();
    }
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketSellPageResp)
    {
        if(message->state)//返回成功
        {
            short itemCount = message->byteStream->getShort();
            if (itemCount>=1&&m_isrearch) {
                AuctionHomeDataManager::getInstance()->clearAuctionHomeList();
            }
            AuctionHomeDataManager::getInstance()->setItemCountData(itemCount);
            for (int i = 0; i < itemCount; i ++) {
                AuctionHomeData* data = new AuctionHomeData;
                data->autorelease();
                data->sellId = message->byteStream->getInt();
                data->itemId = message->byteStream->getInt();
                data->itemType = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->price = message->byteStream->getInt();
                data->sellCount = message->byteStream->getInt();
                data->sellRoleName = message->byteStream->getUTF8();
                data->remainingTimes = message->byteStream->getInt();
                if (data->remainingTimes>0) {
                    AuctionHomeDataManager::getInstance()->addData(data);
                }
            }
            m_homeList = AuctionHomeDataManager::getInstance()->homeList;
            log("itemCount=%d m_homeList->size-==%ld",itemCount,m_homeList->size());
            if(itemCount)
            {
                createTableView();
            }
            else
            {
                if(this->_tableView)
                {
                    this->stopAllActions();
                    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create(CC_CALLBACK_0(MarketAuctionHomeLayer::setTableViewDelegate, this)), NULL));
                }
                if (m_isrearch) {
                    NoticeManager::getInstance()->showNotice("搜索不到您要找的物品！");
//                    requestAuctionHomeListMsg("",0);
                }
            }
        }
    }
}

void MarketAuctionHomeLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketSellPageResp).c_str(), CC_CALLBACK_1(MarketAuctionHomeLayer::onAuctionHomeMsg, this));
    this->addUserMsg(CUSTOM_MARKER_SUCCEEDBUY, CC_CALLBACK_1(MarketAuctionHomeLayer::updataAuctuon, this));
    this->addUserMsg(CUSTOM_MARKET_SETCH, CC_CALLBACK_1(MarketAuctionHomeLayer::setOnSerch, this));

}
void MarketAuctionHomeLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
