//
//  DetailsLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "DetailsLayer.hpp"
#include "SupportNode.hpp"
#include "../../../../common/Dialog/Dialog.h"
#include "../../../../message/Decoding/famouseGeneral/RequestFamouseRewardMsg.hpp"
#include "../../../../net/NetworkDataProcessing.h"
#include "../../../../commonData/dictData/DictMonster/DictMonsterManager.h"
DetailsLayer::DetailsLayer()
:TAG_TABLEVIEW(1)
,TAG_BOSSBG(2)
,m_bossID(0)
,bossName("")
,score(0)
,hp(0)
,hpMax(0)
,status(0)//	boss状态	byte	Y	1 击杀 2 逃跑
,listData(NULL)
,bossDictId(0)
{
    listData = new Vector<DetailsData*>();
}
DetailsLayer::~DetailsLayer()
{
    CC_SAFE_DELETE(listData);
    listData = NULL;
}
bool DetailsLayer::init(int bossID)
{
    m_bossID = bossID;
    this->isAnimation = true;
    this->isClickClose = true;
    this->setClickEnabled(true);
    this->isShowGrayBg = true;
    Sprite* bg = Sprite::create(IMG_PUBLIC_LAYER_LISTBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0,TAG_BG);
    PublicShowUI::setTargetScale(bg);
    this->setContentSize(bg->getContentSize());
    setBossBg();

    return true;
    
}
DetailsLayer* DetailsLayer::create(int bossID)
{
    DetailsLayer* layer = new DetailsLayer();
    if(layer && layer->init(bossID))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void DetailsLayer::show(int bossID)
{
    DetailsLayer* layer = DetailsLayer::create(bossID);
    layer->setAnchorPoint(Point::ZERO);
   
    layer->setPosition(VisibleRect::center().x -layer->getContentSize().width/2,VisibleRect::center().y -layer->getContentSize().height/2 - 30 * GlobalInfo::getInstance()->screenScaleX);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
}
void DetailsLayer::setBossBg()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Sprite* bossBg = Sprite::create(IMG_FAMOUSE_DETAILS_BOSSBG);
    bossBg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bossBg);
    this->addChild(bossBg,0,TAG_BOSSBG);
    bossBg->setPosition(28 * sx,(this->getContentSize().height - bossBg->getContentSize().height)/2 + 30 * sx);
    
}
void DetailsLayer::setBoss()
{
    

    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(this->bossDictId);
    if(!dictMonster)
    {
        return;
    }
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* bossBg = this->getChildByTag(TAG_BOSSBG);
    const char* path = PublicShowUI::getResImgPath(AVATAR_HEROBODY_PATH, dictMonster->halfbodyrResource.c_str());
    Sprite* bossSpr = Sprite::create(path);
    if(bossSpr)
    {
        bossSpr->setAnchorPoint(Point::ZERO);
        bossSpr->setScale(.75);
        bossSpr->setContentSize(bossSpr->getContentSize() * .7);
        bossSpr->setPosition((bossBg->getContentSize().width / sx - bossSpr->getContentSize().width)/2, (bossBg->getContentSize().height / sx - bossSpr->getContentSize().height)/2);
        bossBg->addChild(bossSpr,1);
    }
    

    Label* nameLabel = PublicShowUI::getLabel(dictMonster->name.c_str(),Color3B::WHITE,20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    bossBg->addChild(nameLabel,3);
    nameLabel->setPosition((bossBg->getContentSize().width / sx - nameLabel->getContentSize().width)/2, bossBg->getContentSize().height / sx - nameLabel->getContentSize().height -3);

    int typeNum =  dictMonster->attackType;
    if (typeNum<1) {
        typeNum = 1;
    }
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEROINFO_ATTACTTYPE,typeNum);
    Sprite* forceSprite = Sprite::create(stt);
    forceSprite->setAnchorPoint(Point::ZERO);
    forceSprite->setPosition(-5, bossBg->getContentSize().height / sx - forceSprite->getContentSize().height + 15);
    bossBg->addChild(forceSprite,4);
    
    
 
    path = this->status == 1 ? IMG_FAMOUSE_DETAILS_SUC : IMG_FAMOUSE_DETAILS_FAILS;
    Sprite* flag = Sprite::create(path);
    flag->setAnchorPoint(Point::ZERO);
    flag->setScale(2);
    bossBg->addChild(flag,10);
    flag->setPosition(bossBg->getContentSize().width / sx - flag->getContentSize().width * 2,bossBg->getContentSize().height / sx /2 - flag->getContentSize().height * 2 / 2);
    

 
}
void DetailsLayer::setScore()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    Node* bossBg = this->getChildByTag(TAG_BOSSBG);
    Sprite* scoreBg = Sprite::create(IMG_FAMOUSE_DETAILS_SCOREBG);
    scoreBg->setAnchorPoint(Point::ZERO);
    bossBg->addChild(scoreBg,6);
    scoreBg->setPosition((bossBg->getContentSize().width / sx - scoreBg->getContentSize().width)/2, -scoreBg->getContentSize().height + 25);
    
    Sprite* blood = Sprite::create(IMG_FAMOUSE_COME_BLOOD);
    blood->setAnchorPoint(Point::ZERO);
    float _scaleX = 1.05;
    float percent = this->hp / this->hpMax * 100;
    ProgressTimer* bloodPt = ProgressTimer::create(blood);
    bloodPt->setAnchorPoint(Point::ZERO);
    bloodPt->setScale(_scaleX,1);

    bloodPt->setType(ProgressTimer::Type::BAR);
    bloodPt->setMidpoint(Point(0,1));
    bloodPt->setBarChangeRate(Point(1,0));
    bloodPt->setPercentage(percent);
    bloodPt->setPosition((scoreBg->getContentSize().width - bloodPt->getContentSize().width * _scaleX)/2,scoreBg->getContentSize().height - bloodPt->getContentSize().height - 1);
    
    scoreBg->addChild(bloodPt,8);
    string str = PublicShowUI::numberToString((int)this->hp) + "/" + PublicShowUI::numberToString((int)hpMax);
    Label* bloodLabel =  PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
    scoreBg->addChild(bloodLabel,9);
    bloodLabel->setPosition(scoreBg->getContentSize().width/2, bloodPt->getPositionY() + bloodPt->getContentSize().height/2);
    
    Label* scoreLabel = PublicShowUI::getLabel(PublicShowUI::numberToString(score).c_str(),PublicShowUI::getColor3b(COLOR_WRITE_DEEP),18,false,false);
    scoreLabel->setAnchorPoint(Point::ZERO);
    scoreBg->addChild(scoreLabel,4);
    scoreLabel->setPosition(scoreBg->getContentSize().width/2 + 60, 5);

}
void DetailsLayer::setTableView()
{
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_TABLEVIEW);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Node* bossbg = this->getChildByTag(TAG_BOSSBG);
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height * 2 + _size.height/2 + 25 * GlobalInfo::getInstance()->screenScaleX;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    
    _tableView->setPosition(bossbg->getContentSize().width + 45 * GlobalInfo::getInstance()->screenScaleX,bossbg->getPositionY() + bossbg->getContentSize().height - _size.height);
    this->addChild(_tableView,1,TAG_TABLEVIEW);

}
void DetailsLayer::onEnter()
{
    BaseLayer::onEnter();
   
}
void DetailsLayer::onExit()
{
    BaseLayer::onExit();
}
void DetailsLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    this->setClickEnabled(false);
}
void DetailsLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    Dialog::showServerLoading();
    RequestFamouseRewardMsg* msg = new RequestFamouseRewardMsg(this->m_bossID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg= NULL;
 
}
void DetailsLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_LEGEND_LegendRewardPageResp).c_str(), CC_CALLBACK_1(DetailsLayer::onMsgProcess, this));
}
void DetailsLayer::onMsgProcess(EventCustom* message)
{
    Dialog::hideServerLoading();
    MessageReceive* msg = (MessageReceive*)message->getUserData();
    if(!msg->state)
    {
        return;
    }
//
    if(msg->messageID == SCENSE_CLIENT_LEGEND_LegendRewardPageResp)
    {

        listData->clear();
        this->bossDictId = msg->byteStream->getInt();
        this->bossName	= msg->byteStream->getUTF8();
        this->score = msg->byteStream->getInt();
        this->hp = msg->byteStream->getInt();
        this->hpMax	= msg->byteStream->getInt();
        this->status = msg->byteStream->getByte();
        int roleSize = msg->byteStream->getByte();//	参与者数量	byte	Y
         DetailsData* data = NULL;
        for(int i = 0 ;i < roleSize; i++)
        {
            data = new DetailsData();
            data->autorelease();
            data->roleName	 = msg->byteStream->getUTF8();
            data->iconHeroDictId = msg->byteStream->getInt();
        
            data->roleLevel	= msg->byteStream->getInt();
            data->prestige = msg->byteStream->getInt();
            data->isFinder	= msg->byteStream->get();
         
            data->isTop	= msg->byteStream->get();
            data->attackCount = msg->byteStream->get();
            data->hurt = msg->byteStream->getInt();
            int itemSize	= msg->byteStream->get();
            DetailsItemData * itemData = NULL;
            for(int j = 0; j < itemSize; j++)
            {
                itemData = new DetailsItemData();
                itemData->autorelease();
                itemData->itemType = msg->byteStream->get();
                itemData->itemId = msg->byteStream->getInt();
            
                itemData->quality = msg->byteStream->get();
                itemData->count = msg->byteStream->get();
                data->itemList->pushBack(itemData);
              
            }
            listData->pushBack(data);

        }
        setTableView();
        setBoss();
        setScore();

    }
}
void DetailsLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
TableViewCell* DetailsLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildren();
    Node* node = SupportNode::create(listData->at(idx));
    node->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(node);
    cell->addChild(node);
    return cell;
}
ssize_t DetailsLayer::numberOfCellsInTableView(TableView *table)
{
    return listData->size();
}
void DetailsLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
Size DetailsLayer::tableCellSizeForIndex(TableView *table,ssize_t idx)
{
    if(cellSize.height == 0)
    {
        cellSize = Sprite::create(IMG_FAMOUSE_DETAILS_ITEMBG)->getContentSize();
        cellSize = cellSize *  GlobalInfo::getInstance()->screenScaleX;
    }
    return cellSize;
}