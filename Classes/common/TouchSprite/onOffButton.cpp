//
//  onOffButton.cpp
//  SuiTang
//
//  Created by 超 顾 on 15/4/16.
//
//

#include "onOffButton.h"
#include "../../common/PublicShowUI.h"
onOffButton::onOffButton()
:btnBg(NULL)
,btnOn(NULL)
,btnOff(NULL)
,btnBol(true)
,touchListener(NULL)
{
    
}
onOffButton::~onOffButton()
{
    if(touchListener)
    {
        _eventDispatcher->removeEventListener(touchListener);
    }
    CC_SAFE_RELEASE_NULL(touchListener);
    btnBg=NULL;
    btnOn=NULL;
    btnOff=NULL;
    btnBol=NULL;
}
void onOffButton::onEnter()
{
    Node::onEnter();
    _eventDispatcher->removeEventListener(touchListener);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void onOffButton::onExit()
{
    Node::onExit();
}
onOffButton* onOffButton::create(const std::string&buttonBg, const std::string&buttonOn,const std::string&buttonOff, const ccMenuCallback& callback,const std::string&buttonOnBG)
{
    onOffButton* button=new onOffButton();
    if (button && button->init(buttonBg,buttonOn,buttonOff,callback,buttonOnBG)) {
        button->autorelease();
        return button;
    }
    return NULL;
}
bool onOffButton::init(const std::string&buttonBg, const std::string&buttonOn,const std::string&buttonOff, const ccMenuCallback& callback,const std::string&buttonOnBG)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        this->setAnchorPoint(Point::ZERO);
        btnBg=Sprite::create(buttonBg);
        if(!btnBg)
        {
            btnBg = Sprite::createWithSpriteFrameName(buttonBg);
        }
        btnBg->setAnchorPoint(Point::ZERO);
        this->setContentSize(btnBg->getContentSize());
        this->addChild(btnBg);
        this->m_callBack=callback;
        
        touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(touchListener);
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(onOffButton::ccTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(onOffButton::ccTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(onOffButton::ccTouchEnded, this);
        this->setOnBtn(buttonOn,buttonOnBG);
        this->setOffBtn(buttonOff);
        bref=true;
    } while (false);
    return bref;
}
void onOffButton::setOnBtn(const std::string&buttonOn,const std::string&buttonOnBG)
{
    btnOn=Sprite::create(buttonOn);
    if(!btnOn)
    {
        btnOn = Sprite::createWithSpriteFrameName(buttonOn);
    }
    btnOn->setAnchorPoint(Point::ZERO);
    btnOn->setPosition(-1,-2);
    btnBg->addChild(btnOn);
    if (buttonOnBG != "") {
        Sprite* btnonbg = Sprite::create(buttonOnBG);
        if (!btnonbg) {
            btnonbg = Sprite::createWithSpriteFrameName(buttonOnBG);
        }
        btnonbg->setAnchorPoint(Point::ZERO);
        btnonbg->setPosition(btnOn->getContentSize().width-btnonbg->getContentSize().width+7,-5);
        btnOn->addChild(btnonbg);
    }
    
}
void onOffButton::setOffBtn(const std::string&buttonOff)
{
    btnOff=Sprite::create(buttonOff);
    if(!btnOff)
    {
        btnOff = Sprite::createWithSpriteFrameName(buttonOff);
    }
    btnOff->setAnchorPoint(Point::ZERO);
    btnOff->setPosition(-4,-5);
//    btnOff->setVisible(false);
    btnBg->addChild(btnOff);
}
void onOffButton::setOnButton(bool bol)
{
    if (btnOff and btnOn) {
        if (bol) {
            btnOff->setVisible(false);
            btnOn->setVisible(true);
        }
        else
        {
            btnOff->setVisible(true);
            btnOn->setVisible(false);
        }
    }
}
bool onOffButton::isClickSprite(cocos2d::Touch* pTouch)
{
    
   
    Point touchLocation = pTouch->getLocation();
    Point local = this->convertToNodeSpace(touchLocation);
    Rect r = PublicShowUI::getRect(this);
    r.origin = Point::ZERO;
    if (r.containsPoint(local))
    {
        return true;
    }
   
    return false;
    
}
bool onOffButton::ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    return isClickSprite(pTouch);
 
}
void onOffButton::ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    
    
}
void onOffButton::ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
//    this->m_callBack(this);
    if(!isClickSprite(pTouch))
    {
        return;
    }
    if (btnBol) {
        btnBol=false;
        btnOff->setVisible(true);
        btnOn->setVisible(false);
    }
    else
    {
        btnBol=true;
        btnOff->setVisible(false);
        btnOn->setVisible(true);
    }
    this->m_callBack(this);
}

