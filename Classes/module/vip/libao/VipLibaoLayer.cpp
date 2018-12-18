//
//  VipLibaoLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/12.
//
//

#include "VipLibaoLayer.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/TouchSprite/Button.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../protocol/Protocal.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../common/Dialog/Dialog.h"

#include "../../../net/NetworkDataProcessing.h"
#include "../../../message/Decoding/vip/gilt/RequestGiltMsg.h"
#include "../vipdata/VipGiftManager.h"
#include "ViplibaoBuyLayer.h"
#include "VipHeadGiftLayer.h"
VipLibaoLayer::VipLibaoLayer()
:listBg(NULL)
,_tableView(NULL)
,TAG_TABLEVIEW(10)

{
    
}

VipLibaoLayer::~ VipLibaoLayer()
{

}

bool VipLibaoLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = false;
        setBackGround();
        
        bref = true;
    } while (false);
    return bref;
}

VipLibaoLayer* VipLibaoLayer::create()
{
    VipLibaoLayer* list = new VipLibaoLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void VipLibaoLayer::onEnter()
{
    BaseLayer::onEnter();
}
void VipLibaoLayer::onExit()
{
    BaseLayer::onExit();
}
void VipLibaoLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestGiltListMsg();
   
}
void VipLibaoLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
   
}

void VipLibaoLayer::setBackGround()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_VIP_LIBAO_LIBAOBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,5);
    this->setContentSize(listBg->getContentSize());
    
}

void VipLibaoLayer::createTableView()
{
    if(_tableView)
    {
//        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
//        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+75;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(15,103);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* VipLibaoLayer::singleList(ssize_t idx)
{
    Sprite*layerBg = Sprite::create(IMG_VIP_LIBAO_CELLLIBAOBG);
    layerBg->setAnchorPoint(Point::ZERO);
    if(idx >= VipGiftManager::getInstance()->giftList->size())
    {
        return NULL;
    }
    VipGiltData* data = VipGiftManager::getInstance()->giftList->at(idx);

//    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
//    UserEquipLayer* head = UserEquipLayer::create(resource,data->quality,false);
//    head->setAnchorPoint(Point::ZERO);
//    head->setTag(idx);
//    head->setPosition(20,20);
//    layerBg->addChild(head,1);
    
    TouchSprite* head = TouchSprite::createWithPic(IMG_VIP_LIBAO_GIFTHEAD,this,callfuncN_selector(VipLibaoLayer::onHeadClick));
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(15,15);
    layerBg->addChild(head,2,idx);
    //折扣价
    Sprite* zhekouSpr = Sprite::create(IMG_VIP_LIBAO_ZHEKOUJIAWORD);
    zhekouSpr->setAnchorPoint(Point::ZERO);
    zhekouSpr->setPosition(230,118);
    layerBg->addChild(zhekouSpr);
    //元宝
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.6);
    gold->setPosition(zhekouSpr->getPositionX()+zhekouSpr->getContentSize().width, zhekouSpr->getPositionY()-4);
    layerBg->addChild(gold);
    //折扣价钱
    string nameWord1=StringUtils::format("%d",data->costCheap);
    Label* nameLabel1 = PublicShowUI::getLabel(nameWord1.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    nameLabel1->setAnchorPoint(Point(Point::ZERO));
    nameLabel1->setPosition(gold->getPositionX()+gold->getContentSize().width-20, zhekouSpr->getPositionY()-2);
    layerBg->addChild(nameLabel1);

    //原价
    Sprite* yuanjiaSpr = Sprite::create(IMG_VIP_LIBAO_YUANJIA);
    yuanjiaSpr->setAnchorPoint(Point::ZERO);
    yuanjiaSpr->setPosition(nameLabel1->getPositionX()+nameLabel1->getContentSize().width+5, zhekouSpr->getPositionY());
    layerBg->addChild(yuanjiaSpr);
    Sprite* line = Sprite::create(IMG_VIP_LIBAO_LINE);
    line->setAnchorPoint(Point::ZERO);
    line->setPosition(yuanjiaSpr->getPositionX(), zhekouSpr->getPositionY()+2);
    layerBg->addChild(line,5);
    //元宝
    Sprite* gold1 = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold1->setAnchorPoint(Point::ZERO);
    gold1->setScale(0.6);
    gold1->setPosition(yuanjiaSpr->getPositionX()+yuanjiaSpr->getContentSize().width-10, zhekouSpr->getPositionY()-4);
    layerBg->addChild(gold1);
    //原价钱
    string yuanjiastr=StringUtils::format("%d",data->cost);
    Label* yuanjiaLabel = PublicShowUI::getLabel(yuanjiastr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    yuanjiaLabel->setAnchorPoint(Point(Point::ZERO));
    yuanjiaLabel->setPosition(gold1->getPositionX()+gold1->getContentSize().width-20, zhekouSpr->getPositionY()-2);
    layerBg->addChild(yuanjiaLabel);
    
    //VIP
    Sprite* vipSpr = Sprite::create(IMG_VIP_RECHARGE_VIPBG);
    vipSpr->setAnchorPoint(Point::ZERO);
    vipSpr->setPosition(140,70);
    layerBg->addChild(vipSpr);

    string vipstr=StringUtils::format("%d",data->vipLevel);
    Label* vipLabel = PublicShowUI::getLabel(vipstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),36,false,false);
    vipLabel->setAnchorPoint(Point(Point::ZERO));
    vipLabel->setPosition(vipSpr->getPositionX()+vipSpr->getContentSize().width, vipSpr->getPositionY());
    layerBg->addChild(vipLabel);
    
    
    Sprite* chaozhiSpr = Sprite::create(IMG_VIP_LIBAO_LIBAOWORD);
    chaozhiSpr->setAnchorPoint(Point::ZERO);
    chaozhiSpr->setPosition(vipSpr->getPositionX()+vipSpr->getContentSize().width+40,vipSpr->getPositionY());
    layerBg->addChild(chaozhiSpr);
    
    string desstr=data->desc;
    Label* desLabel = PublicShowUI::getLabel(desstr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_BLUE),16,false,false);
    desLabel->setMaxLineWidth(240);
    desLabel->setAnchorPoint(Point(0,1));
    desLabel->setPosition(vipSpr->getPositionX()+10,65);
    layerBg->addChild(desLabel);
    
    //购买按钮
    Button* buyBg = Button::create(IMG_BUTTON_REDBTN,IMG_BUTTON_REDBTN,CC_CALLBACK_1(VipLibaoLayer::onClick, this));
    buyBg->setAnchorPoint(Point::ZERO);
    buyBg->setPosition(420,15);
    layerBg->addChild(buyBg,1,idx);
    Sprite* beginxunfangSpr=Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
    beginxunfangSpr->setAnchorPoint(Point::ZERO);
    beginxunfangSpr->setPosition(Point::ZERO);
    buyBg->addChild(beginxunfangSpr,4);
    if (data->state==2) {
        buyBg->setEnabled(false);
        buyBg->setVisible(false);
        string buystr="VIP等级不够";
        
        Label* buyLabel = PublicShowUI::getLabel(buystr.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_BROWN),20,false,false);
        buyLabel->setAnchorPoint(Point(Point::ZERO));
        buyLabel->setPosition(chaozhiSpr->getPositionX()+chaozhiSpr->getContentSize().width+5, vipSpr->getPositionY());
        layerBg->addChild(buyLabel);
    }else if (data->state == 3)
    {
        buyBg->setEnabled(false);
        buyBg->setVisible(false);
        string buystr="已购买";
        Label* buyLabel = PublicShowUI::getLabel(buystr.c_str(),PublicShowUI::getColor3b(COLOR_DEEP_BROWN),20,false,false);
        buyLabel->setAnchorPoint(Point(Point::ZERO));
        buyLabel->setPosition(chaozhiSpr->getPositionX()+chaozhiSpr->getContentSize().width+5, vipSpr->getPositionY());
        layerBg->addChild(buyLabel);
    }
    
    return layerBg;
}
//购买
void VipLibaoLayer::onClick(Ref* psender)
{
    Node* target = (Node*)psender;
    log("%d",target->getTag());
    ViplibaoBuyLayer::show(VipGiftManager::getInstance()->giftList->at(target->getTag())->vipLevel,VipGiftManager::getInstance()->giftList->at(target->getTag())->costCheap);
   
}
void VipLibaoLayer::onHeadClick(Node* pSender)
{
    VipHeadGiftLayer::show(VipGiftManager::getInstance()->giftList->at(pSender->getTag())->vipLevel);
}

TableViewCell* VipLibaoLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Sprite* list=singleList(idx);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size VipLibaoLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_VIP_LIBAO_CELLLIBAOBG);
    cellSize.height = temp->getContentSize().height+6;
    cellSize.width = temp->getContentSize().width ;
    return cellSize;
}
//获取view的长度
ssize_t VipLibaoLayer::numberOfCellsInTableView(TableView *table)
{
    
    ssize_t allPage =VipGiftManager::getInstance()->giftList->size();
    return allPage;
}
//点击cell事件
void VipLibaoLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
}
void VipLibaoLayer::onGiltBuyMsgProcess(EventCustom* msg)
{
    requestGiltListMsg();
}
/******------------------------------------访问服务器------------------------------*************/

void VipLibaoLayer::requestGiltListMsg()//请求列表信息
{
    Dialog::showServerLoading();
    RequestGiltMsg* msg = new RequestGiltMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void VipLibaoLayer::onGiltMsgProcess(EventCustom* msg)//获取列表信息返回值
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    VipGiftManager::getInstance()->cleargiltList();
    if(message->messageID == SCENSE_CLIENT_GIFT_GiftPageResp)
    {
        if(message->state)//返回成功
        {
            
            int giftSize = message->byteStream->getByte();
            for (int i = 0; i < giftSize; i ++) {
                VipGiltData* data = new VipGiltData;
                data->autorelease();
                data->vipLevel = message->byteStream->getByte();
                data->state = message->byteStream->getByte();
                data->desc = message->byteStream->getUTF8();
                data->cost = message->byteStream->getInt();
                data->costCheap = message->byteStream->getInt();
                VipGiftManager::getInstance()->addData(data);
            }
            createTableView();
        }
        
    }
}
void VipLibaoLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_GIFT_GiftPageResp).c_str(), CC_CALLBACK_1(VipLibaoLayer::onGiltMsgProcess, this));
     this->addUserMsg(CUSTOM_VIP_LIBAO_BUY, CC_CALLBACK_1(VipLibaoLayer::onGiltBuyMsgProcess, this));
   
}
void VipLibaoLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

