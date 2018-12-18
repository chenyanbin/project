//
//  ChapterListLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/7.
//
//

#include "ChapterListLayer.h"
#include "../../../common/ImagePath.h"

#include "../../../common/PublicShowUI.h"
ChapterListLayer::ChapterListLayer()
:TAG_UPBTN(1)
,TAG_DOWNBTN(2)
,TAG_BG(3)
,TAG_TABLEVIEW(4)
,_itemImage(NULL)
,m_callBack(NULL)
{
    
}
ChapterListLayer::~ChapterListLayer()
{
    CC_SAFE_RELEASE_NULL(_itemImage);
    m_callBack = NULL;
}
bool ChapterListLayer::init(int totalCount,ccMenuCallback callBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->m_chapterCount = totalCount;
        this->m_callBack = callBack;
        setDownBtn();
        setBg();
        setUpBtn();
        setTableView();
        bref = true;
    } while (false);
    return bref;
}
ChapterListLayer* ChapterListLayer::create(int totalCount,ccMenuCallback callBack)
{
    ChapterListLayer* layer = new ChapterListLayer();
    if(layer && layer->init(totalCount,callBack))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void ChapterListLayer::setDownBtn()
{
//    IMG_GENERALSLIST_ARROW
    Button* btn = Button::create(IMG_GENERALSLIST_ARROW, IMG_GENERALSLIST_ARROW, NULL);
    btn->setAnchorPoint(Point::ZERO);
    btn->setScaleY(-1);
    this->addChild(btn,0,TAG_DOWNBTN);
    btn->setPosition(Point::ZERO);
}
void ChapterListLayer::setBg()
{
    Button* btn = (Button*)this->getChildByTag(TAG_DOWNBTN);
    Sprite* bg = Sprite::create(IMG_PUBLIC_COMBOBOX_BG);
    bg->setAnchorPoint(Point::ZERO);
    bg->setPosition(btn->getPositionX() + (btn->getContentSize().width - bg->getContentSize().width)/2, 10);
    this->addChild(bg,1,TAG_BG);
    
}
void ChapterListLayer::setUpBtn()
{
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    Button* downBtn = (Button*)this->getChildByTag(TAG_DOWNBTN);
    Button* btn = Button::create(IMG_GENERALSLIST_ARROW, IMG_GENERALSLIST_ARROW,NULL);
    btn->setAnchorPoint(Point::ZERO);
  
    btn->setPosition(downBtn->getPositionX(), bg->getPositionY() + bg->getContentSize().height + 5);
    this->addChild(btn,2,TAG_UPBTN);
    
    Size size = btn->getContentSize();
    size.height = btn->getPositionY() + btn->getContentSize().height;
    this->setContentSize(size);
}
void ChapterListLayer::onDownClick(Ref* pSender)
{
    log("downclick");
}
void ChapterListLayer::onUPClick(Ref* pSender)
{
      log("updClick");
}
void ChapterListLayer::setSelectedByIndex(int index)
{
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(tableView)
    {
        if(tableView->cellAtIndex(index))
        {
            onSelected(tableView->cellAtIndex(index)->getChildByTag(index));
        }
        
    }
}

void ChapterListLayer::setTableView()
{
    Size size = cellSizeForTable(NULL);
    size.height *= 5;
    size.height -= 5;
    TableView* tableView = TableView::create(this,size);
    tableView->setAnchorPoint(Point::ZERO);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setAnchorPoint(Point::ZERO);
    
    tableView->reloadData();
    tableView->setPosition((this->getContentSize().width - size.width)/2-1, (this->getContentSize().height - size.height)/2 - 10);
    this->addChild(tableView,4,TAG_TABLEVIEW);


}
Node* ChapterListLayer::getNode(int idx)
{
    Sprite* node = Sprite::create();
    node->setAnchorPoint(Point::ZERO);
    Sprite* chapterSpr = Sprite::create(IMG_CHAPTER_CHAPTERWORD);
    chapterSpr->setAnchorPoint(Point::ZERO);
    node->addChild(chapterSpr);
    
    Node* label = PublicShowUI::getNumbers(idx+ 1,IMG_PUBLIC_NUMBER4);
    label->setAnchorPoint(Point::ZERO);
    label->setScale(.4);
    Size size = label->getContentSize();
    size.setSize(size.width * .4, size.height * .4);
    label->setContentSize(size);
    label->setPosition((chapterSpr->getContentSize().width - label->getContentSize().width)/2, chapterSpr->getContentSize().height + 3);
    
    node->addChild(label);
    Sprite* diSpr = Sprite::create(IMG_CHAPTER_DIWORD);
    diSpr->setAnchorPoint(Point::ZERO);
    diSpr->setPosition(chapterSpr->getPosition().x,label->getPositionY() + label->getContentSize().height + 3);
    node->addChild(diSpr);
    
    size = diSpr->getContentSize();
    size.height = diSpr->getPositionY() + diSpr->getContentSize().height;
    node->setContentSize(size);

    Button* btn = Button::create(IMG_PUBLIC_COMBOBOX_BTN1, IMG_PUBLIC_COMBOBOX_BTN2, CC_CALLBACK_1(ChapterListLayer::onChapterClick, this));
    btn->getTouchListener()->setSwallowTouches(false);
    btn->setAnchorPoint(Point::ZERO);
    btn->addChild(node, 10, idx);
    node->setPosition((btn->getContentSize().width - node->getContentSize().width)/2,2);
    return btn;
}
void ChapterListLayer::onSelected(Ref* pSender)
{
    Button* itemImage = (Button*)pSender;
    if(_itemImage == itemImage)
    {
        _itemImage->selected();
        return;
    }
    if(_itemImage)
    {
        _itemImage->unselected();
        _itemImage->release();
    }
    _itemImage = itemImage;
    _itemImage->selected();
    _itemImage->retain();
}
void ChapterListLayer::onChapterClick(Ref* pSender)
{
    onSelected(pSender);
    Button* itemImage = (Button*)pSender;
    int tag = itemImage->getTag();
    if(m_callBack)
    {
        m_callBack(__Integer::create(tag));
    }
}
Size ChapterListLayer::cellSizeForTable(TableView *table)
{
    if(cellSize.height == 0)
    {
        cellSize = getNode(0)->getContentSize();
    }
    return cellSize;
}
TableViewCell* ChapterListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
        cell->setAnchorPoint(Point::ZERO);
    }
    cell->removeAllChildren();
    Node* node = getNode(idx);
    cell->addChild(node,0,idx);
    return cell;
}
ssize_t ChapterListLayer::numberOfCellsInTableView(TableView *table)
{
    return m_chapterCount;// m_chapterCount;
}
void ChapterListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
}



void ChapterListLayer::onEnter()
{
    Layer::onEnter();

}
void ChapterListLayer::onExit()
{
    Layer::onExit();
}
void ChapterListLayer::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void ChapterListLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}
