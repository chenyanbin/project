//
//  FamouseDetails.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "FamouseDetails.hpp"
#include "DetailsNode.hpp"
#include "detailsLayer/DetailsLayer.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseDetailsList.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../data/BaseTypeData.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../../common/noticeManager/NoticeManager.h"
FamouseDetails::FamouseDetails()
:TAG_TABLEVIEW(1)
,dataList(NULL)
{
    dataList = new Vector<DetailsListData*>();
}
FamouseDetails::~FamouseDetails()
{
    CC_SAFE_DELETE(dataList);
    dataList = NULL;
}
bool FamouseDetails::init()
{
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    this->setContentSize(_size);
    return true;
}
void FamouseDetails::setTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
 
    _tableView->setPosition(0,0);
    this->addChild(_tableView,1,TAG_TABLEVIEW);
    
}
void FamouseDetails::onEnter()
{
    BaseLayer::onEnter();
}
void FamouseDetails::onExit()
{
    BaseLayer::onExit();
}
void FamouseDetails::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseDetails::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestList();
    
}
void FamouseDetails::requestList()
{
    Dialog::showServerLoading();
    FamouseDetailsList* msg = new FamouseDetailsList();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseDetails::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendBossCompletePageResp).c_str(), CC_CALLBACK_1(FamouseDetails::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendRewardResp).c_str(), CC_CALLBACK_1(FamouseDetails::onMsgProcess, this));
}
void FamouseDetails::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void FamouseDetails::onMsgProcess(EventCustom* message)
{
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendBossCompletePageResp)
    {
        int bossSize = msg->byteStream->getShort();
        DetailsListData* listData  = NULL;
        for(int i = 0; i < bossSize; i++)
        {
            listData = new DetailsListData();
            listData->autorelease();
            listData->bossID = msg->byteStream->getInt();
            listData->bossDictID = msg->byteStream->getInt();
            listData->bossName = msg->byteStream->getUTF8();
            listData->bossLevel = msg->byteStream->getShort();
            listData->bossFinderName = msg->byteStream->getUTF8();
            listData->attackRoleCount = msg->byteStream->getShort();
            listData->bossRemainSeconds = msg->byteStream->getInt();
            listData->hurt = msg->byteStream->getInt();
            listData->hp = msg->byteStream->getInt();
            listData->hpMax = msg->byteStream->getInt();
            listData->status = msg->byteStream->getByte();
            listData->isGettedPrize = msg->byteStream->get();
            dataList->pushBack(listData);
            
        }
        setTableView();
    }
    else if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendRewardResp)
    {
        int rewardCoin = msg->byteStream->getInt();
        int itemSize = msg->byteStream->get();
        Vector<BaseTypeData*>* itemList = new Vector<BaseTypeData*>();
        for(int i = 0; i < itemSize; i++)
        {

            BaseTypeData* data = new BaseTypeData();
            data->autorelease();
            data->dataType = msg->byteStream->get();
            data->dataId = msg->byteStream->getInt();
            data->dataQuality = msg->byteStream->get();
            data->dataCount = msg->byteStream->get();
            data->heroPrestige = msg->byteStream->getInt();
            itemList->pushBack(data);
        }
        if(itemList->size())
        {
            AwardBox_Layer* layer=AwardBox_Layer::create(itemList);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
        }
        if(rewardCoin > 0)
        {
            string str = "铜币+" + PublicShowUI::numberToString(rewardCoin);
            NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
        }

    }
}
TableViewCell* FamouseDetails::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = DetailsNode::create(dataList->at(idx));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    cell->setContentSize(node->getContentSize());
    cell->setTag(idx);
    
    return cell;
}
ssize_t FamouseDetails::numberOfCellsInTableView(TableView *table)
{
    return dataList->size();
}
void FamouseDetails::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size FamouseDetails::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_HEROITEMBG)->getContentSize();
    }
    return cellSize;
}