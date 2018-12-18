//
//  RankPriceLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 16/1/6.
//
//

#include "RankPriceLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../limitCard/LimitCardSkillLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
#include "../../commonData/dictData/DictLegendRank/DictLegendRankManager.h"
#include "../../commonData/dictData/DictHero/DictHeroManager.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../../avatar/hero/Hero.h"
#include "../tips/TipsLayer.h"
#include "../userWealth/UserHeadLayer.h"
#include "../userWealth/UserEquipLayer.h"
#include "../../commonData/dictData/DictItemBook/DictItemBookManager.h"
#include "../../commonData/dictData/DictItemEquip/DictItemEquipManager.h"
#include "../../commonData/dictData/DictItemHero/DictItemHeroManager.h"
#include "../../commonData/dictData/DictItemMater/DictItemMaterManager.h"
#include "../../commonData/dictData/DictItem/DictItemManager.h"
#include "../../commonData/dictData/DictResource/DictResourceManager.h"

RankPriceLayer::RankPriceLayer()
:sx(0)
,_tableView(NULL)
,TAG_TABLEBG(1)
,TAG_TABLEVIEW(2)
,TAG_PERDETAILBG(3)
,isMoveing(false)
,isDownPoint(Point::ZERO)
{
    
}
RankPriceLayer::~ RankPriceLayer()
{
    
}
void RankPriceLayer::onExit()
{
    BaseLayer::onExit();
}
void RankPriceLayer::onEnter()
{
    BaseLayer::onEnter();
}
void RankPriceLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    removeEventListener();
}
void RankPriceLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
bool RankPriceLayer::init()
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
        createTable();
        bref = true;
    } while (false);
    return bref;
}
RankPriceLayer* RankPriceLayer::create()
{
    RankPriceLayer* layer = new RankPriceLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
    
}
void RankPriceLayer::show()
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
    RankPriceLayer* layer = RankPriceLayer::create();
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    scene->addChild(layer,0);
}

void RankPriceLayer::createLayer()
{
    Sprite* layerbg = (Sprite*)this->getChildByTag(TAG_BG);
    Sprite* titlebg = Sprite::create(IMG_LIMITCARD_SKILLONETITLEBG);
    titlebg->setAnchorPoint(Point::ZERO);
    titlebg->setPosition(15,this->getContentSize().height/sx-titlebg->getContentSize().height-15);
    layerbg->addChild(titlebg,1);
    Sprite* title = Sprite::create(IMG_RANK_RANKPRICE);
    title->setAnchorPoint(Point::ZERO);
    title->setPosition(20,8);
    titlebg->addChild(title);
    
    
}
//-----------------------------------------------tableView------------------------------------------------------//
void RankPriceLayer::createTable()
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

Sprite* RankPriceLayer::singleList(int idx)
{
    Sprite* cellbg = Sprite::create(IMG_LIMITCARD_SKILLONEBG);
    
    DictLegendRank* data = DictLegendRankManager::getInstance()->getData(idx+1);
    
    if (idx == 0) {
        Sprite* one  = Sprite::create(IMG_RANK_FIRST);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(20,cellbg->getContentSize().height/2-one->getContentSize().height/2);
        cellbg->addChild(one);
    }else if (idx == 1) {
        Sprite* one  = Sprite::create(IMG_RANK_SECOND);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(20,cellbg->getContentSize().height/2-one->getContentSize().height/2);
        cellbg->addChild(one);
    }else if (idx == 2) {
        Sprite* one  = Sprite::create(IMG_RANK_THIRD);
        one->setAnchorPoint(Point::ZERO);
        one->setPosition(20,cellbg->getContentSize().height/2-one->getContentSize().height/2);
        cellbg->addChild(one);
    }else{
//        Node* ranklabel = PublicShowUI::getNumbers(idx+ 1,IMG_PUBLIC_NUMBER1);
//        ranklabel->setAnchorPoint(Point(0.5,0.5));
//        ranklabel->setScale(.5);
//        ranklabel->setPosition(50,cellbg->getContentSize().height/2);
//        cellbg->addChild(ranklabel);
        string scoreStr = "";
        if (data->rankmax == data->rankmin) {
            scoreStr = StringUtils::format("%hd",data->rankmax);
        }else{
            scoreStr = StringUtils::format("%hd~%hd",data->rankmin,data->rankmax);
        }
        Label* scoreLabel = PublicShowUI::getLabel(scoreStr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),24,false,false);
        scoreLabel->setPosition(75,cellbg->getContentSize().height/2);
        cellbg->addChild(scoreLabel,3);
    }
    //奖励元宝
    Sprite* gold = Sprite::create(IMG_ICON_PUBLIC_GOLD);
    gold->setScale(0.7);
    gold->setPosition(167,70);
    cellbg->addChild(gold);
    string goldstr = StringUtils::format("%d",data->honor);
    Label* goldLabel = PublicShowUI::getLabel(goldstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    goldLabel->setAnchorPoint(Point::ZERO);
    goldLabel->setPosition(gold->getPositionX()+gold->getContentSize().width/2-10,gold->getPositionY()-goldLabel->getContentSize().height/2);
    cellbg->addChild(goldLabel,3);
    
    //奖励铜钱
    Sprite* icon = Sprite::create(IMG_ICON_PUBLIC_COIN);
    icon->setScale(0.8);
    icon->setPosition(167 ,30);
    cellbg->addChild(icon);
    string coinstr = StringUtils::format("%d",data->coin);
    Label* coinLabel = PublicShowUI::getLabel(coinstr.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    coinLabel->setAnchorPoint(Point::ZERO);
    coinLabel->setPosition(icon->getPositionX()+icon->getContentSize().width/2-10,icon->getPositionY()-coinLabel->getContentSize().height/2);
    cellbg->addChild(coinLabel,3);
   
    //奖励1
    const char* path = NULL;
    int m_qulity = 1;
    if(  data->item1Type == DictItemTypeEnumItemHero)
    {
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId1);
        if (dicthero) {
            path =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
        }else{
            path = PublicShowUI::getGoods(data->item1Type, data->itemId1);
        }
        if (path) {
            DictItemHero* dataitemhero = DictItemHeroManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitemhero->quality;
            UserHeadLayer* userHead=UserHeadLayer::create(path,m_qulity,false);
            userHead->setHeadInfo(1, data->hero1Prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setScale(0.6);
            userHead->setPosition(262,12);
            cellbg->addChild(userHead,5,idx);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick));
        }
    }
    else if(data->item1Type == DictItemTypeEnumItemEquip || data->item1Type == DictItemTypeEnumItemBook || data->item1Type == DictItemTypeEnumItemMater|| data->item1Type == DictItemTypeEnumItem|| data->item1Type == DictItemTypeEnumRoleResource)
    {
        if (data->item1Type == DictItemTypeEnumItemEquip)
        {
            DictItemEquip* dataitem = DictItemEquipManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitem->quality;
        }
        else if (data->item1Type == DictItemTypeEnumItemBook)
        {
            DictItemBook* dataitem = DictItemBookManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitem->quality;
        }
        else if (data->item1Type == DictItemTypeEnumItemMater)
        {
            DictItemMater* dataitem = DictItemMaterManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitem->quality;
        }
        else if (data->item1Type == DictItemTypeEnumItem)
        {
            DictItem* dataitem = DictItemManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitem->quality;
        }
        else if (data->item1Type == DictItemTypeEnumRoleResource)
        {
            DictResource* dataitem = DictResourceManager::getInstance()->getData(data->itemId1);
            m_qulity = dataitem->quality;
        }
        const char* resource = PublicShowUI::getGoods(data->item1Type, data->itemId1);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_qulity,false);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.6);
        if (data->item1Type == 4) {
            head->setFragment();
        }else if (data->item1Type == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(265,10);
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick));
    }
    string namestr =  "x" + PublicShowUI::numberToString(data->item1Number);
    Label* nameLabel = PublicShowUI::getLabel(namestr.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    nameLabel->setAnchorPoint(Point(0,0));
    cellbg->addChild(nameLabel,20);
    nameLabel->setPosition(335,10);
    
    //奖励2
    const char* path2 = NULL;
    if(  data->item2Type == DictItemTypeEnumItemHero)
    {
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId2);
        if (dicthero) {
            path2 =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
        }else{
            path2 = PublicShowUI::getGoods(data->item2Type, data->itemId2);
        }
        if (path2) {
            DictItemHero* dataitemhero = DictItemHeroManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitemhero->quality;
            UserHeadLayer* userHead=UserHeadLayer::create(path2,m_qulity,false);
            userHead->setHeadInfo(1, data->hero1Prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setScale(0.6);
            userHead->setPosition(357,12);
            cellbg->addChild(userHead,5,idx);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick2));
        }
    }
    else if(data->item2Type == DictItemTypeEnumItemEquip || data->item2Type == DictItemTypeEnumItemBook || data->item2Type == DictItemTypeEnumItemMater|| data->item2Type == DictItemTypeEnumItem|| data->item2Type == DictItemTypeEnumRoleResource)
    {
        if (data->item2Type == DictItemTypeEnumItemEquip)
        {
            DictItemEquip* dataitem = DictItemEquipManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitem->quality;
        }
        else if (data->item2Type == DictItemTypeEnumItemBook)
        {
            DictItemBook* dataitem = DictItemBookManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitem->quality;
        }
        else if (data->item2Type == DictItemTypeEnumItemMater)
        {
            DictItemMater* dataitem = DictItemMaterManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitem->quality;
        }
        else if (data->item2Type == DictItemTypeEnumItem)
        {
            DictItem* dataitem = DictItemManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitem->quality;
        }
        else if (data->item2Type == DictItemTypeEnumRoleResource)
        {
            DictResource* dataitem = DictResourceManager::getInstance()->getData(data->itemId2);
            m_qulity = dataitem->quality;
        }
        
        const char* resource = PublicShowUI::getGoods(data->item2Type, data->itemId2);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_qulity,false);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.6);
        if (data->item2Type == 4) {
            head->setFragment();
        }else if (data->item2Type == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(355,10);
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick2));
    }
    
    string namestr2 =  "x" + PublicShowUI::numberToString(data->item2Number);
    Label* nameLabel2 = PublicShowUI::getLabel(namestr2.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    nameLabel2->setAnchorPoint(Point(0,0));
    cellbg->addChild(nameLabel2,20);
    nameLabel2->setPosition(425,10);
    
    //奖励3
    const char* path3 = NULL;
    if(  data->item3Type == DictItemTypeEnumItemHero)
    {
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId3);
        if (dicthero) {
            path3 =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
        }else{
            path3 = PublicShowUI::getGoods(data->item3Type, data->itemId3);
        }
        if (path3) {
            DictItemHero* dataitemhero = DictItemHeroManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitemhero->quality;
            UserHeadLayer* userHead=UserHeadLayer::create(path3,m_qulity,false);
            userHead->setHeadInfo(1, data->hero1Prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setScale(0.6);
            userHead->setPosition(452,12);
            cellbg->addChild(userHead,5,idx);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick3));
        }
    }
    else if(data->item3Type == DictItemTypeEnumItemEquip || data->item3Type == DictItemTypeEnumItemBook || data->item3Type == DictItemTypeEnumItemMater|| data->item3Type == DictItemTypeEnumItem|| data->item3Type == DictItemTypeEnumRoleResource)
    {
        if (data->item3Type == DictItemTypeEnumItemEquip)
        {
            DictItemEquip* dataitem = DictItemEquipManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitem->quality;
        }
        else if (data->item3Type == DictItemTypeEnumItemBook)
        {
            DictItemBook* dataitem = DictItemBookManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitem->quality;
        }
        else if (data->item3Type == DictItemTypeEnumItemMater)
        {
            DictItemMater* dataitem = DictItemMaterManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitem->quality;
        }
        else if (data->item3Type == DictItemTypeEnumItem)
        {
            DictItem* dataitem = DictItemManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitem->quality;
        }
        else if (data->item3Type == DictItemTypeEnumRoleResource)
        {
            DictResource* dataitem = DictResourceManager::getInstance()->getData(data->itemId3);
            m_qulity = dataitem->quality;
        }
        
        const char* resource = PublicShowUI::getGoods(data->item3Type, data->itemId3);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_qulity,false);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.6);
        if (data->item3Type == 4) {
            head->setFragment();
        }else if (data->item3Type == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(450,10);
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick3));
    }
    
    string namestr3 =  "x" + PublicShowUI::numberToString(data->item3Number);
    Label* nameLabel3 = PublicShowUI::getLabel(namestr3.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    if(data->item3Number != 0)
    {
        nameLabel3->setAnchorPoint(Point(0,0));
        cellbg->addChild(nameLabel3,20);
        nameLabel3->setPosition(520,10);
    }
    
    //奖励4
    const char* path4 = NULL;
    if(  data->item4Type == DictItemTypeEnumItemHero)
    {
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId4);
        if (dicthero) {
            path4 =  PublicShowUI::getResImgPath(AVATAR_HEAD_PATH,dicthero->headResource.c_str());
        }else{
            path4 = PublicShowUI::getGoods(data->item4Type, data->itemId4);
        }
        if (path4) {
            DictItemHero* dataitemhero = DictItemHeroManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitemhero->quality;
            UserHeadLayer* userHead=UserHeadLayer::create(path4,m_qulity,false);
            userHead->setHeadInfo(1, data->hero1Prestige);
            userHead->setAnchorPoint(Point::ZERO);
            userHead->setScale(0.6);
            userHead->setPosition(542,12);
            cellbg->addChild(userHead,5,idx);
            userHead->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick4));
        }
    }
    else if(data->item4Type == DictItemTypeEnumItemEquip || data->item4Type == DictItemTypeEnumItemBook || data->item4Type == DictItemTypeEnumItemMater|| data->item4Type == DictItemTypeEnumItem|| data->item4Type == DictItemTypeEnumRoleResource)
    {
        if (data->item4Type == DictItemTypeEnumItemEquip)
        {
            DictItemEquip* dataitem = DictItemEquipManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitem->quality;
        }
        else if (data->item4Type == DictItemTypeEnumItemBook)
        {
            DictItemBook* dataitem = DictItemBookManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitem->quality;
        }
        else if (data->item4Type == DictItemTypeEnumItemMater)
        {
            DictItemMater* dataitem = DictItemMaterManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitem->quality;
        }
        else if (data->item4Type == DictItemTypeEnumItem)
        {
            DictItem* dataitem = DictItemManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitem->quality;
        }
        else if (data->item4Type == DictItemTypeEnumRoleResource)
        {
            DictResource* dataitem = DictResourceManager::getInstance()->getData(data->itemId4);
            m_qulity = dataitem->quality;
        }//
        
        const char* resource = PublicShowUI::getGoods(data->item4Type, data->itemId4);
        UserEquipLayer* head = UserEquipLayer::create(resource,m_qulity,false);
        head->setAnchorPoint(Point::ZERO);
        head->setScale(0.6);
        if (data->item4Type == 4) {
            head->setFragment();
        }else if (data->item4Type == 3)
        {
            head->setLetterFragment();
        }
        head->setPosition(540,10);
        cellbg->addChild(head,5,idx);
        head->addTouchBegainCallBack(this, callfuncN_selector(RankPriceLayer::onHeroHeadClick4));
    }
    
    string namestr4 =  "x" + PublicShowUI::numberToString(data->item4Number);
    Label* nameLabel4 = PublicShowUI::getLabel(namestr4.c_str(),PublicShowUI::getColor3b(COLOR_GOLDEN_YELLOW),16,false,false);
    if(data->item4Number != 0)
    {
        nameLabel4->setAnchorPoint(Point(0,0));
        cellbg->addChild(nameLabel4,20);
        nameLabel4->setPosition(610,10);
    }
    
    return cellbg;
}
void RankPriceLayer::onHeroHeadClick(Node* pSender)
{
    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_TABLEVIEW);
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
        
        DictLegendRank* data = DictLegendRankManager::getInstance()->getData(pSender->getTag()+1);
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId1);
        if (!dicthero) {
            TipsLayer::show(data->item1Type, data->itemId1, data->item1Number);
        }
    }
    
//    DictLegendRank* data = DictLegendRankManager::getInstance()->getData(pSender->getTag()+1);
//    DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId1);
//    if (!dicthero) {
//        TipsLayer::show(data->item1Type, data->itemId1, data->item1Number);
//    }
}
void RankPriceLayer::onHeroHeadClick2(Node* pSender)
{
    
    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_TABLEVIEW);
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
        
        DictLegendRank* data = DictLegendRankManager::getInstance()->getData(pSender->getTag()+1);
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId2);
        if (!dicthero) {
            TipsLayer::show(data->item2Type, data->itemId2, data->item2Number);
        }
    }
}
void RankPriceLayer::onHeroHeadClick3(Node* pSender)
{
    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_TABLEVIEW);
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
        
        DictLegendRank* data = DictLegendRankManager::getInstance()->getData(pSender->getTag()+1);
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId3);
        if (!dicthero) {
            TipsLayer::show(data->item3Type, data->itemId3, data->item3Number);
        }
    }
}
void RankPriceLayer::onHeroHeadClick4(Node* pSender)
{
    log("列表点击 isMoveing＝%d",isMoveing);
    if(isMoveing)
    {
        return;
    }
    Node* target = (Node*)pSender;
    int index = target->getTag();
    log("%d",index);
    TableView* _tableView = (TableView*)this->getChildByTag(TAG_BG)->getChildByTag(TAG_TABLEVIEW);
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
        
        DictLegendRank* data = DictLegendRankManager::getInstance()->getData(pSender->getTag()+1);
        DictHero* dicthero = DictHeroManager::getInstance()->getData(data->itemId4);
        if (!dicthero) {
            TipsLayer::show(data->item4Type, data->itemId4, data->item4Number);
        }
    }
}
TableViewCell* RankPriceLayer::tableCellAtIndex(TableView *table, ssize_t idx)
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
Size RankPriceLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    Size cellSize;
    Sprite* temp = Sprite::create(IMG_LIMITCARD_SKILLONEBG);
    cellSize.height = temp->getContentSize().height+10;
    cellSize.width = temp->getContentSize().width;
    return cellSize;
}
//获取view的长度
ssize_t RankPriceLayer::numberOfCellsInTableView(TableView *table)
{
    return 21;
    
}
//点击cell事件
void RankPriceLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    isMoveing = false;
    log("%d",cell->getTag());
}
void RankPriceLayer::scrollViewDidScroll(ScrollView* view)
{
    if(view->isDragging())
    {
        if(view->getContentOffset().x != 0 || view->getContentOffset().y != 0)
        {
            this->isMoveing = true;
        }
    }
    
}
bool RankPriceLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    BaseLayer::onTouchBegan(touch, unused_event);
    isDownPoint=touch->getLocation();
    isDownPoint = this->convertToNodeSpace(isDownPoint);
    return true;
}
void RankPriceLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    if(touch->getDelta().x > 10 or touch->getDelta().y>10)
    {
        isMoveing = true;
    }
    
}
void RankPriceLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    isMoveing = false;
    BaseLayer::onTouchEnded(touch, unused_event);
}

//-----------------------------------------------访问服务器-------------------------------------------------------//