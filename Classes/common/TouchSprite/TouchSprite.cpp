#include "TouchSprite.h"
USING_NS_CC;
#include "../../commonData/GlobalInfo.h"
#include "../../soundManager/SoundManager.h"
#include "../../common/GameConfig.h"
TouchSprite::TouchSprite()
:isButtonMode(false)
,isAllowTouches(false)
,touchListener(NULL)
,touchAllListener(NULL)
,_isLongPress(0)
,m_scale(0)
,isSuccessDelay(false)
,m_touchMode(Touch::DispatchMode::ONE_BY_ONE)
{
    
//    log("_isLongPress===%4f ==== 1",_isLongPress);
    this->isMovedSprite = false;
    this->c_pfnSelector = NULL;
    this->m_pListener = NULL;
    this->isDoubleClick = false;
    c_touchBegainSelector = NULL;
    c_touchBegainTarget = NULL;
    this->onMoveOutCallBack = NULL;
    this->onMoveInCallBack = NULL;
    onRelesaseOutCallBack = NULL;
    setTouchMode(m_touchMode);
   
}
TouchSprite::~TouchSprite()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    if(touchListener)
    {
        _eventDispatcher->removeEventListener(touchListener);
    }
    touchListener = NULL;
    
    if(touchAllListener)
    {
        _eventDispatcher->removeEventListener(touchAllListener);
    }
    touchAllListener = NULL;
    
    this->m_pListener = NULL;
    this->c_pfnSelector = NULL;
    
    c_touchBegainTarget = NULL;
    c_touchBegainSelector = NULL;
    this->onMoveOutCallBack = NULL;
    this->onMoveInCallBack = NULL;
    onRelesaseOutCallBack = NULL;
}
void TouchSprite::setTouchMode(Touch::DispatchMode mode)
{
    _eventDispatcher->removeEventListenersForTarget(this);
    if(touchListener)
    {
        _eventDispatcher->removeEventListener(touchListener);
    }
    if(touchAllListener)
    {
        _eventDispatcher->removeEventListener(touchAllListener);
    }
    setSwallowTouches(true);
    if(mode == Touch::DispatchMode::ALL_AT_ONCE)
    {
      
        if(!touchAllListener)
        {
            touchAllListener = EventListenerTouchAllAtOnce::create();
  
            touchAllListener->onTouchesBegan = CC_CALLBACK_2(TouchSprite::onTouchesBegan, this);
            touchAllListener->onTouchesMoved = CC_CALLBACK_2(TouchSprite::onTouchesMoved, this);
            touchAllListener->onTouchesEnded = CC_CALLBACK_2(TouchSprite::onTouchesEnded, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(touchAllListener, this);
        }
    }
    else
    {
        if(!touchListener)
        {
            touchListener = EventListenerTouchOneByOne::create();
            setSwallowTouches(this->isAllowTouches);
            touchListener->onTouchBegan = CC_CALLBACK_2(TouchSprite::ccTouchBegan, this);
            touchListener->onTouchMoved = CC_CALLBACK_2(TouchSprite::ccTouchMoved, this);
            touchListener->onTouchEnded = CC_CALLBACK_2(TouchSprite::ccTouchEnded, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        }
    }
}
void TouchSprite::onEnter()
{
    Sprite::onEnter();
    
}
void TouchSprite::onExit()
{
    Sprite::onExit();
}


TouchSprite* TouchSprite::createWithPic(const char *fileName)
{
	return TouchSprite::createWithPic(fileName, NULL, NULL);
}

TouchSprite* TouchSprite::createWithPic(const char *fileName,Ref* rec, SEL_CallFuncN selector)
{
    bool bref = false;
	TouchSprite* pMySprite = new TouchSprite();
 
	if (pMySprite)
	{
        if(fileName)
        {
            
            SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
            if(frame)
            {
                bref = pMySprite->initWithSpriteFrame(frame);
            }
            else
            {
                bref = pMySprite->initWithFile(fileName);
            }
          
        }
        if(bref)
        {
            pMySprite->autorelease();
            pMySprite->c_pfnSelector = selector;
            pMySprite->m_pListener = rec;
            return pMySprite;
        }
	}
	CC_SAFE_DELETE(pMySprite);
    pMySprite = NULL;
	return NULL;
}

//ªÒ»°œµÕ≥∫¡√Î ˝£®À´ª˜“ª∞„ ±º‰º‰∏Ù «250ms°´300ms£©
static inline long millisecondNow()
{
    struct timeval now;
    gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}


static inline bool isDoubleTouch()
{
	static long lastTouchTime = 0;
	long newTouchTime = millisecondNow();
	if (abs(newTouchTime-lastTouchTime) < 250)
	{
		lastTouchTime = newTouchTime;
		return true;
	}
	else
	{
		lastTouchTime = newTouchTime;
		return false;
	}
}
void TouchSprite::setScale(float scale)
{
    if (m_scale == scale)
    {
        return;
    }
    if(this->m_scale == 0)
    {
        m_scale = scale;
    }
    Node::setScale(scale);
    _scaleX = _scaleY = _scaleZ = scale;
    _transformUpdated = _transformDirty = _inverseDirty = true;
    
}
void TouchSprite::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    ccTouchBegan(touches.at(0),unused_event);
}
void TouchSprite::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    ccTouchMoved(touches.at(0),unused_event);
}
void TouchSprite::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    ccTouchEnded(touches.at(0),unused_event);
}
bool TouchSprite::ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    isSuccessDelay = false;
    
    isMovedSprite = false;
    
    
    
	if (this->isClickSprite(pTouch))
	{
//        setSwallowTouches(true);
        if(isButtonMode)
        {
            
            if(m_scale == 0)
            {
                this->runAction(ScaleTo::create(0.05, 0.95 ));
            }
            else
            {
                this->runAction(ScaleTo::create(0.05, 0.95 * m_scale));
            }
            
           
        }
        if(_isLongPress > 0.001)
        {
            this->schedule((SEL_SCHEDULE)schedule_selector(TouchSprite::longPressBack),_isLongPress);
        }
        else
        {
            if(this->c_touchBegainSelector && this->c_touchBegainTarget)
            {
              
                (c_touchBegainTarget->*c_touchBegainSelector)(this);
                
            }
        }
		if (isDoubleTouch())
		{
			isDoubleClick = true;
			return true;
		}
		isDoubleClick = false;

        
        return true;
	}
//    setSwallowTouches(false);
    return false;
}

void TouchSprite::ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    if(pTouch->getDelta().x > 20)
    {
        this->isMovedSprite = true;
    }
   
    if(this->isClickSprite(pTouch))
    {
       
      
        if(this->onMoveInCallBack)
        {
            this->onMoveInCallBack(this);
        }
    }
    else
    {
        if(this->onMoveOutCallBack)
        {
            this->onMoveOutCallBack(this);
        }
//        if(this->isButtonMode)
//        {
//            if(m_scale == 0)
//            {
//                this->runAction(ScaleTo::create(0.05, 1.0));
//            }
//            else
//            {
//               this->runAction(ScaleTo::create(0.05, 1.0 * m_scale));
//            }
//            
//        }
    }
}
bool TouchSprite::getIsMoveSprite()
{
    return this->isMovedSprite;
}
void TouchSprite::ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    
    if(isButtonMode)
    {
        if(m_scale == 0)
        {
            this->runAction(ScaleTo::create(0.05, 1.0));
        }
        else
        {
            this->runAction(ScaleTo::create(0.05, 1.0 * m_scale));
        }
    }
    if(isClickSprite(pTouch))
    {
        //如果对象，回调 没有延时成功  都满足的话就不触发点击触发的回调
       if (m_pListener && c_pfnSelector && !isSuccessDelay)
       {
           (m_pListener->*c_pfnSelector)(this);
           if(this->isButtonMode)
           {
                SoundManager::playEffectMusic(EFFECT_CLICK);
           }
       }
    }
    else
    {
        if(this->onRelesaseOutCallBack)
        {
            this->onRelesaseOutCallBack(this);
        }
    }
    if(_isLongPress < 0.51 && _isLongPress > 0.001)
    {
        this->unschedule((SEL_SCHEDULE)schedule_selector(TouchSprite::longPressBack));
    }
    isSuccessDelay = false;
    
}

void TouchSprite::ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{

}


void TouchSprite::setSwallowTouches(bool enabled)//是否屏蔽下层事件
{
    if(touchListener)
    {
         touchListener->setSwallowTouches(enabled);
    }
    isAllowTouches = enabled;
}

Rect TouchSprite::getRect(Node* spr)
{
    //获取精灵区域大小
	return Rect(spr->getPositionX()- spr->getContentSize().width  * spr->getAnchorPoint().x,spr->getPositionY()-spr->getContentSize().height* spr->getAnchorPoint().y,spr->getContentSize().width, spr->getContentSize().height);
}
bool TouchSprite::isClickSprite(cocos2d::Touch* pTouch)
{
    if(!this->getParent())
    {
        return false;
    }
    Rect rect = getRect(this);
    Point point = pTouch->getLocation();
    
    point = this->getParent()->convertToNodeSpace(point);
    if(rect.containsPoint(point))
    {
        return true;
    }
	return false;
}
//长按模式的回调
void TouchSprite::longPressBack(float fd)
{
    if(this->c_touchBegainSelector && this->c_touchBegainTarget)
    {
        
        (c_touchBegainTarget->*c_touchBegainSelector)(this);
        
    }
    isSuccessDelay = true;
    this->unschedule((SEL_SCHEDULE)schedule_selector(TouchSprite::longPressBack));
}
void TouchSprite::addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector,int longPressType)
{

    this->c_touchBegainTarget = target;
    this->c_touchBegainSelector = selector;
    
    if(longPressType == 1)
    {
        _isLongPress = 0;
//        log("_isLongPress===%4f ==== 2",_isLongPress);
    }
    else if(longPressType == 2)
    {
        _isLongPress = 0.5;
//        log("_isLongPress===%4f ==== 2",_isLongPress);
    }
    
}
