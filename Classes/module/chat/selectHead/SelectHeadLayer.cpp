//
//  SelectHeadLayer.cpp
//  FightPass
//
//  Created by 超 顾 on 15/12/28.
//
//

#include "SelectHeadLayer.h"
#include "../../../common/Dialog/Dialog.h"
#include "../../../protocol/UserCustomEvent.h"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "../../userWealth/UserEquipLayer.h"
#include "../../../message/Decoding/chat/FriendHeadIconSelPage.h"
#include "../../../message/Decoding/chat/FriendSetIcon.h"

SelectHeadLayer::SelectHeadLayer()
:sx(1)
,selectIconId(0)
,TAG_TABLEVIEW(1)

,selectIcon(NULL)
{

    iconList=new Vector<iconData*>();
}
SelectHeadLayer::~SelectHeadLayer()
{
    CC_SAFE_DELETE(iconList);
}

void SelectHeadLayer::onExit()
{
    BaseLayer::onExit();
}
void SelectHeadLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SelectHeadLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void SelectHeadLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    this->setClickEnabled(true);
    this->requestListMsg();
}
bool SelectHeadLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->setBackground(IMG_PUBLIC_LAYER_LISTBG);
        this->setGrayBg();
        this->isClickClose=true;
        this->setIconSelList();
        bref = true;
    } while (false);
    return bref;
}
SelectHeadLayer* SelectHeadLayer::create()
{
    SelectHeadLayer* layer = new SelectHeadLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void SelectHeadLayer::setIconSelList()
{
    Vector<DictItemHero*>* list=DictItemHeroManager::getInstance()->getDataList();
    for (DictItemHero* data: *list) {
        if (data->quality==1) {
            iconData* i_data=new iconData();
            i_data->iconId=data->heroId;
            i_data->resource=data->resource;
            iconList->pushBack(i_data);
        }
    }
//    iconList;
    
}
int SelectHeadLayer::getIndexByIconID(int _id)
{
    int len = (int)iconList->size();
    for(int i = 0; i < len; i++)
    {
        if(iconList->at(i)->iconId == _id)
        {
            return i;
        }
    }
    return -1;
}

void SelectHeadLayer::initTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        _tableView->reloadData();
        return;
    }
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*4-35*sx;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    PublicShowUI::setTargetScale(_tableView);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(40*sx,55*sx);
    this->addChild(_tableView,2,TAG_TABLEVIEW);
    
    Sprite* shade=Sprite::create(IMG_PUBLIC_TABLE_VIEW_SHADE);
    shade->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(shade);
    shade->setPosition(0*sx,40*sx);
    this->addChild(shade,3);
    
}
//--------------------------------------------------------tabelView开始----------------------------------------------------------------------//
TableViewCell* SelectHeadLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    for (int i=0; i<7; i++) {
        int tag=(int)idx*6+i;
        if (tag>=iconList->size()) {
            break;
        }
        iconData* data=iconList->at(tag);
        const char* imgPath = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH, data->resource.c_str());
        UserEquipLayer* userHead=UserEquipLayer::create(imgPath,0,false);
        userHead->setIsSlect(data->isSelect);
        if (!data->isHave) {
            userHead->setGray();
        }else
        {
            userHead->addTouchBegainCallBack(this, callfuncN_selector(SelectHeadLayer::onUserClick));
        }
        userHead->setPosition(5+136*i,5);
        cell->addChild(userHead,1,tag);
    }
    return cell;
}

//列表大小
Size SelectHeadLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,1);
    Sprite* headBox=Sprite::create(stt);
    cellSize.height=headBox->getContentSize().height+5;
    cellSize.width=(headBox->getContentSize().width+15)*6;
    return cellSize;
}
//获取view的长度
ssize_t SelectHeadLayer::numberOfCellsInTableView(TableView *table)
{
    float t=(float)iconList->size()/6;
    int count = ceil(t);
    return count;
}

//点击cell事件
void SelectHeadLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
void SelectHeadLayer::scrollViewDidScroll(ScrollView* view)
{
    
}
//--------------------------------------------------------tabelView结束----------------------------------------------------------------------//
void SelectHeadLayer::onUserClick(Node* pSender)
{
    if (selectIcon) {
        selectIcon->setIsSlect(false);
        int tag=selectIcon->getTag();
        iconList->at(tag)->isSelect=false;
    }
    
    selectIcon=(UserEquipLayer*)pSender;
    if (selectIcon) {
        int tag=selectIcon->getTag();
        iconList->at(tag)->isSelect=true;
        selectIcon->setIsSlect(true);
        selectIconId=iconList->at(tag)->iconId;
        requestSetIconMsg(selectIconId);
    }
}
void SelectHeadLayer::requestSetIconMsg(int _id)
{
    FriendSetIcon* msg = new FriendSetIcon(_id);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;

}
void SelectHeadLayer::requestListMsg()
{
//
    FriendHeadIconSelPage* msg = new FriendHeadIconSelPage();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void SelectHeadLayer::onMsgProcess(EventCustom* msg)
{
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    if (message->state==false) {
        return;
    }
    if(message->messageID == SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageResp)
    {
        int len=message->byteStream->getShort();
        for (int i=0; i<len; i++) {
            int id=message->byteStream->getInt();
            
            int index=getIndexByIconID(id);
            if (index>=0) {
                iconList->at(index)->isHave=true;
            }
        }
        this->sortList();
    }else if (message->messageID == SCENSE_CLIENT_FRIEND_FriendSetIconResp)
    {
        log("修改头像成功了");
        this->broadMsg(CUSTOM_ALTER_HEAD,__Integer::create(selectIconId));
    }
}
void SelectHeadLayer::addEventListener()
{
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendHeadIconSelPageResp).c_str(), CC_CALLBACK_1(SelectHeadLayer::onMsgProcess, this));
    this->addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_FRIEND_FriendSetIconResp).c_str(), CC_CALLBACK_1(SelectHeadLayer::onMsgProcess, this));
}
void SelectHeadLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}

//状态排序

bool sortOnIconIsHave(iconData* n1, iconData* n2)//正序(从大到小)
{
    return n1->isHave;
}
void SelectHeadLayer::sortList()
{
    stable_sort(iconList->begin(), iconList->end(),sortOnIconIsHave);
    this->initTableView();
    
}

