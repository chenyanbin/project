//
//  EveryTaskLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/14.
//
//

#include "EveryTaskLayer.hpp"

#include "../../../message/Decoding/sevenday/WeekTeskMag.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../avatar/hero/Hero.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../message/Decoding/sevenday/WeekReceiveMsg.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../data/BaseTypeData.h"
#include "../../tips/TipsLayer.h"
#include "../../publicLayer/GotoModule.h"
#include "../../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../../commonData/dictData/DictTaskCommonType/DictTaskCommonTypeManager.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
EveryTaskLayer::EveryTaskLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,m_day(1)
,sx(0)
,m_type(1)
,m_taskTag(1)
{
    
    
}

EveryTaskLayer:: ~ EveryTaskLayer()
{
    
}

bool EveryTaskLayer::init(int day,int type)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        sx = GlobalInfo::getInstance()->screenScaleX;
        this->isAnimation = false;
        m_day = day;
        m_type = type;
        this->setBackground();
        
        bref = true;
    } while (false);
    return bref;
}

EveryTaskLayer* EveryTaskLayer::create(int day,int type)
{
    EveryTaskLayer* list = new EveryTaskLayer();
    if(list && list->init(day,type))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void EveryTaskLayer::onEnter()
{
    BaseLayer::onEnter();
}
void EveryTaskLayer::onExit()
{
    BaseLayer::onExit();
}
void EveryTaskLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestWeeTaskPage(m_day,m_type);
    
}
void EveryTaskLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void EveryTaskLayer::setBackground()
{
    listBg = Sprite::create(IMG_SEVEENDAY_MODULEBG);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    listBg->setOpacity(0);
    this->addChild(listBg);
    
    Size size = listBg->getContentSize();
    this->setContentSize(size);
}

void EveryTaskLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 20;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(30,22);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* EveryTaskLayer::singleList(ssize_t idx)
{
    Sprite* cellbg = Sprite::create(IMG_SEVEENDAY_CELLBG);
    if (idx>TeskDexPriceDataManager::getInstance()->lineupList->size()) {
        return NULL;
    }
    TeskDesData* data = TeskDexPriceDataManager::getInstance()->lineupList->at(idx);
    
    string str = data->desc;
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(30,68);
    cellbg->addChild(label);
    
    if (data->status == 1) {//领取
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(EveryTaskLayer::onButtonClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,cellbg->getContentSize().height/2-btn->getContentSize().height/2);
        cellbg->addChild(btn,1,idx);
        Sprite* spr = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,4);
    }else if (data->status == 2)//不可领取
    {
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(EveryTaskLayer::onqianwangClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,cellbg->getContentSize().height/2-btn->getContentSize().height/2);
        cellbg->addChild(btn,1,idx);
        
        Sprite* spr = Sprite::create(IMG_PUBLIC_BUTTON_GOTO);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,4);
    }else{//已领取
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(EveryTaskLayer::onButtonClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,cellbg->getContentSize().height/2-btn->getContentSize().height/2);
        cellbg->addChild(btn,1,idx);
        
        Sprite* spr = Sprite::create(IMG_PUBLIC_LABEL_ISLINGQU);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(Point::ZERO);
        btn->addChild(spr,4);
        btn->setEnabled(false);
    }
    
    //奖励
    UserEquipLayer* head = NULL;
    UserHeadLayer* userHead = NULL;
    long priceCount = data->priceList.size();
    for (int i = 0; i<priceCount; i++) {
        TaskPrice priceData = data->priceList.at(i);
        int m_quality = priceData.itemQuality;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        const char* path = NULL;
        
        if(  priceData.itemType == DictItemTypeEnumItemHero)
        {
            DictHero* dicthero = DictHeroManager::getInstance()->getData(priceData.itemId);
            if (dicthero) {
                path =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
            }else{
                path = PublicShowUI::getGoods(priceData.itemType, priceData.itemId);
            }
            if (path) {
                userHead=UserHeadLayer::create(path,m_quality,false);
                userHead->setHeadInfo(1, 1);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.4);
                userHead->setPosition(75 + i*(userHead->getContentSize().width),15);
                cellbg->addChild(userHead,5,idx);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(EveryTaskLayer::onHeroHeadClick));
            }
            
            
            
        }
        else if(priceData.itemType == DictItemTypeEnumItemEquip || priceData.itemType == DictItemTypeEnumItemBook || priceData.itemType == DictItemTypeEnumItemMater|| priceData.itemType == DictItemTypeEnumItem|| priceData.itemType == DictItemTypeEnumRoleResource)
        {
            const char* resource = PublicShowUI::getGoods(priceData.itemType, priceData.itemId);
            head = UserEquipLayer::create(resource,m_quality,false);
            head->setAnchorPoint(Point::ZERO);
            head->setScale(0.4);
            if (priceData.itemType == 4) {
                head->setFragment();
            }else if (priceData.itemType == 3)
            {
                head->setLetterFragment();
            }
            head->setPosition(70 + i*(head->getContentSize().width),10);
            cellbg->addChild(head,5,idx);
            head->addTouchBegainCallBack(this, callfuncN_selector(EveryTaskLayer::onHeroHeadClick));
        }
        
        string count = StringUtils::format("x%d",priceData.itemCount);
        Label* label = PublicShowUI::getLabelNumber(count.c_str(), PublicShowUI::getColor3b(COLOR_HEAD_WHITE), 40, false, false);
        label->setAnchorPoint(Point::ZERO);
        if (head) {
            label->setPosition(head->getContentSize().width,2);
            head->addChild(label,5);
        }else{
            label->setPosition(userHead->getContentSize().width,2);
            userHead->addChild(label,5);
        }

    }
    
    return  cellbg;
    
}
void EveryTaskLayer::onButtonClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    m_taskTag = target->getTag();
    TeskDesData* data = TeskDexPriceDataManager::getInstance()->lineupList->at(m_taskTag);
    requestWeekRewardMsg(m_day,4,data->taskId,0);
}
void EveryTaskLayer::onqianwangClick(Ref* psender)
{
    log("qianwang ");
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    
    TeskDesData* data = TeskDexPriceDataManager::getInstance()->lineupList->at(target->getTag());
    onGoFunctionByTaskData(data);
    
}
void EveryTaskLayer::onGoFunctionByTaskData(TeskDesData* taskData)
{
//    DictTaskCommonType* task = DictTaskCommonTypeManager::getInstance()->getData(taskData->taskId);
//    if(task)
//    {
    
        GotoModule::gotoModuleByFunctionID(taskData->function, SCENE_TAG_MAINUI);
//    }
    
}

void EveryTaskLayer::onHeroHeadClick(Node* pSender)
{
    TeskDesData* data = TeskDexPriceDataManager::getInstance()->lineupList->at(pSender->getTag());
    TaskPrice priceData = data->priceList.at(0);
    TipsLayer::show(priceData.itemType, priceData.itemId, priceData.itemCount);
}
TableViewCell* EveryTaskLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* list=singleList(idx);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size EveryTaskLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_SEVEENDAY_CELLBG);
    cellSize.height = temp->getContentSize().height;
    cellSize.width = temp->getContentSize().width+10;
    return cellSize;
}
//获取view的长度
ssize_t EveryTaskLayer::numberOfCellsInTableView(TableView *table)
{
   
   
    return TeskDexPriceDataManager::getInstance()->lineupList->size();
    
    
}
//点击cell事件
void EveryTaskLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
    log("%d",cell->getTag());
}

/*-------------------------------------请求服务器---------------------------------------*/
void EveryTaskLayer::requestWeeTaskPage(int _day,int tasktag)//第几天内容
{
    Dialog::showServerLoading();
    WeekTeskMag* msg = new WeekTeskMag(_day, tasktag);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void EveryTaskLayer::onWeekRewardProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekTaskPageResp)
    {
        if(message->state)//返回成功
        {
            TeskDexPriceDataManager::getInstance()->destroyInstance();
            int lineupSize = message->byteStream->getByte();
            for (int i = 0; i < lineupSize; i ++)
            {
                TeskDesData* data = new TeskDesData();
                data->autorelease();
                data->taskId = message->byteStream->getByte();
                data->desc = message->byteStream->getUTF8();
                data->status = message->byteStream->getByte();
                data->function = message->byteStream->getByte();
                data->functionType = message->byteStream->getByte();
                int taskSize = message->byteStream->getByte();
                for (int j = 0; j<taskSize; j++) {
                    struct TaskPrice _pricelist = {0,0,0,"","",0};
                    _pricelist.itemType=message->byteStream->getByte();
                    _pricelist.itemId=message->byteStream->getInt();
                    _pricelist.itemCount = message->byteStream->getInt();
                    _pricelist.itemName = message->byteStream->getUTF8();
                    _pricelist.itemDesc = message->byteStream->getUTF8();
                    _pricelist.itemQuality = message->byteStream->getByte();
                    data->priceList.push_back(_pricelist);
                }
                TeskDexPriceDataManager::getInstance()->addData(data);
            }
            createTableView();
        }
    }

}

void EveryTaskLayer::requestWeekRewardMsg(int _day, int _type, int _numPrice, int _numHero)//q请求领取奖励
{
    Dialog::showServerLoading();
    WeekReceiveMsg* msg = new WeekReceiveMsg(_day, _type, _numPrice, _numHero);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void EveryTaskLayer::onWeekDayRewardMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekReceiveResp)
    {
        if(message->state)//返回成功
        {
    
            Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
            m_basegift->clear();
            
            TeskDesData* data = TeskDexPriceDataManager::getInstance()->lineupList->at(m_taskTag);
            for (int j = 0; j<data->priceList.size(); j++) {
                BaseTypeData* basedata = new BaseTypeData();
                basedata->autorelease();
                basedata->dataId = data->priceList.at(j).itemId;
                basedata->dataName = data->priceList.at(j).itemName;
                basedata->dataType = data->priceList.at(j).itemType;
                basedata->dataQuality = data->priceList.at(j).itemQuality;
                m_basegift->pushBack(basedata);

            }
            AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            TeskDexPriceDataManager::getInstance()->lineupList->at(m_taskTag)->status = 3;
            
            createTableView();
            broadMsg(CUSTOM_SEVENDAY_REDPOINT);
        }
    }
}
void EveryTaskLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekTaskPageResp).c_str(), CC_CALLBACK_1(EveryTaskLayer::onWeekRewardProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekReceiveResp).c_str(), CC_CALLBACK_1(EveryTaskLayer::onWeekDayRewardMsgProcess, this));
}
void EveryTaskLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
