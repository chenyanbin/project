//
//  RechargeLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/10.
//
//

#include "RechargeLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../../sdk/SdkManager.h"
#include "../.././../message/Decoding/recharge/RequestMonthCardMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../iap/GamePayment.h"
#include "../../../message/Decoding/applePay/ApplePayMsg.hpp"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
RechargeLayer::RechargeLayer()
:TAG_CARDLIST(1)
,TAG_CARDTITLE(2)
,chargeCostList(NULL)
,m_isMove(false)
,m_chargestatusList(NULL)
,m_cardList(NULL)
,m_isyueka(false)
,m_index(1)
{

}

RechargeLayer::~ RechargeLayer()
{
    CC_SAFE_DELETE(chargeCostList);
    chargeCostList = NULL;
    m_cardList = NULL;

//    CC_SAFE_DELETE(m_chargestatusList);
//    m_chargestatusList = NULL;
}
bool sortChargetList(DictChargeCost* a,DictChargeCost* b)
{
    return a->id < b->id;
}
bool RechargeLayer::init(Vector<ChargeStatusData*> *chagerstatusdata)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        chargeCostList = DictChargeCostManager::getInstance()->getDataList();
        sort(chargeCostList->begin(),chargeCostList->end(),sortChargetList);
      
         m_chargestatusList = chagerstatusdata;
        bref = true;
    } while (false);
    return bref;
}

RechargeLayer* RechargeLayer::create(Vector<ChargeStatusData*> *chagerstatusdata)
{
    RechargeLayer* list = new RechargeLayer();
    if(list && list->init(chagerstatusdata))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void RechargeLayer::onEnter()
{
    BaseLayer::onEnter();
}
void RechargeLayer::onExit()
{
    BaseLayer::onExit();
}
void RechargeLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();

    this-> setRechargeCard();
    this->setVipLevel();
}
void RechargeLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}

void RechargeLayer::setYuekaCard(Vector<CardData*> *cardList)
{
    if(this->getChildByTag(TAG_CARDLIST))
    {
        this->removeChildByTag(TAG_CARDLIST);
    }
    this->m_cardList = cardList;
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    Button* yuekabg = NULL;
    Sprite* yuekaword = NULL;
    Sprite* yuekamoney = NULL;
    Sprite* yigoumai = NULL;
    ssize_t len = cardList->size();
    DictCardCost* cardCost = NULL;
    CardData* cardData = NULL;
    for(int i = 0; i < len; i++)
    {
        cardData = cardList->at(i);
        cardCost = DictCardCostManager::getInstance()->getData(cardData->cardID);
        if(!cardCost)
        {
            continue;
        }
        const char* path = PublicShowUI::getResImgPath(IMG_VIP_RECHARGE_YUEKABG, PublicShowUI::numberToString(i + 1).c_str());
        yuekabg = Button::create(path, path, CC_CALLBACK_1(RechargeLayer::onyuekaClick, this));
        yuekabg->setAnchorPoint(Point::ZERO);
        yuekabg->setPositionX(i * (yuekabg->getContentSize().width+50));
        container->addChild(yuekabg,1,i + 1);
        if (cardData->status == CardData::STATUS_ABLE_BUY)
        {//没有购买
            
            const char* pathmoney = PublicShowUI::getResImgPath(IMG_VIP_RECHARGE_YUEKABGMONEY, PublicShowUI::numberToString(i + 1).c_str());
            yuekamoney = Sprite::create(pathmoney);
            yuekamoney->setAnchorPoint(Point::ZERO);
            yuekamoney->setPosition(Point::ZERO);
            yuekabg->addChild(yuekamoney,10);
            
            
            const char* pathword = PublicShowUI::getResImgPath(IMG_VIP_RECHARGE_YUEKAWORD, PublicShowUI::numberToString(i + 1).c_str());
            yuekaword = Sprite::create(pathword);
            yuekaword->setAnchorPoint(Point::ZERO);
            yuekaword->setPosition(Point::ZERO);
            yuekabg->addChild(yuekaword,11);
            string str = PublicShowUI::numberToString(cardCost->goldThen) + "元宝";
            Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),30,false,false);
            label->setPosition(yuekabg->getContentSize().width / 2 , yuekabg->getContentSize().height / 2 - 25);
            yuekabg->addChild(label,12);
        }
        else
        {//已购买
            if(cardData->status == CardData::STATUS_TODAY_GETTED)
            {
                Sprite* stateSpr = Sprite::create(IMG_VIP_RECHARGE_TODAY_GETTED);
                stateSpr->setAnchorPoint(Point::ZERO);
                stateSpr->setPosition(3, (yuekabg->getContentSize().height-stateSpr->getContentSize().height)/2);
                yuekabg->addChild(stateSpr,13);
            }
            else if(cardData->status == CardData::STATUS_UNABLE_BUY)
            {
                Sprite* yigoumai = Sprite::create(IMG_VIP_RECHARGE_ABLEGET);
                yigoumai->setAnchorPoint(Point::ZERO);
                yigoumai->setPositionX(3);
                yigoumai->setPositionY(yuekabg->getContentSize().height-yigoumai->getContentSize().height);
                yuekabg->addChild(yigoumai,2);
            }
         
            const char* pathword = PublicShowUI::getResImgPath(IMG_VIP_RECHARGE_JIDEMEIRILINGQUWORD, PublicShowUI::numberToString(i + 1).c_str());
            yuekaword = Sprite::create(pathword);
            yuekaword->setAnchorPoint(Point::ZERO);
            yuekaword->setPosition(Point::ZERO);
            yuekabg->addChild(yuekaword,3);
            
            string str = PublicShowUI::numberToString(cardCost->goldDaily) ;
            Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),25,false,false);
            label->setAnchorPoint(Point::ZERO);
            label->setPosition(40 , yuekaword->getContentSize().height/2 - 3);
            yuekaword->addChild(label,12);
            
            str = PublicShowUI::numberToString(cardData->getLeftDays()) + "天";
            
            Label* dayLabel = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),22,false,false);
            dayLabel->setAnchorPoint(Point::ZERO);
            dayLabel->setPosition(93 ,39);
            yuekaword->addChild(dayLabel,2);
            
        }
       
        
        
    }
    this->addChild(container,1,TAG_CARDLIST);
    Size size = yuekabg->getContentSize();
    size.width = yuekabg->getPositionX() + yuekabg->getContentSize().width;
    container->setContentSize(size);
    this->setContentSize(size);
    
    if(this->getChildByTag(TAG_CARDTITLE) == NULL)
    {
        Sprite* same = Sprite::create(IMG_VIP_RECHARGE_SAMEUSER);
        same->setAnchorPoint(Point::ZERO);
        same->setPosition(this->getContentSize().width/2-same->getContentSize().width/2, this->getContentSize().height+20);
        this->addChild(same,1,TAG_CARDTITLE);
    }
   
}
void RechargeLayer::onyuekaClick(Ref* psender)
{
    Node* target = (Node*)psender;
    int tag = target->getTag();
    CardData* cardData = m_cardList->at(tag - 1);;
    if (cardData->status == CardData::STATUS_ABLE_BUY)
    {
       
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            m_isyueka = true;
            m_index = target->getTag();
            auto b = std::bind(&RechargeLayer::onRequestCallBack, this,std::placeholders::_1,std::placeholders::_2);
            string str = "";
            if (tag == 1) {
                str = "type1";
            }else if(tag == 2)
            {
                str = "type2";
            }
            //商品信息
            GamePayment::getInstance()->req_iap(str, b);
        #endif
                
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            DictCardCost* cost = DictCardCostManager::getInstance()->getData(target->getTag());
            SdkManager::getInstance()->requestChargeOrder(kRecharge_type_monthCard, 0, target->getTag(), cost->price);
                
        #endif
        
    }
    else
    {
        Dialog::showServerLoading(1);
        RequestMonthCardMsg* msg = new RequestMonthCardMsg(cardData->cardID);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg  = NULL;
    }
   
}

void RechargeLayer::setRechargeCard()
{
    Size size = this->cellSizeForTable(NULL);
    size.width *= 3;
    TableView* tableView = TableView::create(this,size);
    tableView->setDelegate(this);
    tableView->setDirection(TableView::Direction::HORIZONTAL);
    tableView->reloadData();
    tableView->setPositionX(-cellSize.width/2 + 5);
    tableView->setPositionY(-cellSize.height - 10);
    tableView->setTouchEnabled(true);
    this->addChild(tableView,1);
    
    Sprite* arrow = Sprite::create(IMG_GENERALSLIST_ARROW);
    arrow->setAnchorPoint(Point::ZERO);
    arrow->setRotation(90);
    arrow->setPosition(tableView->getPositionX() + size.width -10, tableView->getPositionY() + (size.height - arrow->getContentSize().height)/2 + 20);
    this->addChild(arrow,2);
    
    MoveBy* moveby = MoveBy::create(.5, Point(20,0));
    arrow->runAction(RepeatForever::create(Sequence::create(moveby,moveby->reverse(), NULL)));

}
Node* RechargeLayer::getChargeNode(int index)
{
    if (m_chargestatusList->size()<=0) {
        return NULL;
    }
    DictChargeCost* chargeCost = this->chargeCostList->at(index);
    Button * node = NULL;
    const char* buyBtnPath = "";
    Color3B color ;
    if(chargeCost->id == 3)
    {
//        node = TouchSprite::create(IMG_VIP_RECHARGE_SPERECHARGEBG);
       
        node = Button::create(IMG_VIP_RECHARGE_SPERECHARGEBG, IMG_VIP_RECHARGE_SPERECHARGEBG, CC_CALLBACK_1(RechargeLayer::onbuyBtn, this));
        buyBtnPath = IMG_PUBLIC_BUTTON_TWO_ORANGE;
        color = Color3B::RED;
    }
    else
    {
        node = Button::create(IMG_VIP_RECHARGE_PUTONGRECHARGEBG, IMG_VIP_RECHARGE_PUTONGRECHARGEBG, CC_CALLBACK_1(RechargeLayer::onbuyBtn, this));
        Sprite* goldSpr = Sprite::create(IMG_VIP_RECHARGE_GOLD);
        node->addChild(goldSpr,0);
        goldSpr->setPosition(node->getContentSize().width/2, node->getContentSize().height/2);
        buyBtnPath = IMG_PUBLIC_BUTTON_TWO_RED;
        color = PublicShowUI::getColor3b(COLOR_BROWN);
    }
    node->setAnchorPoint(Point::ZERO);
    node->getTouchListener()->setSwallowTouches(false);
    
    //判断是否第一次充值
    
    ChargeStatusData* data =  m_chargestatusList->at(index);
    string str = "";
    if (data->status == 1 ) {//首充
        
        Sprite* firstSpr = Sprite::create(IMG_VIP_RECHARGE_FIRSTRECHARGE);
        node->addChild(firstSpr,20);
        firstSpr->setPosition(node->getContentSize().width/2+55, node->getContentSize().height/2 + firstSpr->getContentSize().height/2 + 75);
        
        Sprite* outSpr = Sprite::create(IMG_VIP_RECHARGE_FIRSTRECHARGEWORD);
        node->addChild(outSpr,10);
        outSpr->setPosition(node->getContentSize().width/2-20, node->getContentSize().height/2 + outSpr->getContentSize().height/2 + 20);
        
        str = PublicShowUI::numberToString(chargeCost->goldFirst) + "元宝";
//        str += PublicShowUI::numberToString(chargeCost->vipExpFirst) + "VIP经验";
        Label* label = PublicShowUI::getLabel(str.c_str(),color,22,false,false);
        label->setPosition(node->getContentSize().width/2+20, node->getContentSize().height/2+15);
        node->addChild(label,11);

    }
    else if(data->status == 2 )//非首充
    {
        Sprite* firstSpr = Sprite::create(IMG_VIP_RECHARGE_ALLGOLD);
        firstSpr->setAnchorPoint(Point::ZERO);
        node->addChild(firstSpr,20);
        firstSpr->setPosition(node->getContentSize().width/2-firstSpr->getContentSize().width/2, node->getContentSize().height/2 - firstSpr->getContentSize().height/2 );
    }
    
    Label* nameLabel1 = PublicShowUI::getLabel(chargeCost->name.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),26,false,false);
    nameLabel1->setAnchorPoint(Point(Point::ZERO));
    nameLabel1->setPosition((node->getContentSize().width-nameLabel1->getContentSize().width)/2,node->getContentSize().height-50);
    node->addChild(nameLabel1,12);
    
   
    Sprite* buyBtn = Sprite::create(buyBtnPath);//, this,callfuncN_selector(RechargeLayer::onbuyBtn)
   
    buyBtn->setPosition(node->getContentSize().width/2, buyBtn->getContentSize().height);
    node->addChild(buyBtn,13);
    str = "￥" + PublicShowUI::numberToString(chargeCost->price);
    Label* nameLabel2 = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),22,false,false);
    nameLabel2->setAnchorPoint(Point(Point::ZERO));
    nameLabel2->setPosition((buyBtn->getContentSize().width - nameLabel2->getContentSize().width)/2,(buyBtn->getContentSize().height - nameLabel2->getContentSize().height)/2);
    buyBtn->addChild(nameLabel2,2);

    
    return node;
}
void RechargeLayer::onbuyBtn(Ref* target)
{
    if(m_isMove)
    {
        return;
    }
    Node* btn = (Node*)target;
    int tag = btn->getTag();
    m_index = tag;
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        m_isyueka = false;
        auto b = std::bind(&RechargeLayer::onRequestCallBack, this,std::placeholders::_1,std::placeholders::_2);
        string str = "";
        if (tag == 0) {
            str = "gold1";
        }
        else if (tag == 1) {
            str = "gold2";
        }
        else if (tag == 2) {
            str = "gold3";
        }
        else if (tag == 3) {
            str = "gold9";
        }
        else if (tag == 4) {
            str = "gold5";
        }
        else if (tag == 5) {
            str = "gold6";
        }
        else if (tag == 6) {
            str = "gold7";
        }
        else if (tag == 7) {
            str = "gold8";
        }
        //商品信息
        GamePayment::getInstance()->req_iap(str, b);
       
    #endif
        
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
         DictChargeCost* chargeCost = chargeCostList->at(tag);
         SdkManager::getInstance()->requestChargeOrder(kRecharge_type_gold, chargeCost->id, 0, chargeCost->price);
        
    #endif
   
}
void RechargeLayer::onRequestCallBack(IOSProduct* product,int code)//回调付款
{
    if(product)
    {
        
//        this->setVisible(false);
        auto b = std::bind(&RechargeLayer::onPayCallBack, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
        //付款
        GamePayment::getInstance()->pay_iap(1, b);
    }
    
}
void RechargeLayer::onPayCallBack(bool isSuc,std::string &identifier, int quantity,std::string &receipt)//付款成功
{
    if (isSuc) {
        
        
        
        
//        rapidjson::Document _doc;
//        _doc.Parse<0>(receipt.c_str());
//        if (_doc.HasParseError())
//        {
//            Dialog::show("登陆json格式错误");
//            return;
//        }
        
        
        if (m_isyueka == false)
        {
            DictChargeCost* chargeCost = chargeCostList->at(m_index);
            
            log("=================================\\\%s",receipt.c_str());
            requestApplePayPageMsg(kRecharge_type_gold,chargeCost->id,0,(chargeCost->price)*100,"apple","apple",receipt,1);
        }else
        {
            DictCardCost* cost = DictCardCostManager::getInstance()->getData(m_index);
            requestApplePayPageMsg(kRecharge_type_monthCard, 0, cost->id, (cost->price)*100,"apple","apple",receipt,1);
        }
    }
//    this->setVisible(true);
}

void RechargeLayer::setVipLevel()
{

}
void RechargeLayer::scrollViewDidScroll(ScrollView* view)
{
 
    m_isMove = view->isDragging();
}
Size RechargeLayer::cellSizeForTable(TableView *table)
{
    if(cellSize.width == 0)
    {
        cellSize = Sprite::create(IMG_VIP_RECHARGE_PUTONGRECHARGEBG)->getContentSize();
        cellSize.width += 10;
    }
    return cellSize;
}
TableViewCell* RechargeLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = this->getChargeNode(idx);
    cell->addChild(node, 0,idx);
    cell->setTag(idx);
    return cell;
}
ssize_t RechargeLayer::numberOfCellsInTableView(TableView *table)
{
    return m_chargestatusList->size();
}
void RechargeLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    m_isMove = false;
}
void RechargeLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
    
}
void RechargeLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
    
}
void RechargeLayer::tableCellWillRecycle(TableView* table, TableViewCell* cell)
{
    
}

/*------------------------------------------------连接服务区---------------------------------------*/

void RechargeLayer::requestApplePayPageMsg(int _charge_type, int _charge_id, int _card_id, int _fee, string _channel_code, string _channel_label, string _ipa_varify_str, int _is_sandbox)
{
    
    Dialog::showServerLoading();
    ApplePayMsg* msg = new ApplePayMsg( _charge_type, _charge_id, _card_id, _fee, _channel_code, _channel_label, _ipa_varify_str, _is_sandbox);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void RechargeLayer::onAppleyapMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    
    if(msg->messageID == ApplePayCreateOrderResp){
        if (msg->state) {
            log("congzhichenggong");
        }
    }
}
void RechargeLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(ApplePayCreateOrderResp).c_str(), CC_CALLBACK_1(RechargeLayer::onAppleyapMsgProcess, this));
    
}
void RechargeLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}