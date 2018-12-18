//
//  HeroListBar_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/8/18.
//
//

#include "HeroListBar_Layer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../message/Decoding/generals/HeroListBarMsg.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../common/commonEffect/CommonEffect.h"
#include "data/CardDataManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../common/customButton/CustomButton.hpp"
#include "Generals_Layer.h"
#include "../../commonData/enum/DictFunctionEnum.h"
HeroListBar_Layer::HeroListBar_Layer()
:sx(1)
,TAG_TABLEVIEW(1)
,heroId(-1)
,touchIdx(-1)
,m_sortMode("")
{
    heroList=new Vector<CardPropertyData*>();
}
HeroListBar_Layer::~HeroListBar_Layer()
{
//    CardDataManager::getInstance()->clearHeroList();
    heroList->clear();
    CC_SAFE_DELETE(heroList);
}

bool HeroListBar_Layer::init(int _id,string sortMode)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        heroId=_id <= 0 ? GlobalInfo::getInstance()->gameRole->mainHeroID : _id;
        
        m_sortMode=sortMode;
        sx= GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_PUBLIC_LAYER_LEFTLISTBG);
        this->setDirectBtn();
        bref = true;
    } while (false);
    return bref;
}
void HeroListBar_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void HeroListBar_Layer::onExit()
{
    BaseLayer::onExit();
}
void HeroListBar_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestListMsg();
//    if(CardDataManager::getInstance()->getPresentData() == NULL)
//    {
//        requestListMsg();
//    }
//    else
//    {
//        this->initTableView();
//        this->broadMsg(CUSTOM_CHOOSE_HERO_FUN,__Integer::create(CardDataManager::getInstance()->getPresentData()->heroId));
//    }
   
}
void HeroListBar_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
HeroListBar_Layer* HeroListBar_Layer::create(int _id,string sortMode)
{
    HeroListBar_Layer* layer = new HeroListBar_Layer();
    if(layer && layer->init(_id,sortMode))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void HeroListBar_Layer::setDirectBtn()
{
    Sprite* bgSprite=(Sprite*)this->getChildByTag(TAG_BG);
    if (bgSprite) {
//        Sprite* downBtn = Sprite::create(IMG_STAGE_RIGHTBTN);
//        downBtn->setAnchorPoint(Point(0.5,0.5));
//        downBtn->setPosition(bgSprite->getContentSize().width/2/sx-10,22);
//        downBtn->setRotation(90);
//        downBtn->setVisible(true);
        
        CustomButton* morBtn = CustomButton::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1(HeroListBar_Layer::onMoreBtnClick, this));
        morBtn->addTitle(IMG_GENERALS_MORELABEL, IMG_GENERALS_MORELABEL);
        morBtn->setPosition(bgSprite->getContentSize().width/2/sx-10,22);
        
        Sprite* upBtn = Sprite::create(IMG_STAGE_RIGHTBTN);
        upBtn->setAnchorPoint(Point(0.5,0.5));
        upBtn->setPosition(bgSprite->getContentSize().width/2/sx-10,bgSprite->getContentSize().height/sx-22);
            upBtn->setRotation(270);
        
       
        upBtn->setScale(0.7);
        bgSprite->addChild(morBtn,5);
        bgSprite->addChild(upBtn,5);

    }
    
}
void HeroListBar_Layer::onMoreBtnClick(Ref* pSender)
{
    Generals_Layer::show(SCENE_TAG_GENERALSCARD);
}
void HeroListBar_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3.4;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(5,this->getContentSize().height/2-_size.height/2*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    this->setLocation();
}
void HeroListBar_Layer::setLocation()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    float tableY=0;
    if (heroList->size()<3) {
        return;
    }
    
    float numHero = 1.0f;
    for (CardPropertyData* data: *heroList) {
        if (data->heroId==heroId or heroId==-1){
            break;
        }
        numHero++;
//        tableY+=_size.height;
    }
    if(_tableView)
    {
        int num = (numHero / 3);
        tableY = num * _size.height * 3;
        Point cp = _tableView->getContentOffset();
        if(numHero > heroList->size() - 3)
        {
          tableY = _tableView->getContentSize().height - 3 * _size.height;
        }
        cp.y+=tableY;
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
    }

}

//--------------------------------列表部分-------------------------------------------------------//
TableViewCell* HeroListBar_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    int tag=(int)idx;
    CardPropertyData* data =heroList->at((int)idx);
    int tempNum=data->heroDictId;
    DictHero* dictHero = DictHeroManager::getInstance()->getData(tempNum);
    string resource = dictHero ? dictHero->resource.c_str() : "";
    UserHeadLayer* userHead=UserHeadLayer::create(resource.c_str(),data->quality);
    userHead->setHeadInfo(data->level, data->prestige);
    userHead->setHeadNumber(data->cardLocation);
    userHead->disableTouchEvent();
    userHead->setPosition(14,5*sx);
    cell->addChild(userHead,1,tag);
    
    if (data->heroId==heroId) {
        CommonEffect* commonEffect = CommonEffect::create("wujiangtouxiang",true,true);
        commonEffect->setAnchorPoint(Point(0.5,0.5));
        commonEffect->setPosition((userHead->getPositionX()+userHead->getContentSize().width/2)-5,(userHead->getPositionY()+userHead->getContentSize().height/2)-5);
        cell->addChild(commonEffect,2);
    }
    
    if (data->headstatus == 1) {
        PublicShowUI::setDot(userHead, Point::ZERO, false,DictFunctionEnumHeroPrestige ,DictFunctionEnumHeroQuality,DictFunctionEnumHeroStar,DictFunctionEnumHeroEquip);
    }

    return cell;
}

//列表大小
Size HeroListBar_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    UserHeadLayer* userHead=UserHeadLayer::create("no");
    cellSize.height=userHead->getContentSize().height+5*sx;
    cellSize.width=(userHead->getContentSize().width+35*sx);
    return cellSize;
}
//获取view的长度
ssize_t HeroListBar_Layer::numberOfCellsInTableView(TableView *table)
{
    int titleCount=(int)heroList->size();
    return titleCount;
}
//点击cell事件
void HeroListBar_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    this->onUserClick((int)cell->getIdx());
}
//
void HeroListBar_Layer::onUserClick(int idx)
{
    touchIdx=idx;
    
    CardPropertyData* cardData=heroList->at(touchIdx);
    heroId=cardData->heroId;
    this->broadMsg(CUSTOM_CHOOSE_HERO_FUN,__Integer::create(cardData->heroId));
    this->initTableView();
    

}
void HeroListBar_Layer::setUpdata()
{
//    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
//    
//    if(_tableView)
//    {
//        this->removeChildByTag(TAG_TABLEVIEW);
//    }
    
    this->requestListMsg();
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void HeroListBar_Layer::requestListMsg()
{
    Dialog::showServerLoading(.5);
    HeroListBarMsg* msg = new HeroListBarMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void HeroListBar_Layer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_HERO_HeroListBarResp)
    {
        heroList->clear();
        int listSize=message->byteStream->getShort();
        CardPropertyData* tempData = NULL;
        for (int i=0; i<listSize; i++) {
            CardPropertyData* cardData=new CardPropertyData();
            cardData->autorelease();
            cardData->heroId=message->byteStream->getInt();
            cardData->heroDictId=message->byteStream->getInt();
            cardData->level=message->byteStream->getInt();
            cardData->prestige=message->byteStream->getInt();
            cardData->quality=message->byteStream->getByte();
            cardData->headstatus = message->byteStream->getByte();
            heroList->pushBack(cardData);
            if(cardData->heroId == heroId)
            {
                tempData = cardData;
            }
        }
        this->sortList(m_sortMode);
        if(CardDataManager::getInstance()->getPresentData() == NULL)
        {
            if(!tempData)
            {
                tempData = heroList->at(0);
            }
           
            CardDataManager::getInstance()->setPresentData(tempData);
   
            this->broadMsg(CUSTOM_CHOOSE_HERO_FUN,__Integer::create(tempData->heroId));
        }
        else
        {
            this->broadMsg(CUSTOM_CHOOSE_HERO_FUN,__Integer::create(CardDataManager::getInstance()->getPresentData()->heroId));
        }
       
//         this->initTableView();
    }
    
}
void HeroListBar_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_HERO_HeroListBarResp).c_str(), CC_CALLBACK_1(HeroListBar_Layer::onMsgProcess, this));
}
void HeroListBar_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

//状态排序
bool sortOnHeroListBarPrestige(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->prestige > n2->prestige;
}
bool sortOnHeroListBarQualityAscend(CardPropertyData* n1, CardPropertyData* n2)//正序(从大到小)
{
    return n1->quality > n2->quality;
}
bool sortOnHeroListBarQualityDescend(CardPropertyData* n1, CardPropertyData* n2)//倒序(从小到大)
{
    return n1->quality < n2->quality;
}
bool sortOnHeroListBarLevel(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->level > n2->level;
}
bool sortOnHeroListBarPackOrder(CardPropertyData* n1, CardPropertyData* n2)
{
    return n1->backPackOrder < n2->backPackOrder;
}
//排序
void HeroListBar_Layer::sortList(string name)
{
    if(name == "prestige" )
    {
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarPackOrder);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarQualityDescend);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarLevel);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarPrestige);
    }
    else if(name == "quality")
    {
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarPackOrder);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarLevel);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarQualityAscend);
    }
    else if(name == "level" )
    {
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarPackOrder);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarQualityDescend);
        stable_sort(heroList->begin(), heroList->end(),sortOnHeroListBarLevel);
    }else if (name=="0")
    {
        return;
    }
    this->initTableView();
    
}
