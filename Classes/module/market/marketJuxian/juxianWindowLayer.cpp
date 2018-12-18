//
//  juxianWindowLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#include "juxianWindowLayer.h"
#include "../../../common/TouchSprite/Button.h"

#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/market/juxian/juxianTimeMSg/JuxianTimeMsg.h"
#include "../marketData/JuxianListDataManager.h"
#include "../../../commonData/enum/DictRolePropEnum.h"
juxianWindowLayer::juxianWindowLayer()
:m_type(1)
,m_ownGold(100)
,m_idx(1)
,TAG_MILITARY(10)
{
    
}
juxianWindowLayer::~juxianWindowLayer()
{
    log("~StageLayer ~StageLayer");
}
bool juxianWindowLayer::init( int tpye, int idx)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_type = tpye;
        m_idx = idx;
        this->setBackground(IMG_DIALOG_BG,Point::ZERO,true);
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        setButton();
        setjuxianType(tpye);
        bref = true;
    } while (false);
    return bref;
}
juxianWindowLayer* juxianWindowLayer::create(int tpye, int idx)
{
    juxianWindowLayer* layer= new juxianWindowLayer();
    if(layer && layer->init(tpye, idx))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void juxianWindowLayer::show(int tpye, int idx)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    juxianWindowLayer* layer = juxianWindowLayer::create(tpye, idx);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void juxianWindowLayer::setButton()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    
    Sprite* buyWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_ORANGE);
    buyWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(buyWord);
    buyWord->setPosition(this->getContentSize().width/2-buyWord->getContentSize().width/2+100*sx ,50*sx);
    this->addChild(buyWord,3);
    Button * surebuy = Button::create(IMG_BUTTON_CONFIRM_LABEL, IMG_BUTTON_CONFIRM_LABEL, CC_CALLBACK_1(juxianWindowLayer::onSureBuyClick, this));
    surebuy->setAnchorPoint(Point::ZERO);
    surebuy->setPosition(Point::ZERO);
    buyWord->addChild(surebuy,2);
    int count = NULL;
    if (m_idx == 1) {
        count = JuxianListDataManager::getInstance()->juxianList->at(m_type-1)->oneConVal;
    }else{
        count = JuxianListDataManager::getInstance()->juxianList->at(m_type-1)->tenConVal;
    }
    string militaryStr = StringUtils::format("%d",count);
    militaryStr = "花费:   " + militaryStr;
    Label* militaryLabel = PublicShowUI::getLabel(militaryStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
    militaryLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(militaryLabel);
    militaryLabel->setPosition(this->getContentSize().width/2-militaryLabel->getContentSize().width/2 ,150*sx);
    this->addChild(militaryLabel,2,TAG_MILITARY);
    
    
    Sprite* cancelWord = Sprite::create(IMG_PUBLIC_BUTTON_TWO_RED);
    cancelWord->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(cancelWord);
    cancelWord->setPosition(this->getContentSize().width/2-cancelWord->getContentSize().width/2-100*sx ,50*sx);
    this->addChild(cancelWord,3);
    Button * cancel = Button::create(IMG_BUTTON_CANCEL_LABEL, IMG_BUTTON_CANCEL_LABEL, CC_CALLBACK_1(juxianWindowLayer::onCencelClick, this));
    cancel->setAnchorPoint(Point::ZERO);
    cancel->setPosition(Point::ZERO);
    cancelWord->addChild(cancel,2);

    setOrderCard(JuxianListDataManager::getInstance()->juxianList->at(m_type-1));
}

void juxianWindowLayer::setjuxianType(int type)
{
    if (type == 1) {
        setqiuxianruoke();
    }else if(type == 2){
        setlixianxiashi();
    }else if (type == 3){
        setweocaishiju();
    }
}
void juxianWindowLayer::setqiuxianruoke()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* lxxsSpr = Sprite::create(IMG_MARKET_MARKETJUXIAN_QIUXIANRUOKE);
    lxxsSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lxxsSpr);
    lxxsSpr->setScale(1.5*sx);
    lxxsSpr->setPosition(this->getContentSize().width/2-lxxsSpr->getContentSize().width/2-15,230*sx);
    this->addChild(lxxsSpr,5);
}
void juxianWindowLayer::setlixianxiashi()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* lxxsSpr = Sprite::create(IMG_MARKET_MARKETJUXIAN_LIXIANXIASHI);
    lxxsSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lxxsSpr);
    lxxsSpr->setScale(1.5*sx);
    lxxsSpr->setPosition(this->getContentSize().width/2-lxxsSpr->getContentSize().width/2-15,230*sx);
    this->addChild(lxxsSpr,2);
}
void juxianWindowLayer::setweocaishiju()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* lxxsSpr = Sprite::create(IMG_MARKET_MARKETJUXIAN_WEICAISHIJU);
    lxxsSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(lxxsSpr);
    lxxsSpr->setScale(1.5*sx);
    lxxsSpr->setPosition(this->getContentSize().width/2-lxxsSpr->getContentSize().width/2-15,230*sx);
    this->addChild(lxxsSpr,5);
}
void juxianWindowLayer::setOrderCard(JuxianListData* data)
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* gold = NULL;
    gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    
    if(data->ConId == DictRolePropEnumGold)
    {
        gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
        gold->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(gold);
        gold->setScale(0.6*sx);
        Label* militaryLabel =(Label*)this->getChildByTag(TAG_MILITARY);
        gold->setPosition(militaryLabel->getPositionX()+militaryLabel->getContentSize().width+10*sx,militaryLabel->getPositionY()-gold->getContentSize().height/2+militaryLabel->getContentSize().height/2+10*sx);
        this->addChild(gold,2);
    }
    else if(data->ConId == DictRolePropEnumHonor)
    {
        gold = Sprite::create(IMG_ICON_JUNGONG);
        gold->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(gold);
        gold->setScale(0.6*sx);
        Label* militaryLabel =(Label*)this->getChildByTag(TAG_MILITARY);
        gold->setPosition(militaryLabel->getPositionX()+militaryLabel->getContentSize().width+10*sx,militaryLabel->getPositionY()-gold->getContentSize().height/2+militaryLabel->getContentSize().height/2+20*sx);
        this->addChild(gold,2);
    }else if (data->ConId == DictRolePropEnumCoin)
    {
        gold = Sprite::create(IMG_ICON_PUBLIC_COIN);
        gold->setAnchorPoint(Point::ZERO);
        PublicShowUI::setTargetScale(gold);
        Label* militaryLabel =(Label*)this->getChildByTag(TAG_MILITARY);
        gold->setPosition(militaryLabel->getPositionX()+militaryLabel->getContentSize().width+10*sx,militaryLabel->getPositionY()-gold->getContentSize().height/2+militaryLabel->getContentSize().height/2);
        this->addChild(gold,2);
    }else{
        log("类型错误%d",data->ConId);
    }
    
}

void juxianWindowLayer::onSureBuyClick(Ref* psender)
{
    log("chongzhi");
    requesttimesMsg(m_type, m_idx);
    this->removeFromParent();
}

void juxianWindowLayer::onCencelClick(Ref* psender)
{
    this->removeFromParent();
}
void juxianWindowLayer::onEnter()
{
    BaseLayer::onEnter();
}
void juxianWindowLayer::onExit()
{
    BaseLayer::onExit();
}
void juxianWindowLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void juxianWindowLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void juxianWindowLayer::requesttimesMsg(int leadId, int countMode)//发送举贤次数消息
{
    JuxianTimeMsg* msg = new JuxianTimeMsg(leadId,countMode);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

