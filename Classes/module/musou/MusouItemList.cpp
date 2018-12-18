//
//  MusouItemList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//

#include "MusouItemList.h"
#include "MusouItem.h"
MusouItemList::MusouItemList()
:musouList(NULL)
,TAG_TABLEVIEW(1)
,pageNum(3)
,m_isMoved(false)
,m_nowPage(1)
{
    musouList = new Vector<MusouStageData*>();
}
MusouItemList::~MusouItemList()
{
    CC_SAFE_DELETE(musouList);
    musouList = NULL;
}
inline bool sortMusouList(const DictMusou* pair1, const DictMusou* pair2)
{
    return pair1->id < pair2->id;
}

bool MusouItemList::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
       
        this->isAnimation = false;
       
        bref = true;
    } while (false);
    return bref;
}
void MusouItemList::setListData(ByteStream* byteStream)
{
    musouList->clear();
    int len = byteStream->get();
    MusouStageData* data = NULL;
    for(int i = 0; i < len; i++)
    {
        data = new MusouStageData();
        data->autorelease();
        data->stageID = byteStream->getInt();
        data->status = byteStream->get();
     
        data->setLeftTimes(byteStream->getInt());
        musouList->pushBack(data);
    }
    
    
     createTableView();
}
void MusouItemList::createTableView()
{
    Size size = cellSizeForTable(NULL);
    TableView* tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::HORIZONTAL);
    tableView->setAnchorPoint(Point::ZERO);
    tableView->reloadData();
    tableView->setPositionX(0);
    this->setContentSize(size);
    
    this->addChild(tableView,0,TAG_TABLEVIEW);
    
   
}
Node* MusouItemList::getNode(int index)
{
    MusouItem* musouItem = MusouItem::create(index, musouList);
    musouItem->setAnchorPoint(Point::ZERO);
    return musouItem;
}
Size MusouItemList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSizeForTable(table);
}
Size MusouItemList::cellSizeForTable(TableView *table)
{
    if(cellSize.width == 0)
    {
        cellSize = getNode(0)->getContentSize();
    }
    return cellSize;
}
TableViewCell* MusouItemList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = getNode(idx);
    cell->addChild(node,0,idx);
    return cell;
}
ssize_t MusouItemList::numberOfCellsInTableView(TableView *table)
{
    int num = ceil(double(musouList->size()) / pageNum);
    return  num;
}
void MusouItemList::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void MusouItemList::scrollViewDidScroll(ScrollView* view)
{
    
}
void MusouItemList::scrollViewDidZoom(ScrollView* view)
{
    
}


bool MusouItemList::onTouchBegan(Touch *touch, Event *unused_event)
{
    touchBeginPos = touch->getLocation();
    m_isMoved = false;
    return true;
}
void MusouItemList::onTouchMoved(Touch *touch, Event *unused_event)
{
    
    m_isMoved = true;
}
void MusouItemList::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(touch->getLocation().x - touchBeginPos.x > 20)
    {
        leftPage(NULL);
    }
    else if(touch->getLocation().x - touchBeginPos.x < -20)
    {
        rightPage(NULL);
    }
    m_isMoved = false;
}
void MusouItemList::leftPage(Ref* pSender)
{
    if(this->m_nowPage <= 1)
    {
        m_nowPage = 1;
        return;
    }
    m_nowPage --;
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    tableView->getContainer()->stopAllActions();
    Point toPos = tableView->getContentOffset();
    toPos.x = -(m_nowPage -1) * cellSize.width;
    tableView->setContentOffsetInDuration(toPos, .4);
 

}
void MusouItemList::rightPage(Ref* pSender)
{
    if(this->m_nowPage >= numberOfCellsInTableView(NULL))
    {
        m_nowPage = numberOfCellsInTableView(NULL);
        return;
    }
    
    m_nowPage ++;
    
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    tableView->getContainer()->stopAllActions();
    Point toPos = tableView->getContentOffset();
    toPos.x = -(m_nowPage -1) * cellSize.width;
    tableView->setContentOffsetInDuration(toPos, .4);
  
}
void MusouItemList::onEnter()
{
    BaseLayer::onEnter();
//    this->setClickEnabled(true);
}
void MusouItemList::onExit()
{
    BaseLayer::onExit();
//    this->setClickEnabled(false);
}