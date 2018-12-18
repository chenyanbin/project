//
//  MoneyDrawingGiftLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/12/1.
//
//

#include "MoneyDrawingGiftLayer.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../../avatar/hero/Hero.h"
#include "MoneyDrawingDataManager.h"
#include "../../../tips/TipsLayer.h"
#include "../../../../message/Decoding/signin/LuckyReceiveAllMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../../protocol/Protocal.h"
#include "../../../awardBox/AwardBox_Layer.h"
MoneyDrawingGiftLayer::MoneyDrawingGiftLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,isMoveing(false)
,isDownPoint(Point::ZERO)
,TAG_LISTBG(10)
,m_canReceive(0)
{
    
}

MoneyDrawingGiftLayer:: ~ MoneyDrawingGiftLayer()
{
    MoneyDrawingDataManager::getInstance()->destroyInstance();
}

bool MoneyDrawingGiftLayer::init(int canReceive)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        m_canReceive = canReceive;
        this->setBackground(IMG_LIMITCARD_SKILLBG,Point::ZERO,true);
        setBg();
        createTableView();
        bref = true;
    } while (false);
    return bref;
}

MoneyDrawingGiftLayer* MoneyDrawingGiftLayer::create(int canReceive)
{
    MoneyDrawingGiftLayer* list = new MoneyDrawingGiftLayer();
    if(list && list->init(canReceive))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MoneyDrawingGiftLayer::show(int canReceive)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MoneyDrawingGiftLayer* layer = MoneyDrawingGiftLayer::create(canReceive);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void MoneyDrawingGiftLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MoneyDrawingGiftLayer::onExit()
{
    BaseLayer::onExit();
}
void MoneyDrawingGiftLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void MoneyDrawingGiftLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MoneyDrawingGiftLayer::setBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    
    Sprite* titlebg = Sprite::create(IMG_LIMITCARD_SKILLONETITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(15,this->getContentSize().height/sx-titlebg->getContentSize().height-15);
    layer->addChild(titlebg,4);
    Sprite* title = Sprite::create(IMG_SIGNIN_MONEYDRAW_TITLEDRAW);
    title->setAnchorPoint(Point::ZERO);
    title->setPosition(20,8);
    titlebg->addChild(title);

    
    if (m_canReceive == 1) {

        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MoneyDrawingGiftLayer::onReceiveClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(layer->getContentSize().width/sx/2-btn->getContentSize().width/2, 20);
        layer->addChild(btn,3);
        Sprite* btnWored = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        btnWored->setAnchorPoint(Point::ZERO);
        btnWored->setPosition(Point::ZERO);
        btn->addChild(btnWored,10);
    }
}
void MoneyDrawingGiftLayer::onReceiveClick(Ref* pSender)
{
    requestLuckyReceiveMsg();
}

void MoneyDrawingGiftLayer::createTableView()
{
    Sprite* layer = (Sprite*)this->getChildByTag(TAG_BG);
    
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3+20;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(50,50);
    _tableView->reloadData();
    layer->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* MoneyDrawingGiftLayer::singleList(ssize_t idx)
{
    if (idx>= MoneyDrawingDataManager::getInstance()->giftList->size()) {
        return NULL;
    }
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);

    Sprite* cellbg = Sprite::create(sttr);
    cellbg->setAnchorPoint(Point::ZERO);
    cellbg->setScale(0.8);
    MoneyDrawingData* data = MoneyDrawingDataManager::getInstance()->giftList->at(idx);
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        int m_quality = data->itemType;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality);
        userHead->setHeadInfo(1, 1);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(5,5);
        cellbg->addChild(userHead,5,idx);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(MoneyDrawingGiftLayer::onUserClick));
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        int m_quality = data->itemQuality;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_quality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(MoneyDrawingGiftLayer::onUserClick));
    }
    else if (data->itemType == 100)
    {
        //        NoticeManager::getInstance()->showNotice("添加角色属性");
    }
    return cellbg;
}
void MoneyDrawingGiftLayer::onUserClick(Node* pSender)
{
    MoneyDrawingData* data = MoneyDrawingDataManager::getInstance()->giftList->at(pSender->getTag());
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}

TableViewCell* MoneyDrawingGiftLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<5; i++) {
        int tag=(int)idx*5+i;
        Sprite* list=singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX((list->getContentSize().width-15)*i);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    return cell;
    
}

//列表大小
Size MoneyDrawingGiftLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    
    
    Size cellSize;
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
    Sprite* temp = Sprite::create(sttr);
    cellSize.height = temp->getContentSize().height;
    cellSize.width = (temp->getContentSize().width-15)*5;
    return cellSize;
}
//获取view的长度
ssize_t MoneyDrawingGiftLayer::numberOfCellsInTableView(TableView *table)
{
    ssize_t  now_count =ceil(double(MoneyDrawingDataManager::getInstance()->giftList->size()) / 5);
    return now_count;
}
//点击cell事件
void MoneyDrawingGiftLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    log("%d",cell->getTag());
}
void MoneyDrawingGiftLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
}

/*--------------------------------------------------访问服务器----------------------------------------------------------*/
void MoneyDrawingGiftLayer::requestLuckyReceiveMsg()
{
    Dialog::showServerLoading();
    LuckyReceiveAllMsg * msg = new LuckyReceiveAllMsg;
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MoneyDrawingGiftLayer::onLuckyReceiveProgress(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->messageID == SCENSE_CLIENT_LUCKY_LuckyReceiveAllResp)
    {
        if (message->state)
        {
            
            Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
            m_basegift->clear();
            
            int size =MoneyDrawingDataManager::getInstance()->giftList->size();
            for (int i; i<size; i ++)
            {
                MoneyDrawingData* data = MoneyDrawingDataManager::getInstance()->giftList->at(i);
                BaseTypeData* basedata = new BaseTypeData();
                basedata->autorelease();
                basedata->dataId = data->itemId;
                basedata->dataName = data->itemName;
                basedata->dataType = data->itemType;
                basedata->dataQuality = data->itemQuality;
                m_basegift->pushBack(basedata);
            }
            AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            this->removeFromParent();
        }
    }
}

void MoneyDrawingGiftLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LUCKY_LuckyReceiveAllResp).c_str() ,CC_CALLBACK_1(MoneyDrawingGiftLayer::onLuckyReceiveProgress,this));
}
void MoneyDrawingGiftLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}