//
//  CustomButton.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/5.
//
//

#include "CustomButton.hpp"
CustomButton::CustomButton()
:_normalTitle(NULL)
,_selectedTitle(NULL)
,_disabledTitle(NULL)
,_titlePath("")
{
    
}
CustomButton::~CustomButton()
{
    _normalTitle = NULL;
    _selectedTitle = NULL;
    _disabledTitle = NULL;
    _titlePath.clear();
}
bool CustomButton::init(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback)
{
    return Button::init(normalImage, selectedImage, callback);
}
/** creates a menu item with a normal and selected image with a callable object */
CustomButton* CustomButton::create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback)
{
    CustomButton* btn = new CustomButton();
    if(btn && btn->init(normalImage, selectedImage, callback))
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return NULL;
}
void CustomButton::addTitle(const std::string& normalTitle,const std::string& selectedTitle)
{
    setNormalTitle(normalTitle);
    setSelectedTitle(selectedTitle);
}
void CustomButton::setNormalTitle(const std::string& normalImage )
{
    if(this->_normalTitle)
    {
        _normalTitle->removeFromParent();
    }
    //
    _titlePath = normalImage;
    this->_normalTitle = Sprite::create(normalImage);
    if(!_normalTitle)
    {
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage);
        if(frame)
        {
            _normalTitle = Sprite::createWithSpriteFrameName(normalImage);
        }
        else
        {
            return;
        }
    }
    Point anchorPoint = this->_normalImage->getAnchorPoint();
    if(anchorPoint.x == .5)
    {
         _normalTitle->setPositionX(0);
    }
    else
    {
         _normalTitle->setPositionX(this->_normalImage->getContentSize().width / 2 );
    }
    if(anchorPoint.y == .5)
    {
        _normalTitle->setPositionY(0);
    }
    else
    {
        _normalTitle->setPositionY(this->_normalImage->getContentSize().height / 2 );
    }
   
    this->addChild(_normalTitle,5);
    _normalTitle->setVisible(this->_normalImage->isVisible());

}
void CustomButton::setSelectedTitle(const std::string& selectedTitle )
{
    if(!_selectedImage)
    {
        return;
    }
    if(_selectedTitle)
    {
        _selectedTitle->removeFromParent();
    }
    if(selectedTitle != "")
    {
        this->_selectedTitle = Sprite::create(selectedTitle);
        if(!_selectedImage)
        {
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(selectedTitle);
            if(frame)
            {
                _selectedTitle = Sprite::createWithSpriteFrameName(selectedTitle);
            }
            else
            {
                return;
            }
            
        }
        _selectedTitle->setPositionX(this->_selectedImage->getContentSize().width / 2);
        _selectedTitle->setPositionY(this->_selectedImage->getContentSize().height / 2);
        _selectedTitle->setVisible(_selectedImage->isVisible());
        this->addChild(_selectedTitle,6);
    }

}
void CustomButton::hideTitles()
{
    if(_selectedTitle)
    {
        _selectedTitle->setVisible(false);
    }
    if(_selectedTitle)
    {
        _selectedTitle->setVisible(false);
    }
    if(_disabledTitle)
    {
        _disabledTitle->setVisible(false);
    }
}

void CustomButton::selected()
{
    Button::selected();
    if(_selectedTitle)
    {
        hideTitles();
        _selectedTitle->setVisible(true);
    }

}
void CustomButton::unselected()
{
    Button::unselected();
    
    if(_normalTitle)
    {
        hideTitles();
        this->_normalTitle->setVisible(true);
    }
}
void CustomButton::setEnabled(bool bEnabled,bool isGray )
{
    Button::setEnabled(bEnabled, isGray);
    hideTitles();
    if(!_disabledTitle && isGray)
    {
        _disabledTitle = GraySprite::create(_titlePath.c_str());
        if(_selectedTitle)
        {
             _disabledTitle->setAnchorPoint(this->_selectedTitle->getAnchorPoint());
             _disabledTitle->setPosition(_selectedTitle->getPosition());
        }
       else
       {
            _disabledTitle->setAnchorPoint(this->_normalTitle->getAnchorPoint());
            _disabledTitle->setPosition(_normalTitle->getPosition());
       }
       
        this->addChild(_disabledTitle,7);
    }
    if(_disabledTitle)
    {
        _disabledTitle->setVisible(true);
    }

}
void CustomButton::setPartEnabled(bool bEnabled)
{
    Button::setPartEnabled(bEnabled);
    
    hideTitles();
    if(!_disabledTitle)
    {
        _disabledTitle = GraySprite::create(_titlePath.c_str());
        _disabledTitle->setAnchorPoint(this->_selectedTitle->getAnchorPoint());
        this->addChild(_disabledTitle,7);
         _disabledTitle->setPosition(_selectedTitle->getPosition());
    }
    if(_disabledTitle)
    {
        _disabledTitle->setVisible(true);
    }

}
void CustomButton::setOpacity(float opacity)
{
    Button::setOpacity(opacity);
    
    if(_normalTitle)
    {
        this->_normalTitle->setOpacity(opacity);
    }
    if(_selectedTitle)
    {
        this->_selectedTitle->setOpacity(opacity);
    }
    if(_disabledTitle)
    {
        _disabledTitle->setOpacity(opacity);
    }
}


bool CustomButton::ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    return Button::ccTouchBegan(pTouch, pEvent);
}
void CustomButton::ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    Button::ccTouchMoved(pTouch, pEvent);
}
void CustomButton::ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    Button::ccTouchEnded(pTouch, pEvent);
}
void CustomButton::ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    Button::ccTouchCancelled(pTouch, pEvent);
}


void CustomButton::onEnter()
{
    Button::onEnter();
}
void CustomButton::onExit()
{
     Button::onExit();
}
void CustomButton::onExitTransitionDidStart()
{
     Button::onExitTransitionDidStart();
}
void CustomButton::onEnterTransitionDidFinish()
{
     Button::onEnterTransitionDidFinish();
}