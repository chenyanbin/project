//
//  VipBlackShopBuyLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#include "VipBlackShopBuyLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../vipdata/VipBlackShopManager.h"
#include "../vipdata/VipBlackshopData.h"
#include "../../../protocol/Protocal.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../message/Decoding/vip/blackshop/RequestBsBuyListMsg.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../../commonData/enum/DictRolePropEnum.h"
VipBlackShopBuyLayer::VipBlackShopBuyLayer()
:m_nowcount(1)
,TAG_COUNT(2)
,m_baselist(NULL)
,m_idx(1)
,allPrice(1)

{
    m_baselist = new Vector<BaseTypeData*>();
}

VipBlackShopBuyLayer::~ VipBlackShopBuyLayer()
{
}


bool VipBlackShopBuyLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_idx = idx;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setButton();
        setSureBuyBtn();
        bref = true;
    } while (false);
    return bref;
}

VipBlackShopBuyLayer* VipBlackShopBuyLayer::create(int idx)
{
    VipBlackShopBuyLayer* list = new VipBlackShopBuyLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void VipBlackShopBuyLayer::show(int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    VipBlackShopBuyLayer* layer = VipBlackShopBuyLayer::create(idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void VipBlackShopBuyLayer::onEnter()
{
    BaseLayer::onEnter();
}
void VipBlackShopBuyLayer::onExit()
{
    BaseLayer::onExit();
}
void VipBlackShopBuyLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void VipBlackShopBuyLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void VipBlackShopBuyLayer::setButton()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    int prive = VipBlackShopManager::getInstance()->bsList->at(m_idx)->price;
    string allPriceStr = StringUtils::format("确认购买：%d",prive);
    
    Label* allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    allPriceLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(allPriceLabel);
    allPriceLabel->setPosition(this->getContentSize().width/2-allPriceLabel->getContentSize().width/2-10*sx,this->getContentSize().height/2-allPriceLabel->getContentSize().height/2+30*sx);
    this->addChild(allPriceLabel,2);
    
    Sprite* gold = NULL;
    if (VipBlackShopManager::getInstance()->bsList->at(m_idx)->conId == DictRolePropEnumCoin) {
        gold = Sprite::create(IMG_ICON_PUBLIC_COIN);
    }else{
        gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    }
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setPosition(allPriceLabel->getPositionX()+allPriceLabel->getContentSize().width+5*sx,allPriceLabel->getPositionY()-7*sx);
    this->addChild(gold,3);
}
void VipBlackShopBuyLayer::setSureBuyBtn()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_PUBLIC_LABEL_BUYWORD, IMG_PUBLIC_LABEL_BUYWORD, CC_CALLBACK_1(VipBlackShopBuyLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(VipBlackShopBuyLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void VipBlackShopBuyLayer::onSureBuyClick(Ref* psender)
{
    if(VipBlackShopManager::getInstance()->bsList->at(m_idx)->price<GlobalInfo::getInstance()->userGold){
        requestListMsg(VipBlackShopManager::getInstance()->bsList->at(m_idx)->shopId);
    }else{
        NoticeManager::getInstance()->showNotice("元宝不足，不能购买!");
    }
    
}
void VipBlackShopBuyLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/******------------------------------------访问服务器------------------------------*************/
void VipBlackShopBuyLayer::requestListMsg(int shopId)//请求列表信息
{
    RequestBsBuyListMsg* msg = new RequestBsBuyListMsg(shopId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void VipBlackShopBuyLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_BLACK_BlackBuyResp)
    {
        if(message->state)//返回成功
        {
            BaseTypeData* basedata = new BaseTypeData;
            basedata->autorelease();
            basedata->dataType =VipBlackShopManager::getInstance()->bsList->at(m_idx)->itemType;
            basedata->dataQuality =VipBlackShopManager::getInstance()->bsList->at(m_idx)->itemQuality;
            basedata->dataName =VipBlackShopManager::getInstance()->bsList->at(m_idx)->itemName;
            basedata->dataId =VipBlackShopManager::getInstance()->bsList->at(m_idx)->itemId;
//            basedata->dataCount =VipBlackShopManager::getInstance()->bsList->at(m_idx)->it
            m_baselist->pushBack(basedata);
            
            AwardBox_Layer* layer = AwardBox_Layer::create(m_baselist);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene = Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
            this->removeFromParent();
            broadMsg(CUSTOM_VIP_BLACKSHOP_BUY);
        }
    }
}
void VipBlackShopBuyLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BLACK_BlackBuyResp).c_str(), CC_CALLBACK_1(VipBlackShopBuyLayer::onMsgProcess, this));
}
void VipBlackShopBuyLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}