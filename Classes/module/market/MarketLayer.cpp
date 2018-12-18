//
//  MarketLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/3.
//
//

#include "MarketLayer.h"
#include "../userWealth/UserWealthLayer.h"

#include "marketFind/MarketFindLayer.h"
#include "marketJuxian/MarketJuxianLayer.h"
#include "marketJuxian/MarketGoodsLayer.h"
#include "marketFind/MarketGetHeroLayer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "marketShop/MarketShopLayer.h"
#include "marketShop/MarketPurchaseLayer.h"
#include "auction/MarketAuctionLayer.h"
#include "marketFind/FindBuyMilitaryLayer.h"
#include "marketFind/FindAccelerationLayer.h"
#include "marketFind/FindExtendLayer.h"
#include "marketFind/MarketGetEquipLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../../protocol/Protocal.h"
#include "marketJuxian/MarketGoodsLayer.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../dot/RefreshDot.h"
#include "../vip/libao/VipLibaoLayer.h"
#include "../vip/blackShop/VipBlackShopLayer.h"
MarketLayer::MarketLayer()
:m_tagLayer(0)
,TAG_NAMEBG(19)
,TAG_SHOPBG(8)
,TAG_PAIMAIBG(11)
,TAG_JUXIANBG(12)
,boxBtn(NULL)
{
    
}
MarketLayer::~MarketLayer()
{
    
}

bool MarketLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
//        this->isShowGrayBg = true;
        this->isAbleGuiding = true;
        this->setBackBtn(0,15*GlobalInfo::getInstance()->screenScaleX,true);
        setbackGround();
        setUserWealth();
        
        bref = true;
    } while (false);
    return bref;

}
MarketLayer* MarketLayer::create()
{
    MarketLayer* layer = new MarketLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void MarketLayer::show(int fromScene,int openLayer)
{
    
    Director::getInstance()->purgeCachedData();
//    Scene* scene = Director::getInstance()->getRunningScene();
    MarketLayer* layer = MarketLayer::create();
    layer->setFromScene(fromScene);
    layer->setInitOpenLayer(openLayer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();//
    scene->addChild(layer,0,SCENE_TAG_MARKET);
    
    Director::getInstance()->replaceScene(scene);
}
void MarketLayer::onEnter()
{
    BaseLayer::onEnter();
    setRightBtn();
}

void MarketLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
}
void MarketLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumLookFor);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumAuctionTag);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumBlackMarketTag);
}
void MarketLayer::setbackGround()
{
    Sprite* bgSpr = Sprite::create(IMG_PUBLIC_MODULE_BG2);
    PublicShowUI::setTargetScale(bgSpr,true);    
    bgSpr->setAnchorPoint(Point::ZERO);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,-4);
    
    Sprite* bgSprgray = Sprite::create(IMG_PUBLIC_MODULE_MASK_BOTTOM);
    PublicShowUI::setTargetScale(bgSprgray,true);
    bgSprgray->setAnchorPoint(Point::ZERO);
    bgSprgray->setPosition(Point::ZERO);
    this->addChild(bgSprgray,-2);
//
}
void MarketLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3,TAG_NAMEBG);
}
void MarketLayer::setRightBtn()
{
    float sx= GlobalInfo::getInstance()->screenScaleX;
    
//    ComboBoxBtn* boxBtn =NULL;
    if(m_tagLayer == TAG_LIBAP || m_tagLayer == TAG_SHANGDIAN || m_tagLayer == TAG_PAIMAI || m_tagLayer == TAG_BLACKSHOP)
    {
        const char* pathList[4] = {IMG_MARKET_WORDBTN_PAIMAI,IMG_MARKET_WORDBTN_HEISHI,IMG_MARKET_WORDBTN_LIBAO,IMG_MARKET_WORDBTN_SHANGDIAN};
        int functionList[4] = {DictFunctionEnumMarket,DictFunctionEnumBlackShop,DictFunctionEnumGift,DictFunctionEnumShopping};
        boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL,-20, CC_CALLBACK_1(MarketLayer::onRightBtnClick, this));
        for (int i =0; i<4;i++) {
            if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[i]))
            {
                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[i],true,functionList[i]);
            }
        }
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumMarket),Point(10,10),false,DictFunctionEnumMarket);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumBlackShop),Point(10,10),false,DictFunctionEnumBlackShop);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumGift),Point(10,10),false,DictFunctionEnumGift);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumShopping),Point(10,10),false,DictFunctionEnumShopping);
    }else if (m_tagLayer == TAG_XUNFANG || m_tagLayer == TAG_JUXIAN)
    {
        const char* pathList[2] = {IMG_MARKET_WORDBTN_XUNFANG,IMG_MARKET_WORDBTN_JUXIAN};
        int functionList[2] = {DictFunctionEnumFind,DictFunctionEnumLead};
        boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL,-20, CC_CALLBACK_1(MarketLayer::onRightBtnClick, this));
        for (int i =0; i<2;i++) {
            if(FunctionOpenManager::getInstance()->functionIsOpened(functionList[i]))
            {
                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, pathList[i],true,functionList[i]);
            }
            
        }
        
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumFind),Point(10,10),false,DictFunctionEnumFind);
        PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumLead),Point(10,10),false,DictFunctionEnumLead);
        
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLookFor, boxBtn->getButtonByTag(DictFunctionEnumFind));
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAuctionTag, boxBtn->getButtonByTag(DictFunctionEnumMarket));
        
    }
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumBlackMarketTag, boxBtn->getButtonByTag(DictFunctionEnumBlackShop));
    PublicShowUI::setTargetScale(boxBtn);
    boxBtn->setPosition(VisibleRect::right().x-150*sx,VisibleRect::center().y-boxBtn->getContentSize().height/2);
    this->addChild(boxBtn,1);
    setInitOpenLayer(m_tagLayer);
    
    switch (this->m_tagLayer)
    {
        case TAG_PAIMAI:
            boxBtn->selectAtByTag(DictFunctionEnumMarket);
            break;
        case TAG_SHANGDIAN:
            boxBtn->selectAtByTag(DictFunctionEnumShopping);
            break;
        case TAG_JUXIAN:
            boxBtn->selectAtByTag(DictFunctionEnumFind);
            break;
        case TAG_XUNFANG:
            boxBtn->selectAtByTag(DictFunctionEnumLead);
            break;
        case TAG_LIBAP:
            boxBtn->selectAtByTag(DictFunctionEnumGift);
            break;
        case TAG_BLACKSHOP:
            boxBtn->selectAtByTag(DictFunctionEnumBlackShop);
            break;
        default:
            break;
    }

    
//    int functionList[4] = {DictFunctionEnumMarket,DictFunctionEnumShopping,DictFunctionEnumFind,DictFunctionEnumLead};
//    boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_VERTICAL,-20, CC_CALLBACK_1(MarketLayer::onRightBtnClick, this));
//    for (int i = 0; i<2; i++) {
//        if (m_tagLayer == 1  || m_tagLayer == 2)
//        {
//            const char* path = PublicShowUI::getResImgPath(IMG_MARKET_WORDBTN, PublicShowUI::numberToString(i + 3).c_str());
//            boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, path,true,functionList[i+2]);
//            
//        }else{
//            const char* path = PublicShowUI::getResImgPath(IMG_MARKET_WORDBTN, PublicShowUI::numberToString(i + 1).c_str());
//            
//            if(FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMarket))
//            {
//                boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, path,true,functionList[i]);
//            }else{
//                if (i == 1) {
//                    boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_BTNUNCHOSE,IMG_PUBLIC_COMBOBOX_BTNCHOSE, path,true,functionList[i]);
//                }
//            }
//        }
//    }
//    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumFind),Point(10,10),false,DictFunctionEnumFind);
//    PublicShowUI::setDot(boxBtn->getButtonByTag(DictFunctionEnumLead),Point(10,10),false,DictFunctionEnumLead);
//    
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumLookFor, boxBtn->getButtonByTag(DictFunctionEnumFind));
//    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumAuctionTag, boxBtn->getButtonByTag(DictFunctionEnumMarket));
//    
//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(VisibleRect::right().x-150*sx,VisibleRect::center().y-boxBtn->getContentSize().height/2);
//    this->addChild(boxBtn,1);
//    setInitOpenLayer(m_tagLayer);
//    switch (this->m_tagLayer)
//    {
//        case TAG_PAIMAI:
//            boxBtn->selectAtByTag(DictFunctionEnumMarket);
//            break;
//        case TAG_SHANGDIAN:
//            boxBtn->selectAtByTag(DictFunctionEnumShopping);
//            break;
//        case TAG_JUXIAN:
//            boxBtn->selectAtByTag(DictFunctionEnumFind);
//            break;
//        case TAG_XUNFANG:
//            boxBtn->selectAtByTag(DictFunctionEnumLead);
//            break;
//        case TAG_LIBAP:
//            boxBtn->selectAtByTag(DictFunctionEnumLead);
//            break;
//        default:
//            break;
//    }
 }
void MarketLayer::setInitOpenLayer(int layerTag)
{
    if(this->m_tagLayer == layerTag)
    {
        return;
    }
 
    if(m_tagLayer)
    {
        this->removeChildByTag(m_tagLayer);
    }

    if(this->getChildByTag(TAG_JUXIANBG))
    {
        this->removeChildByTag(TAG_JUXIANBG);
    }else if (TAG_NAMELIBAOBG)
    {
        this->removeChildByTag(TAG_NAMELIBAOBG);
        this->removeChildByTag(TAG_LIBAOHERO);
    }
    else if (TAG_NAMEBLACKSHOPBG)
    {
        this->removeChildByTag(TAG_NAMEBLACKSHOPBG);
    }
    this->m_tagLayer = layerTag;
    switch (m_tagLayer)
    {
        case TAG_PAIMAI:
            addpaimaiLayer();
            
            break;
        case TAG_SHANGDIAN:
            addshangdianLayer();
            break;
        case TAG_JUXIAN:
            addjuxianLayer();
            break;
        case TAG_XUNFANG:
            addxunfangLayer();
            break;
        case TAG_LIBAP:
            addLibapLayer();
            break;
        case TAG_BLACKSHOP:
            addBlackShopLayer();
            break;
        default:
            log("参数错误");
            break;
    }
}
void MarketLayer::onRightBtnClick(Ref* psender)
{
    Node* target = (Node*)psender;
    int tag = target->getTag();

    switch (tag)
    {
        case DictFunctionEnumMarket:
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumAuctionTag);
            setInitOpenLayer(TAG_PAIMAI);
            break;
        case DictFunctionEnumShopping:
            setInitOpenLayer(TAG_SHANGDIAN);
            break;
        case DictFunctionEnumFind:
            setInitOpenLayer(TAG_JUXIAN);
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumLookFor);
            break;
        case DictFunctionEnumLead:
            setInitOpenLayer(TAG_XUNFANG);
            break;
        case DictFunctionEnumGift:
            setInitOpenLayer(TAG_LIBAP);
            break;
        case DictFunctionEnumBlackShop:
            setInitOpenLayer(TAG_BLACKSHOP);
            NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumBlackMarketTag);
        break;
            
        default:
            break;
    }
}
//举贤
void MarketLayer::addxunfangLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLead))
    {
         FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
   
    Sprite* bgSpr = Sprite::create(IMG_MARKET_JUXIANBG);
    bgSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,-3,TAG_JUXIANBG);
    
    MarketJuxianLayer* juxianlayer = MarketJuxianLayer::create();
    juxianlayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(juxianlayer);
    juxianlayer->setPositionX(VisibleRect::center().x-juxianlayer->getContentSize().width/2-50*sx);
    juxianlayer->setPositionY(VisibleRect::center().y - juxianlayer->getContentSize().height-80*sx );
    this->addChild(juxianlayer, 2,TAG_XUNFANG);
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
         topBg->setTitle(IMG_PUBLIC_JUXIAN);
    }
   
}
//寻访
void MarketLayer::addjuxianLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumFind))
    {
         FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    MarketFindLayer* choseLayer = MarketFindLayer::create();
    choseLayer->setAnchorPoint(Point::ZERO);
    choseLayer->setPositionX(VisibleRect::center().x-choseLayer->getContentSize().width/2-30*sx);
    choseLayer->setPositionY(VisibleRect::center().y - choseLayer->getContentSize().height/2 -30*sx );
    this->addChild(choseLayer, 2,TAG_JUXIAN );
    
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
        topBg->setTitle(IMG_PUBLIC_FIND);
    }
    
    
}
//商店
void MarketLayer::addshangdianLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumShopping))
    {
         FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Sprite* bgSpr = Sprite::create(IMG_PUBLIC_MODULE_BG2);
//    bgSpr->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bgSpr,true);
//    bgSpr->setPosition(Point::ZERO);
//    this->addChild(bgSpr,-3,TAG_SHOPBG);
   
    MarketShopLayer* shoplayer = MarketShopLayer::create();
    shoplayer->setAnchorPoint(Point::ZERO);
    shoplayer->setPositionX(VisibleRect::center().x-shoplayer->getContentSize().width/2-80*sx);
    shoplayer->setPositionY(VisibleRect::center().y - shoplayer->getContentSize().height/2 -30*sx);
    this->addChild(shoplayer, 2,TAG_SHANGDIAN);
    
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
         topBg->setTitle(IMG_PUBLIC_SHOP);
    }
   

}
//拍卖
void MarketLayer::addpaimaiLayer()
{
   
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumMarket))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
//    Sprite* bgSpr = Sprite::create(IMG_PUBLIC_MODULE_BG2);
//    bgSpr->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bgSpr,true);
//    bgSpr->setPosition(Point::ZERO);
//    this->addChild(bgSpr,-3,TAG_PAIMAIBG);
    
    MarketAuctionLayer* shoplayer = MarketAuctionLayer::create();
    shoplayer->setAnchorPoint(Point::ZERO);
    shoplayer->setPositionX(VisibleRect::center().x-shoplayer->getContentSize().width/2-80*sx);
    shoplayer->setPositionY(VisibleRect::center().y - shoplayer->getContentSize().height/2 -30*sx);
    this->addChild(shoplayer, 2,TAG_PAIMAI);

    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
       topBg->setTitle(IMG_PUBLIC_PAIMAI);
    }
    
}
//礼包
void MarketLayer::addLibapLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumGift))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* bgSpr = Sprite::create(IMG_VIP_RECHARGEBG);
    bgSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,0,TAG_NAMELIBAOBG);
    
    Sprite* heroSpr = Sprite::create(IMG_VIP_HUMANPIC);
    heroSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(heroSpr);
    heroSpr->setPosition(Point::ZERO);
    this->addChild(heroSpr,3,TAG_LIBAOHERO);
    
    VipLibaoLayer* libaolayer = VipLibaoLayer::create();
    libaolayer->setAnchorPoint(Point::ZERO);
    libaolayer->setPositionX(VisibleRect::center().x-libaolayer->getContentSize().width/2 + 80*sx);
    libaolayer->setPositionY(VisibleRect::center().y - libaolayer->getContentSize().height/2 -30*sx);
    this->addChild(libaolayer, 2,TAG_LIBAP);
    
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
        topBg->setTitle(IMG_PUBLIC_LIBAO);
    }

}
//黑市
void MarketLayer::addBlackShopLayer()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumBlackShop))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
//    Sprite* bgSpr = Sprite::create(IMG_MARKET_SHOPBG);
//    bgSpr->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bgSpr,true);
//    bgSpr->setPosition(Point::ZERO);
//    this->addChild(bgSpr,5,TAG_NAMEBLACKSHOPBG);
    
    VipBlackShopLayer* libaolayer = VipBlackShopLayer::create();
    libaolayer->setAnchorPoint(Point::ZERO);
    libaolayer->setPositionX(VisibleRect::center().x-libaolayer->getContentSize().width/2-80*sx);
    libaolayer->setPositionY(VisibleRect::center().y - libaolayer->getContentSize().height/2 -30*sx);
    this->addChild(libaolayer, 2,TAG_BLACKSHOP);
    
    UserWealthLayer* topBg=(UserWealthLayer*)this->getChildByTag(TAG_NAMEBG);
    if(topBg)
    {
        topBg->setTitle(IMG_PUBLIC_LABEL_SHOP_BLACKSHOP);
    }
}
void MarketLayer::oncreateTenItemMsg(EventCustom* msg)//十连抽
{
    MarketGoodsLayer* getHeroLayer = MarketGoodsLayer::create();
    getHeroLayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(getHeroLayer);
    getHeroLayer->setPositionX(VisibleRect::center().x-getHeroLayer->getContentSize().width/2);
    getHeroLayer->setPositionY(VisibleRect::center().y - getHeroLayer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(getHeroLayer, SCENE_LAYER_ZORDER);
}
void MarketLayer::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();
    if (tag_index == DictFunctionEnumLead) {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumLead),Point(10,10),false,DictFunctionEnumLead);
    }else if (DictFunctionEnumGift)
    {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumGift),Point(10,10),false,DictFunctionEnumGift);
    }else if (DictFunctionEnumBlackShop)
    {
        RefreshDot::getInstance()->requestMsg(boxBtn->getButtonByTag(DictFunctionEnumBlackShop),Point(10,10),false,DictFunctionEnumBlackShop);
    }

    
    
}
void MarketLayer::addEventListener()//添加监听
{
    addUserMsg(CUSTOM_MARKER_CTEATTENITEM, CC_CALLBACK_1(MarketLayer::oncreateTenItemMsg, this));
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(MarketLayer::onRefreshDot, this));
}
void MarketLayer::removeEventListener()//清除监听
{
    BaseLayer::removeEventListener();
}
