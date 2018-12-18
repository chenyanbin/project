//
//  RaidsLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/25.
//
//

#include "RaidsLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../protocol/UserCustomEvent.h"
#include "../userWealth/UserEquipLayer.h"
#include "../tips/TipsLayer.h"
#include "../../common/CommonMsgProcesser.h"
RaidsLayer::RaidsLayer()
:prizeList(NULL)
,TAG_TABLEVIEW(1)
,m_nowIndex(0)
,isAbleClick(false)
{
    prizeList = new Vector<RaidsData*>();
}
RaidsLayer::~RaidsLayer()
{
    if(prizeList)
    {
        prizeList->clear();
        CC_SAFE_DELETE(prizeList);
        prizeList = NULL;
    }
}
bool RaidsLayer::init(ByteStream* byteStream)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        setBg();
        this->isShowGrayBg = true;
        this->isClickClose = false;
       
        parseMsg(byteStream);
        setTableView();
        bref = true;
    } while (false);
    return bref;
}
RaidsLayer* RaidsLayer::create(ByteStream* byteStream)
{
    RaidsLayer* layer = new RaidsLayer();
    if(layer && layer->init(byteStream))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void RaidsLayer::show(ByteStream* byteStream)
{
    RaidsLayer* layer = RaidsLayer::create(byteStream);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->removeChildByTag(SCENE_TAG_SWEEP);
    scene->addChild(layer,SCENE_MODULAR_TAG);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
}
void RaidsLayer::setBg()
{
    Sprite* bg = Sprite::create(IMG_PUBLIC_LAYER_BG1);
    bg->setAnchorPoint(Point::ZERO);
    
    Sprite* bg2 = Sprite::create(IMG_PUBLIC_LAYER_BG2);
    bg2->setPosition(bg->getContentSize().width/2, bg->getContentSize().height/2);
    bg->addChild(bg2);
    this->setContentSize(bg->getContentSize());
    
    this->addChild(bg,0,TAG_BG);
}
void RaidsLayer::parseMsg(ByteStream* byteStream)
{
    prizeList->clear();
    int roleOldLevel = byteStream->getInt();
    int roleNewLevel = byteStream->getInt();
    CommonMsgProcesser::onUserLevelUp(roleOldLevel,roleNewLevel);
  
    int len = byteStream->get();
    GlobalInfo::getInstance()->raidsCard -= len;
    broadMsg(CUSTOM_UPDATE_USER_RAIDSCARD);
    for(int i = 0; i < len; i++)
    {
        RaidsData* prize = new RaidsData();
        prize->autorelease();
        prize->expAdd = byteStream->getInt();
        prize->coinAdd = byteStream->getInt();
        prize->commonLen = byteStream->get();
        for(int j = 0; j < prize->commonLen; j++)
        {
            PrizeData *object = new PrizeData();
            object->autorelease();
            object->itemType = byteStream->get();
            object->itemDictId = byteStream->getInt();
            object->itemCount = byteStream->get();
            object->itemQuality = byteStream->get();
            prize->itemList->pushBack(object);
            
        }
        
        prize->prestigeLen = byteStream->get();
        for(int j = 0; j < prize->prestigeLen; j++)
        {
            PrizeData* object = new PrizeData();
            object->autorelease();
            object->itemType = byteStream->get();
            object->itemDictId = byteStream->getInt();
            object->itemCount = byteStream->get();
            object->itemQuality = byteStream->get();
            prize->itemList->pushBack(object);
        }
        prizeList->pushBack(prize);
    }
     
}
void RaidsLayer::setTableView()
{
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(tableView)
    {
        tableView->reloadData();
        return;
    }
    Size size = cellSizeForTable(NULL);
    size.height *= 2.8;
    tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::VERTICAL);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setAnchorPoint(Point::ZERO);
    tableView->setPosition((this->getContentSize().width - size.width)/2, 15);
    tableView->reloadData();
    tableView->setTouchEnabled(false);
    this->addChild(tableView,1,TAG_TABLEVIEW);

    if(numberOfCellsInTableView(tableView) >1)
    {
        tableView->setContentOffset(Point(0,-cellSize.height * this->numberOfCellsInTableView(tableView)));
    }
    initPoint = tableView->getContentOffset();
}
void RaidsLayer::setTitle()
{
    Node* bg = this->getChildByTag(TAG_BG);
    Sprite* title = Sprite::create(IMG_BATTLERAIDS_TITLE);
    title->setAnchorPoint(Point(.5,.5));
    this->addChild(title,20);
    
    title->setPosition(bg->getContentSize().width/2, bg->getContentSize().height - title->getContentSize().height - 5);
    
    Sprite* drumSpr = Sprite::create(IMG_BATTLERAIDS_DRUM);
    drumSpr->setAnchorPoint(Point(.5,.5));
    this->addChild(drumSpr,21);
    drumSpr->setPosition(title->getPositionX() + title->getContentSize().width/2 + + drumSpr->getContentSize().width/2 + 5 ,title->getPositionY());
    
    RotateBy* rotateby = RotateBy::create(.1, 25);
    Sequence* action = Sequence::create(rotateby,rotateby->reverse(), NULL);
    drumSpr->runAction(RepeatForever::create(action));
    
    title->setScale(8);
    ScaleTo* scaleTo = ScaleTo::create(.4, .9);
    ScaleTo* scaleTo2 = ScaleTo::create(.1, 1);
 
    title->runAction(Sequence::create(scaleTo,scaleTo2,NULL));
}
void RaidsLayer::onEnter()
{
    BaseLayer::onEnter();
  
    this->setClickEnabled(true);
}
void RaidsLayer::onExit()
{
    BaseLayer::onExit();
}
void RaidsLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
     this->setClickEnabled(false);
}
void RaidsLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
      setTitle();
    m_nowIndex = 0;
    isAbleClick = false;
    if(this->prizeList->size() > 1)
    {
        this->isClickClose = false;
        this->schedule(schedule_selector(RaidsLayer::onUpdate), 2, this->prizeList->size(), 2);
        
    }
    else
    {
         onCompleted();
      
    }
    
    broadMsg(CUSTOM_UPDATE_USER_ITEMS);
}
void RaidsLayer::onUpdate(float dt)
{
    isAbleClick = false;
    this->m_nowIndex ++;
    
    CallFunc* callBack1 = CallFunc::create(CC_CALLBACK_0(RaidsLayer::setContentOffSet, this));
    DelayTime* delay = DelayTime::create(0.3f);
    CallFunc* callBack2 = CallFunc::create(CC_CALLBACK_0(RaidsLayer::onContentBack, this));
    this->stopAllActions();
    this->runAction(Sequence::create(callBack1,delay,callBack2, NULL));
}
void RaidsLayer::setContentOffSet()
{
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Point cp = tableView->getContentOffset();
    cp.y = initPoint.y + this->cellSize.height *(m_nowIndex );
    cp.y = cp.y  + 25 * GlobalInfo::getInstance()->screenScaleX;
    tableView->setContentOffsetInDuration(cp,0.3);
    
}
void RaidsLayer::onContentBack()
{
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Point cp = tableView->getContentOffset();
    cp.y = initPoint.y + this->cellSize.height *(m_nowIndex);
    
    tableView->setContentOffsetInDuration(cp,0.1);
    
    if(this->m_nowIndex >= this->prizeList->size())
    {
        this->unschedule(schedule_selector(RaidsLayer::onUpdate));
        onCompleted();
    }
    isAbleClick = true;
}
void RaidsLayer::onCompleted()
{
    Node* bg = this->getChildByTag(TAG_BG);
    
    
    Sprite* spr = Sprite::create(IMG_BATTLERAIDS_COMPLETED);
    spr->setAnchorPoint(Point(.5,0.5));
    this->addChild(spr,12);
    spr->setPositionX(bg->getContentSize().width/2);
    spr->setPositionY(-20);

    spr->setScale(10);
    ScaleTo* scaleTo = ScaleTo::create(.4, 1.2);
    ScaleTo* scaleTo2 = ScaleTo::create(.1, 1.5);
    CallFunc* callFun = CallFunc::create(CC_CALLBACK_0(RaidsLayer::onSetCloseState, this));
    spr->runAction(Sequence::create(scaleTo,scaleTo2, callFun,NULL));
    
    isAbleClick = true;
 
}
void RaidsLayer::onCompletedBtnClick(Ref* pSender)
{
    
}
void RaidsLayer::onSetCloseState()
{
    this->isClickClose = true;
    TableView* tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    tableView->setTouchEnabled(true);
}
Node* RaidsLayer::getNode(int index)
{
    
     Sprite* node = Sprite::create(IMG_BATTLERAIDS_ITEMBG);
    node->setAnchorPoint(Point::ZERO);
    Color3B color = PublicShowUI::getColor3b(COLOR_BROWN_WORD);
    string str = "第" + PublicShowUI::numberToString(index + 1) + "次";
    Label* countLabel = PublicShowUI::getLabel(str.c_str(),color,18,false,false);
    countLabel->setAnchorPoint(Point::ZERO);
    countLabel->setPosition(8, node->getContentSize().height - countLabel->getContentSize().height - 10);
    node->addChild(countLabel);
    
    RaidsData* prize = this->prizeList->at(index);
    color = PublicShowUI::getColor3b(COLOR_YELLOW_WHITE);
    //经验
    Label* explabel = PublicShowUI::getLabel(PublicShowUI::numberToString(prize->expAdd).c_str(),color,16,false,false);
    explabel->setAnchorPoint(Point::ZERO);
    explabel->setPosition(48, (node->getContentSize().height - explabel->getContentSize().height)/2);
    node->addChild(explabel);
    
    //铜币
    Label* coinLabel = PublicShowUI::getLabel(PublicShowUI::numberToString(prize->coinAdd).c_str(),color,16,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    coinLabel->setPosition(explabel->getPositionX(),explabel->getPositionY() - coinLabel->getContentSize().height - 24);
    
    node->addChild(coinLabel);
    
    
    int len = prize->itemList->size();
    PrizeData* itemData = NULL;
    const char* path = NULL;

    float sx = .55;
    float _width = 71;
    float startX = 123;
    float startY = node->getContentSize().height - _width - 1 ;
    prize->commonLen = 4;
    UserEquipLayer* icon = NULL;
    for(int i = 0; i < len; i++)
    {
        itemData = prize->itemList->at(i);
        path = PublicShowUI::getGoods(itemData->itemType, itemData->itemDictId);
        icon = UserEquipLayer::create(path,itemData->itemQuality,false);
        icon->setAnchorPoint(Point::ZERO);
        icon->addTouchBegainCallBack(this, callfuncN_selector(RaidsLayer::onItemClick));//
//        if(itemData->itemCount > 1)
//        {
//            Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(itemData->itemCount).c_str(),Color3B::WHITE,17,false,false);
//            label->setAnchorPoint(Point::ZERO);
//            icon->addChild(label);
//            label->setPosition(icon->getContentSize().width - label->getContentSize().width - 2, 2);
//            
//        }
        icon->setScale(sx);
        icon->setPositionX(startX + (i % prize->commonLen)  * _width);
        icon->setPositionY(startY - (i / prize->commonLen) * (_width + 2));
        
        node->addChild(icon,i,i);
    }
    
    return node;
}
void RaidsLayer::onItemClick(Node* psender)
{
    int parentTag = psender->getParent()->getTag();
    int tag = psender->getTag();
     RaidsData* prize = this->prizeList->at(parentTag);
    if(prize)
    {
        PrizeData* itemData = prize->itemList->at(tag);
        if(itemData)
        {
            TipsLayer::show(itemData->itemType, itemData->itemDictId,itemData->itemCount);
        }
 
    }
}
Size RaidsLayer::cellSizeForTable(TableView *table)
{
    if(cellSize.height == 0)
    {
        Sprite* node = Sprite::create(IMG_BATTLERAIDS_ITEMBG);
        cellSize = node->getContentSize();
        cellSize.height += 10;
    }
    return cellSize;
}
TableViewCell* RaidsLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = getNode(int(idx));
    cell->addChild(node,1,idx);
    
    cell->setContentSize(node->getContentSize());
    return cell;
}
ssize_t RaidsLayer::numberOfCellsInTableView(TableView *table)
{
    return this->prizeList->size();
}
void RaidsLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
bool RaidsLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    return true;
}
void RaidsLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchMoved(touch, unused_event);
}
void RaidsLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
   
   if(!isAbleClick)
   {
       return;
   }
    if(this->m_nowIndex >= this->prizeList->size())
    {
        BaseLayer::onTouchEnded(touch, unused_event);
        return;
    }
    onUpdate(2);
    this->unschedule(schedule_selector(RaidsLayer::onUpdate));
    this->schedule(schedule_selector(RaidsLayer::onUpdate), 2, this->prizeList->size(), 2);
}
