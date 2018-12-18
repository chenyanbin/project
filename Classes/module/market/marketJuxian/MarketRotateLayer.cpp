//
//  MarketRotateLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/28.
//
//

#include "MarketRotateLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include <math.h>
#include "../../../protocol/UserCustomEvent.h"
#define PI acos(-1)
USING_NS_CC;
MarketRotateLayer::MarketRotateLayer()
:m_nowSelectedIndex(0)
,m_delegate(NULL)
,m_index(0)
,m_touch(false)
,m_isRight(false)
,m_ischange(false)
,m_isdianjizhong(false)
,sx(1)
,oldindex(0)
{
}
MarketRotateLayer::~MarketRotateLayer()
{
    _items.clear();
    m_delegate = NULL;
}
bool MarketRotateLayer::init(){
    if (!Layer::init())
        return false;
    _angle = 0.0;
    sx = GlobalInfo::getInstance()->screenScaleX;
    this->ignoreAnchorPointForPosition(false);
    Size s = SDResource.size;
    this->setAnchorPoint(Point(0.5,0.5));
    this->setContentSize(s/3*2);
    
    auto listener = EventListenerTouchOneByOne::create();
    //    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MarketRotateLayer::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(MarketRotateLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MarketRotateLayer::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
};

void MarketRotateLayer::addMenuItem(cocos2d::MenuItem *item)
{
    addMenuItem(item, item->getZOrder(), item->getTag());
    return;
}
void MarketRotateLayer::addMenuItem(cocos2d::MenuItem *item, int zOrder)
{
    addMenuItem(item, zOrder, item->getTag());
    
}
void MarketRotateLayer::addMenuItem(cocos2d::MenuItem *item, int zOrder, int tag)
{
    item->setPosition(Point::ZERO);
    this->addChild(item,zOrder,tag);
    _items.pushBack(item);
    setUnitAngle(2 * PI / _items.size());
    reset();
    
    auto menuSize =this->getContentSize();
    auto disX = menuSize.width / 2.4;
    auto disY = menuSize.height / 10;
    for (int i = 0; i < _items.size(); i++)
    {
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        
        _items.at(i)->setPosition(Point(x, y));
//        _items.at(i)->setOpacity(90 + 165 * cos(i*_unitAngle + getAngle()));
        if(_items.at(i)->getScale() == 1)
        {
            this->m_nowSelectedIndex = i;
        }
    }
    
    return;
}
void MarketRotateLayer::updatePosition(){
    
//    if(m_delegate)
//    {
//        m_delegate->scrollViewDidScroll(this);
//    }
    auto menuSize = getContentSize();
    auto disX = menuSize.width / 2.4;
    auto disY = menuSize.height / 10;
    for (int i = 0; i < _items.size(); i++){
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle+getAngle());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        _items.at(i)->setPosition(Point(x, y));
        _items.at(i)->setZOrder(-(int)y);
        //Opacity  129~255
        _items.at(i)->setOpacity(255);
    }

    return;
}
void MarketRotateLayer::updatePositionWithAnimation()
{
    int nextSelectedIndex = 0;
    float scale = 0;
    auto menuSize = this->getContentSize();
    auto disX = menuSize.width / 2.4;
    auto disY = menuSize.height / 10;
    for (int i = 0; i < _items.size(); i++)
    {
        _items.at(i)->stopAllActions();
        float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
        log("%f==================",_items.at(0)->getPositionX());
        float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
        auto moveTo = MoveTo::create(animationDuration, Point(x, y));
        _items.at(i)->runAction(moveTo);
        //缩放比例  0.5~1
        scale = 0.9 + 0.1*cos(i*_unitAngle + getAngle());
        _items.at(i)->setZOrder(-(int)y);
        if(scale == 1)
          {
            nextSelectedIndex = i;
        }
    }
    
    if(nextSelectedIndex == oldindex)
    {
        m_ischange = false;
    }else{
        oldindex = nextSelectedIndex;
        m_ischange = true;
    }
    if (!m_ischange) {
        return;
    }
    if (m_isRight)
    {
        if (m_index == 0) {
            m_index = 2;
        }else if (m_index == 1)
        {
            m_index =0;
        }else if (m_index == 2)
        {
            m_index = 1;
        }
    }
    else
    {
        if (m_index == 0) {
            m_index = 1;
        }else if (m_index == 1)
        {
            m_index =2;
        }else if (m_index == 2)
        {
            m_index = 0;
        }

    }
//    m_index = nextSelectedIndex;
    DelayTime* delay = DelayTime::create(animationDuration);
    CallFunc* callBack = CallFunc::create(CC_CALLBACK_0(MarketRotateLayer::onMoveEnded, this,m_index));
    this->stopAllActions();
    this->runAction(Sequence::create(delay,callBack, NULL));

    return;
}
void MarketRotateLayer::onMoveEnded(int nextSelected)
{
    log("nextSelected==%d",nextSelected);
    if(m_delegate)
    {
        m_delegate->tableCellTouched(this);
    }
    broadMsg(CUSTOM_MARKER_CHANGECARDPOS,__Integer::create(nextSelected));
 
}
int MarketRotateLayer::getSelected()
{
    
    return m_nowSelectedIndex;
}
void MarketRotateLayer::reset(){
    _angle = 0;
    m_nowSelectedIndex = 0;
}
void MarketRotateLayer::setAngle(float angle){
    this->_angle = angle;
}
float MarketRotateLayer::getAngle(){
    return _angle;
}
void MarketRotateLayer::setUnitAngle(float angle){
    _unitAngle = angle;
}
float MarketRotateLayer::getUnitAngle(){
    return _unitAngle;
}

float MarketRotateLayer::disToAngle(float dis){
    float width = this->getContentSize().width / 2;
    return dis / width*getUnitAngle();
}

MenuItem * MarketRotateLayer::getCurrentItem(){
    if (_items.size() == 0)
        return nullptr;
    //这里实际加上了0.1getAngle(),用来防止精度丢失
    int  index = (int)((2 * PI - getAngle()) / getUnitAngle()+0.1*getUnitAngle());
    index %= _items.size();
    return _items.at(index);
}

bool MarketRotateLayer::onTouchBegan(Touch* touch, Event* event)
{
    if (m_isdianjizhong) {
        return false;
    }
    m_isdianjizhong = true;
    m_touch = false;
    m_ischange = false;
    //先停止所有可能存在的动作
    touchBeginPos = touch->getLocation();
    for (int i = 0; i < _items.size(); i++)
        _items.at(i)->stopAllActions();
    
//    auto position = this->convertToNodeSpace(touch->getLocation());
//    auto size = this->getContentSize();
//    auto rect = Rect(0, 0, size.width, size.height);
//    if (rect.containsPoint(position)){
    
        updatePosition();
//        return true;
//    }
    return true;
}
void MarketRotateLayer::onTouchMoved(Touch* touch, Event* event){
    
    if(m_delegate)
    {
        m_delegate->scrollViewDidScroll(this);
    }
    
    if(abs(touch->getLocation().x - touchBeginPos.x)<400)
    {
    auto angle = disToAngle(touch->getDelta().x);
    setAngle(getAngle() + angle);
    updatePosition();
    m_touch = true;
    }
    return;
}
void MarketRotateLayer::onTouchEnded(Touch* touch, Event* event)
{
    m_isdianjizhong = false;
    log("---------------------%f",touch->getLocation().x - touchBeginPos.x);
//    if (fabs(touch->getLocation().x - touchBeginPos.x)>126) {
//        m_ischange = true;
//    }
    auto xDelta = touch->getLocation().x - touch->getStartLocation().x;
    rectify(xDelta>0);
    if (xDelta>0) {
        m_isRight = true;
    }else if (xDelta<0)
    {
        m_isRight = false;
    }
    if (m_touch == true)
    {
        updatePositionWithAnimation();
    }
    else
    {
        auto position = this->convertToNodeSpace(touch->getLocation());
        log("%f,%f,%f,%f",this->getPositionX(),this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
        log("TouchPOs ========= %f,000=========%f",position.x,_items.at(0)->getPositionX());
        auto rect = Rect(this->getPositionX(),this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
        if (rect.containsPoint(position)) {
            if (position.x < 378-_items.at(0)->getContentSize().width/2)
            {
                clickTurnrRight();
            }else if ( position.x >378+_items.at(0)->getContentSize().width/2)
            {
                clicktTurnLeft();
            }
        }
        
    }
    return;
}

void MarketRotateLayer::rectify(bool forward){
    auto angle = getAngle();
    while (angle<0)
        angle += PI * 2;
    while (angle>PI * 2)
        angle -= PI * 2;
    if(forward>0)
        angle = ((int)((angle + getUnitAngle() / 3*2) / getUnitAngle()))*getUnitAngle();
    else
        angle = ((int)((angle + getUnitAngle() / 3 ) / getUnitAngle()))*getUnitAngle();
    setAngle(angle);
}

void MarketRotateLayer::clickTurnrRight()
{
    Point s =_items.at(0)->getPosition();    
    auto moveTo1 = MoveTo::create(animationDuration, Point(_items.at(1)->getPositionX(),_items.at(1)->getPositionY()));
    _items.at(0)->runAction(moveTo1);
    auto moveTo2 = MoveTo::create(animationDuration, Point(_items.at(2)->getPositionX(),_items.at(2)->getPositionY()));
    _items.at(1)->runAction(moveTo2);
    auto moveTo3 = MoveTo::create(animationDuration, Point(s.x,s.y));
    _items.at(2)->runAction(moveTo3);

    MenuItem *m_item =  _items.at(2);
    _items.popBack();
    _items.insert(0, m_item);
    
    
    if (m_index == 0)
    {
        m_index = 2;
    }else if (m_index == 1)
    {
        m_index =0;
    }else if (m_index == 2)
    {
        m_index = 1;
    }
    log("m_index==========%d",m_index);
    onMoveEnded(m_index);

}
void MarketRotateLayer::clicktTurnLeft()
{
    Point s =_items.at(0)->getPosition();
    auto moveTo1 = MoveTo::create(animationDuration, Point(_items.at(2)->getPositionX(),_items.at(2)->getPositionY()));
    _items.at(0)->runAction(moveTo1);
    auto moveTo2 = MoveTo::create(animationDuration, Point(_items.at(1)->getPositionX(),_items.at(1)->getPositionY()));
    _items.at(2)->runAction(moveTo2);
    auto moveTo3 = MoveTo::create(animationDuration, Point(s.x,s.y));
    _items.at(1)->runAction(moveTo3);
    
    MenuItem *m_item =  _items.at(0);
    _items.erase(_items.begin());
    _items.pushBack(m_item);
    
    if (m_index == 0)
    {
        m_index = 1;
    }else if (m_index == 1)
    {
        m_index =2;
    }else if (m_index == 2)
    {
        m_index = 0;
    }
    log("m_index==========%d",m_index);
    onMoveEnded(m_index);
}
void MarketRotateLayer::setDelegate(RotateDeleate* delegate)
{
    this->m_delegate = delegate;
}

