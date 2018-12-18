//
//  PopUpLayer.cpp
//  SuiTang
//
//  Created by mac on 14-6-26.
//
//

#include "PopUpLayer.h"
//#include "../TouchSprite/Button.h"
PopUpLayer::PopUpLayer()
:m_callbackListener(NULL)
,m_callback(NULL)
,menu(NULL)
,isAutoClose(true)
,TAG_LABEL(3)
{
    
}
PopUpLayer::~PopUpLayer()
{
    CC_SAFE_RELEASE(m_callbackListener);
    m_callback = NULL;
}
bool PopUpLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
       this->setBackground(IMG_DIALOG_BG1,Point::ZERO,true);
        
        this->setClickEnabled(true);
        
        menu = Menu::create();
        menu->setAnchorPoint(Point::ZERO);
        this->addChild(menu,1);

        
        bref = true;
    } while (false);
    return bref;
}
void PopUpLayer::setCallBack(Ref* listener,SEL_CallFuncN callBack)
{
    CC_SAFE_RELEASE(this->m_callbackListener);
    this->m_callbackListener = listener;
    CC_SAFE_RETAIN(this->m_callbackListener);
    
    this->m_callback = callBack;
}

void PopUpLayer::addButton(const char* path,int tag,const char* btnBg)
{
    
    MenuItemImage* button = MenuItemImage::create(btnBg, "",CC_CALLBACK_1(PopUpLayer::onMenuClick, this));
    button->setTag(tag);
    ssize_t num = this->menu->getChildrenCount();
    button->setPositionX(num * (button->getContentSize().width + 150));
    
    Sprite* label = Sprite::create(path);
    label->setAnchorPoint(Point::ZERO);
    label->setPositionX((button->getContentSize().width - label->getContentSize().width)/2);
    label->setPositionY((button->getContentSize().height - label->getContentSize().height)/2);
    button->addChild(label,1);
    
    Size size = button->getContentSize();
    size.width = button->getPositionX() + button->getContentSize().width;
    menu->setContentSize(size);
     PublicShowUI::setTargetScale(menu);
    menu->setPositionX((this->getContentSize().width - menu->getContentSize().width)/2 + button->getContentSize().width * GlobalInfo::getInstance()->screenScaleX/2);
    menu->setPositionY(45 * GlobalInfo::getInstance()->screenScaleX);
    this->menu->addChild(button);
   
   
}
void PopUpLayer::setContent(const char* msg)
{
    Label* label = (Label*)this->getChildByTag(TAG_LABEL);
    if(label)
    {
        label->removeFromParent();
    }
 
    label = PublicShowUI::getLabel(msg,PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),18,false,true);
    label->setAnchorPoint(Point::ZERO);
    float _height = label->getContentSize().height;
    float _width = this->getContentSize().width - 70 * GlobalInfo::getInstance()->screenScaleX;
    int row = ceil(label->getContentSize().width / _width);
    if(label->getContentSize().width > _width)
    {
        label->setLineBreakWithoutSpace(true);
        label->setDimensions(_width, row * _height);
        label->setContentSize(Size(_width,row * _height));
    }
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    
    
    label->setPositionX((this->getContentSize().width - label->getContentSize().width)/2);
    label->setPositionY((this->getContentSize().height - label->getContentSize().height)/2);
    
    this->addChild(label,3,TAG_LABEL);
}

void PopUpLayer::setTitle(const char* msg)
{
    if(strcmp(msg, "") == 0)
    {
        msg = "提示";
    }
    Label* label = PublicShowUI::getLabel(msg,PublicShowUI::getColor3b(0Xe07434),24,false,true);
    label->setAnchorPoint(Point::ZERO);
    float _width = this->getContentSize().width - 30 * GlobalInfo::getInstance()->screenScaleX;
    label->setMaxLineWidth(_width);
    label->setPositionX((this->getContentSize().width - label->getContentSize().width)/2);
    label->setPositionY(this->getContentSize().height - label->getContentSize().height - 10 * GlobalInfo::getInstance()->screenScaleX);
    
    this->addChild(label);
}
void PopUpLayer::onMenuClick(Ref* pSender)
{
    MenuItemLabel* label = (MenuItemLabel*)pSender;
    
    if(this->m_callbackListener && m_callback)
    {
        (m_callbackListener->*m_callback)(label);
    }
    if(isAutoClose)
    {
         close();
    }
   
    
}
bool PopUpLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void PopUpLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
}
void PopUpLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    
    Rect rect = this->getBoundingBox();
    if(rect.containsPoint(touch->getLocation()) == false)
    {
        if(this->menu->getChildrenCount() <= 1 && this->m_callbackListener == NULL && m_callback == NULL)
        {//如果有1个以上按钮则必须选择功能
            close();
        }
        
    }
}
void PopUpLayer::onEnter()
{
    BaseLayer::onEnter();
}
void PopUpLayer::onExit()
{
    BaseLayer::onExit();
}
void PopUpLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void PopUpLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void PopUpLayer::close()
{
    if(this->getParent())
    {
        this->removeFromParent();
    }
}