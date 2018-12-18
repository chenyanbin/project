//
//  ComboBoxBtn.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/30.
//
//

#include "ComboBoxBtn.h"
#include "../ImagePath.h"

ComboBoxBtn::ComboBoxBtn()
:btnList(NULL)
,m_distance(0)
,m_asideType(ASIDE::ASIDE_HORIZONTAL)
,TAG_REDPOINT(2)
,m_callBack(NULL)
,m_selectedBtn(NULL)
{
    btnList = new Vector<Button*>();

}
ComboBoxBtn::~ComboBoxBtn()
{
    btnList->clear();
    CC_SAFE_DELETE(btnList);
    btnList = NULL;
    m_callBack = NULL;
    m_selectedBtn = NULL;
}

ComboBoxBtn* ComboBoxBtn::create(ASIDE aside,float distance,const ccMenuCallback& callback, ALIGN align)
{
    
    ComboBoxBtn* btn = new ComboBoxBtn();
    if(btn && btn->init(aside,distance,callback, align))
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    btn = NULL;
    return btn;
   
}
bool ComboBoxBtn::init(ASIDE aside,float distance,const ccMenuCallback& callback , ALIGN align)
{
    this->m_asideType = aside;
    this->m_alignType=align;
    m_distance = distance;
    this->m_callBack = callback;
    return true;
}
void ComboBoxBtn::onBtnOutSide(Ref* pSender)
{
    if(pSender == m_selectedBtn)
    {
        m_selectedBtn->selected();
    }
}
CustomButton* ComboBoxBtn::addCustomBtn(const std::string&normalImage, const std::string&selectedImage,const string& normalTitleImage,const string& selectedTitleImage,bool isScale,int tag)
{
    CustomButton* btn = this->addBtn(normalImage,selectedImage,"",isScale,tag);
    if(normalTitleImage.size())
    {
        btn->setNormalTitle(normalTitleImage);
    }
    if(selectedTitleImage.size())
    {
        btn->setSelectedTitle(selectedTitleImage);
    }
   
    return btn;
}
CustomButton* ComboBoxBtn::addBtn(const std::string&normalImage, const std::string&selectedImage,const string& titleImage,bool isScale,int tag)
{
    CustomButton* btn = CustomButton::create(normalImage, selectedImage, CC_CALLBACK_1(ComboBoxBtn::onComBtnClick, this));
    if (isScale) {
        btn->setScale(0.8);
    }
    btn->setAnchorPoint(Point::ZERO);
    btn->onReleaseOutSide = CC_CALLBACK_1(ComboBoxBtn::onBtnOutSide, this);
    Size size = btn->getContentSize();
    if(titleImage != "")
    {
        Sprite* title = Sprite::create(titleImage);
        title->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
        btn->addChild(title,20);
    }
    
    int id = (int)btnList->size();

    switch (this->m_asideType) {
        case ASIDE::ASIDE_HORIZONTAL:
            btn->setPosition(this->getContentSize().width + m_distance, 0);
            size.width = btn->getPositionX() + btn->getContentSize().width;
       
            break;
        case ASIDE::ASIDE_VERTICAL:
            btn->setPosition(0,  this->getContentSize().height+ m_distance);
            size.height = btn->getPositionY() + btn->getContentSize().height;
            
        default:
            break;
    }
    
    switch (this->m_alignType) {
        case ALIGN::ALIGN_UP:
            if (this->btnList->size()>0) {
                btn->setPosition(btn->getPositionX(),this->getContentSize().height-btn->getContentSize().height);
                size.height=this->getContentSize().height;
            }
            break;
            
        default:
            break;
    }
    this->setContentSize(size);
    int nowTag = tag >= 0 ? tag : (int)id;
    this->addChild(btn,id,nowTag);
    this->btnList->pushBack(btn);
    return btn;
}
Button* ComboBoxBtn::getNowSelected()
{
    return this->m_selectedBtn;
}
void ComboBoxBtn::onComBtnClick(Ref* pSender)
{
    Button* btn = (Button*)pSender;
   if(!btn)
   {
       return;
   }
    if(!m_selectedBtn || (m_selectedBtn && btn->getTag() != m_selectedBtn->getTag()))
    {
        this->resetAllBtn();
        btn->selected();
        btn->setLocalZOrder(int(btnList->size()));
        m_selectedBtn = btn;
        if(this->m_callBack)
        {
            this->m_callBack(btn);
        }
    }
    else if(m_selectedBtn)
    {
        m_selectedBtn->selected();
    }
    
    
}
void ComboBoxBtn::resetAllBtn()
{
    for(Button* node : *btnList)
    {
        node->setLocalZOrder(node->getTag());
        node->unselected();
    }
    m_selectedBtn = NULL;
}
void ComboBoxBtn::addRedPointAt(int index)
{
    Button* btn = this->btnList->at(index);
    if(btn->getChildByTag(TAG_REDPOINT))
    {
        return;
    }
//    Sprite* msgFlag = Sprite::create(IMG_PUBLIC_MSGFLAG);
//    msgFlag->setAnchorPoint(Point::ZERO);
//    btn->addChild(msgFlag,21,TAG_REDPOINT);
//    msgFlag->setPositionX(btn->getContentSize().width - msgFlag->getContentSize().width);
//    msgFlag->setPositionY( btn->getContentSize().height - msgFlag->getContentSize().height/2);
}
void ComboBoxBtn::removePointAt(int index)
{
    Button* btn = this->btnList->at(index);
    if(btn->getChildByTag(TAG_REDPOINT))
    {
        btn->removeChildByTag(TAG_REDPOINT);
    }
}
Button* ComboBoxBtn::getButtonByTag(int tag)
{
    return (Button*)this->getChildByTag(tag);
}
Button* ComboBoxBtn::getButtonAt(int index)
{
    return this->btnList->at(index);
}
void ComboBoxBtn::selectedAt(int index)
{
    Button* btn = this->btnList->at(index);
    
    onComBtnClick(btn);
}
void ComboBoxBtn::selectAtByTag(int tag)
{
    Button* btn = this->getButtonByTag(tag);
    
    onComBtnClick(btn);
}