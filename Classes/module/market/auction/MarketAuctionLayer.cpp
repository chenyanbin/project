//
//  MarketAuctionLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//

#include "MarketAuctionLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../protocol/UserCustomEvent.h"
#include "paimaisuo/MarketAuctionHomeLayer.h"
#include "quchushou/MarketAuctionSellLayer.h"
#include "shangjiazhong/MarketAuctionShangjiaLayer.h"
#include "../../../message/Decoding/market/paimai/paimaiHomeMsg/AuctionHomeMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../newPlayerGuide/NewPlayerGuild.h"
MarketAuctionLayer::MarketAuctionLayer()
:m_layer(1)
,editbox(NULL)
,TAG_LISTBG(2)
,TAG_SERCH(3)
{
    
}

MarketAuctionLayer::~MarketAuctionLayer()
{
    
}

bool MarketAuctionLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
        setPaimaisuo();
        setEditBox();
        bref = true;
    } while (false);
    return bref;
}

MarketAuctionLayer* MarketAuctionLayer::create()
{
    MarketAuctionLayer* list = new MarketAuctionLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MarketAuctionLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MarketAuctionLayer::onExit()
{
    BaseLayer::onExit();
}
void MarketAuctionLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void MarketAuctionLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSearchButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumShelvesButton);
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSellButton);
}

void MarketAuctionLayer::setBackGround()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
//    listBg->setOpacity(0);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1,TAG_LISTBG);
    this->setContentSize(listBg->getContentSize());
    
//    Sprite* listbgbox = Sprite::create(IMG_MARKET_AUCTION_CELLBGBOX);
//    listbgbox->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(listbgbox);
//    listbgbox->setPosition(Point::ZERO);
//    this->addChild(listbgbox,10);
    
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(listBg->getPositionX()+15*sx,listBg->getPositionY()+450*sx);
    this->addChild(listBg2,10);
    
    const char* pathList[3] = {IMG_PUBLIC_LABEL_PAIMAIUSO1,IMG_PUBLIC_LABEL_QUCHUSAO1,IMG_PUBLIC_LABEL_SAHNGJIA1};
    const char* pathList2[3] = {IMG_PUBLIC_LABEL_PAIMAIUSO,IMG_PUBLIC_LABEL_QUCHUSAO,IMG_PUBLIC_LABEL_SAHNGJIA};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(MarketAuctionLayer::onTopComboBoxClick, this));
    for (int i = 0; i<3; i++) {
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList2[i], pathList[i]);
    }
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumShelvesButton, boxBtn->getButtonAt(2));
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSellButton, boxBtn->getButtonAt(1));
    boxBtn->setAnchorPoint(Point::ZERO);
    boxBtn->setPosition(6*sx,(listBg2->getContentSize().height/sx-boxBtn->getContentSize().height)/2+5*sx);
    boxBtn->getButtonAt(0)->selected();
    listBg2->addChild(boxBtn,3);

    
//    const char* pathList[3] = {IMG_MARKET_AUCTION_PAIMAISUO,IMG_MARKET_AUCTION_QUCHUSHOU,IMG_MARKET_AUCTION_SHANGJIAZHONG};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 16, CC_CALLBACK_1(MarketAuctionLayer::onTopComboBoxClick, this));
//    for (int i = 0; i<3; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_COMBOBOX_FRIST1, IMG_PUBLIC_COMBOBOX_FRIST2, pathList[i]);
//    }
//    boxBtn->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(boxBtn);
//    boxBtn->setPosition(10*sx  ,listBg->getContentSize().height);
//    boxBtn->getButtonAt(0)->selected();
//    this->addChild(boxBtn,1);
    
    //所搜按钮
    Button* serch = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE,IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MarketAuctionLayer::onSerchBtn, this));
    serch->setAnchorPoint(Point::ZERO);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSearchButton, serch);
    PublicShowUI::setTargetScale(serch);
    serch->setPosition(listBg->getContentSize().width-serch->getContentSize().width-30*sx,listBg->getPositionY()+475*sx);
    this->addChild(serch,11,TAG_SERCH);
    
    Sprite* serchSpr = Sprite::create(IMG_MARKET_AUCTION_SERCH);
    serchSpr->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(serchSpr);
    serchSpr->setPosition(listBg->getContentSize().width-serchSpr->getContentSize().width-30*sx,listBg->getPositionY()+475*sx);
    this->addChild(serchSpr,15);
}

void MarketAuctionLayer::setEditBox()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    editbox = EditBox::create(Size(224 * sx,39 * sx), Scale9Sprite::create(IMG_MARKET_AUCTION_SERCHBG));
    editbox->setAnchorPoint(Point::ZERO);
    editbox->setPlaceHolder("商品名称");
    editbox->setInputMode(EditBox::InputMode::ANY);
    editbox->setPosition(Point(this->getContentSize().width-editbox->getContentSize().width-135*sx,listBg->getPositionY()+475*sx));
    this->addChild(editbox,11);
}
//搜索
void MarketAuctionLayer::onSerchBtn(Ref* psender)
{
    log("dddd");
    log("%s",editbox->getText());
    broadMsg(CUSTOM_MARKET_SETCH,__String::create(editbox->getText()));
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSearchButton);
//    requestAuctionHomeListMsg(editbox->getText(),0);
}
void MarketAuctionLayer::onTopComboBoxClick(Ref * psender)
{
    Node* target = (Node*)psender;
    int tag = target->getTag();
    switch (tag) {
        case 0:
            if (m_layer != TAG_PAIMAISUO) {
                setPaimaisuo();
                Button* btn = (Button*)this->getChildByTag(TAG_SERCH);
                btn->setEnabled(true);
            }
            break;
        case 1:
            if (m_layer != TAG_QUCHUSHOU) {
                setQuchushou();
                Button* btn = (Button*)this->getChildByTag(TAG_SERCH);
                btn->setEnabled(false);
           
                NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSellButton);
           
               
            }
            break;
        case 2:
            if (m_layer != TAG_SHANGJIAZHONG) {
                setShangjiazhong();
                Button* btn = (Button*)this->getChildByTag(TAG_SERCH);
                btn->setEnabled(false);
          
                NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumShelvesButton);
          
            }
            break;
            
        default:
            break;
    }
}
void MarketAuctionLayer::setPaimaisuo()//拍卖所
{
    this->removeChildByTag(m_layer);
    MarketAuctionHomeLayer* layer = MarketAuctionHomeLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(Point::ZERO);
    this->addChild(layer,3,TAG_PAIMAISUO);
    m_layer = TAG_PAIMAISUO;
}
void MarketAuctionLayer::setQuchushou()//去出售
{
    this->removeChildByTag(m_layer);
    MarketAuctionSellLayer* layer = MarketAuctionSellLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(Point::ZERO);
    this->addChild(layer,3,TAG_QUCHUSHOU);
    m_layer = TAG_QUCHUSHOU;
}
void MarketAuctionLayer::setShangjiazhong()//上架中
{
    this->removeChildByTag(m_layer);
    MarketAuctionShangjiaLayer* layer = MarketAuctionShangjiaLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(Point::ZERO);
    this->addChild(layer,3,TAG_SHANGJIAZHONG);
    m_layer = TAG_SHANGJIAZHONG;
}
void MarketAuctionLayer::requestAuctionHomeListMsg(const char* itemName,int lastSellId)//搜索拍卖所列表信息
{
    Dialog::showServerLoading(.2);
    AuctionHomeMsg* msg = new AuctionHomeMsg(itemName,lastSellId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
