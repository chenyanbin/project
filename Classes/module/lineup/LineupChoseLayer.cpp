//
//  LineupChoseLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#include "LineupChoseLayer.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "LineupPage.h"
LineupChoseLayer::LineupChoseLayer()
:pageNum(1)
,m_nowPage(1)
,TAG_TABLEVIEW(1)
,m_totalCount(12)
,downBtn(NULL)
,upBtn(NULL)
{
    
}
LineupChoseLayer::~LineupChoseLayer()
{
    log("~LineupChoseLayer ~LineupChoseLayer");
}

bool LineupChoseLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        createTableView();
        setBackGround();
        setDirectBtn();
        bref = true;
    } while (false);
    return bref;
}

LineupChoseLayer* LineupChoseLayer::create()
{
    LineupChoseLayer* list = new LineupChoseLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void LineupChoseLayer::setBackGround()
{
    Sprite* Bg = Sprite::create(IMG_LINEUP_HEADBG);
    Bg->setAnchorPoint(Point::ZERO);
    addChild(Bg, -1, TAG_BG);
    Size size = Bg->getContentSize();
    Bg->setPosition(Point::ZERO);
    this->setContentSize(Bg->getContentSize());
}

void LineupChoseLayer::createTableView()
{
    
    Size size = cellSizeForTable(NULL);
    size.width = getCellSizeNode(0)->getContentSize().width;
    size.height = getCellSizeNode(0)->getContentSize().height*3;
    
    TableView* tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::VERTICAL);
    tableView->setAnchorPoint(Point::ZERO);
    tableView->reloadData();
    tableView->setPositionX(10);
    tableView->setPositionY(100);
    tableView->setTouchEnabled(false);
    this->addChild(tableView,0,TAG_TABLEVIEW);
}

Size LineupChoseLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    
    cellSize = cellSizeForTable(table);
    
    return cellSize;
    
}
Size LineupChoseLayer::cellSizeForTable(TableView *table)
{
    if(cellSize.width == 0 || cellSize.height == 0)
    {
          cellSize = getCellSizeNode(0)->getContentSize();
    }
    
    return cellSize;
}
TableViewCell* LineupChoseLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = getCellSizeNode(int(idx));
    node->setPositionY(0);
    node->setPositionX(0);
    cell->addChild(node,0,idx);
    cell->setTag(idx + 1);
    return cell;

}
Node* LineupChoseLayer::getCellSizeNode(int index)
{
    LineupPage* page = LineupPage::create(index,m_totalCount);
    page->setAnchorPoint(Point::ZERO);
    return page;
}
ssize_t LineupChoseLayer::numberOfCellsInTableView(TableView *table)
{
    int num = ceil(double(m_totalCount) / pageNum);
    return  num;
}

void LineupChoseLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    if(!m_isMoved)
    {
   
//       log("cell===%d",cell->getTag());
    }
}

void LineupChoseLayer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void LineupChoseLayer::onExit()
{
    BaseLayer::onExit();

}
void LineupChoseLayer::scrollViewDidScroll(ScrollView* view)
{
    
}
void LineupChoseLayer::scrollViewDidZoom(ScrollView* view)
{
    
}

bool LineupChoseLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    touchBeginPos = touch->getLocation();
    m_isMoved = false;
    
    Rect rect = this->getBoundingBox();
    if(rect.containsPoint(this->getParent()->convertToNodeSpace(touchBeginPos)) == false)
    {
        return false;
    }

    return true;
}
void LineupChoseLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    m_isMoved = true;
}
void LineupChoseLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(touch->getLocation().y - touchBeginPos.y > 20 )
    {
        leftPage(NULL);
    }
  
    else if(touch->getLocation().y - touchBeginPos.y < -20)
    {
        rightPage(NULL);
    }

     m_isMoved = false;

}

void LineupChoseLayer::setDirectBtn()
{
    downBtn = Sprite::create(IMG_STAGE_RIGHTBTN);
    downBtn->setAnchorPoint(Point(0.5,0.5));
    downBtn->setScale(.8, .8);
    downBtn->setRotation(90);
    downBtn->setPosition(50,100-downBtn->getContentSize().height/2);
    downBtn->setVisible(true);
    
    upBtn = Sprite::create(IMG_STAGE_RIGHTBTN);
    upBtn->setAnchorPoint(Point(0.5,0.5));
    upBtn->setScale(.8, .8);
    upBtn->setRotation(270);
    upBtn->setPosition(50,425+upBtn->getContentSize().height/2);
    this->addChild(downBtn,5);
    this->addChild(upBtn,5);
    upBtn->setVisible(false);
   
    
}
void LineupChoseLayer::LeftAndRightVisible(float pt)
{
    int allPage = ceil(double(m_totalCount) / pageNum);
    if (this->m_nowPage == 1)
    {
        upBtn->setVisible(false);
        return;
    }
    if (this->m_nowPage == allPage-2)
    {
        downBtn->setVisible(false);
        return;
    }
    else
    {
        downBtn->setVisible(true);
        upBtn->setVisible(true);
        return;
    }
}

void LineupChoseLayer::leftPage(Ref* pSender)
{
    
    if(this->m_nowPage >= m_totalCount-2)
    {
        m_nowPage = m_totalCount-2;
        return;
    }
    m_nowPage ++;
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    tableView->getContainer()->stopAllActions();
    Point toPos = tableView->getContentOffset();
    toPos.y +=  cellSize.height;
    tableView->setContentOffsetInDuration(toPos, .2);
    LeftAndRightVisible(NULL);
}
void LineupChoseLayer::rightPage(Ref* pSender)
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
    toPos.y -=  cellSize.height;
    tableView->setContentOffsetInDuration(toPos, .2);
    LeftAndRightVisible(NULL);
}