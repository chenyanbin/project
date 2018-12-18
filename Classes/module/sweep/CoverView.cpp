//
//  CoverView.cpp
//  FightPass
//
//  Created by chenyanbin on 15/7/16.
//
//

#include "CoverView.h"
CoverView::CoverView()
:wSize()
,m_isleft(true)
{
    
}

CoverView::~CoverView()
{
    cardList->clear();
    CC_SAFE_DELETE(cardList);
    cardList = NULL;
}

CoverView* CoverView::create(Rect swBox, Size slSize , float disDistance , float disScale)
{
    CoverView* cover = new CoverView();
    if(cover && cover->init(swBox,slSize,disDistance,disScale))
    {
        cover->autorelease();
        return cover;
    }
    CC_SAFE_DELETE(cover);
    return NULL;
}

bool CoverView::init(Rect swBox , Size slSize , float disDistance , float disScale)
{
    if(!Node::init()) return false;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CoverView::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CoverView::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CoverView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->swBox = swBox;
    this->swPosition = swBox.origin;
    this->swSize = swBox.size;
    this->slSize = slSize;
    this->disDistance = disDistance;
    this->disScale = disScale;
    initData();
    return true;
}


void CoverView::initData()
{
    cardList = new Vector<Sprite*>();
    Size s = VisibleRect::getVisibleRect().size;
    wSize.width = s.width;
    wSize.height = s.height;
    cardNum = 0;
    
    offsetPosition = Point(swSize.width/2,swSize.height/2);
    
    scrollLayer = Layer::create();
    scrollLayer->setAnchorPoint(Point::ZERO);
    scrollLayer->setPosition(Point::ZERO);
    scrollLayer->setContentSize(slSize);
    
    scrollView = ScrollView::create(swSize,scrollLayer);
    scrollView->setAnchorPoint(Point::ZERO);
    scrollView->setContentOffset(Point(0,0));
    scrollView->setTouchEnabled(false);
    scrollView->setDelegate(this);
    addChild(scrollView,1);
    this->setContentSize(scrollView->getContentSize());
    

    slayerPosition = Point::ZERO;
    isMove = true;

}

void CoverView::onEnter()
{
    BaseLayer::onEnter();
//    adjusetEndScrollView();

}

void CoverView::onExit()
{
    removeAllChildren();
    BaseLayer::onExit();
}

bool CoverView::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    
    return !GlobalInfo::getInstance()->isGuiding;
}

void CoverView::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Point scroll_prepoint = pTouch->getPreviousLocation();
    Point scroll_movepoint = pTouch->getLocation();
    if(swBox.containsPoint(scroll_movepoint))
    {
        Point adjustPoint = scroll_movepoint-scroll_prepoint;
        adjustScrollView(adjustPoint);
        adjustCardScale(adjustPoint);
    }

}

void CoverView::onTouchEnded(Touch* pTouch, Event* pEvent)
{

    adjusetEndScrollView();
    Point curPosition = scrollLayer->getPosition();
    float distance =  slayerPosition.getDistance(curPosition);//ccpDistance(slayerPosition, curPosition);
    if (distance < 5.0f) isMove = false;
}

void CoverView::adjustCardScale(Point adjustPoint)
{
    
    for( auto card : *cardList)
    {
        float offset = scrollView->getContentOffset().x;
        float posX = card->getPositionX() + offset;
        float disMid = std::abs(swSize.width/2-posX);
        float scale = 1- disMid/disDistance*disScale;
        card->setScale(scale);
        int zOr = (int) (1000-disMid*0.1);
        card->setZOrder(zOr);
    }
}

void CoverView::adjustScrollView(Point adjustPoint)
{
    Point endPoint = scrollView->getContentOffset()+Point(adjustPoint.x,0);
    scrollView->unscheduleAllSelectors();
    scrollView->setContentOffset(endPoint,false);
 
}

void CoverView::adjusetEndScrollView()
{
    float minX = wSize.width;
    float midX = swSize.width/2;
    //获取距离中间最小值的card
    for( auto card : *cardList)
    {
//        Node* card = (Node*) obj;
        float offset = scrollView->getContentOffset().x;
        //转化父类坐标
        float posX = card->getPositionX() + offset;
        float disMid = midX-posX;
        if(std::abs(disMid) < std::abs(minX)) minX = disMid;
    }
    
    for( auto card : *cardList)
    {
        //转化父类坐标
        float offset = scrollView->getContentOffset().x;
        float posX = card->getPositionX() + offset ;
        //距离中间长度
        float disMid = std::abs(midX - posX - minX);
        //目标scale
        float scale = 1- disMid/disDistance*disScale;
        ScaleTo* scaleBy = ScaleTo::create(0.2f,scale);
        card->runAction(scaleBy);
        int zOr = (int) (1000-disMid*0.1);
        card->setZOrder(zOr);
    }

    
   
    
    Layer* scrollLayer = (Layer*)scrollView->getContainer();
    MoveBy* moveBy = MoveBy::create(0.2f,Point(minX,0));
    CallFuncN* callFuncN = CallFuncN::create(CC_CALLBACK_1(CoverView::cardViewEnd_callBack,this));
    Sequence* seq = CCSequence::create(moveBy,callFuncN,NULL);
    scrollLayer->runAction(seq);
}
void CoverView::update(float dt)
{
    
}
void CoverView::cardViewEnd_callBack(Node* pSender)
{
    slayerPosition = scrollLayer->getPosition();
    isMove = true;
    
    
    for( auto card : *cardList)
    {
        if (card->getLocalZOrder() == 1000)
        {
            card->setOpacity(255);
        }
        else
        {
            card->setOpacity(110);
        }
        card->setCascadeOpacityEnabled(true);
    }
}

void CoverView::scrollViewDidScroll(ScrollView* view)
{
   
}

void CoverView::scrollViewDidZoom(ScrollView* view)
{
    
}

void CoverView::addCard(Sprite * card)
{
    int zOrder = 1000 - cardNum;
    this->addCard(card, zOrder, 0);
}

void CoverView::addCard(Sprite * card, int zOrder)
{
    this->addCard(card, zOrder,0);
}

void CoverView::addCard(Sprite* card, int zOrder, int tag)
{
    float positionX = offsetPosition.x + disDistance*cardNum;
    float scale = 1 - disScale*cardNum;
    card->setAnchorPoint(Point(0.5,0.5));
    card->setPosition(Point(positionX,offsetPosition.y));
    card->setScale(scale);
    cardList->pushBack(card);
    scrollLayer->addChild(card , zOrder,tag);
    cardNum++;
    log("crad%d:[%f , %f]",cardNum,card->getPositionX(),card->getPositionY());
    adjusetEndScrollView();
}

int CoverView::getCurCardIndex()
{
    float distance1 = - scrollLayer->getPositionX();
    float distance2 = swSize.width/2 - offsetPosition.x;
    //+5 浮点数误差
    int index = (distance1 + distance2 + 5) / (disDistance);
    //log("card index:%d  distance1:%f",index,distance1);
    return index;
}
void CoverView::setCurCardByIndex(int index)
{
    auto card = cardList->at(index);
    float offX = card->getPositionX()  - offsetPosition.x;
    
    offX = -scrollLayer->getPositionX() - offX;
   
   
    Point adjustPoint = Point(offX,0);
     adjustScrollView(adjustPoint);
     adjustCardScale(adjustPoint);
    adjusetEndScrollView();
}
void CoverView::setOffsetPosition(Point var)
{
    offsetPosition = var;
    cardNum = 0;
    for( auto card : *cardList)
    {
        float positionX = offsetPosition.x + disDistance*cardNum;
        card->setPosition(Point(positionX,offsetPosition.y));
        cardNum++;
    }
    adjustCardScale(Point::ZERO);

}

Point CoverView::getOffsetPosition()
{
    return offsetPosition;
}