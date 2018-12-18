//
//  SimplePad.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#include "SimplePad.h"
SimplePad::SimplePad()
:m_delegate(NULL)
,handShank(NULL)
,isHold(false)
,_radius(0)
,sx(0)
,downStart(Point::ZERO)
,m_isClickThis(false)
{
    
}
SimplePad::~SimplePad()
{
    m_delegate = NULL;
}
bool SimplePad::init(const char* path,float radius)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        
        this->setBackground(path);
        winSize =  VisibleRect::getVisibleRect().size;
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->_radius = 50;
       
        bref = true;
    } while (false);
    return  bref;
}
void SimplePad::setBackground(const char* path)
{
    Sprite* handShank = Sprite::create(path);
    handShank->setOpacity(130);
    this->addChild(handShank,0,TAG_BG);
    this->setContentSize(handShank->getContentSize());
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumJoystick,handShank);
}
SimplePad* SimplePad::create(const char* path,float radius)
{
    SimplePad* pad  = new SimplePad();
    if(pad && pad->init(path, radius))
    {
        pad->autorelease();
        return pad;
    }
    CC_SAFE_DELETE(pad);
    pad = NULL;
    return  NULL;
}

void SimplePad::onEnter()
{
    BaseLayer::onEnter();
}
void SimplePad::onExit()
{
    BaseLayer::onExit();
}
void SimplePad::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
    this->unscheduleUpdate();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumJoystick);
}
void SimplePad::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    this->setClickEnabled(true);
    this->scheduleUpdate();
}

void SimplePad::setDelegate(SimplePadDelegate* delegate)
{
    m_delegate = delegate;
}
bool SimplePad::isClickSprite(cocos2d::Touch* pTouch)
{
    
    if(this->isHold)
    {
        return false;
    }
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    
    Rect rect = PublicShowUI::getRect(bg);
    Point point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    if (rect.containsPoint(point))
    {
        return true;
    }
    
    return false;
    
}
bool SimplePad::onTouchBegan(Touch *touch, Event *unused_event)
{
    if(!this->isVisible())
    {
        return false;
    }
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
    Point tempDownStart= touch->getLocation();
    Node* battleLayer = Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_BATTLE);
    float _scale = battleLayer? .7 : .3;
    if(tempDownStart.x < winSize.width * .4 && tempDownStart.y < winSize.height * _scale && tempDownStart.y)
    {
        downStart = tempDownStart;
        if (bgSprite)
        {
            bgSprite->setOpacity(255);
            selfInitPoint = this->getPosition();
            this->setPosition(tempDownStart.x,tempDownStart.y);
        }
        isHold = true;
        m_isClickThis=true;
    }
    else
    {
        m_isClickThis= false;
    }
    return m_isClickThis;
}
void SimplePad::onTouchMoved(Touch *touch, Event *unused_event)
{
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
    Point tempDownStart = touch->getLocation();
    Point reachPoint=Point(tempDownStart.x-downStart.x, tempDownStart.y-downStart.y);
    //计算2点间的距离
    float tempNum = sqrt(reachPoint.x*reachPoint.x+reachPoint.y*reachPoint.y);
    if(tempNum < 5)
    {
        return;
    }
    Point tempPoint;
    if (tempNum < _radius)
    {
        tempPoint = reachPoint;
    }
    else
    {
        float radian = reachPoint.getAngle();//求出两点的狐度值
        float degrees =CC_RADIANS_TO_DEGREES(radian);//孤度转角度
        //求在圆心的点
        tempPoint=Point(_radius*cos(degrees*M_PI/180),_radius*sin(degrees*M_PI/180));
        
    }
  
    bgSprite->setPosition(tempPoint);
    if(this->isHold)
    {
        this->updateDirectionForTouchLocation(tempPoint);
    }

}

void SimplePad::onTouchEnded(Touch *touch, Event *unused_event)
{
    downStart=Point(0, 0);
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
    bgSprite->setPosition(Point::ZERO);
    if (bgSprite)
    {
        bgSprite->setOpacity(130);
    }
    
    this->_direction = Point::ZERO;
    this->isHold = false;
    if(this->m_delegate)
    {
        this->m_delegate->simplePadTouchEnded(this);
    }
    this->setPosition(selfInitPoint);
}
void SimplePad::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if(touches.size() > 1 || isHold)
    {
        return;
    }
    
    Touch* touch = touches.at(0);
    onTouchBegan(touch,unused_event);
    
}
void SimplePad::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch* touch = touches.at(0);
    onTouchMoved(touch,unused_event);
}
void SimplePad::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    onTouchEnded(touches.at(0),unused_event);
}

void SimplePad::update(float dt)
{
    if(this->m_delegate && this->isHold && _direction != Point::ZERO)
    {
        this->m_delegate->isHoldingDirector(this, this->_direction);
    }
}
void SimplePad::updateDirectionForTouchLocation(Point location)
{
    _direction = Point::ZERO;
    //    Point cp = location - this->getPosition();
    float radian = location.getAngle();//求出两点的狐度值
    float degrees = - 1 * CC_RADIANS_TO_DEGREES(radian);//孤度转角度
//    log("degrees====%f",degrees);
    //22.5为360/8/2
    //    float minDegree = 360 / 8 / 2;
    if(degrees >= -22.5 && degrees <= 22.5)
    {
        this->_direction = Point(1,0);
//        log("向右");
    }
    else if(degrees > 22.5 && degrees <= 67.5)
    {
        this->_direction = Point(1,-1);
//        log("右下");
    }
    else if(degrees > 67.5 && degrees <= 112.5)
    {
        this->_direction = Point(0,-1);
//        log("向下");
    }
    else if(degrees > 112.5 && degrees < 157.5)
    {
        this->_direction = Point(-1,-1);
//        log("左上");
    }
    else if(degrees >= 157.5 || degrees <= -157.5)
    {
        this->_direction = Point(-1,0);
//        log("向左");
    }
    else if(degrees <-22.5 && degrees > - 67.5)
    {
        this->_direction = Point(1,1);
//        log("右上");
    }
    else if(degrees <= -67.5 && degrees >= - 112.5)
    {
        this->_direction = Point(0,1);
//        log("向上");
    }
    else if(degrees <-112.5 && degrees > -157.5)
    {
        this->_direction = Point(-1,1);
//        log("左下");
    }
    else
    {
//        log("上一个方向");
    }
    //    log("direction.x=%f,directon.y=%f",_direction.x,_direction.y);
    if(this->m_delegate)
    {
        this->m_delegate->didChangeDirectorTo(this, _direction);
    }
}