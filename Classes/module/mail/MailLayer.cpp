//
//  MailLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/20.
//
//

#include "MailLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"

#include "../../common/TouchSprite/TouchSprite.h"
#include "../../protocol/UserCustomEvent.h"
#include "../../net/NetworkDataProcessing.h"
#include "MailPageLayer.h"
#include "maildata/MailDataManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/mail/MailMsg.h"
#include "../../message/Decoding/mail/MailReceiveAllMsg.h"
#include "maildata/MailAllGiftDataManager.h"
#include "MailAllGiftLayer.h"
#include "../../message/Decoding/mail/MailReceiveMsg.h"

MailLayer::MailLayer()
:listBg(NULL)
,TAG_TABLEVIEW(3)
,_tableView(NULL)
,isMoveing(false)
,isDownPoint(Point::ZERO)
,TAG_LISTBG(10)
,TAG_BTNLINGQU(11)
,m_index(0)
{
    
}

MailLayer:: ~ MailLayer()
{
    MailDataManager::getInstance()->destroyInstance();
}

bool MailLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        
        this->isAnimation = true;
        this->setClickEnabled(true);
        this->isClickClose = true;//点击外面自动关闭
        this->isShowGrayBg = true;
        this->setBackground(IMG_MAIL_LAYERBG,Point::ZERO,true);
        setBg();
//        createTableView();
        requestMailListMsg();
        bref = true;
    } while (false);
    return bref;
}

MailLayer* MailLayer::create()
{
    MailLayer* list = new MailLayer();
    if(list && list->init())
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return list;
}
void MailLayer::show()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MailLayer* layer = MailLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,0);
}
void MailLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MailLayer::onExit()
{
    BaseLayer::onExit();
}
void MailLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
}
void MailLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

void MailLayer::setBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    listBg=Sprite::create(IMG_MAIL_LAYERBG);
    PublicShowUI::setTargetScale(listBg);
    listBg->setAnchorPoint(Point::ZERO);
    listBg->setPosition(Point::ZERO);
    this->addChild(listBg,1,TAG_LISTBG);
    this->setContentSize(listBg->getContentSize());
    
    Sprite* mailword = Sprite::create(IMG_MAIL_MAILWORD);
    mailword->setAnchorPoint(Point::ZERO);
    listBg->addChild(mailword);
    mailword->setPosition(40,listBg->getContentSize().height/sx-mailword->getContentSize().height-13);
    
    Sprite* topLabel = Sprite::create(IMG_MAIL_TOPLIBLE);
    topLabel->setAnchorPoint(Point::ZERO);
    listBg->addChild(topLabel);
    topLabel->setPosition(20,listBg->getContentSize().height/sx-topLabel->getContentSize().height-65);
    
    Sprite* line = Sprite::create(IMG_MAIL_LINE);
    line->setAnchorPoint(Point::ZERO);
    listBg->addChild(line);
    line->setPositionY(listBg->getContentSize().height/sx-line->getContentSize().height-100);
    
   
    //一键领取
//    Button* btnword = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE, IMG_PUBLIC_BUTTON_FOUR_ORANGE, CC_CALLBACK_1(MailLayer::onallClick, this));
//    btnword->setAnchorPoint(Point::ZERO);
//    listBg->addChild(btnword,1,TAG_BTNLINGQU);
//    btnword->setPosition(listBg->getContentSize().width/sx-btnword->getContentSize().width-30,listBg->getContentSize().height/sx-btnword->getContentSize().height-10);
//
//    Sprite* btn = Sprite::create(IMG_MAIL_RECEIVEWORD);
//    btn->setAnchorPoint(Point::ZERO);
//    btnword->addChild(btn,5);
//    btn->setPosition(Point::ZERO);
//   
//    btnword->setEnabled(false);
//    btnword->setVisible(false);
    
    
}
//一键领取
void MailLayer::onallClick(Ref* psender)
{
//    requestMailAllGiftListMsg();
}

void MailLayer::createTableView()
{
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*2+150;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(15,22);
    _tableView->reloadData();
    listBg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Button* MailLayer::singleList(ssize_t idx)
{
    if(idx >= MailDataManager::getInstance()->mailList->size())
    {
        return NULL;
    }
    MailData* data = MailDataManager::getInstance()->mailList->at(idx);
    Button* cellBg = Button::create(IMG_MAIL_CELLBG, IMG_MAIL_CELLBG, CC_CALLBACK_1(MailLayer::onReiveClick, this));
    cellBg->getTouchListener()->setSwallowTouches(false);
    cellBg->setTag(idx);
    cellBg->setAnchorPoint(Point::ZERO);
    //发件人
    string mailname =data->itemName;
    Label* mailnameLabel = NULL;
    if (data->status == 3)
    {
        mailnameLabel = PublicShowUI::getLabel(mailname.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),20,false,false);
    }else{
        mailnameLabel = PublicShowUI::getLabel(mailname.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    }
    mailnameLabel->setAnchorPoint(Point::ZERO);
    mailnameLabel->setPosition(20,35);
    cellBg->addChild(mailnameLabel,2);

    //
    string maildtpye =  "";
    int m_type = data->type;
    if (m_type ==1) {
        maildtpye = "活动奖励";
    }else if (m_type == 2)
    {
        maildtpye = "系统补偿";
    }
    else if (m_type == 3)
    {
        maildtpye = "游戏公告";
    }
    else if (m_type == 4)
    {
        maildtpye = "战斗结算";
    }
    else if (m_type == 5)
    {
        maildtpye = "出售成功";
    }
    else if (m_type == 6)
    {
        maildtpye = "出售失败";
    }
    else if (m_type == 7)
    {
        maildtpye = "GM私语";
    }else{
        maildtpye =  "";
    }
    
    Label* maildtypeLabel = NULL;
    if (data->status == 3)
    {
        maildtypeLabel = PublicShowUI::getLabel(maildtpye.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),20,false,false);
    }else{
        maildtypeLabel = PublicShowUI::getLabel(maildtpye.c_str(),PublicShowUI::getColor3b(COLOR_LIGHT_RED),20,false,false);
    }
    maildtypeLabel->setAnchorPoint(Point::ZERO);
    maildtypeLabel->setPosition(230,55);
    cellBg->addChild(maildtypeLabel,2);
    
    
    //邮件标题
    string maildes =  data->itemtitle;
    Label* maildesLabel=NULL;
    if (data->status == 3)
    {
        maildesLabel = PublicShowUI::getLabel(maildes.c_str(),PublicShowUI::getColor3b(COLOR_BROWN_HESE),20,false,false);
    }else{
        maildesLabel = PublicShowUI::getLabel(maildes.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    }
    maildesLabel->setAnchorPoint(Point::ZERO);
    maildesLabel->setPosition(250,20);
    cellBg->addChild(maildesLabel,2);
    
    Button* btn = Button::create(IMG_MAIL_GIFTBTN,IMG_MAIL_GIFTBTN,CC_CALLBACK_1(MailLayer::onClick, this));
    btn->setAnchorPoint(Point::ZERO);
    cellBg->addChild(btn,3,idx);
    
    btn->setPosition(cellBg->getContentSize().width-btn->getContentSize().width-20,(cellBg->getContentSize().height-btn->getContentSize().height)/2);
    if (data->status == 1) {
        btn->setEnabled(true);
    }else{
        btn->setPartEnabled(false);
    }
    return cellBg;
}

void MailLayer::onReiveClick(Ref* psender)
{

    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)psender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_LISTBG)->getChildByTag(TAG_TABLEVIEW);
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=(_size.height*2+150*GlobalInfo::getInstance()->screenScaleX);
    _size.width=_size.width+10*GlobalInfo::getInstance()->screenScaleX;
    isDownPoint.x = isDownPoint.x/GlobalInfo::getInstance()->screenScaleX;
    isDownPoint.y = isDownPoint.y/GlobalInfo::getInstance()->screenScaleX;
    log("%f,%f,%f,%f",_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_tableView->getContentSize().width,_tableView->getContentSize().height);
    log("%f,%f",isDownPoint.x,isDownPoint.y);
    log("%f,%f",GlobalInfo::getInstance()->screenScaleX,GlobalInfo::getInstance()->screenScaleY);
    Rect bb=Rect(_tableView->getPositionX()- _tableView->getContentSize().width  * _tableView->getAnchorPoint().x,_tableView->getPositionY()-_tableView->getContentSize().height* _tableView->getAnchorPoint().y,_size.width, _size.height);
    if (bb.containsPoint(isDownPoint)) {
        MailPageLayer::show(MailDataManager::getInstance()->mailList->at(index)->mailId);
        m_index = index;
    }
}

void MailLayer::onClick(Ref* psender)
{
    Node* target = (Node*)psender;
    int index = target->getTag();
    log("%d",index);
    MailPageLayer::show(MailDataManager::getInstance()->mailList->at(index)->mailId);
    m_index = index;
//    requestMailCelReceivelMsg(MailDataManager::getInstance()->mailList->at(index)->mailId);
}
TableViewCell* MailLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Button* list=singleList(idx);
    list->setAnchorPoint(Point::ZERO);
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size MailLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_MAIL_CELLBG);
    cellSize.height = temp->getContentSize().height;
    cellSize.width = temp->getContentSize().width+10;
    return cellSize;
}
//获取view的长度
ssize_t MailLayer::numberOfCellsInTableView(TableView *table)
{
//    ssize_t  now_count =ceil(double(MailDataManager::getInstance()->mailList->size()) / 2);
    ssize_t  now_count = MailDataManager::getInstance()->mailList->size();
    return now_count;
//    return 10;
   
}
//点击cell事件
void MailLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    log("%d",cell->getTag());
}
void MailLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
bool MailLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void MailLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
}
void MailLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    BaseLayer::onTouchEnded(touch, unused_event);
}


void MailLayer::onlingquchenggongProgress(EventCustom* msg)
{
    MailDataManager::getInstance()->mailList ->erase(m_index);
    _tableView->reloadData();
}
//-----------------------------------------------访问服务器-------------------------------------------------------//

void MailLayer::requestMailListMsg()//请求邮件列表信息
{
    Dialog::showServerLoading();
    MailMsg* msg = new MailMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void MailLayer::onMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MailDataManager::getInstance()->clearMailList();//    cleargiltList();
    if(message->messageID == SCENSE_CLIENT_MAIL_MailPageResp)
    {
        if(message->state)//返回成功
        {
            
            int mailsize = message->byteStream->getByte();
            for (int i = 0; i < mailsize; i ++) {
                MailData* data = new MailData;
                data->autorelease();
                data->mailId = message->byteStream->getInt();
                data->type = message->byteStream->getByte();
                data->typeText = message->byteStream->getUTF8();
                data->itemName = message->byteStream->getUTF8();
                data->itemtitle = message->byteStream->getUTF8();
                data->status = message->byteStream->getByte();
                MailDataManager::getInstance()->addData(data);
            }
            createTableView();
//            Button* btn = (Button*)listBg->getChildByTag(TAG_BTNLINGQU);
//            if ( mailsize < 1 ) {
//                btn->setEnabled(false);
//                btn->setVisible(false);
//            }
        }
        
    }

}
void MailLayer::requestMailAllGiftListMsg()//一键领取 请求邮件所有礼物列表信息
{
    Dialog::showServerLoading();
    MailReceiveAllMsg* msg = new MailReceiveAllMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void MailLayer::onMailAllGiftMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MailAllGiftDataManager::getInstance()->clearfindList();
    if(message->messageID == SCENSE_CLIENT_MAIL_MailReceiveAllItemResp)
    {
        if(message->state)//返回成功
        {
            
            short giftsize = message->byteStream->getShort();
            MailAllGiftDataManager::getInstance()->setGiftSizeData(giftsize);
            for (int i = 0; i< giftsize; i++) {
                MailAllGiftData* dataten = new MailAllGiftData;
                dataten->autorelease();
                dataten->itemType = message->byteStream->getByte();
                if (dataten->itemType == 1) {
                    dataten->heroId = message->byteStream->getInt();
                    dataten->heroDictId = message->byteStream->getInt();
                    dataten->force = message->byteStream->getByte();
                    dataten->heroName = message->byteStream->getUTF8();
                    dataten->heroQuality = message->byteStream->getByte();
                    dataten->heroLevel = message->byteStream->getInt();
                    dataten->prestige = message->byteStream->getInt();
                    dataten->combatPower = message->byteStream->getInt();
                    dataten->leadership = message->byteStream->getInt();
                }
                else if(dataten->itemType>1 && dataten->itemType<7)
                {
                    dataten->itemDictId = message->byteStream->getInt();
                    dataten->itemName = message->byteStream->getUTF8();
                    dataten->itemQuality = message->byteStream->getByte();
                    dataten->itemDesc = message->byteStream->getUTF8();
                }
                else if (dataten->itemType == 100)
                {
                    dataten->rolePropId = message->byteStream->getByte();
                    dataten->rolePropId = message->byteStream->getByte();
                }
                MailAllGiftDataManager::getInstance()->addData(dataten);
            }
            if (giftsize>=1) {
                MailAllGiftLayer::show();
            }
            this->removeFromParent();
        }
    }
}

void MailLayer::requestMailCelReceivelMsg(int mailId)//请求领取礼包
{
    Dialog::showServerLoading();
    MailReceiveMsg* msg = new MailReceiveMsg(mailId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MailLayer::onMailCelReceivelMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MailAllGiftDataManager::getInstance()->clearfindList();
    if(message->messageID == SCENSE_CLIENT_MAIL_MailReceiveItemResp)
    {
        if(message->state)//返回成功
        {
            int giftsize = message->byteStream->getByte();
            MailAllGiftDataManager::getInstance()->setGiftSizeData(giftsize);
            for (int i = 0; i< giftsize; i++) {
                MailAllGiftData* dataten = new MailAllGiftData;
                dataten->autorelease();
                dataten->itemType = message->byteStream->getByte();
                if (dataten->itemType == 1) {
                    dataten->heroId = message->byteStream->getInt();
                    dataten->heroDictId = message->byteStream->getInt();
                    dataten->force = message->byteStream->getByte();
                    dataten->heroName = message->byteStream->getUTF8();
                    dataten->heroQuality = message->byteStream->getByte();
                    dataten->heroLevel = message->byteStream->getInt();
                    dataten->prestige = message->byteStream->getInt();
                    dataten->combatPower = message->byteStream->getInt();
                    dataten->leadership = message->byteStream->getInt();
                }
                else if(dataten->itemType>1 && dataten->itemType<7)
                {
                    dataten->itemDictId = message->byteStream->getInt();
                    dataten->itemName = message->byteStream->getUTF8();
                    dataten->itemQuality = message->byteStream->getByte();
                    dataten->itemDesc = message->byteStream->getUTF8();
                }
                else if (dataten->itemType == 100)
                {
                    dataten->rolePropId = message->byteStream->getByte();
                    dataten->rolePropId = message->byteStream->getByte();
                }
                MailAllGiftDataManager::getInstance()->addData(dataten);
            }
            
            MailAllGiftLayer::show();
            this->removeFromParent();
        }
        
    }
}
void MailLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MAIL_MailPageResp).c_str(), CC_CALLBACK_1(MailLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MAIL_MailReceiveAllItemResp).c_str(), CC_CALLBACK_1(MailLayer::onMailAllGiftMsgProcess, this));
//    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MAIL_MailReceiveItemResp).c_str(), CC_CALLBACK_1(MailLayer::onMailCelReceivelMsgProcess, this));
    this->addUserMsg(CUSTOM_MAIL_MAILCELLINGQUSUEEM, CC_CALLBACK_1(MailLayer::onlingquchenggongProgress, this));
}
void MailLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}


