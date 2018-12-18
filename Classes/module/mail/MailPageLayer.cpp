//
//  MailPageLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/10/21.
//
//

#include "MailPageLayer.h"
#include "../../common/TouchSprite/Button.h"

#include "../../common/StringUtil.h"
#include "../../net/NetworkDataProcessing.h"
#include "maildata/MailCellDataManager.h"
#include "../../common/Dialog/Dialog.h"
#include "../../message/Decoding/mail/MailCellMsg.h"
#include "../../message/Decoding/mail/MailReceiveMsg.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../avatar/hero/Hero.h"
#include "../userWealth/UserHeadLayer.h"
#include "../awardBox/AwardBox_Layer.h"
#include "../tips/TipsLayer.h"
#include "../../commonData/enum/DictFunctionEnum.h"
MailPageLayer::MailPageLayer()
:listBg(NULL)
,m_mailId(0)
,TAG_BUTTON(10)
,TAG_TABLEVIEW(11)
,_tableView(NULL)
,sx(1)
,m_baseList(NULL)
{
    m_baseList=new Vector<BaseTypeData*>();
}
MailPageLayer::~MailPageLayer()
{
   
}
bool MailPageLayer::init( int _index)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        m_mailId = _index;
        sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_MAIL_LAYERBG);
        this->setClickEnabled(true);
        this->isClickClose = true;
        setbg();
        requestMailCellMsg(m_mailId);
        bref = true;
    } while (false);
    return bref;
}
MailPageLayer* MailPageLayer::create(int _index)
{
    MailPageLayer* layer= new MailPageLayer();
    if(layer && layer->init(_index))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void MailPageLayer::show(int _index)
{
    Scene* scene = Director::getInstance()->getRunningScene();
    MailPageLayer* layer = MailPageLayer::create(_index);
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,10);
}
void MailPageLayer::setbg()
{
    
//    listBg=Sprite::create(IMG_MAIL_LAYERBG);
//    PublicShowUI::setTargetScale(listBg);
//    listBg->setAnchorPoint(Point::ZERO);
//    listBg->setPosition(Point::ZERO);
//    this->addChild(listBg,1);
//    this->setContentSize(listBg->getContentSize());
    
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    Sprite* mailword = Sprite::create(IMG_MAIL_MAILWORD);
    mailword->setAnchorPoint(Point::ZERO);
    layerbg->addChild(mailword,2);
    mailword->setPosition(40,layerbg->getContentSize().height/sx-mailword->getContentSize().height-13);

    Sprite* labelbg = Sprite::create(IMG_MAIL_MAILBG);
    labelbg->setAnchorPoint(Point::ZERO);
    layerbg->addChild(labelbg,2);
    labelbg->setPositionY(this->getContentSize().height/sx-labelbg->getContentSize().height-60);
    
    //领取
    Button* btnword = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, IMG_PUBLIC_BUTTON_TWO_ORANGE, CC_CALLBACK_1(MailPageLayer::onclick, this));
    btnword->setAnchorPoint(Point::ZERO);
    layerbg->addChild(btnword,2,TAG_BUTTON);
    btnword->setPosition(this->getContentSize().width/sx-btnword->getContentSize().width-30,btnword->getContentSize().height+50);
    Sprite* btn = Sprite::create(IMG_PUBLIC_LABEL_DRAW);
    btn->setAnchorPoint(Point::ZERO);
    btnword->addChild(btn,2);
    btn->setPosition(Point::ZERO);
}
void MailPageLayer::onclick(Ref* psender)
{
    requestMailCelReceivelMsg(m_mailId);
}
void MailPageLayer::setgiftItem(int _tpye, string _content,string _sender, string _title)
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    
    //邮件类型
    string maildtpye =  _title;
//    if (_tpye ==1) {
//        maildtpye = "活动奖励";
//    }else if (_tpye == 2)
//    {
//        maildtpye = "系统补偿";
//    }
//    else if (_tpye == 3)
//    {
//        maildtpye = "游戏公告";
//    }
//    else if (_tpye == 4)
//    {
//        maildtpye = "战斗结算";
//    }
//    else if (_tpye == 5)
//    {
//        maildtpye = "出售成功";
//    }
//    else if (_tpye == 6)
//    {
//        maildtpye = "出售失败";
//    }
//    else if (_tpye == 7)
//    {
//        maildtpye = "GM私语";
//    }else{
//        maildtpye =  "";
//    }
    Label* senderlabel = PublicShowUI::getLabel(maildtpye.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),26,false,false);
    senderlabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(senderlabel,2);
    senderlabel->setPosition(30,this->getContentSize().height/sx-120);
    
    //类型文字
    _content = "        "+_content;
    Label* levelLabel = PublicShowUI::getLabel(_content.c_str(),PublicShowUI::getColor3b(COLOR_YELLOW_WHITE),18,false,false);
    levelLabel->setAnchorPoint(Point(0,1));
    levelLabel->setMaxLineWidth(670);
    layerbg->addChild(levelLabel,2);
    levelLabel->setPosition(60,this->getContentSize().height/sx-120);
    
    //发件人
    Label* titlelabel = PublicShowUI::getLabel(_sender.c_str(),PublicShowUI::getColor3b(COLOR_GOLD_LIGHT),26,false,false);
    titlelabel->setAnchorPoint(Point(Point::ZERO));
    layerbg->addChild(titlelabel,2);
    titlelabel->setPosition(this->getContentSize().width/sx-titlelabel->getContentSize().width-40,this->getContentSize().height/sx-260);
}

void MailPageLayer::createTableView()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height+30;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(15,10);
    _tableView->reloadData();
    layerbg->addChild(_tableView,2,TAG_TABLEVIEW);
}
Sprite* MailPageLayer::singleList(ssize_t idx)
{
    if (idx>= MailCellDataManager::getInstance()->mailCellList->size()) {
        return NULL;
    }
    char sttr[100] = "";
    memset(sttr, 0, 100);
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
    Sprite* cellbg = Sprite::create(sttr);
    
    MailCellData* data = MailCellDataManager::getInstance()->mailCellList->at(idx);
    int m_quality = data->quality;
    if (m_quality == 0)
    {
        m_quality = 1;
    }
    const char* path = NULL;
    if(  data->itemType == DictItemTypeEnumItemHero)
    {
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId);
        if (dicthero) {
            path =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
        }else{
            path = PublicShowUI::getGoods(data->itemType, data->itemId);
        }
        if (path) {
            UserHeadLayer* userHead=UserHeadLayer::create(path,m_quality,false);
            userHead->setHeadInfo(1, 1);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setPosition(5,5);
            cellbg->addChild(userHead,5,idx);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(MailPageLayer::onHeroHeadClick));
        }

        

    }
    else if(data->itemType == DictItemTypeEnumItemEquip || data->itemType == DictItemTypeEnumItemBook || data->itemType == DictItemTypeEnumItemMater|| data->itemType == DictItemTypeEnumItem|| data->itemType == DictItemTypeEnumRoleResource)
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
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(MailPageLayer::onHeroHeadClick));
    }
    else if (data->itemType == 100)
    {
        
    }
    
    string namestr =  "x" + PublicShowUI::numberToString(data->itemCount);
    Label* nameLabel = PublicShowUI::getLabel(namestr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    nameLabel->setAnchorPoint(Point(0,0));
    cellbg->addChild(nameLabel,20);
    nameLabel->setPosition(cellbg->getPosition().x+cellbg->getContentSize().width,1);
    
    return cellbg;

}
void MailPageLayer::onHeroHeadClick(Node* pSender)
{
    MailCellData* data = MailCellDataManager::getInstance()->mailCellList->at(pSender->getTag());
    
    DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId);
    if (!dicthero) {
        TipsLayer::show(data->itemType, data->itemId, data->itemCount);

    }
}
TableViewCell* MailPageLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<4; i++) {
        int tag=(int)idx*4+i;
        Sprite* list=singleList(tag);
        if(!list)
        {
            break;
        }
        list->setAnchorPoint(Point::ZERO);
        list->setPositionX((list->getContentSize().width+40)*i+10);
        cell->addChild(list);
        cell->setContentSize(list->getContentSize());
        cell->setTag(tag);
    }
    return cell;

}

//列表大小
Size MailPageLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    if(cellSize.height == 0)
    {
        char sttr[100] = "";
        memset(sttr, 0, 100);
        sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,1);
        Sprite* temp = Sprite::create(sttr);
        cellSize = temp->getContentSize();
        cellSize.width =cellSize.width*4 + 160;
        cellSize.height += 20;
    }
    return cellSize;
}
//获取view的长度
ssize_t MailPageLayer::numberOfCellsInTableView(TableView *table)
{
    int allPage = ceil(double(MailCellDataManager::getInstance()->mailCellList->size()) / 4);
    return allPage;
}
//点击cell事件
void MailPageLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{

    log("%d",cell->getTag());
}

void MailPageLayer::onEnter()
{
    BaseLayer::onEnter();
}
void MailPageLayer::onExit()
{
    BaseLayer::onExit();
}
void MailPageLayer::onEnterTransitionDidFinish()
{
    
    BaseLayer::onEnterTransitionDidFinish();
    
}
void MailPageLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}

//-----------------------------------------------访问服务器-------------------------------------------------------//

void MailPageLayer::requestMailCellMsg(int mailId)//chakanyoujina
{
    Dialog::showServerLoading();
    MailCellMsg* msg = new MailCellMsg(mailId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}

void MailPageLayer::onMailCellMsgProcess(EventCustom* msg)
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    MailCellDataManager::getInstance()->clearMailCellList();//    cleargiltList();
    m_baseList->clear();
    if(message->messageID == SCENSE_CLIENT_MAIL_MailContentResp)
    {
        if(message->state)//返回成功
        {
            int type = message->byteStream->getByte();//邮件类型
            string typeText = message->byteStream->getUTF8();//类型文字
            string sender = message->byteStream->getUTF8();//发件人
            string title = message->byteStream->getUTF8();//邮件标题
            string content = message->byteStream->getUTF8();//邮件美容
            int status = message->byteStream->getByte();
            int len = message->byteStream->getByte();
            for (int i = 0; i < len; i ++) {
                MailCellData* data = new MailCellData;
                BaseTypeData *baseData=new BaseTypeData();
                data->autorelease();
                baseData->autorelease();
                data->itemType = message->byteStream->getByte();
                data->itemId = message->byteStream->getInt();
                data->quality = message->byteStream->getByte();
                data->itemCount = message->byteStream->getShort();
                MailCellDataManager::getInstance()->addData(data);
                
                DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId);
                if (!dicthero) {
                    string stt = PublicShowUI::getName(data->itemType, data->itemId);
                    baseData->dataName = stt;
                }
                baseData->dataType = data->itemType;
                baseData->dataId = data->itemId;
                baseData->dataQuality = data->quality;
                baseData->dataCount = data->itemCount;
                m_baseList->pushBack(baseData);
            }
            setgiftItem(type, content, sender,  title);
            if (len <1) {
                Sprite* btn = (Sprite*)layerbg->getChildByTag(TAG_BUTTON);
                btn->setVisible(false);
            }else{
                createTableView();
            }
        }
        
    }
    
}

void MailPageLayer::requestMailCelReceivelMsg(int mailId)//请求领取
{
    Dialog::showServerLoading();
    MailReceiveMsg* msg = new MailReceiveMsg(mailId);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MailPageLayer::onMailCelReceivelMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if(message->messageID == SCENSE_CLIENT_MAIL_MailReceiveItemResp)
    {
        if(message->state)//返回成功
        {
//            NoticeManager::getInstance()->showNotice("领取成功");
            
            AwardBox_Layer* layer=AwardBox_Layer::create(m_baseList);
            layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2);
            Scene* scene=Director::getInstance()->getRunningScene();
            scene->addChild(layer,2);
            
            broadMsg(CUSTOM_MAIL_MAILCELLINGQUSUEEM);
            broadMsg(CUSTOM_REFRESH_DOT,__Integer::create(DictFunctionEnumMail));
            this->removeFromParent();
            
        }
        
    }
    
}

void MailPageLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MAIL_MailContentResp).c_str(), CC_CALLBACK_1(MailPageLayer::onMailCellMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_MAIL_MailReceiveItemResp).c_str(), CC_CALLBACK_1(MailPageLayer::onMailCelReceivelMsgProcess, this));
}
void MailPageLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

