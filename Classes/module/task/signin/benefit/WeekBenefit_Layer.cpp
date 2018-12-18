//
//  WeekBenefit_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/16.
//
//

#include "WeekBenefit_Layer.h"
#include "../everydaySignin/EverydaySignin_Layer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../../../../protocol/Protocal.h"
#include "../Signin_Scene.h"

#include "../../../../common/Dialog/Dialog.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../message/Decoding/signin/welfare/BoonWeekPageMsg.h"
#include "../../../../message/Decoding/signin/welfare/BoonWeekBuyMsg.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "data/BenefitWeekDataManager.h"
#include "../../../tips/TipsLayer.h"
#include "../../../awardBox/AwardBox_Layer.h"
WeekBenefit_Layer::WeekBenefit_Layer()
:sx(1)
,selectVip(0)
,TAG_TABLEVIEW(10)
,_itemImage(NULL)
,TAG_NODE(11)
,m_viplevel(0)
,TAG_RESETTIME(12)
,m_resettimess(0)
{
}
WeekBenefit_Layer::~WeekBenefit_Layer()
{
//    CC_SAFE_DELETE(m_baseList);
    
    CC_SAFE_RELEASE_NULL(_itemImage);
    BenefitWeekDataManager::getInstance()->destroyInstance();
}

void WeekBenefit_Layer::onExit()
{
    BaseLayer::onExit();
}
void WeekBenefit_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void WeekBenefit_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void WeekBenefit_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestWeekbenefitMsg();
}
bool WeekBenefit_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_SIGNIN_BENEFIT_DAY_BG);
        this->createLayer();
        bref = true;
    } while (false);
    return bref;
}
WeekBenefit_Layer* WeekBenefit_Layer::create()
{
    WeekBenefit_Layer* layer = new WeekBenefit_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void WeekBenefit_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* line = Sprite::create(IMG_VIP_LIBAO_LINE);
    line->setAnchorPoint(Point::ZERO);
    line->setPosition(300,115);
    bg->addChild(line,10);
    
    Sprite* sellbg = Sprite::create(IMG_SIGNIN_BENEFIT_WEEKSELL_BG);
    sellbg->setAnchorPoint(Point::ZERO);
    sellbg->setPosition(40,250);
    bg->addChild(sellbg,1);
    
    Sprite* pricebg = Sprite::create(IMG_SIGNIN_BENEFIT_WEEKPRICE_BG);
    pricebg->setAnchorPoint(Point::ZERO);
    pricebg->setPosition(120,10);
    bg->addChild(pricebg,1);

    //vip送福利拉 字体
//    Sprite* box=Sprite::create(IMG_SIGNIN_BENEFIT_DAY_OTHERLABEL);
//    box->setAnchorPoint(Point::ZERO);
//    box->setPosition(-(box->getContentSize().width),0);
//    bg->addChild(box,10);
    
//    const char* pathList[2] = {IMG_PUBLIC_LABEL_WEEKBENEFIT,IMG_PUBLIC_LABEL_DAYBENEFIT};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 28, CC_CALLBACK_1(WeekBenefit_Layer::onComboBoxBtnClick, this));
//    for (int i = 0; i<2; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_BUTTON_SIGNIN_GREEN, IMG_PUBLIC_BUTTON_SIGNIN_YELLOW, pathList[1-i]);
//    }
//    boxBtn->selectedAt(0);
//    boxBtn->getButtonAt(1)->selected();
//    boxBtn->setPosition(39,330);
//    bg->addChild(boxBtn,3);
    
//    int functionList[2] = {DictFunctionEnumWelfareDay,DictFunctionEnumWelfareWeek};
    const char* pathlist1[] = {IMG_PUBLIC_LABEL_DAYBENEFITUN,IMG_PUBLIC_LABEL_WEEKBENEFITUN };
    const char* pathlist2[] = {IMG_PUBLIC_LABEL_DAYBENEFITCHOSE,IMG_PUBLIC_LABEL_WEEKBENEFITCHSOE};
    
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 20, CC_CALLBACK_1(WeekBenefit_Layer::onComboBoxBtnClick, this));
    for (int i = 0; i<2; i++) {
        
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathlist1[i], pathlist2[i]);
//        PublicShowUI::setDot(boxBtn, Point::ZERO, false,functionList[i]);
    }
    
    boxBtn->getButtonAt(1)->selected();
    boxBtn->setPosition(180 ,385);
    bg->addChild(boxBtn,3);
    
    
    
    Button* buyBtn=Button::create(IMG_BUTTON_REDBTN,"", CC_CALLBACK_1(WeekBenefit_Layer::onClickBtn, this));
    buyBtn->setPosition(600,80);
    bg->addChild(buyBtn);
    
    Sprite* rechargeLabel=Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
    buyBtn->addChild(rechargeLabel,2);
    
}
void WeekBenefit_Layer::onClickBtn(Ref* psender)
{
    BenefitWeekData* data = BenefitWeekDataManager::getInstance()->benefitweekList->at(m_viplevel);
    
        if (data->status == 1) {
            requestWeeklingquMsg(m_viplevel);
        }else if (data->status == 2)
        {
            NoticeManager::getInstance()->showNotice("已领取");
        }else if (data->status == 3)
        {
            
            NoticeManager::getInstance()->showNotice("VIP等级不够，请前往充值");
        }

}
void WeekBenefit_Layer::onComboBoxBtnClick(Ref* psender)
{
    Node* sp=(Node*)psender;
    int tag=sp->getTag();
    if (tag==0) {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_DAYBENEFIT));
    }else if (tag==1)
    {
        broadMsg(CUSTOM_SIGNIN_SENDMESSAGE_EVENT,__Integer::create(Signin_Scene::TAG_WEEKBENEFIT));
    }
}
void WeekBenefit_Layer::setItem(int viplevel)
{
    
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    if (bg->getChildByTag(TAG_NODE)) {
        bg->removeChildByTag(TAG_NODE);
    }
    Node* node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    UserEquipLayer* head = NULL;
    UserHeadLayer* userHead = NULL;
    BenefitWeekData* data = BenefitWeekDataManager::getInstance()->benefitweekList->at(viplevel);
    const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        userHead=UserHeadLayer::create(resource,data->itemQuality,false);
        userHead->setHeadInfo(1, 1);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(32,30);
        node->addChild(userHead,5,TAG_NODE);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(WeekBenefit_Layer::onHeroHeadClick));
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        head = UserEquipLayer::create(resource,data->itemQuality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(32,30);
        node->addChild(head,5);
        head->addTouchBegainCallBack(this, callfuncN_selector(WeekBenefit_Layer::onHeroHeadClick));
    }
    string count = StringUtils::format("x%d",data->itemCount);
    Label* label = PublicShowUI::getLabelNumber(count.c_str(), PublicShowUI::getColor3b(COLOR_HEAD_WHITE), 16, false, false);
    label->setAnchorPoint(Point::ZERO);
    if (head) {
        label->setPosition(head->getContentSize().width-label->getContentSize().width-5,2);
        head->addChild(label,5);
    }else{
        label->setPosition(userHead->getContentSize().width-label->getContentSize().width-5,2);
        userHead->addChild(label,5);
    }

    
    
    string strold = StringUtils::format("%zd",data->privceOri);
    Label* oldlabelstr = PublicShowUI::getLabel(strold.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),24,false,false);
    oldlabelstr->setAnchorPoint(Point::ZERO);
    oldlabelstr->setPosition(230,100);
    node->addChild(oldlabelstr,5);
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setAnchorPoint(Point::ZERO);
    gold->setScale(0.7);
    gold->setPosition(oldlabelstr->getPositionX()+oldlabelstr->getContentSize().width,oldlabelstr->getPositionY()-2);
    node->addChild(gold);
    
    string strnow = StringUtils::format("%zd",data->price);
    Label* nowlabelstr = PublicShowUI::getLabel(strnow.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),24,false,false);
    nowlabelstr->setAnchorPoint(Point::ZERO);
    nowlabelstr->setPosition(250,40);
    node->addChild(nowlabelstr,5);
    Sprite* goldone = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    goldone->setAnchorPoint(Point::ZERO);
    goldone->setScale(0.7);
    goldone->setPosition(nowlabelstr->getPositionX()+nowlabelstr->getContentSize().width,nowlabelstr->getPositionY()-2);
    node->addChild(goldone);
    
    string str = StringUtils::format("VIP%zd专属大礼包",viplevel);
    Label* labelstr = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),30,false,false);
    labelstr->setAnchorPoint(Point::ZERO);
    labelstr->setPosition(150,180);
    node->addChild(labelstr,5);
//
//    string levelstr = StringUtils::format("VIP%zd",viplevel);
//    Label* levelstrlabel = PublicShowUI::getLabel(levelstr.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),18,false,false);
//    levelstrlabel->setAnchorPoint(Point::ZERO);
//    levelstrlabel->setPosition(410,110);
//    node->addChild(levelstrlabel,5);
    
    //剩余时间
    string recuittime=StringUtils::format("%02ld天 %02ld小时 %02ld分 %02ld秒",m_resettimess/86400,m_resettimess%86400/3600, m_resettimess%3600/60,m_resettimess%60);
    m_resettimeLabel = PublicShowUI::getLabel(recuittime.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),20,false,false);
    m_resettimeLabel->setAnchorPoint(Point::ZERO);
    node->addChild(m_resettimeLabel,5);
    m_resettimeLabel->setTag(TAG_RESETTIME);
    m_resettimeLabel->setPosition(120,256);
    this->schedule(schedule_selector(WeekBenefit_Layer::UpdataTime),1);
    node->setPosition(150,10);
    bg->addChild(node,5,TAG_NODE);

}
void WeekBenefit_Layer::onHeroHeadClick(Node* pSender)
{
     BenefitWeekData* data = BenefitWeekDataManager::getInstance()->benefitweekList->at(m_viplevel);
     TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}
void WeekBenefit_Layer::UpdataTime(float dt)
{
    log("........................%ld",m_resettimess);
    m_resettimess -= 1;
    if (m_resettimess <= 0) {
        m_resettimess =0;
        log("........................%ld",m_resettimess);
        unschedule(schedule_selector(WeekBenefit_Layer::UpdataTime));
    }
    char*mtime = new char[100];
    //显示小时，分钟，秒
    sprintf(mtime,"%02ld天 %02ld小时 %02ld分 %02ld秒",m_resettimess/86400,m_resettimess%86400/3600, m_resettimess%3600/60,m_resettimess%60);
    m_resettimeLabel->setString(mtime);
}

//--------------------------------列表部分-------------------------------------------------------//
void WeekBenefit_Layer::initTableView()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    TableView* _tableView = (TableView*)bg->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.width=_size.width*4;
    _size.height=_size.height;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
//    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::HORIZONTAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition((this->getContentSize().width/sx-_size.width)/2,-(_size.height));
    bg->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* arrow = Sprite::create(IMG_GENERALSLIST_ARROW);
    arrow->setAnchorPoint(Point::ZERO);
    arrow->setRotation(90);
    arrow->setPosition(_tableView->getPositionX() + _size.width -10, _tableView->getPositionY() + (_size.height - arrow->getContentSize().height)/2 + 20);
    bg->addChild(arrow,2);
    
    MoveBy* moveby = MoveBy::create(.5, Point(20,0));
    arrow->runAction(RepeatForever::create(Sequence::create(moveby,moveby->reverse(), NULL)));
    
}
Node* WeekBenefit_Layer::singleList(ssize_t idx)
{
    
    Button* btn = Button::create(IMG_SIGNIN_BENEFIT_VIP_BG1, IMG_SIGNIN_BENEFIT_VIP_BG2, CC_CALLBACK_1(WeekBenefit_Layer::onVipClick, this));
    btn->getTouchListener()->setSwallowTouches(false);
    btn->setAnchorPoint(Point::ZERO);
    
    string str = StringUtils::format("VIP%zd",idx);
    Label* labelstr = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),26,false,false);
    labelstr->setAnchorPoint(Point::ZERO);
    labelstr->setPosition((btn->getContentSize().width-labelstr->getContentSize().width)/2,(btn->getContentSize().height-labelstr->getContentSize().height)/2);
    btn->addChild(labelstr,5);
    return btn;
}
void WeekBenefit_Layer::onSelected(Ref* pSender)
{
    Button* itemImage = (Button*)pSender;
    if(_itemImage == itemImage)
    {
        _itemImage->selected();
        return;
    }
    if(_itemImage)
    {
        _itemImage->unselected();
        _itemImage->release();
    }
    _itemImage = itemImage;
    _itemImage->selected();
    _itemImage->retain();
}
void WeekBenefit_Layer::setSelectedByIndex(int index)
{
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    TableView* tableView = (TableView*)bg->getChildByTag(TAG_TABLEVIEW);
    if(tableView)
    {
        if(tableView->cellAtIndex(index))
        {
            onSelected(tableView->cellAtIndex(index)->getChildByTag(index));
        }
        
    }
}

void WeekBenefit_Layer::onVipClick(Ref* pSender)
{
    onSelected(pSender);
    Button* itemImage = (Button*)pSender;
    int tag = itemImage->getTag();
    setItem(tag);
    m_viplevel = tag;
}
TableViewCell* WeekBenefit_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* bg = singleList(idx);

    bg->setAnchorPoint(Point::ZERO);
    cell->addChild(bg,1,idx);

    return cell;
}

//列表大小
Size WeekBenefit_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* headBox=Sprite::create(IMG_SIGNIN_BENEFIT_VIP_BG1);
    cellSize.height=headBox->getContentSize().height;
    cellSize.width=headBox->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t WeekBenefit_Layer::numberOfCellsInTableView(TableView *table)
{
    size_t count = BenefitWeekDataManager::getInstance()->benefitweekList->size();
    return count;
}
//点击cell事件
void WeekBenefit_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{

}



void WeekBenefit_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

void WeekBenefit_Layer::requestWeekbenefitMsg()
{
    BoonWeekPageMsg* msg = new BoonWeekPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void WeekBenefit_Layer::onWeekBenefitMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    BenefitWeekDataManager::getInstance()->clearweekList();
    if(message->messageID == SCENSE_CLIENT_BOON_BoonWeekPageResp)
    {
        if(message->state)//返回成功
        {
            m_resettimess = message->byteStream->getInt();//剩余时间
            int vipsize = message->byteStream->getByte();
            for (int i = 0; i<vipsize; i++)
            {
                BenefitWeekData * data = new BenefitWeekData();
                data->autorelease();
                data->status = message->byteStream->getByte();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->itemQuality = message->byteStream->getByte();
                data->itemCount = message->byteStream->getInt();
                data->itemName = message->byteStream->getUTF8();
                data->privceOri = message->byteStream->getInt();
                data->price = message->byteStream->getInt();
                BenefitWeekDataManager::getInstance()->addData(data);
            }
            initTableView();
            setItem(0);
            setSelectedByIndex(0);
        }
    }
}

void WeekBenefit_Layer::requestWeeklingquMsg(int viplevel)
{

    BoonWeekBuyMsg* msg = new BoonWeekBuyMsg(viplevel);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void WeekBenefit_Layer::onWeeklingquProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_BOON_BoonWeekBuyResp)
    {
        if(message->state)//返回成功
        {
        
            
            
            BenefitWeekData* data = BenefitWeekDataManager::getInstance()->benefitweekList->at(m_viplevel);
            
            Vector<BaseTypeData*> *m_baseList = new Vector<BaseTypeData*>();
            m_baseList->clear();
            BaseTypeData *baseData=new BaseTypeData();
            baseData->autorelease();
            baseData->dataId=data->itemId;
            baseData->dataName=data->itemName;
            baseData->dataType=data->itemType;
            baseData->dataQuality=data->itemQuality;
            baseData->dataCount = data->itemCount;
            m_baseList->pushBack(baseData);
            
            AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
            data->status =2;
            
        }
        
    }
}

void WeekBenefit_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOON_BoonWeekPageResp).c_str(), CC_CALLBACK_1(WeekBenefit_Layer::onWeekBenefitMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOON_BoonWeekBuyResp).c_str(), CC_CALLBACK_1(WeekBenefit_Layer::onWeeklingquProcess, this));
}
