//
//  SevendayChoseHeroLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#include "SevendayChoseHeroLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "weekrewarddata/WeekRewardPageDatamanager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../tips/TipsLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../awardBox/AwardBox_Layer.h"
SevendayChoseHeroLayer::SevendayChoseHeroLayer()
:m_type(1)
,TAG_NODE(10)
,TAG_USERHEAD(11)
,m_numHero(1)
,m_baseList(NULL)
{
    m_baseList = new Vector<BaseTypeData*>();
}

SevendayChoseHeroLayer::~ SevendayChoseHeroLayer()
{
}


bool SevendayChoseHeroLayer::init(int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        m_type = idx;
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

SevendayChoseHeroLayer* SevendayChoseHeroLayer::create(int idx)
{
    SevendayChoseHeroLayer* list = new SevendayChoseHeroLayer();
    if(list && list->init(idx))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void SevendayChoseHeroLayer::show(int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    SevendayChoseHeroLayer* layer = SevendayChoseHeroLayer::create(idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void SevendayChoseHeroLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SevendayChoseHeroLayer::onExit()
{
    BaseLayer::onExit();
}
void SevendayChoseHeroLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void SevendayChoseHeroLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void SevendayChoseHeroLayer::setButton()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string allPriceStr = "可免费领取其中一个英雄";
    Label* allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),26,false,false);
    allPriceLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(allPriceLabel);
    allPriceLabel->setPosition(this->getContentSize().width/2-allPriceLabel->getContentSize().width/2,this->getContentSize().height/2+90*sx);
    this->addChild(allPriceLabel,2);
    
    Node* node = node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(node);
    size_t len = WeekRewardPageDatamanager::getInstance()->rewardlList->size();
    int m_tag = 0;
    for (int i = 0; i<len; i++)
    {
        if(WeekRewardPageDatamanager::getInstance()->rewardlList->at(i)->rewardType == m_type)
        {
            WeekRewardData* data = WeekRewardPageDatamanager::getInstance()->rewardlList->at(i);
            int m_quality = data->itemQuality;
            if (m_quality == 0)
            {
                m_quality = 1;
            }
            const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
            UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality,false);
            userHead->setHeadInfo(1, 1);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setPosition(m_tag*(userHead->getContentSize().width+20),100);
            node->addChild(userHead,2,m_tag);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(SevendayChoseHeroLayer::onitemClick));
            m_tag ++;
        }
    }
    node->setPosition(70*sx,20*sx);
    this->addChild(node,2,TAG_NODE);
    
   
    
}

void SevendayChoseHeroLayer::onitemClick(Node* pSender)
{
    Node* node = (Node*)this->getChildByTag(TAG_NODE);
    UserHeadLayer* userhead = (UserHeadLayer*)node->getChildByTag(pSender->getTag());
   
    CommonEffect* commonEffect = (CommonEffect*)node->getChildByTag(TAG_USERHEAD);
    if (commonEffect) {
        commonEffect->setPosition((userhead->getPositionX()+userhead->getContentSize().width/2)-5,(userhead->getPositionY()+userhead->getContentSize().height/2)-5);
    }else
    {
    commonEffect = CommonEffect::create("wujiangtouxiang",true,false);
    commonEffect->setAnchorPoint(Point(0.5,0.5));
    commonEffect->setPosition((userhead->getPositionX()+userhead->getContentSize().width/2)-5,(userhead->getPositionY()+userhead->getContentSize().height/2)-5);
    node->addChild(commonEffect,2,TAG_USERHEAD);
    }
    m_numHero = pSender->getTag()+1;
}

void SevendayChoseHeroLayer::setSureBuyBtn()
{
    
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(SevendayChoseHeroLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(SevendayChoseHeroLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);
    
}
void SevendayChoseHeroLayer::onSureBuyClick(Ref* psender)
{
    broadMsg(CUSTOM_WEEK_CHOSE_HERO,__Integer::create(m_numHero));
    
}
void SevendayChoseHeroLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
/******------------------------------------访问服务器------------------------------*************/
void SevendayChoseHeroLayer::requestListMsg(int shopId)//请求列表信息
{
//    RequestBsBuyListMsg* msg = new RequestBsBuyListMsg(shopId);
//    NetworkDataProcessing::getInstance()->sendMessage(msg);
//    msg = NULL;
}
void SevendayChoseHeroLayer::onMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekReceiveResp)
    {
        if(message->state)//返回成功
        {
            
//            WeekRewardData* data = WeekRewardPageDatamanager::getInstance()->rewardlList->at(m_numHero -1);
//            BaseTypeData* basedata = new BaseTypeData();
//            basedata->dataId = data->itemId;
//            basedata->dataType = data->itemType;
//            basedata->dataQuality = data->itemQuality;
//            basedata->dataName = data->itemName;
//            m_baseList->pushBack(basedata);
//            
//            AwardBox_Layer* layer = AwardBox_Layer::create(m_baseList);
//            layer->setAnchorPoint(Point::ZERO);
//            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
//            Scene* scene = Director::getInstance()->getRunningScene();
//            scene->addChild(layer);
            
        this->removeFromParent();
    
        }
    }
}
void SevendayChoseHeroLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekReceiveResp).c_str(), CC_CALLBACK_1(SevendayChoseHeroLayer::onMsgProcess, this));
}
void SevendayChoseHeroLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}