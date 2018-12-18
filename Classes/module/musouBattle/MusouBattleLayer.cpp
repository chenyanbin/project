//
//  MusouBattleLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#include "MusouBattleLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "MusouBattleDataList.h"
#include "../../message/Decoding/musou/RequestMusouBattleListMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/Dialog/Dialog.h"
#include "MusouBattle.h"
MusouBattleLayer::MusouBattleLayer()
:battleList(NULL)
,TAG_LEFTTIME(1)
,TAG_BATTLELIST(2)
,m_leftTime(0)
{
    battleList = new Vector<MusouBattleData*>();
}
MusouBattleLayer::~MusouBattleLayer()
{
    CC_SAFE_DELETE(battleList);
    battleList = NULL;
    MusouBattleDataList::destoryInstance();
}
bool MusouBattleLayer::init(ByteStream* byteStream)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        
        parseByteStream(byteStream);
        this->isShowGrayBg = true;
        setBg();
        setUserWealth();
        setBattleList();
        setLeftTime();
        bref = true;
    } while (false);
    return bref;
}
MusouBattleLayer* MusouBattleLayer::create(ByteStream* byteStream)
{
    MusouBattleLayer* layer = new MusouBattleLayer();
    if(layer && layer->init(byteStream))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void MusouBattleLayer::show(ByteStream* byteStream)
{
    Director::getInstance()->purgeCachedData();
    MusouBattleLayer* layer = MusouBattleLayer::create(byteStream);
    layer->setAnchorPoint(Point::ZERO);
    layer->setFromScene(SCENE_TAG_MUSOU);
  
    Scene* scene = Scene::create();
    scene->addChild(layer,SCENE_LAYER_ZORDER);
    Director::getInstance()->replaceScene(scene);
    
}
void MusouBattleLayer::requestBattleList(int stageID)
{
    Dialog::showServerLoading();
    RequestMusouBattleListMsg* msg = new RequestMusouBattleListMsg(stageID);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void MusouBattleLayer::setBg()
{
    this->setBackground(IMG_PUBLIC_MODULE_BG,Point::ZERO,false);
    Node* bg = this->getChildByTag(TAG_BG);
    PublicShowUI::setTargetScale(bg,true,true);
    this->setContentSize(bg->getContentSize());
}
void MusouBattleLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
    layer->setTitle(IMG_PUBLIC_SANGUOWUSHUANG);
    layer->setPositionX(VisibleRect::left().x);
    layer->setPositionY(VisibleRect::top().y - layer->getContentSize().height);
    this->addChild(layer,4);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    this->setBackBtn(20 * sx,15 * sx);
}
void MusouBattleLayer::parseByteStream(ByteStream* byteStream)
{
    this->m_leftTime = byteStream->getInt();
    if(this->m_leftTime > 0)
    {
        this->schedule(schedule_selector(MusouBattleLayer::showDelayTime), 1, m_leftTime, 0);
    }
    battleList->clear();
    int len = byteStream->get();
    MusouBattleData* musouBattle = NULL;
    int prizeCount = 0;
    for(int i = 0; i < len; i++)
    {
        musouBattle = new MusouBattleData();
        musouBattle->autorelease();
        musouBattle->battleId = byteStream->getInt();
        musouBattle->battleType = byteStream->getByte();
        musouBattle->status = byteStream->getByte();
        musouBattle->costPower = byteStream->getInt();
        prizeCount = byteStream->getByte();
        for(int j = 0; j < prizeCount; j++)
        {
            PrizeData* prizeData = new PrizeData();
            prizeData->autorelease();
            prizeData->itemType = byteStream->get();
            prizeData->itemDictId = byteStream->getInt();
            prizeData->itemCount = byteStream->get();
            musouBattle->rewardList->pushBack(prizeData);
        }
        
        prizeCount = byteStream->getByte();
        for(int j = 0; j < prizeCount; j++)
        {
            PrizeData* prizeData = new PrizeData();
            prizeData->autorelease();
            prizeData->itemType = byteStream->get();
            prizeData->itemDictId = byteStream->getInt();
            prizeData->itemCount = byteStream->get();
            musouBattle->prestigeList->pushBack(prizeData);
        }
        battleList->pushBack(musouBattle);
    }
}
void MusouBattleLayer::setBattleList()
{
//    battleList = MusouBattleDataList::getInstance()->getMusouBattleListByMusouID(this->m_musouID);
//    MusouBattleList* list = MusouBattleList::create(battleList);
//    list->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(list);
//     list->setPosition(VisibleRect::center().x - list->getContentSize().width/2, VisibleRect::center().y - list->getContentSize().height/2);
//    this->addChild(list);
//    this->setContentSize(list->getContentSize());
    MusouBattle* list = MusouBattle::create(battleList);
    list->setAnchorPoint(Point::ZERO);
    list->setPosition(VisibleRect::center().x - list->getContentSize().width/2, VisibleRect::center().y - list->getContentSize().height/2 - 20 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(list,2,TAG_BATTLELIST);
    this->setContentSize(list->getContentSize());
}
void MusouBattleLayer::setLeftTime()
{
    Node* battleList = this->getChildByTag(TAG_BATTLELIST);
//    Sprite* leftTimeBg =Sprite::create(IMG_MUSOUBATTLE_LEFTTIMEBG);
//    leftTimeBg->setAnchorPoint(Point::ZERO);
    float sx = GlobalInfo::getInstance()->screenScaleX;
    string str = "00:00:00";
    Label* label = PublicShowUI::getLabel(str.c_str(),PublicShowUI::getColor3b(COLOR_MILK_WHITE),28,false,true);
    label->setAnchorPoint(Point(0,0));
    this->addChild(label,4,TAG_LEFTTIME);
    label->setPosition(battleList->getPositionX() + 180 * sx,battleList->getPositionY() + battleList->getContentSize().height - label->getContentSize().height - 10 * sx);
 
}
void MusouBattleLayer::showDelayTime(float dt)
{
    m_leftTime --;
    if(m_leftTime < 0)
    {
        this->unschedule(schedule_selector(MusouBattleLayer::showDelayTime));
        return;
    }

    Label* label = (Label*)this->getChildByTag(TAG_LEFTTIME);
    label->setString(PublicShowUI::getTime(this->m_leftTime * 1000));
    
}