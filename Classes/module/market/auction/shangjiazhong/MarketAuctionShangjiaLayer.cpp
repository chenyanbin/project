//
//  MarketAuctionShangjiaLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//

#include "MarketAuctionShangjiaLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../message/Decoding/market/paimai/paimaiShangjiaMsg/AuctionShangjiaMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../marketData/auctionData/AuctionShangjiaDataManger.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../message/Decoding/market/paimai/paimaiShangjiaMsg/surexuajiaMsg/SureXiajiaMsg.h"
#include "../../../../protocol/Protocal.h"
#include "AuctionSahngjiaCellLayer.h"
#include "../../../../common/noticeManager/NoticeManager.h"
MarketAuctionShangjiaLayer::MarketAuctionShangjiaLayer()
:listBg(NULL)
,_tableView(NULL)
,TAG_COUNTSELL(22)
,m_selectedIndex(1)
,isremove(false)
{
    
}

MarketAuctionShangjiaLayer::~MarketAuctionShangjiaLayer()
{
    AuctionShangjiaDataManger::getInstance()->destroyInstance();
}

bool MarketAuctionShangjiaLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
//        setrightBg(0);
        bref = true;
    } while (false);
    return bref;
}

MarketAuctionShangjiaLayer* MarketAuctionShangjiaLayer::create()
{
    MarketAuctionShangjiaLayer* list = new MarketAuctionShangjiaLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketAuctionShangjiaLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketAuctionShangjiaLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketAuctionShangjiaLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestAuctionsahngjiaListMsg(0);
}
void MarketAuctionShangjiaLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MarketAuctionShangjiaLayer::setBackGround()
{
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
}
void MarketAuctionShangjiaLayer::setTableViewDelegate()
{
    _tableView->setDelegate(this);
}
void MarketAuctionShangjiaLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->getContainer()->stopAllActions();
        _tableView->stopAllActions();
        cp.y = 0;
        _tableView->setContentOffsetInDuration(cp, 0);
        
        DelayTime* delay = DelayTime::create(.8);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketAuctionShangjiaLayer::setTableViewDelegate, this));
        _tableView->runAction(Sequence::create(delay,callBack, NULL));
        log("66666");
        return;
    }

    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-5;
    _tableView =TableView::create(this,_size);
    
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0,0));
    _tableView->setPosition(32,43);
    listBg->addChild(_tableView,2);
    _tableView->setDelegate(this);

}

TableViewCell* MarketAuctionShangjiaLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        AuctionSahngjiaCellLayer *list = AuctionSahngjiaCellLayer::create(tag);
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
Size MarketAuctionShangjiaLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
        Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
        cellSize = temp->getContentSize();
        cellSize.height += 3.5;
        cellSize.width = temp->getContentSize().width*2+10;
    }
    return cellSize;
}
//获取view的长度
ssize_t MarketAuctionShangjiaLayer::numberOfCellsInTableView(TableView *table)
{
    
//    int cellcount = (AuctionShangjiaDataManger::getInstance()->shangjiaList->size()+1)/2 ;
//    int countcell = (AuctionShangjiaDataManger::getInstance()->shangjiaList->size())/2 ;
//    log("%d",AuctionShangjiaDataManger::getInstance()->shangjiaList->size()%2 == 1 ? cellcount : countcell);
//    return AuctionShangjiaDataManger::getInstance()->shangjiaList->size()%2 == 1 ? cellcount : countcell;
    
    int allPage = ceil(double(AuctionShangjiaDataManger::getInstance()->shangjiaList->size()) / 2);
    if(allPage<3)
        allPage = 3;
    return allPage;
}
//点击cell事件
void MarketAuctionShangjiaLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}

void MarketAuctionShangjiaLayer::onReceiveXiajiaMsg(EventCustom* msg)//接收下架信息
{
    isremove = true;
    __Integer* inter = (__Integer*)msg->getUserData();
    m_selectedIndex = inter->getValue();
    AuctionShangjiaDataManger::getInstance()->shangjiaList->erase(m_selectedIndex);
    
    if(m_selectedIndex>6)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->getContainer()->stopAllActions();
        _tableView->stopAllActions();
        _tableView->setContentOffsetInDuration(cp, 0);
    }else{
        _tableView->reloadData();
    }
    
    
}
void MarketAuctionShangjiaLayer::scrollViewDidScroll(ScrollView* view)
{
    if(AuctionShangjiaDataManger::getInstance()->shangjiaList->size()<5)
    {
        return;
    }
    if(this->_tableView ->getContentOffset().y > cellSize.height / 2)
    {
        
        this->_tableView->setDelegate(NULL);
        if (isremove) {
            isremove = false;
        }else{
            requestAuctionsahngjiaListMsg(AuctionShangjiaDataManger::getInstance()->shangjiaList->at(AuctionShangjiaDataManger::getInstance()->shangjiaList->size()-1)->sellId);
        }
        return;
    }
    
}
/******------------------------------------访问服务器------------------------------*************/

void MarketAuctionShangjiaLayer::requestAuctionsahngjiaListMsg(int lastMarketGoodsId)//请求上架中列表信息
{
    isremove = false;
    Dialog::showServerLoading();
    AuctionShangjiaMsg* msg = new AuctionShangjiaMsg(lastMarketGoodsId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketAuctionShangjiaLayer::onAuctionshangjiaMsg(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketMySellPageResp)
    {
        if(message->state)//返回成功
        {
            short itemCount= message->byteStream->getShort();
            AuctionShangjiaDataManger::getInstance()->setItemCountData(itemCount);
            for (int i = 0; i < itemCount; i ++) {
                AuctionShangjiaData* data = new AuctionShangjiaData;
                data->autorelease();
                data->sellId = message->byteStream->getInt();
                data->itemId = message->byteStream->getInt();
                data->itemType = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->price = message->byteStream->getInt();
                data->sellCount = message->byteStream->getInt();
                data->remainingTimes = message->byteStream->getInt();
                if(data->remainingTimes>0)
                {
                    AuctionShangjiaDataManger::getInstance()->addData(data);
                }
            }
    
            
            size_t  count = AuctionShangjiaDataManger::getInstance()->shangjiaList->size();
            if(count > 0)
            {
                if(itemCount<=0)
                {
                    return;
                }else{
                    createTableView();
                    log("11111111");

                }
            }
            else
            {
                if(this->_tableView)
                {
                    this->stopAllActions();
                    this->runAction(Sequence::create(DelayTime::create(2),CallFunc::create(CC_CALLBACK_0(MarketAuctionShangjiaLayer::setTableViewDelegate, this)), NULL));
                    log("3333333");
                }
                
                
            }
        }
       
    }
    
}
void MarketAuctionShangjiaLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketMySellPageResp).c_str(), CC_CALLBACK_1(MarketAuctionShangjiaLayer::onAuctionshangjiaMsg, this));
    this->addUserMsg(CUSTOM_MARKER_XIAJIABTN, CC_CALLBACK_1(MarketAuctionShangjiaLayer::onReceiveXiajiaMsg, this));
}
void MarketAuctionShangjiaLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}



