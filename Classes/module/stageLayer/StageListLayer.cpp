//
//  StageListLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/13.
//
//

#include "StageListLayer.h"
#include "../../common/PublicShowUI.h"
#include "../../common/ImagePath.h"

#include "StagePage.h"

StageListLayer::StageListLayer()
:pageNum(3)
,battleList(NULL)
,m_nowPage(1)
,TAG_TABLEVIEW(1)
,leftBtn(NULL)
,rightBtn(NULL)

{
    battleList = new vector<BattleType>();
    battleList->push_back(kBattleType_MingZhanYi);
    battleList->push_back(kBattleTYPe_SanGuoWushuan);
    battleList->push_back(kBattleType_MingJiangZhuan);
}
StageListLayer::~StageListLayer()
{
    battleList->clear();
    CC_SAFE_DELETE(battleList);
    battleList = NULL;
}

bool StageListLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        
        createTableView();
        setDirectBtn();
        setParticle();
        bref = true;
    } while (false);
    return bref;
}

StageListLayer* StageListLayer::create()
{
    StageListLayer* list = new StageListLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void StageListLayer::createTableView()
{
    Size size = cellSizeForTable(NULL);
   
    TableView* tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::HORIZONTAL);
    tableView->setAnchorPoint(Point::ZERO);
    tableView->setTouchEnabled(false);
    tableView->reloadData();
    tableView->setPositionX(0);
    this->setContentSize(size);
    
    this->addChild(tableView,0,TAG_TABLEVIEW);

}
Size StageListLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cellSizeForTable(table);
}
Size StageListLayer::cellSizeForTable(TableView *table)
{
     if(cellSize.width == 0 || cellSize.height == 0)
     {
         cellSize = getCellSizeNode(0)->getContentSize();
     }
    
    return cellSize;
}
TableViewCell* StageListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = getCellSizeNode(int(idx));
    node->setPositionX(-20);//70
    cell->addChild(node,0,idx);
    cell->setTag(idx + 1);
    return cell;
}
Node* StageListLayer::getCellSizeNode(int index)
{
    StagePage* page = StagePage::create(index,battleList);
    page->setAnchorPoint(Point::ZERO);
    return page;
}
ssize_t StageListLayer::numberOfCellsInTableView(TableView *table)
{
    int num = ceil(double(battleList->size()) / pageNum);
    return  num;
}

void StageListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    if(!m_isMoved)
    {

        log("%d",cell->getTag());
    }
}

void StageListLayer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void StageListLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void StageListLayer::scrollViewDidScroll(ScrollView* view)
{
    
}
void StageListLayer::scrollViewDidZoom(ScrollView* view)
{
    
}

bool StageListLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    touchBeginPos = touch->getLocation();
    m_isMoved = false;
    return true;
}
void StageListLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
      m_isMoved = true;
}
void StageListLayer::onTouchEnded(Touch *touch, Event *unused_event)
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
void StageListLayer::leftPage(Ref* pSender)
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
    LeftAndRightVisible();
    
}
void StageListLayer::rightPage(Ref* pSender)
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
    LeftAndRightVisible();
 
}
void StageListLayer::setDirectBtn()
{
    leftBtn = Button::create(IMG_STAGE_RIGHTBTN,IMG_STAGE_RIGHTBTN,CC_CALLBACK_1(StageListLayer::leftPage, this));
    leftBtn->setAnchorPoint(Point::ZERO);
    leftBtn->setRotation(180);
    leftBtn->setPosition(VisibleRect::left().x+leftBtn->getContentSize().width,cellSize.height/2+leftBtn->getContentSize().height);
    leftBtn->setVisible(false);
   
    rightBtn = Button::create(IMG_STAGE_RIGHTBTN,IMG_STAGE_RIGHTBTN,CC_CALLBACK_1(StageListLayer::rightPage, this));
    rightBtn->setAnchorPoint(Point::ZERO);
    rightBtn->setPosition(cellSize.width-rightBtn->getContentSize().width,cellSize.height/2);
    this->addChild(leftBtn,5);
    this->addChild(rightBtn,5);
    rightBtn->setVisible(battleList->size() > pageNum);

}
void StageListLayer::LeftAndRightVisible()
{
    int allPage = ceil(double(battleList->size()) / pageNum);
    if (this->m_nowPage == 1)
    {
        leftBtn->setVisible(false);
        return;
    }
    if (this->m_nowPage == allPage)
    {
        rightBtn->setVisible(false);
        return;
    }
    else
    {
        leftBtn->setVisible(true);
        rightBtn->setVisible(true);
        return;
    }
}

void StageListLayer::setParticle()
{
//    Sprite* particle = Sprite::create(IMG_STAGE_PARTICLE);
//    particle->setPosition(cellSize.width/2,cellSize.height/2);
  //  this->addChild(particle,6);
}