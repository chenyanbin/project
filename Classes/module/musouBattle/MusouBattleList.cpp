//
//  MusouBattleList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#include "MusouBattleList.h"
#include "../sweep/CoverView.h"
#include "../../common/TouchSprite/Button.h"

#include "../../message/Decoding/musou/RequestMusouFightMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "../../commonData/enum/DictItemTypeEnum.h"
#include "../tips/TipsLayer.h"
MusouBattleList::MusouBattleList()
:m_battleList(NULL)
{

}
//inline bool sortMusouBattleReward(DictMusouBattleReward* a,DictMusouBattleReward* b)
//{
//    return a->id < b->id;
//}
//inline bool sortMusouBattlePrestigeReward(DictMusouBattlePrestigeReward* a,DictMusouBattlePrestigeReward* b)
//{
//    return a->id < b->id;
//}
MusouBattleList::~MusouBattleList()
{
    m_battleList = NULL;
}
bool MusouBattleList::init(Vector<MusouBattleData*>* battleList)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Layer::init());
        this->isAnimation = false;
        this->m_battleList = battleList;

//        this->setContentSize(SDResource.size);
        this->setContentSize(Director::getInstance()->getWinSize());
        setBattleList();
        bref = true;
    } while (false);
    return bref;
}
MusouBattleList* MusouBattleList::create(Vector<MusouBattleData*>* battleList)
{
    MusouBattleList* list = new MusouBattleList();
    if(list && list->init(battleList))
    {
        list->autorelease();
        return list;
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return NULL;
}
Sprite* MusouBattleList::getBattleItem(int index)
{
    MusouBattleData* data = m_battleList->at(index);
    DictMusouBattle* dictMusouBattle = DictMusouBattleManager::getInstance()->getData(data->battleId);
    Sprite* bottomSpr = Sprite::create(IMG_SWEEP_BOTTOMSPR);
    bottomSpr->setAnchorPoint(Point::ZERO);

    Sprite* centerBg = Sprite::create(IMG_MUSOUBATTLE_CENTERBG);
    centerBg->setPosition(bottomSpr->getContentSize().width/2, bottomSpr->getContentSize().height/2);
    bottomSpr->addChild(centerBg,1,index);
    
    const char* path = PublicShowUI::getResImgPath(IMG_MUSOUBATTLE_LEVEL, PublicShowUI::numberToString(dictMusouBattle->indexOrder).c_str());
    Sprite* levelSpr = Sprite::create(path);
    levelSpr->setAnchorPoint(Point::ZERO);
    levelSpr->setPosition(25, centerBg->getContentSize().height - levelSpr->getContentSize().height - 20);
    centerBg->addChild(levelSpr);
    
   
    const char* pathbg = PublicShowUI::getResImgPath(IMG_MUSOUBATTLE_FRONT, PublicShowUI::numberToString(dictMusouBattle->indexOrder).c_str());
    Sprite* smallmap = Sprite::create(pathbg);
    smallmap->setAnchorPoint(Point::ZERO);
    smallmap->setPosition((centerBg->getContentSize().width - smallmap->getContentSize().width)/2, centerBg->getContentSize().height - smallmap->getContentSize().height - 55);
    centerBg->addChild(smallmap,2);
    path = PublicShowUI::getResImgPath(IMG_BATTLE_SMALLMAP, dictMusouBattle->cardResource.c_str());
    Sprite* smallMapbg = Sprite::create(path);
    
    smallMapbg->setScale(.96);
    smallMapbg->setPosition(smallmap->getPositionX() + smallmap->getContentSize().width/2, smallmap->getPositionY() + smallmap->getContentSize().height/2);
    centerBg->addChild(smallMapbg,1);
    
    
    
    //消耗
    Sprite* costPower = Sprite::create(IMG_ICON_PUBLIC_POWER);
    costPower->setAnchorPoint(Point::ZERO);
    Label* label = PublicShowUI::getLabel(PublicShowUI::numberToString(data->costPower).c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),18,false,false);
    label->setAnchorPoint(Point::ZERO);
    label->setPosition(costPower->getContentSize().width, (costPower->getContentSize().height - label->getContentSize().height)/2);
    costPower->addChild(label);
    costPower->setPosition(80, 20);
    centerBg->addChild(costPower,4);
    
    
    Button* btn = Button::create(IMG_PUBLIC_BUTTON_TWO_ORANGE, "", CC_CALLBACK_1( MusouBattleList::onGoBtnclick, this));
    btn->setEnabled(data->status == MusouBattleData::STATUS_ABLE_FIGHT);
    centerBg->addChild(btn,4,data->battleId);
    btn->setPosition(centerBg->getContentSize().width -btn->getContentSize().width/ 2 - 25, 40);
    Sprite* btnTitle = Sprite::create(IMG_PUBLIC_LABEL_JINJIWORD);

    btn->addChild(btnTitle,10,data->battleId);
    
    setDropItems(centerBg,data->rewardList);
    setDropPrestigeItems(centerBg,data->prestigeList);
    return bottomSpr;

    
}
void MusouBattleList::setDropItems(Node* parent,Vector<PrizeData*>* rewardList)//设置掉落物 概率获得
{
    int index = 0;
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    TouchSprite* icon = NULL;
    ssize_t len = rewardList->size();
    PrizeData* data = NULL;
    
    for (int i =0; i < len ; i++)
    {
        data = rewardList->at(i);

        path = PublicShowUI::getGoods(data->itemType, data->itemDictId);
        icon = getItemIcon(path,PublicShowUI::getQuality(data->itemType, data->itemDictId));
        if(icon)
        {
            icon->addTouchBegainCallBack(this, callfuncN_selector(MusouBattleList::onDropItemClick));
            icon->setAnchorPoint(Point::ZERO);
            icon->setPositionX(index * (icon->getContentSize().width + 4));
            container->addChild(icon,index,i);
            index++;
        }
        
    }
    if(icon)
    {
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(120, 140);
        parent->addChild(container,10,parent->getTag());
    }
}
void MusouBattleList::setDropPrestigeItems(Node* parent,Vector<PrizeData*>* prestigeList)//声望获得
{
    int index = 0;
    Node* container = Node::create();
    container->setAnchorPoint(Point::ZERO);
    const char* path = NULL;
    TouchSprite* icon = NULL;
    ssize_t len = prestigeList->size();
    PrizeData* data = NULL;
    for (int i = 0; i < len; i++)
    {
        data = prestigeList->at(i);
      
        path = PublicShowUI::getGoods(data->itemType, data->itemDictId);
        icon = getItemIcon(path,PublicShowUI::getQuality(data->itemType, data->itemDictId));
        if(icon)
        {
            icon->addTouchBegainCallBack(this, callfuncN_selector(MusouBattleList::onPrestigeClick));
            icon->setAnchorPoint(Point::ZERO);
            icon->setPositionX(index * (icon->getContentSize().width + 4));
            container->addChild(icon,index,i);
            index++;
        }
       
    }
    if(icon)
    {
        Size size = icon->getContentSize();
        size.width = icon->getPositionX() + icon->getContentSize().width;
        container->setContentSize(size);
        container->setPosition(120, 75);
        parent->addChild(container,10,parent->getTag());
    }
}
void MusouBattleList::onDropItemClick(Node* node)
{
     MusouBattleData* data = m_battleList->at(node->getParent()->getTag());
    PrizeData* prizeData =data->rewardList->at(node->getTag());
    TipsLayer::show(prizeData->itemType, prizeData->itemDictId, 0);
}
void MusouBattleList::onPrestigeClick(Node* node)
{
    MusouBattleData* data = m_battleList->at(node->getParent()->getTag());
    PrizeData* prizeData =data->prestigeList->at(node->getTag());
    TipsLayer::show(prizeData->itemType, prizeData->itemDictId, 0);
}
TouchSprite* MusouBattleList::getItemIcon(const char* resource,int quality)
{
    if(strcmp(resource, "") == 0)
    {
        return NULL;
    }
    quality = PublicShowUI::getColorIndexByQuality(DictItemTypeEnumItemHero,quality);
    char sttr[100]="";
    sprintf(sttr,IMG_PUBLIC_HEROHEADFRAMEBG,quality);
    
    TouchSprite* headBg = TouchSprite::createWithPic(sttr, NULL, NULL);
    headBg->setAnchorPoint(Point::ZERO);
    
    Sprite* head = Sprite::create(resource);
    if(!head)
    {
        return NULL;
    }
    headBg->addChild(head);
    head->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
    
    
    char stt[100]="";
    sprintf(stt,IMG_PUBLIC_HEADTALENTFRAME,quality);
    
    Sprite* headForm = Sprite::create(stt);
    float sx = (headForm->getContentSize().width - 10) / head->getContentSize().width;
    head->setScale(sx);
    headBg->addChild(headForm);
    headForm->setPosition(headBg->getContentSize().width/2, headBg->getContentSize().height/2);
    headBg->setScale(.5);
    headBg->setContentSize(headBg->getContentSize() * .5);
    return headBg;
}
void MusouBattleList::onGoBtnclick(Ref* pSender)
{
    Dialog::showServerLoading();
    Button* btn = (Button*)pSender;
    
    RequestMusouFightMsg* msg = new RequestMusouFightMsg(btn->getTag());
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
  
}
void MusouBattleList::setBattleList()
{

    Rect swRect = Rect(0,0,VisibleRect::getVisibleRect().size.width,VisibleRect::getVisibleRect().size.height);//scrollView大小
    Size slSize = SDResource.size;//scrollLayer 大小
    float disDistance = 0.31f * SDResource.size.width;//card距离间隔
    float disScale = 0.12f;//crad缩放间隔0.05
    CoverView* coverView = CoverView::create(swRect,slSize,disDistance,disScale);
    
    ssize_t len = m_battleList->size();
    Sprite* item = NULL;
    for(int i = 0; i < len; i++)
    {
        item = getBattleItem(i);
        coverView->addCard(item, i, i);
    }
    this->addChild(coverView);
}