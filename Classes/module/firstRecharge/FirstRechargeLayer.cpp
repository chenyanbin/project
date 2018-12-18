//
//  FirstRechargeLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/16.
//
//

#include "FirstRechargeLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../common/StringUtil.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/firstRecharge/FirstRechargeMsg.h"
#include "../../message/Decoding/firstRecharge/FirstRechargeLingquMsg.h"
#include "FirstRechargeDataManager.h"
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../tips/TipsLayer.h"
#include "../../sdk/SdkManager.h"
#include "../awardBox/AwardBox_Layer.h"
#include "../vip/VipLayer.h"
FirstRechargeLayer::FirstRechargeLayer()
:m_baselist(NULL)
,TAG_PERSON(1)
{
    m_baselist = new Vector<BaseTypeData*>();
}
FirstRechargeLayer::~FirstRechargeLayer()
{
    m_baselist->clear();
    CC_SAFE_DELETE(m_baselist);
    m_baselist = NULL;
}
bool FirstRechargeLayer::init(int firstCharge)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->setBackground(ING_FIRSTRECHARGE_BG,Point::ZERO,true);
        
        const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, "lvbu");
        Sprite* lvBu = Sprite::create(path);
        lvBu->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(lvBu);
        lvBu->setPosition(230 * GlobalInfo::getInstance()->screenScaleX, (this->getContentSize().height - lvBu->getContentSize().height)/2 );
        this->addChild(lvBu,1,TAG_PERSON);
 
        this->setClickEnabled(true);
        this->isClickClose = true;
        this->isShowGrayBg = true;
        this->isAnimation = true;
       
        bref = true;
    } while (false);
    return bref;
}
FirstRechargeLayer* FirstRechargeLayer::create(int firstCharge)
{
    FirstRechargeLayer* layer= new FirstRechargeLayer();
    if(layer && layer->init(firstCharge))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void FirstRechargeLayer::show(int firstCharge)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    FirstRechargeLayer* layer = FirstRechargeLayer::create(firstCharge);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2+40*GlobalInfo::getInstance()->screenScaleX, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void FirstRechargeLayer::onEnter()
{
    BaseLayer::onEnter();
}
void FirstRechargeLayer::onExit()
{
    BaseLayer::onExit();
}
void FirstRechargeLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
     requestFirstRechargeReceivelMsg();
}
void FirstRechargeLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void FirstRechargeLayer::setButton(int _status)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    if (_status == 2)//不可领取，未到vip1
    {
        Sprite* btn = Sprite::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE);
        btn->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(btn);
        this->addChild(btn);
        btn->setPosition(this->getContentSize().width/2-btn->getContentSize().width/2,50*sx);
        
        Button* btnword = Button::create(ING_FIRSTRECHARGE_RECHARGE, ING_FIRSTRECHARGE_RECHARGE, CC_CALLBACK_1(FirstRechargeLayer::onclick, this));
        btnword->setAnchorPoint(Point::ZERO);
        btn->addChild(btnword,2,0);
        btnword->setPosition(Point::ZERO);
    }else if(_status == 1)//可领取
    {
        
        Sprite* btn = Sprite::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE);
        btn->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(btn);
        this->addChild(btn);
        btn->setPosition(this->getContentSize().width/2-btn->getContentSize().width/2,50*sx);
        
        Button* btnword = Button::create(ING_FIRSTRECHARGE_LINGQU, ING_FIRSTRECHARGE_LINGQU, CC_CALLBACK_1(FirstRechargeLayer::onclick, this));
        btnword->setAnchorPoint(Point::ZERO);
        btn->addChild(btnword,2,1);
        btnword->setPosition(Point::ZERO);
    }else if (_status == 3)
    {
        
        Sprite* yilingqu = Sprite::create(IMG_VIP_RECHARGE_TODAY_GETTED);
        yilingqu->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(yilingqu);
        this->addChild(yilingqu,10);
        yilingqu->setPosition(this->getContentSize().width/2+200*sx,80*sx);
//        string succeedStr = "领取成功";
//        Label* label = PublicShowUI::getLabel(succeedStr.c_str(),Color3B::RED,24,false,false);
//        label->setAnchorPoint(Point::ZERO);
//        PublicShowUI::setTargetScale(label);
//        this->addChild(label);
//        label->setPosition(this->getContentSize().width/2-label->getContentSize().width/2,50*sx);
    }
    
    
}
void FirstRechargeLayer::onclick(Ref* psender)
{
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case 0:
            
//            SdkManager::getInstance()->requestChargeOrder(kRecharge_type_other, 0, 0, 10);
            VipLayer::show(SCENE_TAG_MAINUI,VipLayer::TAG_RECHARGE);
            break;
        case 1:
            requestFirstRechargeLingquMsg();
            break;
        default:
            break;
    }
}
void FirstRechargeLayer::setItemPic()
{
    float sx  = GlobalInfo::getInstance()->screenScaleX;
    size_t len = FirstRechargeDataManager::getInstance()->firstList->size();
    
    Node* person = this->getChildByTag(TAG_PERSON);
    float startX = person->getPositionX() + person->getContentSize().width - 100 * sx;
    float startY = 100 * sx;
    for (int i = 0; i< len; i++) {
        FirstRechargeData* data = FirstRechargeDataManager::getInstance()->firstList->at(i);
        int m_quality = data->itemQuality;
        if (m_quality == 0)
        {
            m_quality = 1;
        }
        
        if( data->itemType == DictItemTypeEnumItemHero)
        {
            const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
            UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality,false);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setHeadInfo(1, 3);
            PublicShowUI::setTargetScale(userHead);
            userHead->setScale(0.7*sx);
            userHead->setPosition(startX+i%4*(userHead->getContentSize().width-20*sx),(floor(i/4)*userHead->getContentSize().height)+startY);
            this->addChild(userHead,2,i);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(FirstRechargeLayer::onHeroHeadClick));
        }
        else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
        {
            const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
            UserEquipLayer* head = UserEquipLayer::create(resource,m_quality,false);
            head->setAnchorPoint(Point::ZERO);
            if (data->itemType == 4) {
                head->setFragment();
            }else if (data->itemType == 3)
            {
                head->setLetterFragment();
            }
            PublicShowUI::setTargetScale(head);
            head->setScale(0.7*sx);
            if (i>1) {
                head->setPosition(startX+i%4*(head->getContentSize().width-20*sx),(floor(i/4)*head->getContentSize().height)+startY );
            }else{
               head->setPosition(startX+i%4*(head->getContentSize().width-20*sx),(floor(i/4)*head->getContentSize().height)+startY);
            }
            
            this->addChild(head,5,i);
            
            head->addTouchBegainCallBack(this, callfuncN_selector(FirstRechargeLayer::onHeroHeadClick));
        }
    }
}
void FirstRechargeLayer::onHeroHeadClick(Node* pSender)
{
    FirstRechargeData* data = FirstRechargeDataManager::getInstance()->firstList->at(pSender->getTag());
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}
//-----------------------------------------------访问服务器-------------------------------------------------------//
void FirstRechargeLayer::requestFirstRechargeReceivelMsg()//请求列表信息
{
    Dialog::showServerLoading();
    FirstRechargeMsg* msg = new FirstRechargeMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FirstRechargeLayer::onFirstRechargeMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    FirstRechargeDataManager::getInstance()->clearFirstList();
    if(message->messageID == SCENSE_CLIENT_FIRSTCHARGE_FirstChargePageResp)
    {
        if(message->state)//返回成功
        {
            int status = message->byteStream->getByte();
            int len = message->byteStream->getByte();
            for (int i = 0; i < len; i ++) {
                FirstRechargeData* data = new FirstRechargeData;
                
                data->autorelease();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemCount = message->byteStream->getByte();
                data->itemQuality = message->byteStream->getByte();
                data->itemName = message->byteStream->getUTF8();
                FirstRechargeDataManager::getInstance()->addData(data);
                
                BaseTypeData* basedata = new BaseTypeData;
                basedata->autorelease();
                basedata->dataId = data->itemId;
                basedata->dataType = data->itemType;
                basedata->dataQuality = data->itemQuality;
                basedata->dataName = data->itemName;
                basedata->dataCount = data->itemCount;
                basedata->heroPrestige = 3;
                m_baselist->pushBack(basedata);
            }
            setButton(status);
            setItemPic();
        }
    }
}
void FirstRechargeLayer::requestFirstRechargeLingquMsg()//请求领取
{
    Dialog::showServerLoading();
    FirstRechargeLingquMsg* msg = new FirstRechargeLingquMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FirstRechargeLayer::onFirstRechargeLingquMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_FIRSTCHARGE_FirstChargeReceiveResp)
    {
        if(message->state)//返回成功
        {
            AwardBox_Layer* layer = AwardBox_Layer::create(m_baselist);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene = Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            GlobalInfo::getInstance()->firstRechargeStatus = 3;
            this->removeFromParent();
        }
    }
}

void FirstRechargeLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIRSTCHARGE_FirstChargePageResp).c_str(), CC_CALLBACK_1(FirstRechargeLayer::onFirstRechargeMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FIRSTCHARGE_FirstChargeReceiveResp).c_str(), CC_CALLBACK_1(FirstRechargeLayer::onFirstRechargeLingquMsgProcess, this));   
}
void FirstRechargeLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}



