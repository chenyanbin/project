//
//  FamouseFriendLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/29.
//
//

#include "FamouseFriendLayer.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseFriendMsg.hpp"
#include "../../../message/Decoding/famouseGeneral/FamouseShareFriendMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../userWealth/UserHeadLayer.h"
#include "../../../common/comboxBtn/ComboBoxBtn.h"
#include "../../../common/noticeManager/NoticeManager.h"
#include "../../../protocol/UserCustomEvent.h"
FamouseFriendLayer::FamouseFriendLayer()
:TAG_TABLEVIEW(1)
,m_dataList(NULL)
,isMoveing(false)
{
    m_dataList = new Vector<FamouseFriendData*>();
    shareList = new vector<long>();
}
FamouseFriendLayer::~FamouseFriendLayer()
{
    CC_SAFE_DELETE(m_dataList);
    m_dataList = NULL;
   CC_SAFE_DELETE(shareList);
    shareList = NULL;
}
bool FamouseFriendLayer::init()
{
    this->isClickClose = true;
    this->isShowGrayBg = true;
    
    setBg();
    setPageBtn();
    return true;
}
void FamouseFriendLayer::setBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
    Node* bg = this->getChildByTag(TAG_BG);
    Sprite* listBg2=Sprite::create(IMG_PUBLIC_LAYER_TITLEBG);
    listBg2->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(listBg2);
    listBg2->setPosition(bg->getPositionX()+15*sx,bg->getPositionY()+450*sx);
    this->addChild(listBg2,3);

    Sprite* bottomWord = Sprite::create(IMG_FAOUSE_FRIENDWORD);
    bottomWord->setAnchorPoint(Point(.5,0));
    PublicShowUI::setTargetScale(bottomWord,false,false);
    bottomWord->setPosition(bg->getContentSize().width/2, 15 * sx);
    this->addChild(bottomWord,4);
}
void FamouseFriendLayer::setPageBtn()
{
     float sx = GlobalInfo::getInstance()->screenScaleX;
    const char* pathList[3] = {IMG_PUBLIC_LABEL_NAMEFIRST1,IMG_PUBLIC_LABEL_LEVEL,IMG_PUBLIC_LABEL_BFIRST1};
    const char* pathList2[3] = {IMG_PUBLIC_LABEL_NAMEFIRST2,IMG_PUBLIC_LABEL_LEVEL1,IMG_PUBLIC_LABEL_BFIRST2};
    ComboBoxBtn* boxBtn = ComboBoxBtn::create(ComboBoxBtn::ASIDE::ASIDE_HORIZONTAL, 10, CC_CALLBACK_1(FamouseFriendLayer::onTopComboBoxClick, this));
    for (int i = 0; i<3; i++) {

        boxBtn->addCustomBtn(IMG_PUBLIC_COMBOBOX_RANK1, IMG_PUBLIC_COMBOBOX_RANK2, pathList[i], pathList2[i]);
    }
    boxBtn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(boxBtn);
    boxBtn->setPosition(20*sx,this->getContentSize().height - boxBtn->getContentSize().height - 26 * sx);
    boxBtn->getButtonAt(0)->selected();
    this->addChild(boxBtn,4);
    
    
    //请求支援
    Button* supportBtn = Button::create(IMG_PUBLIC_BUTTON_FOUR_ORANGE,"", CC_CALLBACK_1(FamouseFriendLayer::onSupportBtnClick, this));
    supportBtn->setAnchorPoint(Point(.5,.5));
    Sprite* title = Sprite::create(IMG_PUBLIC_LABEL_SUPPORTLABEL);
    supportBtn->addChild(title, 10);
  
    PublicShowUI::setTargetScale(supportBtn);
    supportBtn->setPosition(this->getContentSize().width - supportBtn->getContentSize().width,this->getContentSize().height - supportBtn->getContentSize().height - 5 * sx);
    this->addChild(supportBtn,5);
}
void FamouseFriendLayer::onSupportBtnClick(Ref* pSender)
{
    if(this->shareList->size() <= 0)
    {
        NoticeManager::getInstance()->showNotice("请选择好友！",NoticeManager::COLOR_RED);
        return;
    }
    Dialog::showServerLoading();
    FamouseShareFriendMsg* msg = new FamouseShareFriendMsg(GlobalInfo::getInstance()->famouseBossID,this->shareList);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
bool sortOnName(MessageData* n1, MessageData* n2)
{
    return n1->nickName < n2->nickName;
}
bool sortOnLevel(MessageData* n1, MessageData* n2)
{
    return n1->level > n2->level;
}
bool sortOnBGe(MessageData* n1, MessageData* n2)
{
    return n1->combat > n2->combat;
}
void FamouseFriendLayer::onTopComboBoxClick(Ref* pSender)
{
    Node* target = (Node*)pSender;
    int tag = target->getTag();
    if(tag == 0)
    {
        sort(this->m_dataList->begin(), this->m_dataList->end(),sortOnName);
    }
    else if(tag == 1)
    {
        sort(this->m_dataList->begin(), this->m_dataList->end(),sortOnLevel);
    }
    else if(tag == 2)
    {
         sort(this->m_dataList->begin(), this->m_dataList->end(),sortOnBGe);
    }
    this->setTableView();
}
void FamouseFriendLayer::show()
{
    FamouseFriendLayer* layer = FamouseFriendLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2 - 30 * GlobalInfo::getInstance()->screenScaleX);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
}

void FamouseFriendLayer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void FamouseFriendLayer::onExit()
{
    BaseLayer::onExit();
}
void FamouseFriendLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
}
void FamouseFriendLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Dialog::showServerLoading();
    FamouseFriendMsg* msg = new FamouseFriendMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void FamouseFriendLayer::setTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
//        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
//        _tableView->setContentOffset(cp);
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height * 2 + _size.height/2 - 10 * sx;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));

    _tableView->setPosition(30 * sx,45 * sx);
    this->addChild(_tableView,1,TAG_TABLEVIEW);
    
}
void FamouseFriendLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
    
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendMyFriendPageResp)
    {
        m_dataList->clear();
        int friendSize = msg->byteStream->get();
        FamouseFriendData* data = NULL;
        for(int i = 0; i < friendSize; i++)
        {
            data = new FamouseFriendData();
            data->autorelease();
            data->roleId = msg->byteStream->getLong();
            data->yayaId = msg->byteStream->getInt();
            data->nickName = msg->byteStream->getUTF8();
            data->level = msg->byteStream->getInt();
            data->combat = msg->byteStream->getInt();
            data->headId = msg->byteStream->getInt();
            data->online = msg->byteStream->get();//1在线  2 离线
            data->isSelected = false;
            m_dataList->pushBack(data);
          
       
        }
        setTableView();
    
    }
    else if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendShareBossResp)
    {
        NoticeManager::getInstance()->showNotice("支援信息已经成功发送",NoticeManager::COLOR_YELLOW);
//        broadMsg(CUSTOM_BATTLE_QUITBATTLE,__Bool::create(false));
        this->removeFromParent();
    }
}
void FamouseFriendLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendMyFriendPageResp).c_str(), CC_CALLBACK_1(FamouseFriendLayer::onMsgProcess, this));
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendShareBossResp).c_str(), CC_CALLBACK_1(FamouseFriendLayer::onMsgProcess, this));
}
void FamouseFriendLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void FamouseFriendLayer::onUserClick(Node* pSender)
{
    if(isMoveing)
    {
        return;
    }
    FamouseFriendData* data = this->m_dataList->at(pSender->getTag());
    UserHeadLayer* layer = (UserHeadLayer*)pSender;
    data->isSelected = !data->isSelected;

    if(data->isSelected)
    {
        if(shareList->size() >= 5)
        {
            NoticeManager::getInstance()->showNotice("最多只能选择5个好友哦！",NoticeManager::COLOR_RED);
            data->isSelected = false;
            return;
        }
        shareList->push_back(data->roleId);
    }
    else
    {
        auto iter = std::find(shareList->begin(), shareList->end(), data->roleId);
        if (iter != shareList->end())
        {
            shareList->erase(iter);
        }

    }
    layer->setHeadNumber(data->isSelected);
}
Node* FamouseFriendLayer::getNode(int idx)
{
    
    Sprite* layerBg = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
    layerBg->setAnchorPoint(Point::ZERO);
    
    FamouseFriendData* data = m_dataList->at(idx);
    //头像
 
    DictHero* dictHero = DictHeroManager::getInstance()->getData(data->headId);
    if (!dictHero)
    {
        return NULL;
    }
    UserHeadLayer* head = UserHeadLayer::create(dictHero->resource.c_str(),5);
    head->setAnchorPoint(Point::ZERO);
    head->setPosition(27,30);
    layerBg->addChild(head,2,idx);
    head->setHeadNumber(data->isSelected);
    head->hideHeadInfo();
    head->addTouchBegainCallBack(this, callfuncN_selector(FamouseFriendLayer::onUserClick));
 
    //名字背景
    Sprite* nameBg=Sprite::create(IMG_PUBLIC_EQUIP_NAMEBG);
    nameBg->setAnchorPoint(Point::ZERO);
    nameBg->setPosition(145,(layerBg->getContentSize().height-nameBg->getContentSize().height)-18);
    layerBg->addChild(nameBg,2);
    //名字
    Label* nameLabel = PublicShowUI::getLabel(data->nickName.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(200,(layerBg->getContentSize().height-nameLabel->getContentSize().height) - 20);
    layerBg->addChild(nameLabel,2);
    //等级
    Sprite* levelSpr = Sprite::create(IMG_PUBLIC_LABEL_LEVELWORD);
    levelSpr->setAnchorPoint(Point::ZERO);
    Label* levelLabel = PublicShowUI::getLabel(PublicShowUI::numberToString(data->level).c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(levelSpr->getContentSize().width + 5, (levelSpr->getContentSize().height - levelLabel->getContentSize().height)/2);
    levelSpr->addChild(levelLabel,2);
    levelSpr->setPosition(160,(layerBg->getContentSize().height-levelSpr->getContentSize().height)/2);
    layerBg->addChild(levelSpr,4);
    //列表战力
    Sprite* listMilitary=Sprite::create(IMG_PUBLIC_MILITARY);
    listMilitary->setAnchorPoint(Point::ZERO);
    listMilitary->setPosition(160,23.5);
    layerBg->addChild(listMilitary,2);
    
    //列表战力数值
    string combatStr=PublicShowUI::numberToString(data->combat);
    
    Label* combatLabel = PublicShowUI::getLabel(combatStr.c_str(),PublicShowUI::getColor3b(COLOR_HERLIST_BLACK),16,false,false);
    combatLabel->setAnchorPoint(Point::ZERO);
    combatLabel->setPosition(70,(listMilitary->getContentSize().height-combatLabel->getContentSize().height)/2);
    listMilitary->addChild(combatLabel);
    
    
    return layerBg;
}
TableViewCell* FamouseFriendLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<2; i++)
    {
        if (idx*2+i < m_dataList->size())
        {
            Node* list= getNode(idx* 2 + i);
            PublicShowUI::setTargetScale(list);
            list->setPosition(i*(list->getContentSize().width + 8),0);
            cell->addChild(list,1);
        }
    }
    
    
    return cell;

}
ssize_t FamouseFriendLayer::numberOfCellsInTableView(TableView *table)
{
    return ceil((float)m_dataList->size() / 2);
}
void FamouseFriendLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    this->isMoveing = false;
}
Size FamouseFriendLayer::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        Sprite* spr = Sprite::create(IMG_PUBLIC_LAYER_TWO_CELLBG);
        spr->setAnchorPoint(Point::ZERO);
        cellSize = spr->getContentSize() * GlobalInfo::getInstance()->screenScaleX;
        cellSize.width *= 2 + 15 * GlobalInfo::getInstance()->screenScaleX;
        cellSize.height += 15 * GlobalInfo::getInstance()->screenScaleX;
    }
    return cellSize;
}
void FamouseFriendLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
}

bool FamouseFriendLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isMoveing = false;
    return true;
}
void FamouseFriendLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
     BaseLayer::onTouchMoved(touch, unused_event);
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
}
void FamouseFriendLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
     BaseLayer::onTouchEnded(touch, unused_event);
    isMoveing = false;
}

