//
//  CdkeyActivity.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/19.
//
//

#include "CdkeyActivity.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../message/Decoding/cdkeyMsg/CdkeyMsg.h"
#include "../../market/marketData/MarketFindResultDataManager.h"
#include "../../market/marketJuxian/MarketGoodsLayer.h"
#include "../../awardBox/AwardBox_Layer.h"
CdkeyActivity::CdkeyActivity()
:editbox(NULL)
,sx(1)
{
}

CdkeyActivity::~CdkeyActivity()
{
    
}


bool CdkeyActivity::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->setBackground(IMG_DIALOG_BG1);
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->isAnimation = true;
        this->setGrayBg();
        this->setClickEnabled(true);
        this->isClickClose=true;
        
        bref = true;
    } while (false);
    return bref;
}

CdkeyActivity* CdkeyActivity::create()
{
    CdkeyActivity* list = new CdkeyActivity();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}

void CdkeyActivity::onEnter()
{
    BaseLayer::onEnter();
}
void CdkeyActivity::onExit()
{
    BaseLayer::onExit();
}
void CdkeyActivity::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->createLayer();
}
void CdkeyActivity::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();

}
void CdkeyActivity::createLayer()
{
    Sprite* title=Sprite::create(IMG_PUBLIC_LABEL_EXCHANGEGIFT);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition((this->getContentSize().width-title->getContentSize().width)/2, this->getContentSize().height-title->getContentSize().height-20*sx);
    this->addChild(title,1);
    
    Sprite* cdkey=Sprite::create(IMG_PUBLIC_LABEL_CDKEY);
    cdkey->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cdkey);
    cdkey->setPosition(10*sx,(this->getContentSize().height-cdkey->getContentSize().height)/2+10*sx);
    this->addChild(cdkey,1);
    
    Sprite* inputBg=Sprite::create(IMG_PUBLIC_LAYER_CDKEY_INPUTBG);
//    inputBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(inputBg);
    inputBg->setPosition(cdkey->getPositionX()+cdkey->getContentSize().width +5*sx, (this->getContentSize().height-inputBg->getContentSize().height)/2+10*sx);
//    this->addChild(inputBg,1);
    
    //输入框
    string str = "";
    editbox = EditBox::create(inputBg->getContentSize(), Scale9Sprite::create(IMG_PUBLIC_LAYER_CDKEY_INPUTBG));
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setMaxLength(100);
    editbox->setText(str.c_str());
    editbox->setDelegate(this);
    editbox->setInputMode(EditBox::InputMode::ANY);
    editbox->setPosition(Point(inputBg->getPositionX(),inputBg->getPositionY()));
    this->addChild(editbox,1);
    
    //一键装备
    Button* exchange = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,"", CC_CALLBACK_1(CdkeyActivity::onBtnClick, this));
    exchange->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(exchange);
    exchange->setPosition((this->getContentSize().width-exchange->getContentSize().width)/2,40*sx);
    this->addChild(exchange,2);
    
    Sprite* exchangeLabel=Sprite::create(IMG_PUBLIC_LABEL_EXCHANGE);
    exchangeLabel->setAnchorPoint(Point::ZERO);
    exchangeLabel->setPosition((exchange->getContentSize().width/sx-exchangeLabel->getContentSize().width)/2,(exchange->getContentSize().height/sx-exchangeLabel->getContentSize().height)/2);
    exchange->addChild(exchangeLabel,2);

}
void CdkeyActivity::onBtnClick(Ref* pSender)
{
    this->editBoxEditingDidEnd(editbox);
    this->editBoxReturn(editbox);
    
    string str = editbox->getText();
    this->requestMsg(str);
    
}
/************************************************服务器***************************************************/
void CdkeyActivity::requestMsg(string str)//
{
    CdkeyMsg* msg = new CdkeyMsg(str);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void CdkeyActivity::onChageNameMsgProcess(EventCustom* msg)//获取成功返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_CDKEY_CdkeyEnterResp)
    {
        if(message->state)//返回成功
        {
            Vector<BaseTypeData*> *m_baseList=new  Vector<BaseTypeData*>();
            int len=message->byteStream->getByte();
            for (int i=0; i<len; i++) {
                BaseTypeData* data  = new BaseTypeData();
                data->autorelease();
                data->dataType=message->byteStream->getByte();
                
                data->dataId=message->byteStream->getInt();
                data->dataCount=message->byteStream->getByte();
                data->dataQuality=message->byteStream->getByte();
                data->dataName=message->byteStream->getUTF8();
                m_baseList->pushBack(data);
            }
//            AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
//            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
//            Scene* scene=Director::getInstance()->getRunningScene();
//            scene->addChild(layer,100);
            
            string str="恭喜您兑换成功,奖励已发送至邮箱,请及时领取！";
            NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
            this->removeFromParent();
        }
    }
}
void CdkeyActivity::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_CDKEY_CdkeyEnterResp).c_str(), CC_CALLBACK_1(CdkeyActivity::onChageNameMsgProcess, this));
}
void CdkeyActivity::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void CdkeyActivity::editBoxEditingDidBegin(EditBox* editBox)
{
    
}
void CdkeyActivity::editBoxEditingDidEnd(EditBox* editBox)
{
    log("editBoxEditingDidEnd");
}
void CdkeyActivity::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}
void CdkeyActivity::editBoxReturn(EditBox* editBox)
{
    log("editBoxReturn");
}
