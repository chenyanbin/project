//
//  Button.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14/10/29.
//
//

#include "Button.h"
#include "../PublicShowUI.h"
#include "../../soundManager/SoundManager.h"
#include "../../common/GameConfig.h"

Button::Button()
:_normalImage(NULL)
,_selectedImage(NULL)
,_disabledImage(NULL)
,m_callBack(NULL)
,touchListener(NULL)
,m_userData(NULL)
,m_state(0)
,m_scale(0)
,onReleaseOutSide(NULL)
,onTouchPress(NULL)
,isBegainThis(false)
,imagePath("")
,isShowClickSound(true)
,m_touchEventIsEnabled(true)
,m_selectedScale(1.2)
{
    
}
Button::~Button()
{
    _normalImage = NULL;
    _selectedImage = NULL;
    _disabledImage = NULL;
    m_callBack = NULL;
    onReleaseOutSide = NULL;
    if(touchListener)
    {
        _eventDispatcher->removeEventListener(touchListener);
    }
    CC_SAFE_RELEASE_NULL(touchListener);
    m_userData = NULL;

}
void Button::onEnter()
{
    Node::onEnter();
    _eventDispatcher->removeEventListener(touchListener);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Button::onExit()
{
    Node::onExit();
   
}
void Button::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
     _eventDispatcher->removeEventListener(touchListener);
}
void Button::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
   this->setCascadeOpacityEnabled(true);
}
bool Button::init(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->setAnchorPoint(Point(.5,.5));
        setNormalImage(normalImage);
        setSelectedImage(selectedImage);
 
        this->m_callBack = callback;
        touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(touchListener);
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(Button::ccTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(Button::ccTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Button::ccTouchEnded, this);
        hideAll(false);
        
        if(_normalImage)
        {
            this->_normalImage->setVisible(true);
        }
        
        bref = true;
    } while (false);
    return bref;
   
}
void Button::setNormalImage(const std::string& normalImage )
{
   
    if(_normalImage)
    {
        _normalImage->removeFromParent();
    }
//
    imagePath = normalImage;
    this->_normalImage = Sprite::create(normalImage);
    if(!_normalImage)
    {
       SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage);
        if(frame)
        {
          _normalImage = Sprite::createWithSpriteFrameName(normalImage);
        }
        else
        {
            return;
        }
    }
 
    _normalImage->setAnchorPoint(m_anchorPoint);
   _normalImage->setCascadeOpacityEnabled(true);
    this->setContentSize(_normalImage->getContentSize());
    this->addChild(_normalImage,2);
    _normalImage->setVisible(true);
    
}
void Button::setSelectedImage(const std::string&selectedImage)
{
    bool _visible = true;
    if(_selectedImage)
    {
        _visible = _selectedImage->isVisible();
        _selectedImage->removeFromParent();
    }
    if(selectedImage != "")
    {
        this->_selectedImage = Sprite::create(selectedImage);
        if(!_selectedImage)
        {
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(selectedImage);
            if(frame)
            {
                _selectedImage = Sprite::createWithSpriteFrameName(selectedImage);
            }
            else
            {
                return;
            }
            
        }
        
        _selectedImage->setVisible(_visible);
          _selectedImage->setCascadeOpacityEnabled(true);
        this->addChild(_selectedImage,1);
    }

}

void Button::setAnchorPoint(const Point& anchorPoint)
{
//    Node::setAnchorPoint(anchorPoint);
    m_anchorPoint = anchorPoint;
    if(_normalImage)
    {
         _normalImage->setAnchorPoint(anchorPoint);
    }
    if(_selectedImage)
    {
         _selectedImage->setAnchorPoint(anchorPoint);
    }
    if(_disabledImage)
    {
        _disabledImage->setAnchorPoint(anchorPoint);
    }
}
Point Button::getAnchorPoint()
{
    if(_normalImage)
    {
        return _normalImage->getAnchorPoint();
    }
    return m_anchorPoint;
}
Node* Button::getDisAbleImage()
{
    return this->_disabledImage;
}
Node* Button::getNormalImage()
{
    return this->_normalImage;
}
Node* Button::getSelectedImage()
{
    return this->_selectedImage;
}
EventListenerTouchOneByOne* Button::getTouchListener()
{
    return touchListener;
}
bool Button::isClickSprite(cocos2d::Touch* pTouch)
{
    
    if(m_state == STATE_DISABLED || this->isVisible() == false)
    {
        return false;
    }
    
    
    Point touchLocation = pTouch->getLocation();
    
    if (!_children.empty())
    {
        for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter)
        {
            Node* child = dynamic_cast<Node*>(*iter);
            if (child && child->isVisible())
            {
                Point local = child->convertToNodeSpace(touchLocation);
                Rect r = PublicShowUI::getRect(child);
                r.origin = Point::ZERO;
                
                if (r.containsPoint(local))
                {
                    return true;
                }
            }
        }
    }
    return false;

}
bool Button::ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    if(!m_touchEventIsEnabled)
    {
        return false;
    }
    if (this->isClickSprite(pTouch))
    {
        isBegainThis = true;
        this->selected();
        
        if(onTouchPress)
        {
            onTouchPress(this);
        }
        return true;
    }
    else
    {
        
        isBegainThis = false;
    }

    return false;
}
void Button::ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
  
    if(!m_touchEventIsEnabled)
    {
        return;
    }
    if(this->m_state == STATE_SELECTED)
    {
        return;
    }
    if(isClickSprite(pTouch))
    {
        this->selected();
    }
    else
    {
        this->unselected();
    }
}
void Button::ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    if(!m_touchEventIsEnabled)
    {
        return;
    }
   
    
    this->unselected();
    
    if(isClickSprite(pTouch))
    {
        if(this->m_callBack)
        {
            if(isBegainThis)
            {
                if(isShowClickSound)
                {
                    SoundManager::playEffectMusic(EFFECT_CLICK);
                }
                this->m_callBack(this);
                isBegainThis = false;
            }
           
        }
    }
    else
    {
        if(onReleaseOutSide)
        {
            onReleaseOutSide(this);
        }
    }
}
void Button::ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    this->unselected();
}
/** creates a menu item with a normal and selected image with a callable object */
Button* Button::create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback)
{
    Button* button = new Button();
//    button->setCascadeOpacityEnabled(true);
    if(button && button->init(normalImage, selectedImage, callback))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}
void Button::setOpacity(float opacity)
{
    if(_normalImage)
    {
        this->_normalImage->setOpacity(opacity);
    }
    if(_selectedImage)
    {
        this->_selectedImage->setOpacity(opacity);
    }
}
void Button::updateDisplayedOpacity(GLubyte parentOpacity)
{
    Node::updateDisplayedOpacity(parentOpacity);
    if(_normalImage)
    {
        this->_normalImage->updateDisplayedOpacity(_displayedOpacity);
    }
    if(_selectedImage)
    {
        this->_selectedImage->updateDisplayedOpacity(_displayedOpacity);
    }
}
void Button::setScale(float scale)
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
void Button::hideAll(bool isAction)
{
    if(_selectedImage)
    {
        _selectedImage->setVisible(false);
    }
    else if(_normalImage)
    {
        if(m_scale == 0)
        {
          if(isAction)
          {
             _normalImage->runAction(ScaleTo::create(0.1,1));
          }
          else
          {
              _normalImage->setScale(1);
          }
        }
        else
        {
           if(isAction)
           {
                _normalImage->runAction(ScaleTo::create(0.1,1));
           }
           else
           {
              _normalImage->setScale(1);
           }
        }
    }
    if(_normalImage)
    {
        _normalImage->setVisible(false);
    }
    if(_disabledImage)
    {
        _disabledImage->setVisible(false);
    }
    
}
void Button::selected()
{
    
    if(m_state == STATE_PARTDISABLED || m_state == STATE_SELECTED)
    {
        return;
    }
    if(_selectedImage)
    {
        hideAll();
         _selectedImage->setVisible(true);
    }
    else if(_normalImage)
    {
        //外部未缩放
        if(m_scale == 0)
        {
            this->_normalImage->runAction(ScaleTo::create(0.1,m_selectedScale));
        }
        else
        {//外部已经缩放
           _normalImage->runAction(ScaleTo::create(0.1,m_selectedScale));
        }
    }
    m_state = STATE_SELECTED;
   
}
void Button::unselected()
{
    if(m_state == STATE_PARTDISABLED || m_state == STATE_UNSELECTED)
    {
        return;
    }
   
    hideAll();
    if(_normalImage)
    {
        this->_normalImage->setVisible(true);
    }
    
    m_state =STATE_UNSELECTED;
}
void Button::setPartEnabled(bool bEnabled)
{
    if(bEnabled)
    {
        m_state = STATE_NONE;
        this->unselected();
        return;
    }
    else
    {
        if(m_state == STATE_PARTDISABLED)
        {
            return;
        }
    }
    m_state = STATE_PARTDISABLED;
    hideAll();
    if(!_disabledImage)
    {
        _disabledImage = GraySprite::create(imagePath.c_str());
        _disabledImage->setAnchorPoint(this->_normalImage->getAnchorPoint());
        this->addChild(_disabledImage,0);
          _disabledImage->setCascadeOpacityEnabled(true);
    }
    if(_disabledImage)
    {
        _disabledImage->setVisible(true);
    }
    
}
void Button::disableTouchEvent()//取消点击事件
{
    m_touchEventIsEnabled = false;
}
void Button::enableTouchEvent()//响应点击事件
{
    m_touchEventIsEnabled = true;
}
void Button::setEnabled(bool bEnabled,bool isGray)
{
    if(bEnabled)
    {
        m_state = STATE_NONE;
        this->unselected();
        return;
      
    }
    else
    {
        if(m_state == STATE_DISABLED)
        {
            return;
        }
    }
    m_state = STATE_DISABLED;
    hideAll();
    if(!_disabledImage && isGray)
    {
        _disabledImage = GraySprite::create(imagePath.c_str());
        _disabledImage->setAnchorPoint(this->_normalImage->getAnchorPoint());
        this->addChild(_disabledImage,0);
        _disabledImage->setCascadeOpacityEnabled(true);
    }
    if(_disabledImage)
    {
        _disabledImage->setVisible(true);
    }
    
}