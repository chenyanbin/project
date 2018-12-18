//
//  EverydaySignin_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/9.
//
//

#include "EverydaySignin_Layer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../Signin_Scene.h"
#include "../../../newPlayerGuide/NewPlayerGuild.h"
#include "../../../../message/Decoding/signin/SigninDayMsg.h"
#include "../../../../message/Decoding/signin/SigninDayGetMsg.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../protocol/Protocal.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../tips/TipsLayer.h"
#include "../../../awardBox/AwardBox_Layer.h"
EverydaySignin_Layer::EverydaySignin_Layer()
:sx(1)
,m_month(0)
,m_day(0)
,TAG_TABLEVIEW(2)
,isMoveing(false)
{
    m_list=new vector<SigninData*>();
    m_baseList=new Vector<BaseTypeData*>();
}
EverydaySignin_Layer::~EverydaySignin_Layer()
{
//    m_baseList->clear();
//    CC_SAFE_DELETE(m_baseList);
    m_list->clear();
    CC_SAFE_DELETE(m_list);
}

void EverydaySignin_Layer::onExit()
{
    BaseLayer::onExit();
}
void EverydaySignin_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void EverydaySignin_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    GuideButtonManager::getInstance()->removeButton(DictNewGuideEventEnumSign);
}
void EverydaySignin_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->requestListMsg();
    
}
bool EverydaySignin_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_SIGNIN_EVERYDAY_BG);
        this->setClickEnabled(true);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
EverydaySignin_Layer* EverydaySignin_Layer::create()
{
    EverydaySignin_Layer* layer = new EverydaySignin_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void EverydaySignin_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* box=Sprite::create(IMG_SIGNIN_EVERYDAY_OTHER);
    box->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(box);
    box->setPosition(-(box->getContentSize().width-50),0);
    this->addChild(box,10);
    
    
    
    const char* pathList[2] = {IMG_PUBLIC_LABEL_LUXURY,IMG_PUBLIC_LABEL_EVERYDAY};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 28, CC_CALLBACK_1(EverydaySignin_Layer::onComboBoxBtnClick, this));
    for (int i = 0; i<2; i++) {
        boxBtn->addBtn(IMG_PUBLIC_BUTTON_SIGNIN_GREEN, IMG_PUBLIC_BUTTON_SIGNIN_YELLOW, pathList[1-i]);
    }
    boxBtn->setPosition(70,380);
    boxBtn->getButtonAt(0)->selected();
    bg->addChild(boxBtn,3);
}
void EverydaySignin_Layer::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag==0) {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_EVERYDAY));
    }else if (tag==1)
    {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_LUXURY));
    }
}
//--------------------------------列表部分-------------------------------------------------------//
void EverydaySignin_Layer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.width=_size.width*5;
    _size.height=_size.height*2-18;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(18*sx,22*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    
    string month=PublicShowUI::numberToString(m_month)+"月奖励";
    Label* monthLabel = PublicShowUI::getLabel(month.c_str(),PublicShowUI::getColor3b(0xfdb300),20,false,false);
    PublicShowUI::setTargetScale(monthLabel);
    monthLabel->setAnchorPoint(Point::ZERO);
    monthLabel->setPosition((this->getContentSize().width-monthLabel->getContentSize().width)/2,(this->getContentSize().height-monthLabel->getContentSize().height)/2+92*sx);

    this->addChild(monthLabel,2);
    NewPlayerGuild::getInstance()->showNowGuide();
    
}
TableViewCell* EverydaySignin_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
        
        
        Sprite* bg=Sprite::create(IMG_SIGNIN_EVERYDAY_CELL_BG);
        bg->setAnchorPoint(Point::ZERO);
        bg->setTag(tag);
        bg->setPosition(i*(bg->getContentSize().width-4),-4);
        cell->addChild(bg);
        if(tag >= m_list->size())
        {
            continue;
        }
        SigninData* data=m_list->at(tag);
        const char* str=PublicShowUI::getGoods(data->itemType, data->itemId);
        UserEquipLayer* userHead=UserEquipLayer::create(str,data->itemQuality,false);
        userHead->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            userHead->setFragment();
        }
        userHead->setPosition((bg->getContentSize().width-userHead->getContentSize().width)/2,35);
        bg->addChild(userHead);
        if (data->itemStatus==3) {
            userHead->setGray();
            Sprite* yetGet=Sprite::create(IMG_SIGNIN_BENEFIT_DAY_DRAWDOWN);
            yetGet->setAnchorPoint(Point::ZERO);
            yetGet->setPosition(40,0);
            userHead->addChild(yetGet,8);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(EverydaySignin_Layer::onUserTipsClick));
        }else if (data->itemStatus==1)
        {
            userHead->addTouchBegainCallBack(this, callfuncN_selector(EverydaySignin_Layer::onUserClick));
            
            CommonEffect* commonEffect = CommonEffect::create("wujiangtouxiang",true,false);
            commonEffect->setAnchorPoint(Point(0.5,0.5));
//            PublicShowUI::setDot(commonEffect,Point::ZERO,false,DictFunctionEnumSign);
            commonEffect->setPosition((userHead->getPositionX()+userHead->getContentSize().width/2)-3,(userHead->getPositionY()+userHead->getContentSize().height/2));
            bg->addChild(commonEffect,2);
        }else if (data->itemStatus==2)
        {
            userHead->addTouchBegainCallBack(this, callfuncN_selector(EverydaySignin_Layer::onUserTipsClick));
        }
        userHead->setTag(tag);
        
        string count = StringUtils::format("x%d",data->itemCount);
        Label* label = PublicShowUI::getLabelNumber(count.c_str(), PublicShowUI::getColor3b(COLOR_HEAD_WHITE), 16, false, false);
        label->setAnchorPoint(Point::ZERO);
        if (userHead) {
            label->setPosition(userHead->getContentSize().width-label->getContentSize().width-5,2);
            userHead->addChild(label,5);
        }
        
        string day="第"+PublicShowUI::numberToString(tag+1)+"天";
        Label* dayLabel = PublicShowUI::getLabel(day.c_str(),PublicShowUI::getColor3b(0x6c2400),18,false,false);
        dayLabel->setAnchorPoint(Point::ZERO);
        dayLabel->setPosition((bg->getContentSize().width-dayLabel->getContentSize().width)/2,8);
        bg->addChild(dayLabel,1);
        
        if (data->vipDouble!=0) {
            Sprite* vipBg=Sprite::create(IMG_SIGNIN_EVERYDAY_VIPBG);
            vipBg->setAnchorPoint(Point::ZERO);
            userHead->addChild(vipBg,4);
            
            string vip="V"+PublicShowUI::numberToString(data->vipDouble)+"双倍";
            Label* vipLabel = PublicShowUI::getLabel(vip.c_str(),PublicShowUI::getColor3b(0xffba00),16,false,false);
            vipLabel->setAnchorPoint(Point::ZERO);
            vipLabel->setPosition(12,58);
            vipLabel->setRotation(-50);
            vipBg->addChild(vipLabel,1);
        }
        if(tag == 0)
        {
            GuideButtonManager::getInstance()->registerButton(DictNewGuideEventEnumSign, userHead);
        }
    }
    return cell;
}

//列表大小
Size EverydaySignin_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* headBox=Sprite::create(IMG_SIGNIN_EVERYDAY_CELL_BG);
    cellSize.height=headBox->getContentSize().height-4;
    cellSize.width=headBox->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t EverydaySignin_Layer::numberOfCellsInTableView(TableView *table)
{
    float t=(float)m_list->size()/5;
    
    int count = ceil(t);
    return count;
}
//点击cell事件
void EverydaySignin_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    this->isMoveing = false;

}

void EverydaySignin_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}

void EverydaySignin_Layer::onUserTipsClick(Node* pSender)
{
    
    if(isMoveing)
    {
        return;
    }
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*2-18)*sx;
    _size.width=_size.width*sx*5;
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (!bb.containsPoint(isDownPoint)) {
        return;
    }
    int tag=pSender->getParent()->getTag();
    
    TipsLayer::show(m_list->at(tag)->itemType, m_list->at(tag)->itemId,m_list->at(tag)->itemCount);
}
void EverydaySignin_Layer::onUserClick(Node* pSender)
{
    if(isMoveing)
    {
        return;
    }
    NewPlayerGuild::getInstance()->next(DictNewGuideEventEnumSign);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*2-18)*sx;
    _size.width=_size.width*sx*5;
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (!bb.containsPoint(isDownPoint)) {
        return;
    }
    this->requestListGetMsg();
}


void EverydaySignin_Layer::requestListMsg()
{
    SigninDayMsg* msg = new SigninDayMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void EverydaySignin_Layer::requestListGetMsg()
{
    SigninDayGetMsg* msg = new SigninDayGetMsg(m_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void EverydaySignin_Layer::onMsgProcess(EventCustom* msg)
{
    
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_SIGNDAY_SignDayPageResp)
    {
        m_month=message->byteStream->getByte();
        m_day=message->byteStream->getByte();
        m_list->clear();
        int daySize=message->byteStream->getByte();
        for (int i=0; i<daySize; i++) {
            SigninData* data=new SigninData();
            data->itemType=message->byteStream->getByte();
            data->itemId=message->byteStream->getInt();
            data->itemQuality=message->byteStream->getByte();
            data->itemCount=message->byteStream->getInt();
            data->vipDouble=message->byteStream->getByte();
            data->itemStatus=message->byteStream->getByte();
            m_list->push_back(data);
        }
        this->initTableView();
        
    }else if(message->messageID == SCENSE_CLIENT_SIGNDAY_SignDaySignResp)
    {
        m_baseList->clear();
        int _num=message->byteStream->getByte();
        for (int i=0; i<_num; i++) {
            BaseTypeData *data=new BaseTypeData();
            data->autorelease();
            int itemType=message->byteStream->getByte();
            int itemDictId=message->byteStream->getInt();
            string itemName=message->byteStream->getUTF8();
            int itemQuality=message->byteStream->getByte();
            string itemDesc=message->byteStream->getUTF8();
            int itemCount=message->byteStream->getInt();
            
            data->dataId=itemDictId;
            data->dataName=itemName;
            data->dataType=itemType;
            data->dataQuality=itemQuality;
            data->dataCount = itemCount;
            m_baseList->pushBack(data);
        }
        AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer);
        this->requestListMsg();
        broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumSign));
    }
}
void EverydaySignin_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SIGNDAY_SignDayPageResp).c_str(), CC_CALLBACK_1(EverydaySignin_Layer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_SIGNDAY_SignDaySignResp).c_str(), CC_CALLBACK_1(EverydaySignin_Layer::onMsgProcess, this));
}
void EverydaySignin_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
bool EverydaySignin_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void EverydaySignin_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (touch->getDelta().x>10 or touch->getDelta().y>10) {
        isMoveing=true;
    }
}
void EverydaySignin_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    
    BaseLayer::onTouchEnded(touch,unused_event);
}
