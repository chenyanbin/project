//
//  RandomNameLayer.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/15.
//
//

#include "RandomNameLayer.hpp"
#include "../../common/customButton/CustomButton.hpp"
#include "../../message/Decoding/setup/RequestSetupMsg.h"
#include "../../message/Decoding/setup/RequestRandName.hpp"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../login/LoginLayer.h"
RandomNameLayer::RandomNameLayer()
:TAG_LABELBG(1)
,editbox(NULL)
{
    
}
RandomNameLayer::~RandomNameLayer()
{
    
}
bool RandomNameLayer::init()
{
//    this->isShowGrayBg = true;
 
//    this->setBackground(IMG_DIALOG_BG1,Point::ZERO,false);
//    setHalfBody();
    setNameLabel();
    setDiceBtn();
    setConfirmBtn();
    return true;
}
void RandomNameLayer::setHalfBody()
{
    const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, "guanyinping");
    Sprite* spr = Sprite::create(path);
    spr->setScale(.8);
    spr->setPosition(0, this->getContentSize().height/2);
    this->addChild(spr,1);
}
void RandomNameLayer::setNameLabel()
{
    Sprite* nameBg = Sprite::create(IMG_CREATEROLE_NAMEBG);
    Size size = nameBg->getContentSize();
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(0,0);
    this->addChild(nameBg,2,TAG_LABELBG);
    this->setContentSize(nameBg->getContentSize());
    
    
    //输入框
    Size labelSize = size ;
    string nameStr = GlobalInfo::getInstance()->gameRole->name;
    editbox = EditBox::create(labelSize, Scale9Sprite::create());
    editbox->setAnchorPoint(Point(.5,.5));
    editbox->setMaxLength(18);
    editbox->setFontSize(20);
    editbox->setText(nameStr.c_str());
    editbox->setDelegate(this);
    editbox->setInputMode(EditBox::InputMode::ANY);
    editbox->setPosition(Point(size.width/2,size.height/2));
//    editbox->setPosition((size.width - labelSize.width)/2,(size.height - labelSize.height)/2);
    nameBg->addChild(editbox,10);
    
}
void RandomNameLayer::setDiceBtn()
{
    Node* nameBg = this->getChildByTag(TAG_LABELBG);
    CustomButton* dictBtn = CustomButton::create(IMG_CREATEROLE_DICE, "", CC_CALLBACK_1(RandomNameLayer::onDiceBtnClick, this));
    dictBtn->setAnchorPoint(Point(.5,0));
    dictBtn->setPosition(nameBg->getContentSize().width + dictBtn->getContentSize().width/2, (nameBg->getContentSize().height - dictBtn->getContentSize().height)/2 + 10);
    nameBg->addChild(dictBtn,3);
    
    PublicShowUI::setTargetSwing(dictBtn);

}
void RandomNameLayer::setConfirmBtn()
{
    Node* namebg = this->getChildByTag(TAG_LABELBG);
    CustomButton* btn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(RandomNameLayer::onConfirmNameMsg, this));
    btn->setPosition((namebg->getContentSize().width - btn->getContentSize().width)/2, -btn->getContentSize().height/2 - 10);
    
    btn->addTitle(IMG_BUTTON_CONFIRM_LABEL,IMG_BUTTON_CONFIRM_LABEL);
    this->addChild(btn,5);
}
void RandomNameLayer::onDiceBtnClick(Ref* pSender)
{
    Dialog::showServerLoading(1);
    int sex = PublicShowUI::genRandom(1, 2);
    RequestRandName* msg = new RequestRandName(sex);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void RandomNameLayer::onConfirmNameMsg(Ref* pSender)
{
    const char* _name = editbox->getText();
    Dialog::showServerLoading(.5);
    RequestSetupMsg* msg = new RequestSetupMsg(_name);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void RandomNameLayer::onEnter()
{
    BaseLayer::onEnter();
}
void RandomNameLayer::onExit()
{
    BaseLayer::onExit();
}
void RandomNameLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void RandomNameLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    onDiceBtnClick(NULL);
    
     Node* nameBg = this->getChildByTag(TAG_LABELBG);
  
    Sprite* textSpr = Sprite::create(IMG_CREATEROLE_TEXT);
    textSpr->setAnchorPoint(Point(.5,0));
    this->addChild(textSpr,3);
    textSpr->setPosition((nameBg->getContentSize().width)/2 - 80, nameBg->getPositionY() + nameBg->getContentSize().height + 15);
    textSpr->setScale(5);
    ScaleTo* scaleTo = ScaleTo::create(.5, 1);
    textSpr->runAction(scaleTo);
    
}
void RandomNameLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_SetRolenameResp).c_str(), CC_CALLBACK_1(RandomNameLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ACCOUNT_RandomRoleNameResp).c_str(), CC_CALLBACK_1(RandomNameLayer::onMsgProcess, this));
}
void RandomNameLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void RandomNameLayer::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void RandomNameLayer::editBoxEditingDidEnd(EditBox* editBox)
{
    log("editBoxEditingDidEnd");
}
void RandomNameLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}
void RandomNameLayer::editBoxReturn(EditBox* editBox)
{
  
}

void RandomNameLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(msg->messageID == SCENSE_CLIENT_ACCOUNT_SetRolenameResp)
    {
        if(msg->state)//返回成功
        {
            GlobalInfo::getInstance()->gameRole->name = editbox->getText();
      
            
            LoginLayer::enterMainUI();
            
            
        }
    }
    else if(msg->messageID == SCENSE_CLIENT_ACCOUNT_RandomRoleNameResp)
    {
        if(msg->state)
        {
            string initName = msg->byteStream->getUTF8();
            initName = initName != "" ? initName : "金永哲";
            this->editbox->setText(initName.c_str());
        }
    }

}
