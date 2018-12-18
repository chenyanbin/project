//
//  MarketAuctionSellLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//

#include "MarketAuctionSellLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../common/TouchSprite/Button.h"

#include "../../../../message/Decoding/market/paimai/paimaiSellMsg/AuctionSellMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../marketData/auctionData/AuctionSellDataManager.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../message/Decoding/market/paimai/paimaiSellMsg/sureSellMsg/SureSellMsg.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../tips/TipsLayer.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../userWealth/UserEquipLayer.h"
MarketAuctionSellLayer::MarketAuctionSellLayer()
:listBg(NULL)
,now_count(17)
,_tableView(NULL)
,m_nowcount(1)
,TAG_COUNT(1)
,m_sellList(NULL)
,TAG_SELL(10)
,TAG_HEAD(11)
,TAG_COUNTSELL(14)
,m_selectedIndex(0)
{
    
}

MarketAuctionSellLayer::~MarketAuctionSellLayer()
{
    m_sellList = NULL;
    AuctionSellDataManager::getInstance()->destroyInstance();
}

bool MarketAuctionSellLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
//        createTableView();
        setrightBg();
        setPrice(m_nowcount);
        bref = true;
    } while (false);
    return bref;
}

MarketAuctionSellLayer* MarketAuctionSellLayer::create()
{
    MarketAuctionSellLayer* list = new MarketAuctionSellLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketAuctionSellLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketAuctionSellLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketAuctionSellLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestAuctionSellListMsg(0);
}
void MarketAuctionSellLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MarketAuctionSellLayer::setBackGround()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1);
    this->setContentSize(listBg->getContentSize());
    
}
void MarketAuctionSellLayer::setTableViewDelegate()
{
    _tableView->setDelegate(this);
}

void MarketAuctionSellLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        
        _tableView->reloadData();
        _tableView->getContainer()->stopAllActions();
        _tableView->stopAllActions();
        cp.y = 0;
        _tableView->setContentOffsetInDuration(cp, 0);
        
        DelayTime* delay = DelayTime::create(0.8);
        CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketAuctionSellLayer::setTableViewDelegate, this));
        _tableView->runAction(Sequence::create(delay,callBack, NULL));
        return;
    }

    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.width = _size.width*4+30;
    _size.height=_size.height*3;
    _tableView =TableView::create(this,_size);
    
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0,0));
    _tableView->setPosition(5,45);
    listBg->addChild(_tableView,4);
    _tableView->setDelegate(this);
    
}

UserEquipLayer* MarketAuctionSellLayer::singleList(ssize_t idx)
{
    if(idx >= m_sellList->size())
    {
        return NULL;
    }
    AuctionSellData* data = m_sellList->at(idx);
    //头像
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    head->setPosition(Point::ZERO);
    head->setTag(idx);
    head->addTouchBegainCallBack(this, callfuncN_selector(MarketAuctionSellLayer::onHeroHeadClick));
    
    return head;
}
//显示详情
void MarketAuctionSellLayer::onHeroHeadClick(Node* psender)//点击头像
{
    setrightLabel(psender->getTag());
}

TableViewCell* MarketAuctionSellLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<4; i++) {
        int tag=(int)idx*4+i;
        UserEquipLayer* list=singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX((list->getContentSize().width+10)*i+30);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    return cell;
}

//列表大小
Size MarketAuctionSellLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    if(cellSize.height == 0)
    {
        char sttr[100] = "";
        memset(sttr, 0, 100);
        sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
//        const char* pathbg = PublicShowUI::getResImgPath(IMG_PUBLIC_HEROHEADFRAMEBG,PublicShowUI::numberToString(1).c_str());
        Sprite* temp = Sprite::create(sttr);
        cellSize = temp->getContentSize();
        cellSize.width += 10;
        cellSize.height += 10;
    }
    return cellSize;
}
//获取view的长度
ssize_t MarketAuctionSellLayer::numberOfCellsInTableView(TableView *table)
{
    int allPage = ceil(double(m_sellList->size()) / 4);
    return allPage;
}
//点击cell事件
void MarketAuctionSellLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}
void MarketAuctionSellLayer::setrightBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
  
    Sprite* rightBg = Sprite::create(IMG_MARKET_AUCTION_RIGHTBG);
    rightBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(rightBg);
    this->addChild(rightBg,3);
    rightBg->setPosition(this->getContentSize().width/2+150*sx,40*sx);
    

    //装备减1
    Button* minus = Button::create(IMG_MARKET_AUCTION_MIN,IMG_MARKET_AUCTION_MIN,CC_CALLBACK_1(MarketAuctionSellLayer::setcount, this));
    minus->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(minus);
    minus->setPosition(this->getContentSize().width/2+210*sx,180*sx);
    this->addChild(minus,4,TAG_MINUS);
    //出售个数底层
    Sprite* priceBg = Sprite::create(IMG_MARKET_MARKETSHOP_PRICEBG);
    priceBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(priceBg);
    priceBg->setPosition(minus->getPositionX()+minus->getContentSize().width,minus->getPositionY()+7*sx);
    this->addChild(priceBg,4);
    //加1
    Button* addspr = Button::create(IMG_MARKET_AUCTION_ADD,IMG_MARKET_AUCTION_ADD,CC_CALLBACK_1(MarketAuctionSellLayer::setcount, this));
    addspr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(addspr);
    addspr->setPosition(priceBg->getPositionX()+priceBg->getContentSize().width,minus->getPositionY());
    this->addChild(addspr,4,TAG_ADD);
    
    editbox = EditBox::create(Size(100 * sx,30 * sx), Scale9Sprite::create(IMG_MARKET_MARKETSHOP_PRICEBG));
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setInputMode(EditBox::InputMode::PHONE_NUMBER);
    editbox->setDelegate(this);
    editbox->setPlaceHolder("输入价格");
    editbox->setPosition(Point(this->getContentSize().width/2+220*sx,133*sx));
    this->addChild(editbox,4);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
//    gold->setScale(0.8*sx);
    gold->setPosition(editbox->getPositionX()+editbox->getContentSize().width,editbox->getPositionY()-7*sx);
    this->addChild(gold,4);
   
    //出售
    Sprite* sellSpr = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    sellSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(sellSpr);
    sellSpr->setPosition(this->getContentSize().width/2+ 220*sx,65*sx);
    this->addChild(sellSpr,4);
    Button* sell = Button::create(IMG_MARKET_AUCTION_SELLWORD,IMG_MARKET_AUCTION_SELLWORD,CC_CALLBACK_1(MarketAuctionSellLayer::setSellEquip, this));
    sell->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(sell);
    sell->setPosition(this->getContentSize().width/2 + 220*sx,65*sx);
    this->addChild(sell,4);
}
void MarketAuctionSellLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    int num_int = std::atoi(text.c_str());//将字符串转成整型
    if (m_sellList->size()==0) {
        return;
    }
    if(num_int > m_sellList->at(m_selectedIndex)->priceHighest*m_nowcount )
    {
        num_int = m_sellList->at(m_selectedIndex)->priceHighest*m_nowcount;
    }
    char buf_str[16];
    sprintf(buf_str,"%d",num_int);//将int的数值放入buf_str中
    editBox->setText(buf_str);//重新设置editBox的值
}
void MarketAuctionSellLayer::editBoxReturn(cocos2d::extension::EditBox*){}
void MarketAuctionSellLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox*){}
void MarketAuctionSellLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox*){}

void MarketAuctionSellLayer::setrightLabel(int idx)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    if (m_sellList->size() == 0) {
        this->removeChildByTag(TAG_HEAD);
        this->removeChildByTag(TAG_SELL);
        this->removeChildByTag(TAG_COUNTSELL);
        return;
    }
    AuctionSellData* data = m_sellList->at(idx);
    //头像
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = (UserEquipLayer*)this->getChildByTag(TAG_HEAD);
    if (head) {
        head->removeFromParent();
    }
    head = UserEquipLayer::create(resource,data->quality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    PublicShowUI::setTargetScale(head);
    this->addChild(head,4,TAG_HEAD);
    head->setPosition(this->getContentSize().width/2+220*sx,310*sx);
    head->addTouchBegainCallBack(this, callfuncN_selector(MarketAuctionSellLayer::onitemHeadClick));
        
    //名字
    string sellnameStr = data->itemName;
    Label* sellnameLabel = (Label*)this->getChildByTag(TAG_SELL);
    if (sellnameLabel) {
        sellnameLabel->setString(sellnameStr.c_str());
    }
    else{
        sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
        sellnameLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(sellnameLabel);
        this->addChild(sellnameLabel,4,TAG_SELL);
    }
    sellnameLabel->setPosition(this->getContentSize().width/2+200*sx,235*sx);
    //可卖数量
    string allCountStr = StringUtils::format("(%d)",data->canSellCount);
    Label* alCountLabel = (Label*)this->getChildByTag(TAG_COUNTSELL);
    if(alCountLabel)
    {
        alCountLabel->setString(allCountStr.c_str());
    }
    else
    {
        alCountLabel = PublicShowUI::getLabel(allCountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
        alCountLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(alCountLabel);
        this->addChild(alCountLabel,4,TAG_COUNTSELL);
    }
     alCountLabel->setPosition(this->getContentSize().width/2+328*sx,236*sx);
    m_selectedIndex = idx;
}
void MarketAuctionSellLayer::onitemHeadClick(Node* psender)//查看物品详情
{
    AuctionSellData* data = m_sellList->at(m_selectedIndex);
    TipsLayer::show(data->itemType, data->itemId, data->canSellCount);
}
void MarketAuctionSellLayer::updateSellLabel(int idx)
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    AuctionSellData* data = m_sellList->at(idx);
    //可卖数量
    data->canSellCount -= m_nowcount;
    string allCountStr = StringUtils::format("(%d)",data->canSellCount);
    Label* alCountLabel = (Label*)this->getChildByTag(TAG_COUNTSELL);
    if(alCountLabel)
    {
        alCountLabel->setString(allCountStr.c_str());
    }
    else
    {
        alCountLabel = PublicShowUI::getLabel(allCountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        alCountLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(alCountLabel);
        this->addChild(alCountLabel,4,TAG_COUNTSELL);
    }
    alCountLabel->setPosition(this->getContentSize().width/2+328*sx,236*sx);
    if (data->canSellCount <= 0) {
        m_sellList->erase(idx);
        _tableView->reloadData();
        setrightLabel(0);
//        requestAuctionSellListMsg(0);
        
    }
}
void MarketAuctionSellLayer::setcount(Ref* psender)
{
    if (m_sellList->size()<1) {
        return;
    }
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case TAG_ADD:
            m_nowcount += 1;
            break;
        case TAG_MINUS:
            m_nowcount -= 1;
            break;
        default:
            break;
    }
    if (m_nowcount <= 1) {
        m_nowcount = 1;
    }
    if (m_nowcount>m_sellList->at(m_selectedIndex)->canSellCount) {
        m_nowcount = m_sellList->at(m_selectedIndex)->canSellCount;
    }
    setPrice(m_nowcount);
}
void MarketAuctionSellLayer::setPrice(int nowCount)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Label* countLabel = (Label*)this->getChildByTag(TAG_COUNT);
    string nowcountStr = StringUtils::format("%d",nowCount);
    if (countLabel) {
        countLabel->setString(nowcountStr);
    }else{
        countLabel = PublicShowUI::getLabel(nowcountStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
        countLabel->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(countLabel);
        this->addChild(countLabel,4,TAG_COUNT);
    }
    countLabel->setPosition(this->getContentSize().width/2+290*sx,190*sx);
//    if (nowCount == 0) {
//        requestAuctionSellListMsg(0);
//    }
    
}
void MarketAuctionSellLayer::setSellEquip(Ref* psender)
{
    if (m_sellList->size()<1) {
        NoticeManager::getInstance()->showNotice("无可出售物品");
        return;
    }
    AuctionSellData* data = m_sellList->at(m_selectedIndex);
    int  allCount = atoi(editbox->getText());
    if (allCount <= 0) {
        NoticeManager::getInstance()->showNotice("请填写售价");
        return;
    }
    if (allCount < data->priceLowest*m_nowcount) {
        string numCard = StringUtils::format("最低出售价为%d",data->priceLowest*m_nowcount);
        NoticeManager::getInstance()->showNotice(numCard.c_str());
        
        string numCard1 = StringUtils::format("%d",data->priceLowest*m_nowcount);
        editbox->setText(numCard1.c_str());
        allCount = data->priceLowest*m_nowcount;
        return;
    }
    requestSureAuctionSellListMsg(data->itemType,data->itemId,m_nowcount,allCount);
}

/******------------------------------------访问服务器------------------------------*************/

void MarketAuctionSellLayer::requestAuctionSellListMsg(int lastMarketGoodsId)//请求出售列表信息
{
    AuctionSellMsg* msg = new AuctionSellMsg(lastMarketGoodsId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketAuctionSellLayer::onAuctionSellMsg(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketToSellPageResp)
    {
        if(message->state)//返回成功
        {
            short itemCount= message->byteStream->getShort();
            AuctionSellDataManager::getInstance()->setItemCountData(itemCount);
            for (int i = 0; i < itemCount; i ++) {
                AuctionSellData* data = new AuctionSellData;
                data->autorelease();
                data->marketGoodsId = message->byteStream->getInt();
                data->itemId = message->byteStream->getInt();
                data->itemType = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                data->quality = message->byteStream->getByte();
                data->priceLowest = message->byteStream->getInt();
                data->priceHighest = message->byteStream->getInt();
                data->canSellCount = message->byteStream->getInt();
                AuctionSellDataManager::getInstance()->addData(data);
            }
            m_sellList = AuctionSellDataManager::getInstance()->sellList;
           
            if(itemCount)
            {
                createTableView();
                setrightLabel(0);
            }
            else
            {
                if(this->_tableView)
                {
                    this->stopAllActions();
                    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create(CC_CALLBACK_0(MarketAuctionSellLayer::setTableViewDelegate, this)), NULL));
                }
            }
        }
        else
        {
            return;
        }
    }
}

void MarketAuctionSellLayer::requestSureAuctionSellListMsg(int itemType, int itemId, int sellCount,int price)//请求出售列表信息
{
    SureSellMsg* msg = new SureSellMsg(itemType,itemId,sellCount,price);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MarketAuctionSellLayer::onAuctionSureSell(EventCustom* msg)//卖出
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_MARKET_MarketSellResp)
    {
        if(message->state)//返回成功
        {
            NoticeManager::getInstance()->showNotice("上架成功");
            updateSellLabel(m_selectedIndex);
        }
        else
        {
            return;
        }
    }
}
void MarketAuctionSellLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketToSellPageResp).c_str(), CC_CALLBACK_1(MarketAuctionSellLayer::onAuctionSellMsg, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MARKET_MarketSellResp).c_str(), CC_CALLBACK_1(MarketAuctionSellLayer::onAuctionSureSell, this));
}
void MarketAuctionSellLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void MarketAuctionSellLayer::scrollViewDidScroll(ScrollView* view)
{
    log("aaa");
    
    if(this->_tableView ->getContentOffset().y > cellSize.height / 2)
    {
        
        this->_tableView->setDelegate(NULL);
        
        requestAuctionSellListMsg(this->m_sellList->at(m_sellList->size()-1)->marketGoodsId);
        return;
    }
}

