//
//  FamouseFightGo.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#include "FamouseFightGo.hpp"
#include "BossNode.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseBossListMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
FamouseFightGo::FamouseFightGo()
:TAG_TABLEVIEW(1)
,dataList(NULL)
{
    dataList = new Vector<FamouseBossData*>();
}
FamouseFightGo::~FamouseFightGo()
{
    CC_SAFE_DELETE(dataList);
    dataList = NULL;
}
bool FamouseFightGo::init()
{
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3 + 5;
    this->setContentSize(_size);
    return true;
}
void FamouseFightGo::setTableView()
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
void FamouseFightGo::onEnter()
{
    BaseLayer::onEnter();
}
void FamouseFightGo::onExit()
{
    BaseLayer::onExit();
}
void FamouseFightGo::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseFightGo::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
 
    requestListMsg();
}
void FamouseFightGo::requestListMsg()
{
    Dialog::showServerLoading();
    FamouseBossListMsg* msg = new FamouseBossListMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseFightGo::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendBossPageResp)
    {
        dataList->clear();
        int len = msg->byteStream->getShort();
        FamouseBossData* data = NULL;
        for(int i = 0; i < len ; i++)
        {
            data = new FamouseBossData();
            data->autorelease();
            data->bossId = msg->byteStream->getInt();
            data->bossDictId = msg->byteStream->getInt();
            data->bossName = msg->byteStream->getUTF8();
            data->bossLevel = msg->byteStream->getShort();
            data->bossLevel = data->bossLevel <= 0 ? 1 : data->bossLevel;
            data->bossFinderName = msg->byteStream->getUTF8();
            data->bossRemainSeconds = msg->byteStream->getInt();
            data->endTime = time(0) + data->bossRemainSeconds;
            data->attackRoleCount = msg->byteStream->getShort();
            data->hurt = msg->byteStream->getInt();
            data->hp = msg->byteStream->getInt();
            data->hpMax = msg->byteStream->getInt();
            dataList->pushBack(data);
            
        }

         setTableView();
    }
   
}
void FamouseFightGo::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendBossPageResp).c_str(), CC_CALLBACK_1(FamouseFightGo::onMsgProcess, this));
}
void FamouseFightGo::removeEventListener()
{
    BaseLayer::removeEventListener();
}
TableViewCell* FamouseFightGo::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = BossNode::create(dataList->at(idx));
    node->setAnchorPoint(Point::ZERO);
    cell->addChild(node);
    cell->setContentSize(node->getContentSize());
    cell->setTag((int)idx);
    
    return cell;
}
ssize_t FamouseFightGo::numberOfCellsInTableView(TableView *table)
{
    return dataList->size();;
}
void FamouseFightGo::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size FamouseFightGo::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_HEROITEMBG)->getContentSize();
    }
    return cellSize;
}