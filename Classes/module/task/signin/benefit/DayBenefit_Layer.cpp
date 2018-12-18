//
//  DayBenefit_Layer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/10/16.
//
//

#include "DayBenefit_Layer.h"
#include "../everydaySignin/EverydaySignin_Layer.h"
#include "../../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../protocol/UserCustomEvent.h"
#include "../Signin_Scene.h"
#include "../../../../common/TouchSprite/Button.h"
#include "data/BenefitDataManager.h"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../message/Decoding/signin/welfare/BoonDayPageMsg.h"
#include "../../../../message/Decoding/signin/welfare/BoonDayReceiveMsg.h"
#include "../../../userWealth/UserHeadLayer.h"
#include "../../../userWealth/UserEquipLayer.h"
#include "../../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../../common/noticeManager/NoticeManager.h"
#include "../../../../sdk/SdkManager.h"
#include "../../../data/BaseTypeData.h"
#include "../../../awardBox/AwardBox_Layer.h"
#include "../../../tips/TipsLayer.h"
#include "../../../../common/commonEffect/CommonEffect.h"
#include "../../../../commonData/enum/DictFunctionEnum.h"
DayBenefit_Layer::DayBenefit_Layer()
:sx(1)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,m_userVipLevel(0)
,isMoveing(false)
{
    
}
DayBenefit_Layer::~DayBenefit_Layer()
{
    BenefitDataManager::getInstance()->destroyInstance();
}

void DayBenefit_Layer::onExit()
{
    BaseLayer::onExit();
}
void DayBenefit_Layer::onEnter()
{
    BaseLayer::onEnter();
}
void DayBenefit_Layer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void DayBenefit_Layer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestbenefitMsg();
}
bool DayBenefit_Layer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        m_userVipLevel = GlobalInfo::getInstance()->vipLevel;
        this->setBackground(IMG_SIGNIN_BENEFIT_DAY_BG);
        this->createLayer();
        this->isAbleGuiding = true;
        bref = true;
    } while (false);
    return bref;
}
DayBenefit_Layer* DayBenefit_Layer::create()
{
    DayBenefit_Layer* layer = new DayBenefit_Layer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void DayBenefit_Layer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    //vip送福利拉 字体
//    Sprite* box=Sprite::create(IMG_SIGNIN_BENEFIT_DAY_OTHERLABEL);
//    box->setAnchorPoint(Point::ZERO);
//    box->setPosition(-(box->getContentSize().width),0);
//    bg->addChild(box,10);
//    
//    CommonEffect* commonEffect2 = CommonEffect::create("fuli-VIP",true,false);
//    commonEffect2->setAnchorPoint(Point(0.5,0.5));
//    commonEffect2->setPosition(-(box->getContentSize().width)+50,125);
//    bg->addChild(commonEffect2,11);
    
    
    
//    const char* pathList[2] = {IMG_PUBLIC_LABEL_WEEKBENEFIT,IMG_PUBLIC_LABEL_DAYBENEFIT};
//    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 28, CC_CALLBACK_1(DayBenefit_Layer::onComboBoxBtnClick, this));
//    for (int i = 0; i<2; i++) {
//        boxBtn->addBtn(IMG_PUBLIC_BUTTON_SIGNIN_GREEN, IMG_PUBLIC_BUTTON_SIGNIN_YELLOW, pathList[1-i]);
//        PublicShowUI::setDot(boxBtn, Point::ZERO, false,functionList[i]);
//    }
    
    
    int functionList[2] = {DictFunctionEnumWelfareDay,DictFunctionEnumWelfareWeek};
    const char* pathlist1[] = {IMG_PUBLIC_LABEL_DAYBENEFITUN,IMG_PUBLIC_LABEL_WEEKBENEFITUN };
    const char* pathlist2[] = {IMG_PUBLIC_LABEL_DAYBENEFITCHOSE,IMG_PUBLIC_LABEL_WEEKBENEFITCHSOE};
    
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 20, CC_CALLBACK_1(DayBenefit_Layer::onComboBoxBtnClick, this));
    for (int i = 0; i<2; i++) {
        
        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathlist1[i], pathlist2[i]);
        PublicShowUI::setDot(boxBtn, Point::ZERO, false,functionList[i]);
    }
    
    boxBtn->getButtonAt(0)->selected();
    boxBtn->setPosition(180 ,385);
    bg->addChild(boxBtn,3);
}
void DayBenefit_Layer::onClickBtn(Ref* psender)
{
    
}
void DayBenefit_Layer::onComboBoxBtnClick(Ref* psender)
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
void DayBenefit_Layer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
/*-------------------------------------列表------------------------------------------------*/
void DayBenefit_Layer::createTableView()
{
    
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*3;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
//    PublicShowUI::setTargetScale(_tableView);
    _tableView->setPosition(150,5);
    _tableView->reloadData();
    bg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* DayBenefit_Layer::singleList(ssize_t idx)
{
    
    Sprite* cellbg = Sprite::create(IMG_SEVEENDAY_CELLBG);//IMG_SEVEENDAY_CELLBG
    cellbg->setAnchorPoint(Point::ZERO);
    
    
    BenefitDayData* data = BenefitDataManager::getInstance()->benefitDayList->at(idx);
    size_t len = data->benefitList->size();
    
    UserHeadLayer* userHead = NULL;
    UserEquipLayer* head = NULL;
    int index = 0;
    string viplevel = StringUtils::format("VIP%ld",m_userVipLevel+idx);
    Label* viplevellabel = PublicShowUI::getLabel(viplevel.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),20,false,false);
    viplevellabel->setAnchorPoint(Point::ZERO);
    viplevellabel->setPosition(50,cellbg->getContentSize().height-viplevellabel->getContentSize().height-13);
    cellbg->addChild(viplevellabel,1);
    
    Sprite* spr = Sprite::create(IMG_SIGNIN_BENEFIT_DAT_SPECIALFRAL);
    spr->setAnchorPoint(Point::ZERO);
    spr->setPosition(10,cellbg->getContentSize().height/2-spr->getContentSize().height/2-20);
    cellbg->addChild(spr,1);
    
//    Label* viplevellabel1 = PublicShowUI::getLabel(viplevel.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),20,false,false);
//    viplevellabel1->setAnchorPoint(Point::ZERO);
//    viplevellabel1->setPosition(40,cellbg->getContentSize().height/2-viplevellabel1->getContentSize().height/2-20);
//    cellbg->addChild(viplevellabel1,1);
    
    for (int i = 0; i < len; i++) {
        BenefitData* dataitem = data->benefitList->at(i);
        
        const char* resource = PublicShowUI::getGoods(dataitem->itemType, dataitem->itemId);
        if(  dataitem->itemType == DictItemTypeEnumItemHero)
        {
            userHead=UserHeadLayer::create(resource,dataitem->itemQuality,false);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setScale(.6);
            userHead->setHeadInfo(1, 1);
            userHead->setPosition(180+index*(userHead->getContentSize().width-30),10);
            cellbg->addChild(userHead,5,idx*10+i);
            index++;
            userHead->addTouchBegainCallBack(this, callfuncN_selector(DayBenefit_Layer::onHeroHeadClick));
        }
        else if(dataitem->itemType == DictItemTypeEnumItemEquip || dataitem->itemType == DictItemTypeEnumItemBook || dataitem->itemType == DictItemTypeEnumItemMater|| dataitem->itemType == DictItemTypeEnumItem|| dataitem->itemType == DictItemTypeEnumRoleResource)
        {
            head = UserEquipLayer::create(resource,dataitem->itemQuality,false);
            head->setAnchorPoint(Point::ZERO);
            head->setScale(.6);
            if (dataitem->itemType == 4) {
                head->setFragment();
            }else if (dataitem->itemType == 3)
            {
                head->setLetterFragment();
            }
            head->setPosition(180+index*(head->getContentSize().width-30),10);
            cellbg->addChild(head,5,idx*10+i);
            index++;
            head->addTouchBegainCallBack(this, callfuncN_selector(DayBenefit_Layer::onHeroHeadClick));
        }
        string count = StringUtils::format("x%d",dataitem->itemCount);
        Label* label = PublicShowUI::getLabelNumber(count.c_str(), PublicShowUI::getColor3b(COLOR_HEAD_WHITE), 26, false, false);
        label->setAnchorPoint(Point::ZERO);
        if (head) {
            label->setPosition(head->getContentSize().width-label->getContentSize().width-5,2);
            head->addChild(label,5);
        }else{
            label->setPosition(userHead->getContentSize().width-label->getContentSize().width-5,2);
            userHead->addChild(label,5);
        }
    }
    
    if (data->vipStatue  == 1)//可领取
    {
        
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(DayBenefit_Layer::onClick,this));
        btn->setAnchorPoint(Point::ZERO);
        PublicShowUI::setDot(btn,Point::ZERO,false,DictFunctionEnumWelfareDay);
        btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,cellbg->getContentSize().height/2-btn->getContentSize().height/2);
        cellbg->addChild(btn,1,1);
        Sprite* btnWored = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        btnWored->setAnchorPoint(Point::ZERO);
        btnWored->setPosition(Point::ZERO);
        btn->addChild(btnWored,10);
        
    }
    else if (data->vipStatue == 2)//不可领取
    {
        
        Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(DayBenefit_Layer::onClick,this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(cellbg->getContentSize().width-btn->getContentSize().width-20,cellbg->getContentSize().height/2-btn->getContentSize().height/2);
        cellbg->addChild(btn,1,2);
        Sprite* btnWored = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        btnWored->setAnchorPoint(Point::ZERO);
        btnWored->setPosition(Point::ZERO);
        btn->addChild(btnWored,10);
        btn->setEnabled(false);
    }
    else if (data->vipStatue == 3)//当日已领取
    {
        Sprite* spr = Sprite::create(IMG_SIGNIN_BENEFIT_DAY_DRAWDOWN);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPosition(cellbg->getContentSize().width-spr->getContentSize().width-5,10);
        cellbg->addChild(spr);
    }

    return cellbg;
}

void DayBenefit_Layer::onHeroHeadClick(Node* pSender)
{
    if(!isMoveing)
    {
        BenefitDayData* data = BenefitDataManager::getInstance()->benefitDayList->at(pSender->getTag()/10);
        BenefitData* dataitem = data->benefitList->at(pSender->getTag()%10);
        TipsLayer::show(dataitem->itemType, dataitem->itemId, dataitem->itemCount);
    }
    log("%d,%d,%d",pSender->getTag(),pSender->getTag()/10,pSender->getTag()%10);
    
}
void DayBenefit_Layer::onClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    if (target->getTag() == 1) {
        requestlingquMsg();
    }else if (target->getTag() == 2)
    {
        SdkManager::getInstance()->requestChargeOrder(kRecharge_type_other, 0, 0, 10);
    }
}
TableViewCell* DayBenefit_Layer::tableCellAtIndex(TableView *table, ssize_t idx)
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
    list->setPosition(0,10);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size DayBenefit_Layer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_SEVEENDAY_CELLBG);
    cellSize.height = temp->getContentSize().height+10;
    cellSize.width = temp->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t DayBenefit_Layer::numberOfCellsInTableView(TableView *table)
{
    ssize_t  now_count =BenefitDataManager::getInstance()->benefitDayList->size();
    return now_count;
}
//点击cell事件
void DayBenefit_Layer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%d",cell->getTag());
     isMoveing = false; 
}
void DayBenefit_Layer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
}
//-------------------------------------------------连接服务器--------------------------------------------------//
void DayBenefit_Layer::requestbenefitMsg()
{
    Dialog::showServerLoading();
    BoonDayPageMsg* msg = new BoonDayPageMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void DayBenefit_Layer::onBenefitMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    BenefitDataManager::getInstance()->clearbenefitList();
    if(message->messageID == SCENSE_CLIENT_BOON_BoonDayPageResp)
    {
        if(message->state)//返回成功
        {
            int vipsize = message->byteStream->getByte();
            for (int i = 0; i<vipsize; i++)
            {
                BenefitDayData * data = new BenefitDayData();
                data->autorelease();
                data->vipStatue = message->byteStream->getByte();
                data->ItemSize = message->byteStream->getByte();
                for (int j = 0; j < data->ItemSize; j ++)
                {
                    BenefitData* itemdata = new BenefitData();
                    itemdata->autorelease();
                    itemdata->itemType = message->byteStream->getByte();
                    itemdata->itemId = message->byteStream->getInt();
                    itemdata->itemQuality = message->byteStream->getByte();
                    itemdata->itemCount = message->byteStream->getInt();
                    itemdata->itemName = message->byteStream->getUTF8();
                    data->benefitList->pushBack(itemdata);
                }
                BenefitDataManager::getInstance()->addData(data);
            }
            
            createTableView();
        }
        
    }
}

void DayBenefit_Layer::requestlingquMsg()
{
    Dialog::showServerLoading();
    BoonDayReceiveMsg* msg = new BoonDayReceiveMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void DayBenefit_Layer::onlingquProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();

    if(message->messageID == SCENSE_CLIENT_BOON_BoonDayReceiveResp)
    {
        if(message->state)//返回成功
        {
//            NoticeManager::getInstance()->showNotice("恭喜您领取成功！");
            
            
            Vector<BaseTypeData*> *m_baseList = new Vector<BaseTypeData*>();
            m_baseList->clear();
            
            size_t lendata = BenefitDataManager::getInstance()->benefitDayList->size();
            for (int i = 0 ; i < lendata; i++) {
                BenefitDayData* data = BenefitDataManager::getInstance()->benefitDayList->at(i);
                if (data->vipStatue == 1) {
                    size_t len = data->benefitList->size();
                    for (int j= 0; j<len; j++) {
                        BaseTypeData *baseData=new BaseTypeData();
                        baseData->autorelease();
                        baseData->dataId=data->benefitList->at(j)->itemId;
                        baseData->dataName=data->benefitList->at(j)->itemName;
                        baseData->dataType=data->benefitList->at(j)->itemType;
                        baseData->dataQuality=data->benefitList->at(j)->itemQuality;
                        baseData->dataCount = data->benefitList->at(j)->itemCount;
                        m_baseList->pushBack(baseData);
                    }
                }
            }
    
            AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
            
            requestbenefitMsg();
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumWelfareDay));
        }
        
    }
}


void DayBenefit_Layer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOON_BoonDayPageResp).c_str(), CC_CALLBACK_1(DayBenefit_Layer::onBenefitMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_BOON_BoonDayReceiveResp).c_str(), CC_CALLBACK_1(DayBenefit_Layer::onlingquProcess, this));
}
