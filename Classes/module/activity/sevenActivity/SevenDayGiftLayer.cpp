//
//  SevenDayGiftLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#include "SevenDayGiftLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "weekrewarddata/WeekRewardPageDatamanager.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../../commonData/enum/DictItemTypeEnum.h"
#include "../../../avatar/hero/Hero.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../tips/TipsLayer.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/Protocal.h"
#include "../../../message/Decoding/sevenday/WeekReceiveMsg.h"
#include "../../../net/NetworkDataProcessing.h"
#include "weekrewarddata/WeekHalfGiftDataManager.h"
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../message/Decoding/sevenday/WeekHalfBuyMsg.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "SevendayChoseHeroLayer.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../publicLayer/GotoModule.h"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../awardBox/AwardBox_Layer.h"
SevenDayGiftLayer::SevenDayGiftLayer()
:sx(1)
,TAG_TABLEVIEW(2)
,TAG_ITEMBG(3)
,TAG_HALFPRIVE(4)
,TAG_NODE(5)
,m_day(1)
,m_rewardType(1)
,m_numhero(1)
{

}
SevenDayGiftLayer::~ SevenDayGiftLayer()
{
    
}

void SevenDayGiftLayer::onExit()
{
    BaseLayer::onExit();
}
void SevenDayGiftLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SevenDayGiftLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void SevenDayGiftLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool SevenDayGiftLayer::init(int _day)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_day = _day;
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_GENERALS_SEVENACTIVITY_BG2);
        this->createLayer();
        initTableView();
        setItembuy(1);
        bref = true;
    } while (false);
    return bref;
}
SevenDayGiftLayer* SevenDayGiftLayer::create(int _day)
{
    SevenDayGiftLayer* layer = new SevenDayGiftLayer();
    if(layer && layer->init(_day))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void SevenDayGiftLayer::createLayer()
{
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    
    const char* pathList[2] = {IMG_PUBLIC_LABEL_SEVENBEN,IMG_PUBLIC_LABEL_HALFPAY};
    ComboBoxBtn* box2Btn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 28, CC_CALLBACK_1(SevenDayGiftLayer::onComboBoxBtn2Click, this));
    for (int i = 0; i<2; i++) {
        box2Btn->addBtn(IMG_PUBLIC_BUTTON_CUSP_FOUR_BLUE, IMG_PUBLIC_BUTTON_CUSP_FOUR_GREEN, pathList[i]);
    }
    box2Btn->setPositionY(285);
    bg->addChild(box2Btn,2);
    box2Btn->getButtonAt(0)->selected();
    
}
void SevenDayGiftLayer::onComboBoxBtn2Click(Ref* psender)
{
    Sprite* spr = (Sprite*)this->getChildByTag(TAG_BG);
    Node* target = (Node*)psender;
    switch (target->getTag()) {
        case 0:
            spr->removeChildByTag(TAG_HALFPRIVE);
            break;
        case 1:
            sethalfPrive();
            break;
        default:
            break;
    }
}

//--------------------------------------------------半价购买------------------------------------------------//
void SevenDayGiftLayer::sethalfPrive()
{
    Sprite* spr = (Sprite*)this->getChildByTag(TAG_BG);
    
    TouchSprite*  halfprivebg =TouchSprite::createWithPic(IMG_GENERALS_SEVENACTIVITY_BG2);
    halfprivebg->setAnchorPoint(Point::ZERO);
    halfprivebg->setPosition(Point::ZERO);
    halfprivebg->setSwallowTouches(true);
    spr->addChild(halfprivebg,4,TAG_HALFPRIVE);
    
    Sprite*  halfbg = Sprite::create(IMG_GENERALS_SEVENACTIVITY_HALFPAY_BG);
    halfbg->setAnchorPoint(Point::ZERO);
    halfbg->setPosition(Point::ZERO);
    halfprivebg->addChild(halfbg,1);
    if (WeekHalfGiftDataManager::getInstance()->halfpriceList->size()<1) {
        return;
    }
    WeekHalfGiftData* data = WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0);
    
    //现价
    string timesStr=StringUtils::format("%d",data->price);
    timesStr = timesStr + "元宝";
    Label* timesLabel = PublicShowUI::getLabel(timesStr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),24,false,false);
    timesLabel->setAnchorPoint(Point::ZERO);
    halfprivebg->addChild(timesLabel,10);
    timesLabel->setPosition(85,40);
    
    //原价
    string oleStr=StringUtils::format("%d",data->priceOri);
    oleStr = oleStr + "元宝";
    Label* oldpriceLabel = PublicShowUI::getLabel(oleStr.c_str(),PublicShowUI::getColor3b(COLOR_BLACK_BROWN),24,false,false);
    oldpriceLabel->setAnchorPoint(Point::ZERO);
    halfprivebg->addChild(oldpriceLabel,10);
    oldpriceLabel->setPosition(270,40);
    
//    //购买人数
//    string allPerStr=StringUtils::format("%d",data->sellCount);
//    Label* allPerLabel = PublicShowUI::getLabel(allPerStr.c_str(),PublicShowUI::getColor3b(COLOR_GREEN_WORD),24,false,false);
//    allPerLabel->setAnchorPoint(Point::ZERO);
//    halfprivebg->addChild(allPerLabel,10);
//    allPerLabel->setPosition(85,7);
//    
//    //购买人数
//    string perStr=StringUtils::format("%d",data->selledCount);
//    Label* perLabel = PublicShowUI::getLabel(perStr.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),24,false,false);
//    perLabel->setAnchorPoint(Point::ZERO);
//    halfprivebg->addChild(perLabel,10);
//    perLabel->setPosition(310,5);

    int m_quality = data->itemQuality;
    if (m_quality == 0)
    {
        m_quality = 1;
    }
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserHeadLayer* userHead=UserHeadLayer::create(resource,m_quality,false);
        userHead->setHeadInfo(1, 1);
        userHead->setAnchorPoint(Point::ZERO);
        userHead->setPosition(410,140);
        halfprivebg->addChild(userHead,2);
        userHead->addTouchBegainCallBack(this, callfuncN_selector(SevenDayGiftLayer::onhalfitemClick));
       
    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType ==DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
    {
        const char* resource = PublicShowUI::getGoods(data->itemType, data->itemId);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_quality,false);
        head->setAnchorPoint(Point::ZERO);
        if (data->itemType == 4) {
            head->setFragment();
        }else if (data->itemType == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(410,140);
        halfprivebg->addChild(head,2);
        head->addTouchBegainCallBack(this, callfuncN_selector(SevenDayGiftLayer::onhalfitemClick));
    }
    
    string namestr = data->itemName;
    namestr = namestr + "x" + PublicShowUI::numberToString(data->itemCount);
    Label* nameLabel = PublicShowUI::getLabel(namestr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),18,false,false);
    nameLabel->setAnchorPoint(Point(0.5,0));
    halfprivebg->addChild(nameLabel,20);
    nameLabel->setPosition(475,100);
    
    Button* buybtn = Button::create(IMG_BUTTON_REDBTN, IMG_BUTTON_REDBTN, CC_CALLBACK_1(SevenDayGiftLayer::onBuyClick, this));
    buybtn->setAnchorPoint(Point::ZERO);
    buybtn->setPosition(410,30);
    halfprivebg->addChild(buybtn,2);
    Sprite* buyspr = Sprite::create(IMG_PUBLIC_LABEL_BUYWORD);
    buyspr->setAnchorPoint(Point::ZERO);
    buyspr->setPosition(Point::ZERO);
    buybtn->addChild(buyspr,5);
    if (data->status != 1) {
        buybtn->setEnabled(false);
        buybtn->setVisible(false);
    }
}
void SevenDayGiftLayer::onBuyClick(Ref* pSender)
{
    if(WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0)->status == 2)
    {
        NoticeManager::getInstance()->showNotice("已购买");
        return;
    }
    if (GlobalInfo::getInstance()->userGold < WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0)->price) {
        NoticeManager::getInstance()->showNotice("元宝不足，不可购买");
    }else{
        requestWeekhalfBuyMsg(m_day);
    }
}
void SevenDayGiftLayer::onhalfitemClick(Node* pSender)
{
    WeekHalfGiftData* data = WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0);
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}


//------------------------------------------------------福利-------------------------------------------------------
void SevenDayGiftLayer::setItembuy(int itemtype)
{
    m_rewardType = itemtype;
    Sprite* bg = (Sprite*)this->getChildByTag(TAG_BG);
    bg->removeChildByTag(TAG_ITEMBG);
    Sprite*  itembg = (Sprite*)bg->getChildByTag(TAG_ITEMBG);
    itembg =  Sprite::create(IMG_GENERALS_SEVENACTIVITY_AWARD_BG);
    itembg->setAnchorPoint(Point::ZERO);
    itembg->setPosition(280,8);
    bg->addChild(itembg,1,TAG_ITEMBG);
   
    if (WeekRewardPageDatamanager::getInstance()->desclList->at(itemtype-1)->status == 1)//领取
    {
        Button* btn = Button::create(IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, CC_CALLBACK_1(SevenDayGiftLayer::gotoClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(Point::ZERO);
        itembg->addChild(btn);
        Sprite* spr = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPositionX(85);
        btn->addChild(spr,5);
    }else if (WeekRewardPageDatamanager::getInstance()->desclList->at(itemtype-1)->status == 2)//不可领取
    {
        Button* btn = Button::create(IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, CC_CALLBACK_1(SevenDayGiftLayer::gotoClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(Point::ZERO);
        itembg->addChild(btn);
        Sprite* spr = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPositionX(85);
        btn->addChild(spr,5);
        btn->setEnabled(false);
    }else if (WeekRewardPageDatamanager::getInstance()->desclList->at(itemtype-1)->status == 3)//已领取
    {
        Button* btn = Button::create(IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, IMG_GENERALS_SEVENACTIVITY_AWARD_BTNBG, CC_CALLBACK_1(SevenDayGiftLayer::gotoClick, this));
        btn->setAnchorPoint(Point::ZERO);
        btn->setPosition(Point::ZERO);
        itembg->addChild(btn);
        Sprite* spr = Sprite::create(IMG_PUBLIC_LABEL_ISLINGQU);
        spr->setAnchorPoint(Point::ZERO);
        spr->setPositionX(85);
        btn->addChild(spr,5);
        btn->setEnabled(false);
    }
    
    
    Node* node = bg->getChildByTag(TAG_NODE);
    if (node) {
        bg->removeChildByTag(TAG_NODE);
    }
    node = Node::create();
    node->setAnchorPoint(Point::ZERO);
    size_t len = WeekRewardPageDatamanager::getInstance()->rewardlList->size();
    int m_tag = 0;
    const char* resource = "";
    UserEquipLayer* head = NULL;
    UserHeadLayer* userHead = NULL;
    for (int i = 0; i<len; i++)
    {
        if(WeekRewardPageDatamanager::getInstance()->rewardlList->at(i)->rewardType == itemtype)
        {
            WeekRewardData* data = WeekRewardPageDatamanager::getInstance()->rewardlList->at(i);
            int m_quality = data->itemQuality;
            if (m_quality == 0)
            {
                m_quality = 1;
            }
            
            if(  data->itemType == DictItemTypeEnumItemHero)
            {
                resource = PublicShowUI::getGoods(data->itemType, data->itemId);
                userHead=UserHeadLayer::create(resource,m_quality,false);
                userHead->setHeadInfo(1, 1);
                userHead->setAnchorPoint(Point::ZERO);
                userHead->setScale(0.6);
                userHead->setPosition(m_tag*(userHead->getContentSize().width-30),100);
                node->addChild(userHead,2,i);
                userHead->addTouchBegainCallBack(this, callfuncN_selector(SevenDayGiftLayer::onitemClick));
                m_tag ++;
            }
            else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType ==DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
            {
                resource = PublicShowUI::getGoods(data->itemType, data->itemId);
                head = UserEquipLayer::create(resource,m_quality,false);
                head->setAnchorPoint(Point::ZERO);
                if (data->itemType == 4) {
                    head->setFragment();
                }else if (data->itemType == 3)
                {
                    head->setLetterFragment();
                }
                head->setScale(0.6);
                head->setPosition(m_tag*(head->getContentSize().width-30),100);
                node->addChild(head,2,i);
                m_tag ++;
                head->addTouchBegainCallBack(this, callfuncN_selector(SevenDayGiftLayer::onitemClick));
            }
            
            string countstr = StringUtils::format("x%d",data->itemCount);
            Label* countLabel = PublicShowUI::getLabel(countstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),16,false,false);
            countLabel->setAnchorPoint(Point::ZERO);
            node->addChild(countLabel,20);
            if (head) {
                countLabel->setPosition(72+(m_tag-1) * (head->getContentSize().width-32),100);
            }else{
                countLabel->setPosition(72+(m_tag-1) * (userHead->getContentSize().width-32),100);
            }
        }
    }
    size_t desclen = WeekRewardPageDatamanager::getInstance()->desclList->size();
    for (int i = 0; i< desclen; i++) {
        if(WeekRewardPageDatamanager::getInstance()->desclList->at(i)->rewardType == itemtype)
        {
            string allPriceStr = WeekRewardPageDatamanager::getInstance()->desclList->at(i)->desc;
            Label* allPriceLabel = PublicShowUI::getLabel(allPriceStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
//            allPriceLabel->setAnchorPoint(Point::ZERO);
            allPriceLabel->setMaxLineWidth(200);
            allPriceLabel->setPosition(120,50);
            node->addChild(allPriceLabel,3);
        }
    }
    
    node->setPosition(300,70);
    bg->addChild(node,2,TAG_NODE);
}
void SevenDayGiftLayer::onitemClick(Node* pSender)
{
    WeekRewardData* data = WeekRewardPageDatamanager::getInstance()->rewardlList->at(pSender->getTag());
    TipsLayer::show(data->itemType, data->itemId, data->itemCount);
}
void SevenDayGiftLayer::gotoClick(Ref* pSender)//福利领取
{

    if (WeekRewardPageDatamanager::getInstance()->desclList->at(m_rewardType-1)->status == 1)
    {
        if (m_day == 7 && m_rewardType == 1)
        {
            SevendayChoseHeroLayer::show(m_rewardType);//当请求领取武将的时候（第七天）
        }
        else
        {
            if (m_rewardType>3) {
                requestWeekRewardMsg(m_day, 4, m_rewardType-3,0);//当请求领取任务的时候
            }else{
                requestWeekRewardMsg(m_day, m_rewardType, 0,0);
            }
        }
        
    }
    else if(WeekRewardPageDatamanager::getInstance()->desclList->at(m_rewardType-1)->status == 2)
    {
        NoticeManager::getInstance()->showNotice("完成任务才可以领取哦");
//        onqianwang(m_type);
    }
    else if (WeekRewardPageDatamanager::getInstance()->desclList->at(m_rewardType-1)->status == 3)
    {
        NoticeManager::getInstance()->showNotice("已领取");
    }
}
void SevenDayGiftLayer::onqianwang(int _type)
{
//    if (m_type == 1)
//    {
//        GotoModule::gotoModuleByFunctionID(DictFunctionEnumGoldCharge, 1);
//    }else if (m_type == 3)
//    {
//        NoticeManager::getInstance()->showNotice("完成任务才可以领取哦");
//    }else if (m_type>=4)
//    {
//        
//    }
}

void SevenDayGiftLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
//--------------------------------列表部分-------------------------------------------------------//
void SevenDayGiftLayer::initTableView()
{

    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* bg=(Sprite*)this->getChildByTag(TAG_BG);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp=_tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.width=_size.width+20;
    _size.height=_size.height*3+15;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));

    _tableView->setPosition(8,10);
    bg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Button* SevenDayGiftLayer::singleList(ssize_t idx)
{
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_GENERALS_SEVENACTIVITY_CASE,idx+1);
    Button* cellbg = Button::create(sttr, "", CC_CALLBACK_1(SevenDayGiftLayer::onCellClick, this));
    cellbg->getTouchListener()->setSwallowTouches(false);
    cellbg->setAnchorPoint(Point(0.5,0.5));
    cellbg->setTag(idx);
    
    return cellbg;
}
void SevenDayGiftLayer::onCellClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int index = target->getTag();
    setItembuy(index+1);
}
TableViewCell* SevenDayGiftLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{

    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Button* list=singleList(idx);
    list->setAnchorPoint(Point(0.5,0.5));
    cell->addChild(list);
    list->setPosition(list->getContentSize().width/2,list->getContentSize().height/2);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size SevenDayGiftLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    if(cellSize.height == 0)
    {
        char sttr[100] = "";
        memset(sttr, 0, 100);
        sprintf(sttr,IMG_GENERALS_SEVENACTIVITY_CASE,1);
        Sprite* temp = Sprite::create(sttr);
        cellSize = temp->getContentSize();
        cellSize.height += 3;
    }
    return cellSize;
}
//获取view的长度
ssize_t SevenDayGiftLayer::numberOfCellsInTableView(TableView *table)
{
    return 5;
}
//点击cell事件
void SevenDayGiftLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{

}
void SevenDayGiftLayer::onChoseHeroProcess(EventCustom* msg)
{
    __Integer* inter = (__Integer*)msg->getUserData();
    m_numhero = inter->getValue();
    requestWeekRewardMsg(m_day,m_rewardType,0,m_numhero);
}
//-----------------------------------------------访问服务器-------------------------------------------------------//

void SevenDayGiftLayer::requestWeekRewardMsg(int _day, int _type, int _numPrice, int _numHero)//q请求领取奖励
{
    Dialog::showServerLoading();
    if(_type == 1)
    {
        _type = 2;
    }else if (_type == 2)
    {
        _type = 1;
    }
    WeekReceiveMsg* msg = new WeekReceiveMsg(_day, _type, _numPrice, _numHero);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void SevenDayGiftLayer::onWeekDayRewardMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekReceiveResp)
    {
        if(message->state)//返回成功
        {
            WeekRewardPageDatamanager::getInstance()->desclList->at(m_rewardType-1)->status = 3;
            setItembuy(m_rewardType);
           
            Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
            m_basegift->clear();
            size_t len = WeekRewardPageDatamanager::getInstance()->rewardlList->size();
            for (int i = 0; i<len; i++) {
                WeekRewardData* data =  WeekRewardPageDatamanager::getInstance()->rewardlList->at(i);
                if (data->rewardType == m_rewardType) {
                    if (m_day == 7 && data->rewardType == 1) {
                        if (m_numhero == 1)
                        {
                            m_numhero = i+100;
                        }
                        else if (m_numhero == 2)
                        {
                            m_numhero = i+101;
                        }
                        else if (m_numhero == 3)
                        {
                            m_numhero = i+102;
                        }
                    }else{
                        BaseTypeData* basedata = new BaseTypeData();
                        basedata->autorelease();
                        basedata->dataId = data->itemId;
                        basedata->dataName = data->itemName;// itemName;
                        basedata->dataType = data->itemType;
                        basedata->dataQuality = data->itemQuality;
                        basedata->dataCount = data->itemCount;
                        m_basegift->pushBack(basedata);
                    }
                }
//                if (m_day == 7) {
//                    if (data->rewardType == m_rewardType) {
//                        if(m_rewardType == 2)
//                        {
//                            if (m_numhero == 1)
//                            {
//                                m_numhero = i+100;
//                            }
//                            else if (m_numhero == 2)
//                            {
//                                m_numhero = i+101;
//                            }
//                            else if (m_numhero == 3)
//                            {
//                                m_numhero = i+102;
//                            }
//                        }else{
//                            BaseTypeData* basedata = new BaseTypeData();
//                            basedata->autorelease();
//                            basedata->dataId = data->itemId;
//                            basedata->dataName = data->itemName;// itemName;
//                            basedata->dataType = data->itemType;
//                            basedata->dataQuality = data->itemQuality;
//                            m_basegift->pushBack(basedata);
//                        }
//                    }
//                }else{
//                    if (data->rewardType == m_rewardType) {
//                        BaseTypeData* basedata = new BaseTypeData();
//                        basedata->autorelease();
//                        basedata->dataId = data->itemId;
//                        basedata->dataName = data->itemName;// itemName;
//                        basedata->dataType = data->itemType;
//                        basedata->dataQuality = data->itemQuality;
//                        m_basegift->pushBack(basedata);
//                    }
//                }
            }
            if (m_day == 7 && m_rewardType == 1) {
                WeekRewardData* data =  WeekRewardPageDatamanager::getInstance()->rewardlList->at(m_numhero-100);
                BaseTypeData* basedata = new BaseTypeData();
                basedata->autorelease();
                basedata->dataId = data->itemId;
                basedata->dataName = data->itemName;// itemName;
                basedata->dataType = data->itemType;
                basedata->dataQuality = data->itemQuality;
//                basedata->dataCount = data->itemCount;
                m_basegift->pushBack(basedata);
            }
            AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer);
        }
    }
}
void SevenDayGiftLayer::requestWeekhalfBuyMsg(int _day)//q请求半价购买领取奖励
{
    Dialog::showServerLoading();
    WeekHalfBuyMsg* msg = new WeekHalfBuyMsg(_day);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void SevenDayGiftLayer::onWeekhalfBuyProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_WEEK_WeekHalfBuyResp)
    {
        if(message->state)//返回成功
        {
            NoticeManager::getInstance()->showNotice("购买成功");
        }
        WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0)->status = 2;
        
        
        Vector<BaseTypeData*> *m_basegift = new Vector<BaseTypeData*>();
        m_basegift->clear();
        
        WeekHalfGiftData* data =  WeekHalfGiftDataManager::getInstance()->halfpriceList->at(0);
        BaseTypeData* basedata = new BaseTypeData();
        basedata->autorelease();
        basedata->dataId = data->itemId;
        basedata->dataName = data->itemName;// itemName;
        basedata->dataType = data->itemType;
        basedata->dataQuality = data->itemQuality;
        basedata->dataCount = data->itemCount;
        m_basegift->pushBack(basedata);
        
        AwardBox_Layer* layer=AwardBox_Layer::create(m_basegift);
        layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
        Scene* scene=Director::getInstance()->getRunningScene();
        scene->addChild(layer);

        
    }
    
}
void SevenDayGiftLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekReceiveResp).c_str(), CC_CALLBACK_1(SevenDayGiftLayer::onWeekDayRewardMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_WEEK_WeekHalfBuyResp).c_str(), CC_CALLBACK_1(SevenDayGiftLayer::onWeekhalfBuyProcess, this));
    this->addUserMsg(CUSTOM_WEEK_CHOSE_HERO, CC_CALLBACK_1(SevenDayGiftLayer::onChoseHeroProcess, this));
}


