//
//  MailAllGiftLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#include "MailAllGiftLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"

#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "MailPageLayer.h"
#include "maildata/MailAllGiftDataManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../avatar/hero/Hero.h"
MailAllGiftLayer::MailAllGiftLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,isMoveing(false)
,isDownPoint(Point::ZERO)
,TAG_LISTBG(10)
{
    
}

MailAllGiftLayer:: ~ MailAllGiftLayer()
{
    MailAllGiftDataManager::getInstance()->destroyInstance();
}

bool MailAllGiftLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        this->setBackground(IMG_MARKET_MARKETJUXIAN_JUXIANBG,Point::ZERO,true);
        setBg();
        createTableView();
        bref = true;
    } while (false);
    return bref;
}

MailAllGiftLayer* MailAllGiftLayer::create()
{
    MailAllGiftLayer* list = new MailAllGiftLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MailAllGiftLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MailAllGiftLayer* layer = MailAllGiftLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void MailAllGiftLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MailAllGiftLayer::onExit()
{
    BaseLayer::onExit();
}
void MailAllGiftLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void MailAllGiftLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MailAllGiftLayer::setBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_MARKET_MARKETJUXIAN_JUXIANBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1,TAG_LISTBG);
    
    Sprite* juxianWord = Sprite::create(IMG_MARKET_MARKETJUXIAN_JUXIANWORD);
    juxianWord->setAnchorPoint(Point::ZERO);
    juxianWord->setPosition(listBg->getContentSize().width/2-juxianWord->getContentSize().width/2+20,listBg->getContentSize().height-juxianWord->getContentSize().height-5);
    listBg->addChild(juxianWord);
    
    this->setContentSize(listBg->getContentSize());
}


void MailAllGiftLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+20;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(50,30);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* MailAllGiftLayer::singleList(ssize_t idx)
{
    if (idx>= MailAllGiftDataManager::getInstance()->giftList->size()) {
        return NULL;
    }
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
    Sprite* cellbg = Sprite::create(sttr);
    
    MailAllGiftData* data = MailAllGiftDataManager::getInstance()->giftList->at(idx);
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        int m_quality = data->heroQuality;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemDictId);
        UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality);
        userHead->setHeadInfo(1, 1);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(5,5);
        cellbg->addChild(userHead,5);
//        userHead->addTouchBegainCallBack(this, callfuncN_selector(FinderHeroListLayer::onUserClick));
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        int m_quality = data->itemQuality;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemDictId);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_quality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        cellbg->addChild(head,5);
        //       head->addTouchBegainCallBack(this, callfuncN_selector(MarketAuctionSellLayer::onHeroHeadClick));
    }
    else if (data->itemType == 100)
    {
        //        NoticeManager::getInstance()->showNotice("添加角色属性");
    }
    return cellbg;
}


TableViewCell* MailAllGiftLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        Sprite* list=singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX((list->getContentSize().width+10)*i);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    return cell;

}

//列表大小
Size MailAllGiftLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    

    Size cellSize;
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
    Sprite* temp = Sprite::create(sttr);
    cellSize.height = temp->getContentSize().height+10;
    cellSize.width = (temp->getContentSize().width+10)*4;
    return cellSize;
}
//获取view的长度
ssize_t MailAllGiftLayer::numberOfCellsInTableView(TableView *table)
{
    ssize_t  now_count =ceil(double(MailAllGiftDataManager::getInstance()->getGiftSize()) / 5);
    return now_count;
}
//点击cell事件
void MailAllGiftLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    log("%d",cell->getTag());
}
void MailAllGiftLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
//bool MailAllGiftLayer::onTouchBegan(Touch *touch, Event *unused_event)
//{
//    isDownPoint=touch->getLocation();
//    isDownPoint = this->convertToNodeSpace(isDownPoint);
//    return true;
//}
//void MailAllGiftLayer::onTouchMoved(Touch *touch, Event *unused_event)
//{
//    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
//    {
//        isMoveing = true;
//    }
//    
//    
//}
//void MailAllGiftLayer::onTouchEnded(Touch *touch, Event *unused_event)
//{
////    isMoveing = false;
////    BaseLayer::onTouchEnded(touch, unused_event);
//}
