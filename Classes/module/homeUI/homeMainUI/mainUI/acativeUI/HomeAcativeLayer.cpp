//
//  HomeAcativeLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/23.
//
//

#include "HomeAcativeLayer.h"
#include "../../../../../common/PublicShowUI.h"
#include "../../../../../commonData/GlobalInfo.h"
#include "../../../../../common/TouchSprite/TouchSprite.h"
#include "../../../../../common/commonEffect/CommonEffect.h"
#include "../../../../../common/GameConfig.h"
#include "../../../../../commonData/dictData/DictRoleLevel/DictRoleLevelManager.h"
#include "../../../../../protocol/UserCustomEvent.h"
#include "../../../../../common/ImagePath.h"
#include "../../../../mail/MailLayer.h"
#include "../../../../task/signin/Signin_Scene.h"
#include "../../../../vip/VipLayer.h"
#include "../../../../generals/generalsCard/GeneralsCard_Layer.h"
#include "../../../../market/MarketLayer.h"
#include "../../../../firstRecharge/FirstRechargeLayer.h"
#include "../../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../activity/cdkeyActivity/CdkeyActivity.h"
#include "../../../../activity/Activity_Scene.h"
#include "../../../../rank/RankFightLayer.h"
#include "../../../../limitCard/LimitCardLayer.h"
#include "../../../../../commonData/enum/DictFunctionEnum.h"
#include "../../../../../commonData/data/FunctionOpenManager.h"
#include "../../../../arena/ArenaLayer.hpp"
#include "../../../../sevenday/SevendayLayer.hpp"
#include "../../../../dot/RefreshDot.h"

HomeAcativeLayer::HomeAcativeLayer()
:sx(0)
,TAG_QIANDAO(1)
,TAG_MAIL(2)
,TAG_MARKET(3)
,TAG_GIFT(4)
,TAG_RECHARGE(5)
,TAG_SEVEN(6)
,TAG_EXCHANGE(7)
,TAG_SEVENACATIVE(8)
,TAG_ACATIVE(9)
{
    
}
HomeAcativeLayer::~HomeAcativeLayer()
{
    
}
void HomeAcativeLayer::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGiftButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumShopButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSignButton);
    removeEventListener();
}
void HomeAcativeLayer::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();

}

bool HomeAcativeLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        setAcativeBtn();
        bref = true;
    } while (false);
    return bref;
}
void HomeAcativeLayer::setAcativeBtn()
{
//    //签到
//    Button* qiandao=this->setButton(IMG_PUBLIC_MENUBTN_QIANDAO);
//    qiandao->setPosition(Point::ZERO);
//    PublicShowUI::setDot(qiandao,Point::ZERO,false,DictFunctionEnumSign);
//    this->addChild(qiandao,0,TAG_QIANDAO);
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSignButton, qiandao);
//    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumSign))
//    {
//        qiandao->setVisible(false);
//    }
//    //邮件
//    Button* mail=this->setButton(IMG_PUBLIC_MENUBTN_MAIL);
//    this->addChild(mail,0,TAG_MAIL);
//    mail->setPosition(qiandao->getPositionX()+qiandao->getContentSize().width-10*sx,qiandao->getPositionY());
//    //邮件红点
//    PublicShowUI::setDot(mail,Point::ZERO,false,DictFunctionEnumMail);
//    //商场
//    Button* market =this->setButton(IMG_PUBLIC_MENUBTN_SHOP);
//    this->addChild(market,0,TAG_MARKET);
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumShopButton, market);
//    market->setPosition(mail->getPositionX()+mail->getContentSize().width-10*sx,mail->getPositionY());
//    
//    //活动
//    Button* acativebtn =this->setButton(IMG_PUBLIC_MENUBTN_ACATIVE);
//    this->addChild(acativebtn,0,TAG_ACATIVE);
//    acativebtn->setPosition(market->getPositionX()+market->getContentSize().width-10*sx,market->getPositionY());
//    
//    //充值
//    Button* recharge =this->setButton(IMG_PUBLIC_MENUBTN_RECHARGE);
//    recharge->setAnchorPoint(Point::ZERO);
//    this->addChild(recharge,0,TAG_RECHARGE);
//    recharge->setPosition(market->getPositionX()+market->getContentSize().width-10*sx,market->getPositionY());
// 
//    //七日
//    Button* sevenAcative=Button::create(IMG_PUBLIC_MENUBTN_SEVEN,"", CC_CALLBACK_1(HomeAcativeLayer::onClick, this));
//    sevenAcative->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setDot(sevenAcative,Point(15,15),false,DictFunctionEnumSevenDay);
//    sevenAcative->setPosition(recharge->getPositionX()+recharge->getContentSize().width-10*sx,recharge->getPositionY());
//    this->addChild(sevenAcative,0,TAG_SEVENACATIVE);
    
    
    //充值
    Button* recharge =this->setButton(IMG_PUBLIC_MENUBTN_RECHARGE);
    recharge->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(recharge,Point::ZERO,false,DictFunctionEnumFirstCharge);
    this->addChild(recharge,0,TAG_RECHARGE);
    if (GlobalInfo::getInstance()->firstRechargeStatus == 3) {
        recharge->setVisible(false);
        recharge->setEnabled(false);
    }
    //    recharge->setPosition(market->getPositionX()+market->getContentSize().width-10*sx,market->getPositionY());

    //七日
    Button* sevenAcative=Button::create(IMG_PUBLIC_MENUBTN_SEVEN,"", CC_CALLBACK_1(HomeAcativeLayer::onClick, this));
    sevenAcative->setAnchorPoint(Point::ZERO);
    PublicShowUI::setDot(sevenAcative,Point::ZERO,false,DictFunctionEnumSevenDay);
    sevenAcative->setPosition(recharge->getPositionX()+recharge->getContentSize().width-10*sx,recharge->getPositionY());
    this->addChild(sevenAcative,0,TAG_SEVENACATIVE);
    if (GlobalInfo::getInstance()->sevendayActivity == 1) {
        sevenAcative->setVisible(false);
        sevenAcative->setEnabled(false);
    }
    //签到
    Button* qiandao=this->setButton(IMG_PUBLIC_MENUBTN_QIANDAO);
    qiandao->setPosition(Point::ZERO);
    PublicShowUI::setDot(qiandao,Point::ZERO,false,DictFunctionEnumSign);
    qiandao->setPosition(sevenAcative->getPositionX()+sevenAcative->getContentSize().width-10*sx,sevenAcative->getPositionY());
    if (GlobalInfo::getInstance()->sevendayActivity == 1 && GlobalInfo::getInstance()->firstRechargeStatus != 3) {
        qiandao->setPosition(recharge->getPositionX()+recharge->getContentSize().width-10*sx,recharge->getPositionY());
    }
    this->addChild(qiandao,0,TAG_QIANDAO);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSignButton, qiandao);
    if (!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumSign))
    {
        qiandao->setVisible(false);
    }
    //邮件
    Button* mail=this->setButton(IMG_PUBLIC_MENUBTN_MAIL);
    this->addChild(mail,0,TAG_MAIL);
    mail->setPosition(qiandao->getPositionX()+qiandao->getContentSize().width-10*sx,qiandao->getPositionY());
    PublicShowUI::setDot(mail,Point::ZERO,false,DictFunctionEnumMail);
    //商场
    Button* market =this->setButton(IMG_PUBLIC_MENUBTN_SHOP);
    this->addChild(market,0,TAG_MARKET);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumShopButton, market);
    market->setPosition(mail->getPositionX()+mail->getContentSize().width-10*sx,mail->getPositionY());
    PublicShowUI::setDot(market,Point::ZERO,false,DictFunctionEnumBlackShop,DictFunctionEnumGift);
    //活动
    Button* acativebtn =this->setButton(IMG_PUBLIC_MENUBTN_ACATIVE);
    PublicShowUI::setDot(acativebtn,Point::ZERO,false,DictFunctionEnumWelfareDay,DictFunctionEnumBanquet,DictFunctionEnumSign);
    acativebtn->setPosition(market->getPositionX()+market->getContentSize().width-10*sx,market->getPositionY());
    this->addChild(acativebtn,0,TAG_ACATIVE);
    
    
    
   

    
    Size cellSize;
    cellSize.height = acativebtn->getContentSize().height;
    cellSize.width = acativebtn->getContentSize().width+sevenAcative->getPositionX();
    this->setContentSize(cellSize);
}
Button* HomeAcativeLayer::setButton(const std::string&normalImage)
{
    Button* btn=Button::create(normalImage,"", CC_CALLBACK_1(HomeAcativeLayer::onClick, this));
    btn->setAnchorPoint(Point::ZERO);
    
//    CommonEffect* activeEffect = CommonEffect::create("zcj-huodong",true,true);
//    activeEffect->setAnchorPoint(Point::ZERO);
//    activeEffect->setPosition((btn->getContentSize().width-activeEffect->getContentSize().width)/2,(btn->getContentSize().height-activeEffect->getContentSize().height)/2);
//    btn->addChild(activeEffect,2);
    
    return btn;
}
void HomeAcativeLayer::onClick(Ref* pSender)
{
    Node* temp = (Node*)pSender;
    if(!temp->isVisible())
    {
        return;
    }
    int tag = temp->getTag();
    if(tag == TAG_QIANDAO)//签到
    {
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSignButton);
        Signin_Scene::show(SCENE_TAG_MAINUI,Signin_Scene::TAG_EVERYDAY);
        log("签到");
    }
    else if (tag==TAG_MAIL)//邮件
    {
        log("邮件");
        MailLayer::show();
    }
    else if (tag==TAG_MARKET)//商场
    {
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumShopButton);
        MarketLayer::show(SCENE_TAG_MAINUI,MarketLayer::TAG_SHANGDIAN);
        log("商场");
    }
    else if (tag==TAG_GIFT)//礼包
    {
        log("礼包");
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumGiftButton);
        VipLayer::show(SCENE_TAG_MAINUI,VipLayer::TAG_LIBAO);
    }
    else if (tag==TAG_RECHARGE)//充值
    {
        log("充值");
        FirstRechargeLayer::show();
        
    }else if (tag==TAG_EXCHANGE)
    {

//        CdkeyActivity* layer=CdkeyActivity::create();
//        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
//        Scene* scene=Director::getInstance()->getRunningScene();
//        scene->addChild(layer,SCENE_LAYER_ZORDER);
        
//        ArenaOrderLayer::show(SCENE_TAG_MAINUI);
         ArenaLayer::show(ArenaLayer::PAGE_ARENALIST);
    }else if (tag==TAG_SEVENACATIVE)
    {
        
//        Activity_Scene::show(SCENE_TAG_MAINUI,1);
        SevendayLayer::show(SCENE_TAG_MAINUI);
        
    }else if (tag == TAG_ACATIVE)
    {
        NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumWelfareButton);
        Signin_Scene::show(SCENE_TAG_MAINUI,Signin_Scene::TAG_DAYBENEFIT);
    }
}

void HomeAcativeLayer::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    Button* btn = NULL;
    if (tag_index == DictFunctionEnumMail) {
        btn = (Button*)this->getChildByTag(TAG_MAIL);
        RefreshDot::getInstance()->requestMsg(btn,Point::ZERO,false,DictFunctionEnumMail);
    }
}

void HomeAcativeLayer::addEventListener()
{
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(HomeAcativeLayer::onRefreshDot, this));
}
void HomeAcativeLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}