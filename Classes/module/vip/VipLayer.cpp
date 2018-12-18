//
//  VipLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/8.
//
//

#include "VipLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/Protocal.h"
#include "blackShop/VipBlackShopLayer.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "libao/VipLibaoLayer.h"
#include "tequan/VipTequanLayer.h"
#include "../../sdk/SdkManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/recharge/RequestRechargePage.h"
#include "../../commonData/dictData/DictVip/DictVipManager.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../dot/RefreshDot.h"
VipLayer::VipLayer()
:m_tagLayer(0)
,TAG_NAMEBG(20)
,TAG_BLACKSHOPBG(21)
,TAG_RECHARGEBG(22)
,TAG_LIBAOBG(23)
,TAG_VIPNODE(24)
,TAG_MODULE(25)
,TAG_SELECTED(26)
,TAG_MODULELABEL(27)
,TAG_COMBOBOX(100)
,m_selected(NULL)
,m_curVipExp(0)
,m_totalVipTotal(0)
,TAG_NODEBUTTON(28)
{
     btnList=new Vector<Button*>();
    cardList = new Vector<CardData*>();
    m_chargetstatesdata = new Vector<ChargeStatusData*>();
}
VipLayer::~VipLayer()
{
    btnList->clear();
    CC_SAFE_DELETE(btnList);
    btnList = NULL;
    CC_SAFE_DELETE(cardList);
    cardList = NULL;
    CC_SAFE_DELETE(m_chargetstatesdata);
    m_chargetstatesdata = NULL;
}

bool VipLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->setBackBtn(0,15*GlobalInfo::getInstance()->screenScaleX,true);
        setbackGround();
        setUserWealth();
        setheroPos();
        
        bref = true;
    } while (false);
    return bref;
    
}
VipLayer* VipLayer::create()
{
    VipLayer* layer = new VipLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void VipLayer::show(int fromScene,int openLayer)
{
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    VipLayer* layer = VipLayer::create();
    layer->setFromScene(fromScene);
    layer->setInitOpenLayer(openLayer);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();//
    scene->addChild(layer,0,SCENE_TAG_MARKET);
    
    Director::getInstance()->replaceScene(scene);
}
void VipLayer::onEnter()
{
    BaseLayer::onEnter();
}

void VipLayer::onExit()
{
    BaseLayer::onExit();
}
void VipLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->combobox();
  
}
void VipLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->removeEventListener();
  
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumRechargeTag);
}

void VipLayer::setbackGround()
{
//    Sprite* bgSpr = Sprite::create(IMG_VIP_RECHARGEBG);
//    PublicShowUI::setTargetScale(bgSpr,true);
//    bgSpr->setAnchorPoint(Point::ZERO);
//    bgSpr->setPosition(Point::ZERO);
//    this->addChild(bgSpr,-4);
}
void VipLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::BELONG);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,10,TAG_NAMEBG);
   
    layer->setTitle(IMG_PUBLIC_VIP);
}
void VipLayer::setInitOpenLayer(int layerTag)
{
    if(this->m_tagLayer == layerTag)
    {
        return;
    }
    if(m_tagLayer)
    {
        this->removeChildByTag(m_tagLayer);
    }
    
    if(this->getChildByTag(TAG_BLACKSHOPBG))
    {
        this->removeChildByTag(TAG_BLACKSHOPBG);
    }
    if(this->getChildByTag(TAG_RECHARGEBG))
    {
        this->removeChildByTag(TAG_RECHARGEBG);
    }
    if(this->getChildByTag(TAG_LIBAOBG))
    {
        this->removeChildByTag(TAG_LIBAOBG);
    }
    if (this->getChildByTag(TAG_VIPNODE)) {
        this->removeChildByTag(TAG_VIPNODE);
    }
    
    this->m_tagLayer = layerTag;
    switch (m_tagLayer)
    {
        case TAG_BLACKSHOP:
            addbBlackshopLayer();
            break;
        case TAG_LIBAO:
            addLibaoLayer();
            break;
        case TAG_RECHARGE:
        {
            Sprite* bgSpr = Sprite::create(IMG_VIP_RECHARGEBG);
            bgSpr->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(bgSpr,true);
            bgSpr->setPosition(Point::ZERO);
            
            this->addChild(bgSpr,0,TAG_RECHARGEBG);
           
            requestRechargePageMsg();
        }
            break;
        default:
            log("参数错误");
            break;
    }
}
void VipLayer::combobox()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* node=Node::create();
    node->setAnchorPoint(Point::ZERO);
    int index = 0;
    int functionList[3] = {DictFunctionEnumBlackShop,DictFunctionEnumGift,DictFunctionEnumVip};
    for (int i=0; i<3; i++) {
        if (!FunctionOpenManager::getInstance()->functionIsOpened(functionList[i]))
        {
            continue;
        }
        
        Button* cell=Button::create(IMG_SIGNIN_COMBOBOX_BG,IMG_SIGNIN_COMBOBOX_BG,CC_CALLBACK_1(VipLayer::onComboBoxBtnClick, this));
        cell->setAnchorPoint(Point::ZERO);
        PublicShowUI::setDot(cell, Point(10,10), false,functionList[i]);
        PublicShowUI::setTargetScale(cell);
        cell->setScale(0.8*sx);
        cell->setOpacity(150);
        cell->setPosition(0,index*(cell->getContentSize().height+5));
        node->addChild(cell,1,i);//getChildByTag
        
        Sprite* touchBg=Sprite::create(IMG_SIGNIN_COMBOBOX_SELECTED);
        touchBg->setAnchorPoint(Point::ZERO);
        touchBg->setPosition((cell->getContentSize().width/sx-touchBg->getContentSize().width)/2,(cell->getContentSize().height/sx-touchBg->getContentSize().height)/2);
        touchBg->setVisible(false);
        cell->addChild(touchBg,3,TAG_SELECTED);
        
        string resource=PublicShowUI::numberToString(i+1);
        const char* path = PublicShowUI::getResImgPath(IMG_VIP_BTN,resource.c_str());
        Sprite* module=Sprite::create(path);
        module->setAnchorPoint(Point::ZERO);
        module->setOpacity(150);
        module->setPosition(((cell->getContentSize().width/sx-module->getContentSize().width)/2),(cell->getContentSize().height/sx-module->getContentSize().height));
        cell->addChild(module,2,TAG_MODULE);
        
        path=PublicShowUI::getResImgPath(IMG_VIP_BTNWORD, resource.c_str());
        Sprite* moduleLabel=Sprite::create(path);
        moduleLabel->setAnchorPoint(Point::ZERO);
        moduleLabel->setOpacity(150);
        moduleLabel->setPosition(((cell->getContentSize().width/sx-moduleLabel->getContentSize().width)/2),0);
        cell->addChild(moduleLabel,2,TAG_MODULELABEL);
        btnList->pushBack(cell);
        index ++ ;
    }
    if (btnList->size()>0) {
        Button* btn=(Button*)btnList->at(0);
        
        GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumRechargeTag, node->getChildByTag(2));
        Size cellSize = btn->getContentSize();
        cellSize.height=(cellSize.height+5)*btnList->size();
        node->setContentSize(cellSize);
        log("%f",cellSize.height);
        node->setPosition(VisibleRect::right().x-node->getContentSize().width-18*sx,VisibleRect::center().y - node->getContentSize().height/2 );
        log("%f",VisibleRect::center().y - node->getContentSize().height/2);
        this->addChild(node,10,TAG_NODEBUTTON);
        if (m_tagLayer == TAG_BLACKSHOP)//黑市
        {
            onBtnClick(node->getChildByTag(0));
        }
        else if (m_tagLayer == TAG_LIBAO)//礼包
        {
            onBtnClick(node->getChildByTag(1));
        }
        else if (m_tagLayer == TAG_RECHARGE)//充值
        {
            onBtnClick(node->getChildByTag(2));
        }
        NewPlayerGuild::getInstance()->showNowGuide();
    }
}
void VipLayer::onBtnClick(Ref* psender)
{
//    if (m_selected) {
//        m_selected->setOpacity(100);
//        Sprite* module=(Sprite*)m_selected->getChildByTag(TAG_MODULE);
//        if (module) {
//            module->setOpacity(100);
//        }
//        
//        Sprite* moduleLabel=(Sprite*)m_selected->getChildByTag(TAG_MODULELABEL);
//        if (moduleLabel) {
//            moduleLabel->setOpacity(100);
//        }
//        
//        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
//        if (selected) {
//            //            selected->setOpacity(100);
//            selected->setVisible(false);
//        }
//    }
//    m_selected=NULL;
    
    m_selected=(Sprite*)psender;
    if (m_selected)
    {
        m_selected->setOpacity(255);
        Sprite* module=(Sprite*)m_selected->getChildByTag(TAG_MODULE);
        if (module)
        {
            module->setOpacity(255);
        }
        Sprite* moduleLabel=(Sprite*)m_selected->getChildByTag(TAG_MODULELABEL);
        if (moduleLabel)
        {
            moduleLabel->setOpacity(255);
        }
        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
        if (selected)
        {
            selected->setVisible(true);
        }
    }
}

void VipLayer::onComboBoxBtnClick(Ref* psender)
{
    if (m_selected) {
        m_selected->setOpacity(150);
        Sprite* module=(Sprite*)m_selected->getChildByTag(TAG_MODULE);
        if (module) {
            module->setOpacity(150);
        }
        
        Sprite* moduleLabel=(Sprite*)m_selected->getChildByTag(TAG_MODULELABEL);
        if (moduleLabel) {
            moduleLabel->setOpacity(150);
        }
        
        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
        if (selected) {
            //            selected->setOpacity(100);
            selected->setVisible(false);
        }
    }
    m_selected=NULL;
    m_selected=(Sprite*)psender;
    if (m_selected) {
        m_selected->setOpacity(255);
        Sprite* module=(Sprite*)m_selected->getChildByTag(TAG_MODULE);
        if (module) {
            module->setOpacity(255);
        }
        
        Sprite* moduleLabel=(Sprite*)m_selected->getChildByTag(TAG_MODULELABEL);
        if (moduleLabel) {
            moduleLabel->setOpacity(255);
        }
        
        Sprite* selected=(Sprite*)m_selected->getChildByTag(TAG_SELECTED);
        if (selected) {
            //            selected->setOpacity(255);
            selected->setVisible(true);
        }
    }
    selectLayer(m_selected->getTag());
    DictNewGuide* newguide = NewPlayerGuild::getInstance()->getNowData();
    if(newguide)
    {
        if(newguide->bottomId == DictNewGuideEventEnumRechargeTag)
        {
            NewPlayerGuild::getInstance()->next();
        }
    }
    
}
void VipLayer::selectLayer(int tag)
{
    switch (tag)
    {
            
        case 0:
            setInitOpenLayer(TAG_BLACKSHOP);
            break;
        case 1:
            setInitOpenLayer(TAG_LIBAO);
            break;
        case 2:
            setInitOpenLayer(TAG_RECHARGE);
            break;
            
        default:
            break;
    }

}
void VipLayer::addRechargeLayer()
{
    log("chongzhi");
    

    RechargeLayer* rechargelayer = (RechargeLayer*)this->getChildByTag(TAG_RECHARGE);
    if(rechargelayer)
    {
        rechargelayer->removeFromParent();
      
    }

    float sx = GlobalInfo::getInstance()->screenScaleX;

    rechargelayer = RechargeLayer::create(m_chargetstatesdata);
    if(cardList->size())
    {
        rechargelayer->setYuekaCard(cardList);
    }
    rechargelayer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(rechargelayer);
    rechargelayer->setPositionX(VisibleRect::center().x-rechargelayer->getContentSize().width/2+80*sx);
    rechargelayer->setPositionY(VisibleRect::center().y - rechargelayer->getContentSize().height/2 +70*sx);
    this->addChild(rechargelayer, 4,TAG_RECHARGE);

    
    
}
void VipLayer::addbBlackshopLayer()
{
    log("heishi");
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumBlackShop))
    {
        FunctionOpenManager::getInstance()->showNoOpenNotice();
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* bgSpr = Sprite::create(IMG_MARKET_SHOPBG);
    bgSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,5,TAG_BLACKSHOPBG);
    
    VipBlackShopLayer* shoplayer = VipBlackShopLayer::create();
    shoplayer->setAnchorPoint(Point::ZERO);
    shoplayer->setPositionX(VisibleRect::center().x-shoplayer->getContentSize().width/2-80*sx);
    shoplayer->setPositionY(VisibleRect::center().y - shoplayer->getContentSize().height/2 -40*sx);
    this->addChild(shoplayer, 6,TAG_BLACKSHOP);
}
void VipLayer::addLibaoLayer()
{
    log("libao");
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* bgSpr = Sprite::create(IMG_VIP_RECHARGEBG);
    bgSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bgSpr,true);
    bgSpr->setPosition(Point::ZERO);
    this->addChild(bgSpr,0,TAG_LIBAOBG);
    
    VipLibaoLayer* libaolayer = VipLibaoLayer::create();
    libaolayer->setAnchorPoint(Point::ZERO);
    libaolayer->setPositionX(VisibleRect::center().x-libaolayer->getContentSize().width/2+80*sx);
    libaolayer->setPositionY(VisibleRect::center().y - libaolayer->getContentSize().height/2 - 50*sx);
    this->addChild(libaolayer, 2,TAG_LIBAO);
}

void VipLayer::setheroPos()
{
    Sprite* heroSpr = Sprite::create(IMG_VIP_HUMANPIC);
    heroSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(heroSpr);
    heroSpr->setPosition(Point::ZERO);
    this->addChild(heroSpr,3);
}
void VipLayer::setVipLevel()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;

    if (this->getChildByTag(TAG_VIPNODE)) {
        this->removeChildByTag(TAG_VIPNODE);
    }
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    
    Sprite* vipSpr = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
    vipSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(vipSpr);
    vipSpr->setPosition(10*sx,VisibleRect::leftTop().y-130*sx);
    node->addChild(vipSpr,3);
    //当前vip等级
    int viplevel = GlobalInfo::getInstance()->vipLevel;
    string viplevelstr=StringUtils::format("%d",viplevel);
    Label* viplevelLabel = PublicShowUI::getLabel(viplevelstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),36,false,false);
    viplevelLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(viplevelLabel);
    viplevelLabel->setPosition(vipSpr->getPositionX()+vipSpr->getContentSize().width, vipSpr->getPositionY());
    node->addChild(viplevelLabel,4);
    //进度条
    
    
    int nowlevelexp = GlobalInfo::getInstance()->vipExp; //287;//当前经验
    int alllevelexp  = 0;//升VIP所需总经验
    if (viplevel == 15) {
        alllevelexp = DictVipManager::getInstance()->getData(viplevel)->totalChargeGold;
    }else{
        alllevelexp = DictVipManager::getInstance()->getData(viplevel+1)->totalChargeGold;//升VIP所需总经验
    }
    
    Sprite* downProSpr = Sprite::create(IMG_VIP_RECHARGE_VIPDOWNPROGRESS);
    downProSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(downProSpr);
    downProSpr->setPosition(viplevelLabel->getPositionX()+viplevelLabel->getContentSize().width+10*sx,viplevelLabel->getPositionY()+10*sx);
    node->addChild(downProSpr,3);
    
    Sprite* progress = Sprite::create(IMG_VIP_RECHARGE_VIPPROGRESS);
    progress->setAnchorPoint(Point::ZERO);
    ProgressTimer* progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point::ZERO);
    progressTimer->setPosition(Point::ZERO);
    progressTimer->setPercentage(nowlevelexp*100/alllevelexp);
    downProSpr->addChild(progressTimer);
    
    string expstr=StringUtils::format("%d/%d",nowlevelexp,alllevelexp);
    Label* expLabel = PublicShowUI::getLabel(expstr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),16,false,false);
    expLabel->setAnchorPoint(Point(Point::ZERO));
    PublicShowUI::setTargetScale(expLabel);
    expLabel->setPosition(downProSpr->getPositionX()+30*sx, downProSpr->getPositionY());
    node->addChild(expLabel,4);
    //特权
    Button* tequanbtn = Button::create(IMG_VIP_RECHARGE_TEQUANBEN, "", CC_CALLBACK_1(VipLayer::onTequanCleck, this));
    tequanbtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(tequanbtn);
    tequanbtn->setPosition(10*sx, vipSpr->getPositionY()-tequanbtn->getContentSize().height-50*sx);
    node->addChild(tequanbtn,2,0);
    if (viplevel<15) {
        //下一个VIP需要多少vip经验
        Sprite* viplevelSpr = Sprite::create(IMG_VIP_RECHARGE_VIPLEVEL);
        viplevelSpr->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(viplevelSpr);
        viplevelSpr->setPosition(vipSpr->getPositionX(),vipSpr->getPositionY()-viplevelSpr->getContentSize().height-10*sx);
        node->addChild(viplevelSpr,3);
    
        //升级vip所需要的经验
        string goldlstr=StringUtils::format("%d",alllevelexp-nowlevelexp);
        Label* goldLabel = PublicShowUI::getLabel(goldlstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),18,false,false);
        goldLabel->setAnchorPoint(Point(Point::ZERO));
        PublicShowUI::setTargetScale(goldLabel);
        goldLabel->setPosition(viplevelSpr->getPositionX()+50*sx, viplevelSpr->getPositionY());
        node->addChild(goldLabel,4);
        //缩小的vip
        Sprite* littlevip = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
        littlevip->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(littlevip);
        littlevip->setScale(0.6*sx);
        littlevip->setPosition(viplevelSpr->getPositionX()+viplevelSpr->getContentSize().width,viplevelSpr->getPositionY());
        node->addChild(littlevip,3);
        //下一个等级
        string nextlevelstr=StringUtils::format("%d",viplevel+1);
        Label* nextlevelLabel = PublicShowUI::getLabel(nextlevelstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),26,false,false);
        nextlevelLabel->setAnchorPoint(Point(Point::ZERO));
        PublicShowUI::setTargetScale(nextlevelLabel);
        nextlevelLabel->setPosition(littlevip->getPositionX()+littlevip->getContentSize().width-35*sx, viplevelSpr->getPositionY()-4*sx);
        node->addChild(nextlevelLabel,4);
    }else{
        
    }
    this->addChild(node,4,TAG_VIPNODE);

    //其他特权
    Button* othertequanbtn = Button::create(IMG_VIP_RECHARGE_OTHERBTN, "", CC_CALLBACK_1(VipLayer::onTequanCleck, this));
    othertequanbtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(othertequanbtn);
    othertequanbtn->setPosition(10*sx, 10*sx);
    node->addChild(othertequanbtn,2,1);
    othertequanbtn->setVisible(false);
    
}
void VipLayer::onTequanCleck(Ref* psender)
{
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case 0:
            VipTequanLayer::show(GlobalInfo::getInstance()->vipLevel);
            break;
        case 1:
            SdkManager::getInstance()->requestChargeOrder(kRecharge_type_other,0,0,10);
            break;
        default:
            break;
    }
}

void VipLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_PAY_PayPageResp).c_str(), CC_CALLBACK_1(VipLayer::onMsgProcess, this));
    addUserMsg(CUSTOM_REFRESH_DOT, CC_CALLBACK_1(VipLayer::onRefreshDot, this));
}
void VipLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void VipLayer::requestRechargePageMsg()//请求vip充值消息协议
{
    Dialog::showServerLoading();
    RequestRechargePage* msg = new RequestRechargePage();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void VipLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
  
    if(msg->messageID == SCENSE_CLIENT_PAY_PayPageResp)
    {
        CardData* data = NULL;
        cardList->clear();
        int len = msg->byteStream->get();
        for(int i = 0; i < len; i++)
        {
            data = new CardData();
            data->autorelease();
            data->cardID = msg->byteStream->getByte();
            data->status = msg->byteStream->getByte();
//            data->startDate = msg->byteStream->getUTF8();
//            data->endDate = msg->byteStream->getUTF8();
            data->leftDays = msg->byteStream->getByte();
            cardList->pushBack(data);
        }
        
        ChargeStatusData* statusData = NULL;
        m_chargetstatesdata->clear();
        len = msg->byteStream->get();//充值包数量, 与DictChargeCost中定义数量相同
        for(int i = 0; i < len; i++)
        {
            statusData = new ChargeStatusData();
            statusData->autorelease();
            statusData->chargetCostID = msg->byteStream->get();
            statusData->status = msg->byteStream->get();
            m_chargetstatesdata ->pushBack(statusData);
        }
        m_curVipExp = msg->byteStream->getInt();
        m_totalVipTotal = msg->byteStream->getInt();
        GlobalInfo::getInstance()->vipLevel = msg->byteStream->getInt();
        setVipLevel();
        addRechargeLayer();
    }
}
void VipLayer::onRefreshDot(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    if(!inter)
    {
        return;
    }
    int tag_index = inter->getValue();

    if (tag_index == DictFunctionEnumGift)
    {
        Button* btn = (Button*)this->getChildByTag(TAG_NODEBUTTON)->getChildByTag(1);
        RefreshDot::getInstance()->requestMsg(btn,Point(10,10),false,DictFunctionEnumGift);
    }else if (tag_index == DictFunctionEnumBlackShop)
    {
        Button* btn = (Button*)this->getChildByTag(TAG_NODEBUTTON)->getChildByTag(0);
        RefreshDot::getInstance()->requestMsg(btn,Point(10,10),false,DictFunctionEnumBlackShop);
    }
}
