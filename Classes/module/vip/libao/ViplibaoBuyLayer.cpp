//
//  ViplibaoBuyLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/28.
//
//

#include "ViplibaoBuyLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../message/Decoding/vip/gilt/RequestGiltBuyMsg.h"
#include "../../../common/Dialog/Dialog.h"
#include "../vipdata/VipgiftBuyManager.h"
#include "../../market/marketData/MarketFindResultDataManager.h"
#include "VipHeadGiftLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../awardBox/AwardBox_Layer.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
ViplibaoBuyLayer::ViplibaoBuyLayer()
:m_level(0)
,m_needGold(0)
,m_baselist(NULL)
{
    m_baselist = new Vector<BaseTypeData*>();
}

ViplibaoBuyLayer::~ ViplibaoBuyLayer()
{
    
}


bool ViplibaoBuyLayer::init(int _level, int needGold)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_level = _level;
        m_needGold = needGold;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->isAnimation = false;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setUiSpr();
        
        setSureBuyBtn();
        
        bref = true;
    } while (false);
    return bref;
}

ViplibaoBuyLayer* ViplibaoBuyLayer::create(int _level, int needGold)
{
    ViplibaoBuyLayer* list = new ViplibaoBuyLayer();
    if(list && list->init(_level,needGold))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void ViplibaoBuyLayer::show(int _level, int needGold)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    ViplibaoBuyLayer* layer = ViplibaoBuyLayer::create(_level,needGold);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}

void ViplibaoBuyLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ViplibaoBuyLayer::onExit()
{
    BaseLayer::onExit();
}
void ViplibaoBuyLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void ViplibaoBuyLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void ViplibaoBuyLayer::setUiSpr()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string renwuWord1= "是否购买？";
    Label* renwuLabel1 = PublicShowUI::getLabel(renwuWord1.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    renwuLabel1->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(renwuLabel1);
    renwuLabel1->setPosition(this->getContentSize().width/2-renwuLabel1->getContentSize().width/2 ,this->getContentSize().height/2-renwuLabel1->getContentSize().height/2+100*sx);
    this->addChild(renwuLabel1,2);
    
    string allPriceStr = StringUtils::format("花费：%d",m_needGold);
    Label* allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    allPriceLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(allPriceLabel);
    allPriceLabel->setPosition(this->getContentSize().width/2-allPriceLabel->getContentSize().width/2-10*sx,this->getContentSize().height/2-allPriceLabel->getContentSize().height/2+30*sx);
    this->addChild(allPriceLabel,2);
    
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gold);
    gold->setPosition(allPriceLabel->getPositionX()+allPriceLabel->getContentSize().width+5*sx,allPriceLabel->getPositionY()-7*sx);
    this->addChild(gold,3);
    
}

void ViplibaoBuyLayer::setSureBuyBtn()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(ViplibaoBuyLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(ViplibaoBuyLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void ViplibaoBuyLayer::onSureBuyClick(Ref* psender)
{
    
//    this->removeFromParent();
    if(m_needGold<GlobalInfo::getInstance()->userGold){
        requesgifttListMsg(m_level);
    }else{
        NoticeManager::getInstance()->showNotice("元宝不足，不能购买!");
    }

}

void ViplibaoBuyLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/******------------------------------------访问服务器------------------------------*************/
void ViplibaoBuyLayer::requesgifttListMsg(int _level)//请求列表信息
{
    Dialog::showServerLoading();
    RequestGiltBuyMsg* msg = new RequestGiltBuyMsg(_level);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void ViplibaoBuyLayer::onMsggiftProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    VipgiftBuyManager::getInstance()->clearbuyList();
    if(message->messageID == SCENSE_CLIENT_GIFT_GiftBuyResp)
    {
        if(message->state)//返回成功
        {
            int itemCount = message->byteStream->getByte();
            for (int i = 0; i< itemCount; i++) {
                VipGiftBuyData* data = new VipGiftBuyData;
                BaseTypeData* basedata = new BaseTypeData;
                basedata->autorelease();
                data->autorelease();
                data->itemType = message->byteStream->getByte();
                data->itemDictId = message->byteStream->getInt();
                data->itemName = message->byteStream->getUTF8();
                data->itemQuality = message->byteStream->getByte();
                data->itemDesc = message->byteStream->getUTF8();
                data->itemCount = message->byteStream->getByte();
               
                basedata->dataId = data->itemDictId;
                basedata->dataType = data->itemType;
                basedata->dataName = data->itemName;
                basedata->dataQuality = data->itemQuality;
                basedata->dataCount = data->itemCount;
                
                VipgiftBuyManager::getInstance()->addData(data);
                m_baselist->pushBack(basedata);
            }
            
            AwardBox_Layer* layer = AwardBox_Layer::create(m_baselist);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene = Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
            this->removeFromParent();
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumGift));
            broadMsg(CUSTOM_VIP_LIBAO_BUY);
        }
    }
}
void ViplibaoBuyLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_GIFT_GiftBuyResp).c_str(), CC_CALLBACK_1(ViplibaoBuyLayer::onMsggiftProcess, this));
}
void ViplibaoBuyLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}