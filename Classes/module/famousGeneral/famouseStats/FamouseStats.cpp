//
//  FamouseStats.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "FamouseStats.hpp"
#include "StatsNode.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseStatsMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
FamouseStats::FamouseStats()
:TAG_TABLEVIEW(1)
{
    dataList = new Vector<FamouseStatsData*>();
}
FamouseStats::~FamouseStats()
{
    CC_SAFE_DELETE(dataList);
    dataList = NULL;
}
bool FamouseStats::init()
{
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    this->setContentSize(_size);
    return true;
}
void FamouseStats::setTableView()
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
void FamouseStats::onEnter()
{
    BaseLayer::onEnter();
}
void FamouseStats::onExit()
{
    BaseLayer::onExit();
}
void FamouseStats::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseStats::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestInfoList();
}
void FamouseStats::requestInfoList()
{
    Dialog::showServerLoading(1);
    FamouseStatsMsg* msg = new FamouseStatsMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseStats::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendHistoryPageResp)
    {
        dataList->clear();
        int len = msg->byteStream->get();
        FamouseStatsData* data = NULL;

        for(int i = 0; i < len; i++)
        {
            data = new FamouseStatsData();
            data->autorelease();
            data->period = msg->byteStream->getInt();
            data->activityName = msg->byteStream->getUTF8();//	活动名称	string	Y
            data->bossDictId = msg->byteStream->getInt();
            data->killBossCount = msg->byteStream->getShort();//
            data->maxBossLevel = msg->byteStream->getShort();//	最大boss等级	short	Y	我发现的最大boss等级, 我发现的boss每次出
            data->activityStartTimes = msg->byteStream->getLong();//	活动开始时间	long	Y	单位：毫秒
            data->activityEndTimes = msg->byteStream->getLong();//	活动结束时间	long		单位：毫秒
            dataList->pushBack(data);
        }
        setTableView();
    }
}
void FamouseStats::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendHistoryPageResp).c_str(), CC_CALLBACK_1(FamouseStats::onMsgProcess, this));
}
void FamouseStats::removeEventListener()
{
    BaseLayer::removeEventListener();
}
TableViewCell* FamouseStats::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = StatsNode::create(dataList->at(idx));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    cell->setContentSize(node->getContentSize());
    cell->setTag((int)idx);
    
    return cell;
}
ssize_t FamouseStats::numberOfCellsInTableView(TableView *table)
{
    return dataList->size();
}
void FamouseStats::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size FamouseStats::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_HEROITEMBG)->getContentSize();
    }
    return cellSize;
}