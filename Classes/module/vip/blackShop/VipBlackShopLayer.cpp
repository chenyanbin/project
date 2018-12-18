//
//  VipBlackShopLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/8.
//
//

#include "VipBlackShopLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/Dialog/Dialog.h"

#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/vip/blackshop/RequesBlackshopListMsg.h"
#include "../vipdata/VipBlackShopManager.h"

#include "../../tips/TipsLayer.h"
#include "VipBlackShopBuyLayer.h"
#include "UpdataBlackshopLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/enum/DictRolePropEnum.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
VipBlackShopLayer::VipBlackShopLayer()
:listBg(NULL)
,_tableView(NULL)
,m_todayBuyCount(1)
,m_maxBuyCount(1)
,TAG_TABLEVIEW(10)
,m_selectedIndex(1)
,m_refreshRemainingTimes(1)
,m_manualFrfreshGold(1)
,label(NULL)
,m_isshuaxin(false)
,TAG_LABELTIME(20)
,isMoveing(false)
{
    
}

VipBlackShopLayer::~ VipBlackShopLayer()
{
    VipBlackShopManager::getInstance()->destroyInstance();
}

bool VipBlackShopLayer::init()
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

VipBlackShopLayer* VipBlackShopLayer::create()
{
    VipBlackShopLayer* list = new VipBlackShopLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void VipBlackShopLayer::onEnter()
{
    BaseLayer::onEnter();
}
void VipBlackShopLayer::onExit()
{
    BaseLayer::onExit();
}
void VipBlackShopLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestListMsg(0,0);
}
void VipBlackShopLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void VipBlackShopLayer::setBackGround()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,2);
    this->setContentSize(listBg->getContentSize());

//    Sprite* listbgbox = Sprite::create(IMG_MARKET_AUCTION_CELLBGBOX);
//    listbgbox->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(listbgbox);
//    listbgbox->setPosition(Point::ZERO);
//    this->addChild(listbgbox,10);
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
    this->addChild(listBg2,3);
    
    Sprite* remaintimeBg = Sprite::create(IMG_VIP_BLACKSHOP_RELEATETIME);
    remaintimeBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(remaintimeBg);
    remaintimeBg->setPosition(this->getContentSize().width/2-remaintimeBg->getContentSize().width/2 + 100*sx ,listBg->getPositionY()+480*sx);
    this->addChild(remaintimeBg,4);
    
    
    
    Button* serch = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(VipBlackShopLayer::onUpdataBtn, this));
    serch->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(serch);
    serch->setPosition(listBg->getContentSize().width-serch->getContentSize().width-30*sx,listBg->getPositionY()+475*sx);
    this->addChild(serch,5);
    
    Sprite* serchSpr = Sprite::create(IMG_VIP_BLACKSHOP_SHUAXIN);
    serchSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(serchSpr);
    serchSpr->setPosition(listBg->getContentSize().width-serchSpr->getContentSize().width-30*sx,listBg->getPositionY()+475*sx);
    this->addChild(serchSpr,7);
    
    
}
void VipBlackShopLayer::setlasttime()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string recuittime=StringUtils::format("%02ld:%02ld:%02ld",m_refreshRemainingTimes/3600, m_refreshRemainingTimes%3600/60,m_refreshRemainingTimes%60);
    label = (Label*)this->getChildByTag(TAG_LABELTIME);
    if (label) {
        label->setString(recuittime);
    }else{
        label = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),20,false,false);
        label->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(label);
        this->addChild(label,10,TAG_LABELTIME);
    }
    label->setPosition(this->getContentSize().width/2-label->getContentSize().width/2 + 130*sx ,listBg->getPositionY()+480*sx);
    schedule(schedule_selector(VipBlackShopLayer::update),1);
}
void VipBlackShopLayer::update(float delta)
{
    m_refreshRemainingTimes -= 1;
    if (m_refreshRemainingTimes <= 0) {
        m_refreshRemainingTimes =0;
        
        log("aaaaaaaaaaaaaaaa");
        unschedule(schedule_selector(VipBlackShopLayer::update));
        m_isshuaxin = true;
        requestListMsg(1,1);
        return;
    }
    char* mtime = new char[10];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld:%02ld:%02ld",m_refreshRemainingTimes/3600, m_refreshRemainingTimes%3600/60, m_refreshRemainingTimes%60);
    label->setString(mtime);
}

//刷新
void VipBlackShopLayer::onUpdataBtn(Ref* psender)
{
    log("shuaxin");
    if (m_manualFrfreshGold<=0){
        requestListMsg(1, 0);
        return;
    }
    UpdataBlackshopLayer::show(m_manualFrfreshGold);
}
void VipBlackShopLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+_size.height/2-5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(32,43);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* VipBlackShopLayer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    if(idx >= VipBlackShopManager::getInstance()->bsList->size())
    {
        return NULL;
    }
    
    VipBlackshopData* data = VipBlackShopManager::getInstance()->bsList->at(idx);
    
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    UserEquipLayer* head = UserEquipLayer::create(resource,data->itemQuality,false);
    head->setAnchorPoint(Point::ZERO);
    if (data->itemType == 4) {
        head->setFragment();
    }else if (data->itemType == 3)
    {
        head->setLetterFragment();
    }
    head->setTag(idx);
    head->setPosition(22,26);
    layerBg->addChild(head,1);
    head->addTouchBegainCallBack(this, callfuncN_selector(VipBlackShopLayer::onitemClick));
    
    //道具名称背景
    Sprite* namebg = Sprite::create(IMG_MARKET_MARKETSHOP_DAOJUBG);
    namebg->setAnchorPoint(Point::ZERO);
    namebg->setPosition(150,110);
    layerBg->addChild(namebg,1);
    string sellnameStr = data->itemName  + "x" + PublicShowUI::numberToString(data->count);
    Label* sellnameLabel = PublicShowUI::getLabel(sellnameStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    sellnameLabel->setAnchorPoint(Point::ZERO);
    sellnameLabel->setPosition(10,2);
    namebg->addChild(sellnameLabel,4);
    
    //购买按钮
    Button* buyBg = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,IMG_PUBLIC_BUTTON_TWO_ORANGE,CC_CALLBACK_1(VipBlackShopLayer::onClick, this));
    buyBg->setAnchorPoint(Point::ZERO);
    buyBg->setPosition(layerBg->getContentSize().width-buyBg->getContentSize().width-10,10);
    layerBg->addChild(buyBg,1,idx);
    Sprite* beginxunfangSpr=Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
    beginxunfangSpr->setAnchorPoint(Point::ZERO);
    beginxunfangSpr->setPosition(Point::ZERO);
    buyBg->addChild(beginxunfangSpr,4);
    if (data->status == 2) {
        buyBg->setEnabled(false);
        buyBg->setVisible(false);
        string openlevelStr = StringUtils::format("%d",data->openVipLevel);;
        openlevelStr = "VIP"+openlevelStr+"开启";
        Label* openlevel = PublicShowUI::getLabel(openlevelStr.c_str(),PublicShowUI::getColor3b(COLOR_LOW_RED),20,false,false);
        openlevel->setAnchorPoint(Point::ZERO);
        openlevel->setPosition(150,20);
        layerBg->addChild(openlevel,4);
    }
    else if (data->status == 3)
    {
        buyBg->setEnabled(false);
        buyBg->setVisible(false);
        string openlevelStr = "已购买";
        Label* openlevel = PublicShowUI::getLabel(openlevelStr.c_str(),PublicShowUI::getColor3b(COLOR_LOW_RED),20,false,false);
        openlevel->setAnchorPoint(Point::ZERO);
        openlevel->setPosition(150,20);
        layerBg->addChild(openlevel,4);
    }

    //原价
    int oleCount = data->priceOri;
    string oleCountStr = StringUtils::format("原价 %d",oleCount);;
    Label* oleCountLabel = PublicShowUI::getLabel(oleCountStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    oleCountLabel->setAnchorPoint(Point::ZERO);
    oleCountLabel->setPosition(150,80);
    layerBg->addChild(oleCountLabel,2);
    
    Sprite* olegold = NULL;
    if (data->conId == DictRolePropEnumCoin) {
        olegold = Sprite::create(IMG_ICON_PUBLIC_COIN);
    }else{
        olegold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    }
    olegold->setAnchorPoint(Point::ZERO);
    olegold->setScale(0.5);
    olegold->setPosition(oleCountLabel->getPositionX()+oleCountLabel->getContentSize().width,oleCountLabel->getPositionY()-2);
    layerBg->addChild(olegold,2);
    Sprite* lineSpr = Sprite::create(IMG_MARKET_MARKETSHOP_REMOVELINE);
    lineSpr->setAnchorPoint(Point::ZERO);
    lineSpr->setPosition(oleCountLabel->getPositionX()-5,oleCountLabel->getPositionY()+oleCountLabel->getContentSize().height/2-lineSpr->getContentSize().height/2);
    layerBg->addChild(lineSpr,3);
    
    //现价
    int money = data->price;
    string moneyStr = StringUtils::format("限时折扣 %d",money);
    Label* moneyLabel = PublicShowUI::getLabel(moneyStr.c_str(),PublicShowUI::getColor3b(COLOR_SKILL_LIGHT_YELLOW),20,false,false);
    moneyLabel->setAnchorPoint(Point::ZERO);
    moneyLabel->setPosition(150,50);
    layerBg->addChild(moneyLabel,4);
    Sprite* gold = NULL;
    if (data->conId == DictRolePropEnumCoin) {
        gold = Sprite::create(IMG_ICON_PUBLIC_COIN);
    }else{
        gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    }
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.5);
    gold->setPosition(moneyLabel->getPositionX()+moneyLabel->getContentSize().width+5,moneyLabel->getPositionY()-2);
    layerBg->addChild(gold,2);
    
    return layerBg;
}
void VipBlackShopLayer::onitemClick(Node* pSender)
{
    if (!isMoveing) {
        VipBlackshopData* data = VipBlackShopManager::getInstance()->bsList->at(pSender->getTag());
        TipsLayer::show(data->itemType, data->itemId,0);
    }
}
//购买
void VipBlackShopLayer::onClick(Ref* psender)
{
    Node* target = (Node*)psender;
    VipBlackShopBuyLayer::show(target->getTag());
    m_selectedIndex = target->getTag();
}


TableViewCell* VipBlackShopLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size VipBlackShopLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    cellSize.height = temp->getContentSize().height+3.5;
    cellSize.width = temp->getContentSize().width*2+10;
    
    return cellSize;
}
//获取view的长度
ssize_t VipBlackShopLayer::numberOfCellsInTableView(TableView *table)
{
    
    int allPage = ceil(double(VipBlackShopManager::getInstance()->bsList->size()) / 2);
    return allPage;
}
//点击cell事件
void VipBlackShopLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
    this->isMoveing = false;
}
void VipBlackShopLayer::onShuaxinProcess(EventCustom* msg)//刷新
{
    m_isshuaxin = true;
    requestListMsg(1,0);
}
void VipBlackShopLayer::onbuyProgress(EventCustom* msg)
{
    VipBlackShopManager::getInstance()->bsList->at(m_selectedIndex)->status = 3;
    _tableView->reloadData();
//    _tableView->updateCellAtIndex(m_selectedIndex);
}
void VipBlackShopLayer::scrollViewDidScroll(ScrollView* view)
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
void VipBlackShopLayer::requestListMsg(int refresh, int free)//请求列表信息
{
    Dialog::showServerLoading();
    RequesBlackshopListMsg* msg = new RequesBlackshopListMsg(refresh, free);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void VipBlackShopLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    VipBlackShopManager::getInstance()->clearblackshopList();
    if(message->messageID == SCENSE_CLIENT_BLACK_BlackPageResp)
    {
        if(message->state)//返回成功
        {
         
            m_refreshRemainingTimes = message->byteStream->getInt();
            m_manualFrfreshGold = message->byteStream->getInt();
            int shopCount = message->byteStream->getByte();
            for (int i = 0; i < shopCount; i ++) {
                VipBlackshopData* data = new VipBlackshopData;
                data->autorelease();
                data->shopId = message->byteStream->getInt();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemName = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                data->status = message->byteStream->getByte();
                data->priceOri = message->byteStream->getInt();
                data->price = message->byteStream->getInt();
                data->openVipLevel = message->byteStream->getInt();
                data->count = message->byteStream->getInt();
                data->conId = message->byteStream->getInt();
                
                VipBlackShopManager::getInstance()->addData(data);
            }
            if (m_isshuaxin == true) {
                unschedule(schedule_selector(VipBlackShopLayer::update));
//                broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumBlackShop));
            }
            this->createTableView();
            this->setlasttime();
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumBlackShop));
        }
    }
}
void VipBlackShopLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BLACK_BlackPageResp).c_str(), CC_CALLBACK_1(VipBlackShopLayer::onMsgProcess, this));
    this->addUserMsg(CUSTOM_VIP_BLACKSHOP_SHHUAXIN, CC_CALLBACK_1(VipBlackShopLayer::onShuaxinProcess, this));
    this->addUserMsg(CUSTOM_VIP_BLACKSHOP_BUY, CC_CALLBACK_1(VipBlackShopLayer::onbuyProgress, this));
}
void VipBlackShopLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}