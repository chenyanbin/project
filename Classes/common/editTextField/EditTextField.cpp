//
//  EditTextField.cpp
//  Test
//
//  Created by zhangxiaobin on 14/10/31.
//
//

#include "EditTextField.h"
EditTextField::EditTextField()
:m_contentLabel(NULL)
,TAG_EDITBOX(1)
,isEnableInput(true)
,m_color(Color3B::WHITE)
,maxLength(0)
,m_delegate(NULL)
{
    
}
EditTextField::~EditTextField()
{
    m_contentLabel = NULL;
    _eventDispatcher->removeEventListenersForTarget(this);
    m_delegate = NULL;
}
bool EditTextField::init(const Size& size,int fontSize)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        
        this->m_contentLabel = Label::create();
        this->setString("点击输入文本");
  
        m_contentLabel->setSystemFontSize(fontSize);
     
        this->m_contentLabel->setAnchorPoint(Point::ZERO);
        this->addChild(m_contentLabel,0);
        m_contentLabel->setDimensions(size.width, size.height);
        this->setContentSize(size);
        
        
       
        
        EventListenerTouchOneByOne* m_eventDispatcher = EventListenerTouchOneByOne::create();
        m_eventDispatcher->onTouchBegan = CC_CALLBACK_2(EditTextField::onTouchBegan, this);
        m_eventDispatcher->onTouchMoved = CC_CALLBACK_2(EditTextField::onTouchMoved, this);
        m_eventDispatcher->onTouchEnded = CC_CALLBACK_2(EditTextField::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventDispatcher, this);
        _eventDispatcher->setPriority(m_eventDispatcher, 0);
        
        bref = true;
    } while (false);
    return bref;
}
void EditTextField::setEditBox()
{
    EditBox* editBox = (EditBox*)this->getChildByTag(TAG_EDITBOX);
    if(!editBox)
    {
        Size size = Director::getInstance()->getWinSize();
        size.height = m_contentLabel->getSystemFontSize() * 1.5 * this->getScale();
        editBox = EditBox::create(size, Scale9Sprite::create());
        editBox->setAnchorPoint(Point::ZERO);
        editBox->setDelegate(this);
        editBox->setPositionY(this->getContentSize().height - size.height);
        this->addChild(editBox,1,TAG_EDITBOX);
        editBox->setVisible(false);
        editBox->setColor(this->m_color);
        
        this->m_contentLabel->setColor(m_color);
        if(this->maxLength > 0)
        {
            setMaxLength(this->maxLength);
        }
    }
    editBox->setText(this->m_contentLabel->getString().c_str());
    editBox->sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);
}
void EditTextField::setDelegate(EditBoxDelegate* delegate)
{
    this->m_delegate = delegate;
}
void EditTextField::setMaxLength(int value)
{
    maxLength = value;
    EditBox* editBox = (EditBox*)this->getChildByTag(TAG_EDITBOX);
    if(editBox)
    {
        editBox->setMaxLength(value);
    }
}
void EditTextField::setContentLabel()
{
    EditBox* editBox = (EditBox*)this->getChildByTag(TAG_EDITBOX);
    if(editBox)
    {
        this->setString(editBox->getText());
        this->m_contentLabel->setVisible(true);
    }
     this->m_contentLabel->setColor(m_color);

}
const std::string& EditTextField::getText()
{
    return this->m_contentLabel->getString();
}
EditTextField* EditTextField::create(const Size& size,int fontSize)
{
    EditTextField* textField = new EditTextField();
    if(textField && textField->init(size,fontSize))
    {
        textField->autorelease();
        return textField;
    }
    CC_SAFE_DELETE(textField);
    textField = NULL;
    return NULL;
}
void EditTextField::setString(const std::string& text)
{
    this->m_contentLabel->setString(text);
}
bool EditTextField::isTouchInside(Touch* touch)
{
    Point touchLocation = touch->getLocation(); // Get the touch position
    touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
    Rect bBox = getBoundingBox();
    return bBox.containsPoint(touchLocation);
}
void EditTextField::setColor(Color3B color)
{
    this->m_color = color;
     EditBox* editBox = (EditBox*)this->getChildByTag(TAG_EDITBOX);
    if(editBox)
    {
        editBox->setColor(this->m_color);
    }
    this->m_contentLabel->setColor(this->m_color);
}
bool EditTextField::onTouchBegan(Touch *touch, Event *unused_event)
{
    return isEnableInput;
}
void EditTextField::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void EditTextField::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(isTouchInside(touch) && isEnableInput)
    {
         setEditBox();
        this->m_contentLabel->setVisible(false);
    }
}

void EditTextField::editBoxEditingDidBegin(EditBox* editBox)
{
    if(m_delegate)
    {
        m_delegate->editBoxEditingDidBegin(editBox);
    }
}
void EditTextField::editBoxEditingDidEnd(EditBox* editBox)
{
    setContentLabel();
    if(m_delegate)
    {
        m_delegate->editBoxEditingDidEnd(editBox);
    }
}
void EditTextField::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    if(m_delegate)
    {
        m_delegate->editBoxTextChanged(editBox,text);
    }
}
void EditTextField::editBoxReturn(EditBox* editBox)
{
    setContentLabel();
    if(m_delegate)
    {
        m_delegate->editBoxReturn(editBox);
    }
}