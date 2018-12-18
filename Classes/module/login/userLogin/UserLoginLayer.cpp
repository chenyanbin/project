//
//  UserLoginLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/13.
//
//

#include "UserLoginLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../commonData/GlobalInfo.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../LoginLayer.h"
UserLoginLayer::UserLoginLayer()
:m_uid("")
{
    
}
UserLoginLayer::~UserLoginLayer()
{
    m_uid.clear();
}
void UserLoginLayer::show()
{
     Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_INPUT_UESRNAME))
    {
        return;
    }
    UserLoginLayer* layer = UserLoginLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2,VisibleRect::center().y - layer->getContentSize().height/2);
   
    scene->addChild(layer,SCENE_LAYER_ZORDER,LAYER_INPUT_UESRNAME);
}
bool UserLoginLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(IMG_LOADING_INPUTBG);
        this->isShowGrayBg = false;
        this->isClickClose =false;
        this->isAbleGuiding = false;
        this->isAnimation = false;
        setLoginBtn();
        setUserNameInput();
        
        bref = true;
    } while (false);
    return bref;
}
void UserLoginLayer::setUserNameInput()
{
    string platformID = GlobalInfo::getInstance()->uid;
    float sx = GlobalInfo::getInstance()->screenScaleX;
    EditBox* editbox = EditBox::create(Size(270 * sx,50 * sx), Scale9Sprite::create());
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setText(platformID.c_str());
    editbox->setDelegate(this);
    editbox->setPositionX((this->getContentSize().width - editbox->getContentSize().width)/2 + 25 * sx);
    editbox->setPositionY(this->getContentSize().height - editbox->getContentSize().height - 50 * sx);
    this->addChild(editbox,1);
}
void UserLoginLayer::setLoginBtn()
{
    
    Button* touristBtn = Button::create(IMG_LOADING_TOURSISTBTN, "", CC_CALLBACK_1(UserLoginLayer::onTouristClick, this));
    PublicShowUI::setTargetScale(touristBtn);
    touristBtn->setPosition((this->getContentSize().width)/2,60 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(touristBtn,4);
    
    
    Button* btn = Button::create(IMG_LOADING_LOGINBTN, "", CC_CALLBACK_1(UserLoginLayer::onLoginClick, this));
    PublicShowUI::setTargetScale(btn);
    btn->setPosition((this->getContentSize().width)/2, touristBtn->getPositionY() + touristBtn->getContentSize().height + 15 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(btn,3);
    
    
}
void UserLoginLayer::onTouristClick(Ref* pSender)
{
    if(GlobalInfo::getInstance()->deviceUUID == "")
    {
        GlobalInfo::getInstance()->deviceUUID =  PublicShowUI::getUUID();
    }
    m_uid =  GlobalInfo::getInstance()->deviceUUID;
    onLoginClick(pSender);

}
void UserLoginLayer::onLoginClick(Ref* pSender)
{
    if(m_uid == "")
    {
        NoticeManager::getInstance()->showNotice("请输入用户名");
        return;
    }
    GlobalInfo::getInstance()->uid = m_uid;
    log("m_uid==%s",m_uid.c_str());
    broadMsg(CUSTOM_SDK_LOGINSUC);
    this->backScene();
}
void UserLoginLayer::onEnter()
{
    BaseLayer::onEnter();
   
}
void UserLoginLayer::onExit()
{
    BaseLayer::onExit();
}
void UserLoginLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void UserLoginLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void UserLoginLayer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void UserLoginLayer::editBoxEditingDidEnd(EditBox* editBox)
{
    m_uid = editBox->getText();
}
void UserLoginLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    m_uid = editBox->getText();
}
void UserLoginLayer::editBoxReturn(EditBox* editBox)
{
    m_uid = editBox->getText();
}