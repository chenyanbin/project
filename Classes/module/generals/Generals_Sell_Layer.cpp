//
//  Generals_Sell_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/3.
//
//

#include "Generals_Sell_Layer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../message/Decoding/generals/experience/ChooseCardMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../message/Decoding/generals/sell/SellEquipMsg.h"
#include "../../message/Decoding/generals/sell/SellEquipPageMsg.h"
#include "../../message/Decoding/generals/sell/SellHeroMsg.h"
#include "../../message/Decoding/generals/sell/SellHeroPageMsg.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/dictData/DictHeroQuality/DictHeroQualityManager.h"
#include "../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
Generals_Sell_Layer::Generals_Sell_Layer()
:sx(1)
,TAG_CONSUME(1)
,TAG_TABLEVIEW(2)
,isDownPoint(Point::ZERO)
,isMoveing(false)
,thisSort("")
{
    cardList=new Vector<CardPropertyData*>();
    selectCardList=new Vector<CardPropertyData*>();
    equipList=new Vector<BaseEquipData*>();
    selectEquipList=new Vector<BaseEquipData*>();
    
}
Generals_Sell_Layer::~Generals_Sell_Layer()
{
    CC_SAFE_DELETE(cardList);
    CC_SAFE_DELETE(equipList);
    CC_SAFE_DELETE(selectCardList);
    CC_SAFE_DELETE(selectEquipList);
}

void Generals_Sell_Layer::onExit()
{
    BaseLayer::onExit();
}
void Generals_Sell_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void Generals_Sell_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumGeneralsHead);
}
void Generals_Sell_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->setClickEnabled(true);
    this->requestListMsg();
}
bool Generals_Sell_Layer::init(int isValue)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        isEquipOrHero=isValue;
        thisSort="quality";
        this->setBackground(IMG_GENERALS_EXPERIENCE_LIST_BG);
        this->setGrayBg();
        this->isClickClose=true;
        this->createLayer();
        
        bref = true;
    } while (false);
    return bref;
}
Generals_Sell_Layer* Generals_Sell_Layer::create(int isValue)
{
    Generals_Sell_Layer* layer = new Generals_Sell_Layer();
    if(layer && layer->init(isValue))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void Generals_Sell_Layer::createLayer()
{
    Sprite* title=Sprite::create(IMG_PUBLIC_LABEL_SELLTITLE);
    title->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(title);
    title->setPosition(46*sx,this->getContentSize().height-title->getContentSize().height-12*sx);
    this->addChild(title);
    

    Sprite* gainLabel=Sprite::create(IMG_PUBLIC_LABEL_GAINCOIN);
    gainLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(gainLabel);
    gainLabel->setPosition(40*sx,32*sx);
    this->addChild(gainLabel);
    //出售
    Button* startBtn=Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(Generals_Sell_Layer::onSellBtn, this));
    PublicShowUI::setTargetScale(startBtn);
    startBtn->setPosition(this->getContentSize().width/2+startBtn->getContentSize().width*1.5+18*sx,startBtn->getContentSize().height/2-4*sx);
    this->addChild(startBtn);
    GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumExperience, startBtn);
    Sprite* startLabel=Sprite::create(IMG_MARKET_AUCTION_SELLWORD);
    startBtn->addChild(startLabel,2);
    
    //消耗
    Sprite* coin=Sprite::create(IMG_ICON_PUBLIC_COIN);
    coin->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(coin);
    coin->setPosition(190*sx,26*sx);
    this->addChild(coin,3);
    
    string coinStr="0";
    Label* coinLabel = PublicShowUI::getLabel(coinStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),20,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(coinLabel);
    coinLabel->setPosition(coin->getContentSize().width+coin->getPositionX()+5*sx,coin->getPositionY()+(coin->getContentSize().height-coinLabel->getContentSize().height)/2);
    this->addChild(coinLabel,3,TAG_CONSUME);
}
void Generals_Sell_Layer::onUpData()
{
    Label* coinLabel =(Label*)this->getChildByTag(TAG_CONSUME);
    if (!coinLabel) {
        return;
    }
    
    long money=0;
    if (isEquipOrHero==0) {
        //装备
        int len =(int)selectEquipList->size();
        if (len>0) {
            for (int i=0; i<len; i++) {
                DictItemEquip* data= DictItemEquipManager::getInstance()->getData(selectEquipList->at(i)->equipDictId);
                if (data) {
                    int sellNum=data->sellingPrice;
                    money+=sellNum;
                }
            }
        }
    }else
    {
        int len = (int)selectCardList->size();
        if (len>0) {
            for (int i=0; i<len; i++) {
                DictHero* heroData= DictHeroManager::getInstance()->getData(selectCardList->at(i)->heroDictId);
                DictHeroQuality* qualityData=DictHeroQualityManager::getInstance()->getData(selectCardList->at(i)->quality);
                if (heroData and qualityData) {
                    long sellNum=heroData->fireCoin*qualityData->sellMultiple;
                    money+=sellNum;
                }
            }
        }
    }
    string moneyStr=PublicShowUI::numberToString(money);
    coinLabel->setString(moneyStr);
}
void Generals_Sell_Layer::onSellBtn(Ref* psender)
{
    int len=0;
    string str="";
    if (isEquipOrHero==0) {
        len =(int)selectEquipList->size();
        str="出售装备为空,请选择要出售的装备";
    }else
    {
        len =(int)selectCardList->size();
        str="出售武将为空,请选择要出售的武将";
    }
    if (len>0) {
        this->requestSellMsg();
    }else
    {
        
        NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
    }
}


//--------------------------------列表部分-------------------------------------------------------//
void Generals_Sell_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3-33;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(40*sx,95*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(0*sx,90*sx);
    this->addChild(shade,3);

}
TableViewCell* Generals_Sell_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<5; i++) {
        int tag=(int)idx*5+i;
        if (cardList->size()>tag and isEquipOrHero==1) {
            CardPropertyData* data=cardList->at(tag);
            DictHero* dictHero = DictHeroManager::getInstance()->getData(data->heroDictId);
            if (dictHero) {
                UserHeadLayer* userHead=UserHeadLayer::create(dictHero->resource.c_str(),data->quality);
                userHead->setHeadInfo(data->level, data->prestige);
                log("dddddddddddddddddddd=======%d",data->isSelect);
                userHead->setHeadNumber(data->isSelect);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(Generals_Sell_Layer::onUserClick));
                userHead->setPosition(5+136*i,5);
                cell->addChild(userHead,1,tag);
            }
        }else if (equipList->size()>tag and isEquipOrHero==0)
        {
            BaseEquipData* data=equipList->at(tag);
            DictItemEquip* dictItem= DictItemEquipManager::getInstance()->getData(data->equipDictId);
            if (dictItem) {
                UserEquipLayer* userEquip=UserEquipLayer::create(dictItem->resource,data->quality);
                userEquip->setHeadInfo(data->equipLevel);
                userEquip->addTouchBegainCallBack(this, callfuncN_selector(Generals_Sell_Layer::onUserClick));
                userEquip->setAnchorPoint(Point::ZERO);
                userEquip->setPosition(5+136*i,5);
                log("dddddddddddddddddddd=======%d",data->isSelect);
                userEquip->setIsSlect(data->isSelect);
                cell->addChild(userEquip,1,tag);
            }
            
        }
    }
    return cell;
}

//列表大小
Size Generals_Sell_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,1);
    Sprite* headBox=Sprite::create(stt);
    cellSize.height=headBox->getContentSize().height+5;
    cellSize.width=(headBox->getContentSize().width+15)*5;
    return cellSize;
}
//获取view的长度
ssize_t Generals_Sell_Layer::numberOfCellsInTableView(TableView *table)
{
    float t=0;
    if (isEquipOrHero==0) {
        t=(float)equipList->size()/5;
    }else
    {
        t=(float)cardList->size()/5;
    }
    int count = ceil(t);
    return count;
}

//点击cell事件
void Generals_Sell_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
}
void Generals_Sell_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
//////////////------------------------------------------------------------------------------//////////////////

void Generals_Sell_Layer::onUserClick(Node* pSender)
{
    if(isMoveing)
    {
        return;
    }
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*3-10)*sx;
    _size.width=_size.width*sx;
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (!bb.containsPoint(isDownPoint)) {
        return;
    }
    if (isEquipOrHero==1) {
        UserHeadLayer* card=(UserHeadLayer*)pSender;
        int tag=card->getTag();
        CardPropertyData* data= cardList->at(tag);
        if (data->isSelect) {
            data->isSelect=false;
            int index = this->getIndexByCardID(data->heroId);
            if(index >= 0)
            {
                selectCardList->erase(index);
            }
        }else
        {
            data->isSelect=true;
            selectCardList->pushBack(data);
        }
        card->setHeadNumber(data->isSelect);
    }else
    {
        UserEquipLayer* card=(UserEquipLayer*)pSender;
        int tag=card->getTag();
        BaseEquipData* data= equipList->at(tag);
        if (data->isSelect) {
            data->isSelect=false;
            int index = this->getIndexByEquipID(data->equipId);
            if(index >= 0)
            {
                selectEquipList->erase(index);
            }
        }else
        {
            data->isSelect=true;
            selectEquipList->pushBack(data);
        }
        card->setIsSlect(data->isSelect);
    }
    this->onUpData();
    
}
int Generals_Sell_Layer::getIndexByCardID(int _heroId)
{
    int len = (int)selectCardList->size();
    for(int i = 0; i < len; i++)
    {
        if(selectCardList->at(i)->heroId == _heroId)
        {
            return i;
        }
    }
    return -1;
}
int Generals_Sell_Layer::getIndexByEquipID(int _EquipId)
{
    int len = (int)selectEquipList->size();
    for(int i = 0; i < len; i++)
    {
        if(selectEquipList->at(i)->equipId == _EquipId)
        {
            return i;
        }
    }
    return -1;
}

void Generals_Sell_Layer::updataData()
{
    
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void Generals_Sell_Layer::requestListMsg()
{
    if (isEquipOrHero==0) {
        SellEquipPageMsg* msg = new SellEquipPageMsg();
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }else{
        SellHeroPageMsg* msg = new SellHeroPageMsg();
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
   
}
void Generals_Sell_Layer::requestSellMsg()
{
    if (isEquipOrHero==1) {
        SellHeroMsg* msg = new SellHeroMsg(selectCardList);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }else{
        SellEquipMsg* msg = new SellEquipMsg(selectEquipList);
        NetworkDataProcessing::getInstance()->sendMessage(msg);
        msg = NULL;
    }
}
void Generals_Sell_Layer::onMsgProcess(EventCustom* msg)
{
    
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroSellPageResp)
    {
        cardList->clear();
        int size=message->byteStream->getShort();
        
        for (int i=0; i<size; i++) {
            CardPropertyData* data=new CardPropertyData();
            data->heroId=message->byteStream->getInt();
            data->heroDictId=message->byteStream->getInt();
            data->level=message->byteStream->getInt();
            data->prestige=message->byteStream->getShort();
            data->quality=message->byteStream->getByte();
            DictHero* heroData=DictHeroManager::getInstance()->getData(data->heroDictId);
            if (heroData) {
                data->backPackOrder=heroData->seq;
            }
            cardList->pushBack(data);
        }
        this->sortList("quality");
        
    }else if(message->messageID == SCENSE_CLIENT_HERO_HeroSellResp)
    {
        selectCardList->clear();
        int coint=message->byteStream->getInt();
        this->onUpData();
        this->requestListMsg();
        this->broadMsg(CUSTOM_SELL_HERO,NULL);
//        string str="出售武将成功,恭喜获得"+PublicShowUI::numberToString(coint)+"铜钱";
//        NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
    }else if(message->messageID == SCENSE_CLIENT_EQUIP_EquipSellPageResp)
    {
        equipList->clear();
        int size=message->byteStream->getShort();
        for (int i=0; i<size; i++) {
            BaseEquipData* data =new BaseEquipData();
            data->equipId=message->byteStream->getInt();
            data->equipDictId=message->byteStream->getInt();
            data->quality=message->byteStream->getByte();
            data->equipLevel=message->byteStream->getInt();
            DictItemEquip* equipData= DictItemEquipManager::getInstance()->getData(data->equipDictId);
            if (equipData) {
                data->backPackOrder=equipData->backPackOrder;
            }
            equipList->pushBack(data);
        }
        this->sortList("quality");
        
    }else if(message->messageID == SCENSE_CLIENT_EQUIP_EquipSellResp)
    {
        selectEquipList->clear();
        int coint=message->byteStream->getInt();
        this->onUpData();
        this->requestListMsg();
        this->broadMsg(CUSTOM_SELL_EQUIP,NULL);
//        string str="出售装备成功,恭喜获得"+PublicShowUI::numberToString(coint)+"铜钱";
//        NoticeManager::getInstance()->showNotice(str.c_str(),NoticeManager::COLOR_GREEN);
        
    }
    
}
void Generals_Sell_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroSellPageResp).c_str(), CC_CALLBACK_1(Generals_Sell_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroSellResp).c_str(), CC_CALLBACK_1(Generals_Sell_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipSellPageResp).c_str(), CC_CALLBACK_1(Generals_Sell_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_EQUIP_EquipSellResp).c_str(), CC_CALLBACK_1(Generals_Sell_Layer::onMsgProcess, this));
}

//状态排序
bool sortOnSellQualityDescend(CardPropertyData* n1, CardPropertyData* n2)//倒序(从小到大)
{
    return n1->quality > n2->quality;
}
bool sortOnSellLevel(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->level > n2->level;
}
bool sortOnSellPackOrder(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
bool sortOnSellCardId(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->heroDictId ==114010;
}
bool sortOnSellCardId2(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->heroDictId ==114020;
}
//装备
bool sortOnSellEquipQualityDescend(BaseEquipData* n1, BaseEquipData* n2)//倒序(从小到大)
{
    return n1->quality > n2->quality;
}
bool sortOnSellEquipLevel(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->equipLevel > n2->equipLevel;
}
bool sortOnSellEquipPackOrder(BaseEquipData* n1, BaseEquipData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
//-------------------------------------------------------排序-------------------------------------------------------//
void Generals_Sell_Layer::sortList(string name)
{
    if (isEquipOrHero==0) {
        stable_sort(equipList->begin(), equipList->end(),sortOnSellEquipPackOrder);
        stable_sort(equipList->begin(), equipList->end(),sortOnSellEquipLevel);
        stable_sort(equipList->begin(), equipList->end(),sortOnSellEquipQualityDescend);
    }else
    {
        stable_sort(cardList->begin(), cardList->end(),sortOnSellPackOrder);
        stable_sort(cardList->begin(), cardList->end(),sortOnSellLevel);
        stable_sort(cardList->begin(), cardList->end(),sortOnSellQualityDescend);
        stable_sort(cardList->begin(), cardList->end(),sortOnSellCardId);
        stable_sort(cardList->begin(), cardList->end(),sortOnSellCardId2);
        
       ///金蝉王排序
        int tempNum=0;
        int num2=0;
        ssize_t len = cardList->size();
        for (int i=0;i<len;i++) {
            if (cardList->at(i)->heroDictId==114020) {
                tempNum++;
            }else if (cardList->at(i)->heroDictId==114010)
            {
                num2++;
            }else
            {
                break;
            }
        }
        num2+=tempNum;
        if (tempNum) {
            stable_sort(cardList->begin(), cardList->begin()+tempNum,sortOnSellPackOrder);
            stable_sort(cardList->begin(), cardList->begin()+tempNum,sortOnSellLevel);
            stable_sort(cardList->begin(), cardList->begin()+tempNum,sortOnSellQualityDescend);
        }
        //金蝉幼崽排序
        if (num2) {
            stable_sort(cardList->begin()+tempNum, cardList->begin()+num2,sortOnSellPackOrder);
            stable_sort(cardList->begin()+tempNum, cardList->begin()+num2,sortOnSellLevel);
            stable_sort(cardList->begin()+tempNum, cardList->begin()+num2,sortOnSellQualityDescend);
        }
    }
    
    this->initTableView();
}

bool Generals_Sell_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void Generals_Sell_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
}
void Generals_Sell_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchEnded(touch, unused_event);
    isMoveing = false;
}


void Generals_Sell_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
