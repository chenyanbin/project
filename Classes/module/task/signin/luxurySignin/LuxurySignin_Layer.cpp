//
//  LuxurySignin_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/12.
//
//

#include "LuxurySignin_Layer.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../Signin_Scene.h"
#include "../../../../protocol/Protocal.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../message/Decoding/signin/SigninLuxuryGetMsg.h"
#include "../../../../message/Decoding/signin/SigninLuxuryMsg.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../tips/TipsLayer.h"
#include "../../../awardBox/AwardBox_Layer.h"
#include "../../../vip/VipLayer.h"
LuxurySignin_Layer::LuxurySignin_Layer()
:sx(1)
,m_day(0)
,m_status(0)
,TAG_PRIZE(3)
,TAG_RECHARGE(4)
{
    m_list=new vector<SigninData*>();
    m_baseList=new Vector<BaseTypeData*>();
}
LuxurySignin_Layer::~LuxurySignin_Layer()
{
    m_list->clear();
    CC_SAFE_DELETE(m_list);
//    m_baseList->clear();
//    CC_SAFE_DELETE(m_baseList);
}

void LuxurySignin_Layer::onExit()
{
    BaseLayer::onExit();
}
void LuxurySignin_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void LuxurySignin_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void LuxurySignin_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
}
bool LuxurySignin_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_SIGNIN_LUXURY_LABEL2);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
LuxurySignin_Layer* LuxurySignin_Layer::create()
{
    LuxurySignin_Layer* layer = new LuxurySignin_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void LuxurySignin_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    Sprite* person=Sprite::create(IMG_SIGNIN_LUXURY_PERSON);
    person->setAnchorPoint(Point::ZERO);
    person->setPosition(-14,-245);
    bg->addChild(person);
    
    Sprite* todayReward=Sprite::create(IMG_SIGNIN_LUXURY_TITLE);
    todayReward->setAnchorPoint(Point::ZERO);
    todayReward->setPosition(456,-4);
    bg->addChild(todayReward);
    
    Sprite* bottomLabel=Sprite::create(IMG_SIGNIN_LUXURY_LABEL);
    bottomLabel->setAnchorPoint(Point::ZERO);
    bottomLabel->setPosition(359,-237);
    bg->addChild(bottomLabel);
    
    
    const char* pathList[2] = {IMG_PUBLIC_LABEL_LUXURY,IMG_PUBLIC_LABEL_EVERYDAY};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 28, CC_CALLBACK_1(LuxurySignin_Layer::onComboBoxBtnClick, this));
    for (int i = 0; i<2; i++) {
        boxBtn->addBtn(IMG_PUBLIC_BUTTON_SIGNIN_GREEN, IMG_PUBLIC_BUTTON_SIGNIN_YELLOW, pathList[1-i]);
    }
    boxBtn->setPosition(240,116);
    boxBtn->getButtonAt(1)->selected();
    bg->addChild(boxBtn,3);
    Size size=bg->getContentSize();
    size.height=size.height+person->getPositionY()*sx;
    
    this->setContentSize(size);
}
void LuxurySignin_Layer::onCreateStatus()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    Button* getBtn=getBtn=Button::create(IMG_SIGNIN_LUXURY_BTN, IMG_SIGNIN_LUXURY_BTN, CC_CALLBACK_1(LuxurySignin_Layer::onBtnClick, this));
    getBtn->setAnchorPoint(Point::ZERO);
    getBtn->setPosition(738,-17);
    bg->addChild(getBtn);
    
    int _num=(int)m_list->size();
    for (int i=0; i<_num; i++) {
        const char* str=PublicShowUI::getGoods(m_list->at(i)->itemType, m_list->at(i)->itemId);
        UserEquipLayer* userHead=UserEquipLayer::create(str,m_list->at(i)->itemQuality,false);
        userHead->setPosition(450+i*185,-150);
        if (m_status==2) {
            Sprite* yetGet=Sprite::create(IMG_SIGNIN_BENEFIT_DAY_DRAWDOWN);
            yetGet->setAnchorPoint(Point::ZERO);
            yetGet->setPosition(40,0);
            userHead->addChild(yetGet,8);
            userHead->setGray();
        }
        userHead->addTouchBegainCallBack(this, callfuncN_selector(LuxurySignin_Layer::onUserTipsClick));
        userHead->setTag(i);
        bg->addChild(userHead);
    }
    
    Sprite* btnLabel=NULL;
    if (m_status==1) {
        btnLabel=Sprite::create(IMG_SIGNIN_LUXURY_PRIZE);
        getBtn->setTag(TAG_PRIZE);
        
    }else if (m_status==2)
    {
        btnLabel=GraySprite::create(IMG_SIGNIN_LUXURY_PRIZE);
        getBtn->setEnabled(false);
    }else if (m_status==3)
    {
        btnLabel=Sprite::create(IMG_SIGNIN_LUXURY_RECHARGE);
        getBtn->setTag(TAG_RECHARGE);
    }
    btnLabel->setAnchorPoint(Point::ZERO);
    btnLabel->setPosition(0,31);
    getBtn->addChild(btnLabel,2,1);
}
void LuxurySignin_Layer::onBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag==TAG_PRIZE) {
        
        this->requestListGetMsg();
        
    }else if (tag==TAG_RECHARGE)
    {
        VipLayer::show(SCENE_TAG_MAINUI);
    }
}
void LuxurySignin_Layer::onUserTipsClick(Node* pSender)
{
    
    int tag=pSender->getTag();
    
    TipsLayer::show(m_list->at(tag)->itemType, m_list->at(tag)->itemId,m_list->at(tag)->itemCount);
}

void LuxurySignin_Layer::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag==0) {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_EVERYDAY));
    }else if (tag==1)
    {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_LUXURY));
    }
}
void LuxurySignin_Layer::requestListMsg()
{
    SigninLuxuryMsg* msg = new SigninLuxuryMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LuxurySignin_Layer::requestListGetMsg()
{
    SigninLuxuryGetMsg* msg = new SigninLuxuryGetMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void LuxurySignin_Layer::onMsgProcess(EventCustom* msg)
{
    
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_SIGNELITE_SignElitePageResp)
    {
        m_day=message->byteStream->getByte();
        m_status=message->byteStream->getByte();
        int daySize=message->byteStream->getByte();
        for (int i=0; i<daySize; i++) {
            SigninData* data=new SigninData();
            data->itemType=message->byteStream->getByte();
            data->itemId=message->byteStream->getInt();
            data->itemQuality=message->byteStream->getByte();
            data->itemCount=message->byteStream->getByte();
            m_list->push_back(data);
        }
        this->onCreateStatus();
    
    }else if(message->messageID == SCENSE_CLIENT_SIGNELITE_SignEliteSignResp)
    {
        m_baseList->clear();
        int _num=message->byteStream->getByte();
        for (int i=0; i<_num; i++) {
            BaseTypeData *data=new BaseTypeData();
            int itemType=message->byteStream->getByte();
            int itemDictId=message->byteStream->getInt();
            string itemName=message->byteStream->getUTF8();
            int itemQuality=message->byteStream->getByte();
            string itemDesc=message->byteStream->getUTF8();
            int itemCount=message->byteStream->getByte();
            
            data->dataId=itemDictId;
            data->dataName=itemName;
            data->dataType=itemType;
            data->dataQuality=itemQuality;
            data->dataCount = itemCount;
            m_baseList->pushBack(data);
//            string str="恭喜获得"+PublicShowUI::numberToString(itemCount)+itemName;
//            NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
            
        }
        AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer);
        
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_LUXURY));
    }
}
void LuxurySignin_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SIGNELITE_SignElitePageResp).c_str(), CC_CALLBACK_1(LuxurySignin_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SIGNELITE_SignEliteSignResp).c_str(), CC_CALLBACK_1(LuxurySignin_Layer::onMsgProcess, this));
}
void LuxurySignin_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}