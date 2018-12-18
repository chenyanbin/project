//
//  ArenaRecoredLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/3/14.
//
//

#include "ArenaRecoredLayer.hpp"
#include "../../../common/TouchSprite/Button.h"
#include "../../../message/Decoding/arena/ArenaRecoredMsg.hpp"
#include "../../../net/NetworkDataProcessing.h"
#include "../../../common/Dialog/Dialog.h"
#include "../arenaData/ArenaRecoredDataManager.hpp"
#include "../../../commonData/dictData/DictHero/DictHeroManager.h"
ArenaRecoredLayer::ArenaRecoredLayer()
:sx(0)
,_tableView(NULL)
,TAG_TABLEBG(1)
,TAG_TABLEVIEW(2)
,TAG_PERDETAILBG(3)
,isMoveing(false)
,isDownPoint(Point::ZERO)
{
    
}
ArenaRecoredLayer::~ ArenaRecoredLayer()
{
    
}
void ArenaRecoredLayer::onExit()
{
    BaseLayer::onExit();
}
void ArenaRecoredLayer::onEnter()
{
    BaseLayer::onEnter();
}
void ArenaRecoredLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void ArenaRecoredLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    requestRecoredMsg();
}
bool ArenaRecoredLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        sx=GlobalInfo::getInstance()->screenScaleX;
        this->isAnimation = false;
        this->isClickClose=true;
        this->setClickEnabled(true);
        this->isShowGrayBg = true;
        this->setBackground(IMG_LIMITCARD_SKILLBG,Point::ZERO,true);
        this->createLayer();
//        createTable();
        bref = true;
    } while (false);
    return bref;
}
ArenaRecoredLayer* ArenaRecoredLayer::create()
{
    ArenaRecoredLayer* layer = new ArenaRecoredLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void ArenaRecoredLayer::show()
{
    
    //    Director::getInstance()->purgeCachedData();
    //    Director::getInstance()->getTextureCache()->removeAllTextures();
    //    RankPriceLayer* layer = RankPriceLayer::create();
    //    layer->setFromScene(fromScene);
    //    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    //    Scene* scene = Scene::create();//
    //    scene->addChild(layer,0,SCENE_TAG_RANK);
    //    Director::getInstance()->replaceScene(scene);
    
    Scene* scene = Director::getInstance()->getRunningScene();
    ArenaRecoredLayer* layer = ArenaRecoredLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,0);
}

void ArenaRecoredLayer::createLayer()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    Sprite* titlebg = Sprite::create(IMG_LIMITCARD_SKILLONETITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(15,this->getContentSize().height/sx-titlebg->getContentSize().height-15);
    layerbg->addChild(titlebg,1);
    Sprite* title = Sprite::create(IMG_ARENA_RECORDETITLE1);
    title->setAnchorPoint(Point::ZERO);
    title->setPosition(20,8);
    titlebg->addChild(title);
    
    
}
//-----------------------------------------------tableView------------------------------------------------------//
void ArenaRecoredLayer::createTable()
{
    Sprite* tablebg = (Sprite*)this->getChildByTag(TAG_BG);
    if(_tableView)
    {
        Point cp = _tableView->getContentOffset();
        _tableView->reloadData();
        _tableView->setContentOffset(cp);
        return;
    }
    
    Size _size=tableCellSizeForIndex(NULL,NULL);
    _size.height=_size.height*4;
    _tableView =TableView::create(this,_size);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setAnchorPoint(Point(0, 0));
    _tableView->setPosition(15,30);
    _tableView->reloadData();
    tablebg->addChild(_tableView,2,TAG_TABLEVIEW);
    
}

Sprite* ArenaRecoredLayer::singleList(int idx)
{
    Sprite* cellbg = NULL;
    Sprite* logoSpr = NULL;
    ArenaRecoredData* data =ArenaRecoredDataManager::getInstance()->recoredList->at(idx);

    if (data->isWin == 1)//成功
    {
        cellbg = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_WINBG);
        //成功
        logoSpr = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_WIN);
        logoSpr->setAnchorPoint(Point::ZERO);
        logoSpr->setPosition(Point(0,cellbg->getContentSize().height-logoSpr->getContentSize().height));
        cellbg->addChild(logoSpr,1);
    }
    else if (data->isWin == 2)//失败
    {
        cellbg = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_LOSEBG);
        
        //失败
        logoSpr = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_LOSE);
        logoSpr->setAnchorPoint(Point::ZERO);
        logoSpr->setPosition(Point(0,cellbg->getContentSize().height-logoSpr->getContentSize().height));
        cellbg->addChild(logoSpr,1);
    }
    else
    {
        cellbg = Sprite::create(IMG_LIMITCARD_SKILLONEBG);
        
    }
    //排名增加或减少标志
    Sprite* rankSpr = NULL;
    if (data->upOrDown == 0)//排名不变
    {
        rankSpr = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_UP);
        rankSpr->setAnchorPoint(Point::ZERO);
        rankSpr->setPosition(Point(450,(cellbg->getContentSize().height-rankSpr->getContentSize().height)/2));
        cellbg->addChild(rankSpr,1);
        
    }else if (data->upOrDown == 1)//排名增长
    {
        rankSpr = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_UP);
        rankSpr->setAnchorPoint(Point::ZERO);
        rankSpr->setPosition(Point(450,(cellbg->getContentSize().height-rankSpr->getContentSize().height)/2));
        cellbg->addChild(rankSpr,1);
        
    }else if (data->upOrDown == 2)//排名下降
    {
        rankSpr = Sprite::create(IMG_ARENATEAM_FIGHTRECORED_DOWN);
        rankSpr->setAnchorPoint(Point::ZERO);
        rankSpr->setPosition(Point(450,(cellbg->getContentSize().height-rankSpr->getContentSize().height)/2));
        cellbg->addChild(rankSpr,1);
    }
    
//    DictMonster* dictMonster = DictMonsterManager::getInstance()->getData(113040);
    DictHero* dictMonster = DictHeroManager::getInstance()->getData(data->heroDictId);
    if (dictMonster) {
        const char* path = dictMonster ? dictMonster->headResource.c_str() : "zhaoyun";
        path = PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,path);
        Sprite* head = Sprite::create(path);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.7);
        cellbg->addChild(head,1);
        head->setPosition(70,8);
    }
    
    
    string namestr = data->roleName;//"斯蒂芬急哦过年都没";
    Label* nameLabel = PublicShowUI::getLabel(namestr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),20,false,false);
    nameLabel->setAnchorPoint(Point::ZERO);
    nameLabel->setPosition(180,57);
    cellbg->addChild(nameLabel,2);
    
    int level = data->roleLevel;
    string levelstr = StringUtils::format("lv:%d",level);
    Label* levelLabel = PublicShowUI::getLabel(levelstr.c_str(),PublicShowUI::getColor3b(COLOR_DARK_GREEN),20,false,false);
    levelLabel->setAnchorPoint(Point::ZERO);
    levelLabel->setPosition(nameLabel->getPositionX()+nameLabel->getContentSize().width+15,nameLabel->getPositionY());
    cellbg->addChild(levelLabel,2);
    
    long time = (data->challengeTime)/1000;
    struct tm *l=localtime(&time);
    char buf[128];
    snprintf(buf,sizeof(buf),"%02d-%02d-%02d    %02d:%02d:%02d",l->tm_year,l->tm_mon+1,l->tm_mday,l->tm_hour,l->tm_min,l->tm_sec);
    string start(buf);
    Label* activityStartTimeslabel = PublicShowUI::getLabel(start.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    activityStartTimeslabel->setAnchorPoint(Point::ZERO);
    activityStartTimeslabel->setPosition(180,cellbg->getContentSize().height/2-activityStartTimeslabel->getContentSize().height/2-10);
    cellbg->addChild(activityStartTimeslabel,3);
    
    
    
    return cellbg;
}
TableViewCell* ArenaRecoredLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
    cell->addChild(list);
    cell->setContentSize(list->getContentSize());
    cell->setTag(idx);
    return cell;
}

//列表大小
Size ArenaRecoredLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_LIMITCARD_SKILLONEBG);
    cellSize.height = temp->getContentSize().height+10;
    cellSize.width = temp->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t ArenaRecoredLayer::numberOfCellsInTableView(TableView *table)
{
    return ArenaRecoredDataManager::getInstance()->recoredList->size();
    
}
//点击cell事件
void ArenaRecoredLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    log("%d",cell->getTag());
}
void ArenaRecoredLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
bool ArenaRecoredLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void ArenaRecoredLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
}
void ArenaRecoredLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    BaseLayer::onTouchEnded(touch, unused_event);
}

//-----------------------------------------------访问服务器-------------------------------------------------------//
void ArenaRecoredLayer::requestRecoredMsg()
{
    Dialog::showServerLoading();
    ArenaRecoredMsg* msg = new ArenaRecoredMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
    
}
void ArenaRecoredLayer::onRecoredMsgProcess(EventCustom* msg)
{
    Dialog::hideServerLoading();
    MessageReceive* message = (MessageReceive*)msg->getUserData();
    
    if(message->messageID == SCENSE_CLIENT_ARENA_ArenaBattleRecordPageResp)
    {
        ArenaRecoredDataManager::getInstance()->destroyInstance();
        if(message->state)//返回成功
        {
            int roleSize = message->byteStream->getByte();
            for (int i = 0; i < roleSize; i ++)
            {
                ArenaRecoredData* data = new ArenaRecoredData();
                data->autorelease();
                
                data->heroDictId = message->byteStream->getInt();
                data->roleName = message->byteStream->getUTF8();
                data->roleLevel = message->byteStream->getInt();
                data->isWin = message->byteStream->getByte();
                data->upOrDown = message->byteStream->getByte();
                data->challengeTime = message->byteStream->getLong();
                ArenaRecoredDataManager::getInstance()->addData(data);
            }
            createTable();
        }
    }
    
}

void ArenaRecoredLayer::addEventListener()
{
    addUserMsg(PublicShowUI::numberToString(SCENSE_CLIENT_ARENA_ArenaBattleRecordPageResp).c_str(), CC_CALLBACK_1(ArenaRecoredLayer::onRecoredMsgProcess, this));
}
void ArenaRecoredLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
