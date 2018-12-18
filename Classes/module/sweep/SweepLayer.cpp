//
//  Sweep.cpp
//  FightPass
//
//  Created by chenyanbin on 15/7/1.
//
//

#include "SweepLayer.h"
#include "../userWealth/UserWealthLayer.h"
#include "../homeUI/homeMainUI/userHead/UserHead.h"
#include "SweepCardLayer.h"
#include "SweepBoxLayer.h"
#include "SweepCheckLayer.h"
SweepLayer::SweepLayer()
:TAG_USERHEAD(1)
,m_stageID(0)
,boxData(NULL)
,stageBattleList(NULL)
{
    stageBattleList = new Vector<StageBattleData*>();
}
SweepLayer::~SweepLayer()
{
//    log("~SweepLayer ~SweepLayer");
    CC_SAFE_DELETE(boxData);
    boxData = NULL;
    stageBattleList->clear();
    CC_SAFE_DELETE(stageBattleList);
    stageBattleList = NULL;
}
bool SweepLayer::init(ByteStream* byteStream)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->isShowGrayBg = true;
        parseByteStream(byteStream);
        setBackGround();
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx,true);
        
        setUserHead();
        setUserWealth();
        setCardLayer();
        setBoxLayer();
        
        auto callback = [](Touch * ,Event *)
        {
            return true;
        };
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = callback;
        listener->setSwallowTouches(true);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

        
        bref = true;
    } while (false);
    return bref;
}
SweepLayer* SweepLayer::create(ByteStream* byteStream)
{
    SweepLayer* layer= new SweepLayer();
    if(layer && layer->init( byteStream))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}
void SweepLayer::setGrayBg()
{
    if(this->getChildByTag(TAG_BLACKBG))
    {
        return;
    }
    Size size = VisibleRect::getVisibleRect().size;
    LayerColor* layer = LayerColor::create(Color4B(0,0,0,210), size.width*3, size.height*3);
    layer->setPositionX(-this->getPositionX() - size.width/2);
    layer->setPositionY(-this->getPositionY() - size.height/2);
    this->addChild(layer,-2,TAG_BLACKBG);
}
void SweepLayer::show(ByteStream* byteStream)
{
    SweepLayer* layer = SweepLayer::create(byteStream);
    layer->isHideSceneFun = true;
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_MODULAR_TAG,SCENE_TAG_SWEEP);
}
void SweepLayer::parseByteStream(ByteStream* byteStream)
{
    boxData = new BattleBoxData();
    m_stageID = byteStream->getInt();
    boxData->canOpenCount = byteStream->get();
    boxData->canOpenBoxId = byteStream->getInt();
    boxData->starCountMax = byteStream->get();
    boxData->curStarCount = byteStream->get();
    boxData->raidsCardCount = byteStream->getShort();//扫荡令个数
    GlobalInfo::getInstance()->raidsCard =  boxData->raidsCardCount;
    StageBattleData* battleData = NULL;
    int len = byteStream->get();
    for(int i =0 ;i <len; i++)
    {
        battleData = new StageBattleData();
        battleData->autorelease();
        battleData->battleId = byteStream->getInt();
        battleData->starCount = byteStream->get();
        battleData->usableCount = byteStream->get();
        battleData->state = byteStream->get();
        stageBattleList->pushBack(battleData);
    }
}
void SweepLayer::setBackGround()
{
//    Sprite* bg = Sprite::create(IMG_SWEEP_BG);
//    bg->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(bg,true);
//    addChild(bg, 0, TAG_BG);
//    Size size = bg->getContentSize();
//    bg->setPosition(Point::ZERO);
//    this->setContentSize(bg->getContentSize());
    this->setContentSize(VisibleRect::getVisibleRect().size);
}

void SweepLayer::setUserHead()
{
//    UserHead* userHead = UserHead::create();
//    userHead->setAnchorPoint(Point::ZERO);
//    userHead->setPositionX(VisibleRect::left().x + 10*GlobalInfo::getInstance()->screenScaleX);
//    userHead->setPositionY(VisibleRect::top().y - userHead->getContentSize().height - 5 * GlobalInfo::getInstance()->screenScaleX);
//    this->addChild(userHead,3);
    
}
void SweepLayer::setUserWealth()
{
    
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(VisibleRect::center().x-layer->getContentSize().width/2, VisibleRect::top().y-layer->getContentSize().height);
    this->addChild(layer,3);
    
    layer->setTitle(IMG_PUBLIC_CAMPAIGN);

}

void SweepLayer::setCardLayer()
{
//    SweepCardLayer* layer = SweepCardLayer::create(m_stageID,stageBattleList);
//    layer->setAnchorPoint(Point::ZERO);
//    PublicShowUI::setTargetScale(layer);
//    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
//    this->addChild(layer,1);
    
    SweepCheckLayer* layer = SweepCheckLayer::create(m_stageID, stageBattleList);
    layer->setAnchorPoint(Point::ZERO);
    layer->setSwallowsTouches(true);
    PublicShowUI::setTargetScale(layer,false,true);
    layer->setPosition(VisibleRect::center().x -layer->getContentSize().width/2,VisibleRect::center().y-layer->getContentSize().height/2-40*GlobalInfo::getInstance()->screenScaleX);
    this->addChild(layer,1);
}
void SweepLayer::setBoxLayer()
{
    SweepBoxLayer* layer = SweepBoxLayer::create(boxData);
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setScale(0.8*GlobalInfo::getInstance()->screenScaleX);
    layer->setPosition(VisibleRect::center().x+568*GlobalInfo::getInstance()->screenScaleX-layer->getContentSize().width,VisibleRect::center().y+100*GlobalInfo::getInstance()->screenScaleX);
    this->addChild(layer,5);
}


void SweepLayer::onEnter()
{
    BaseLayer::onEnter();
}
void SweepLayer::onExit()
{
    BaseLayer::onExit();
}
void SweepLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void SweepLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
}
void SweepLayer::addEventListener()
{
    
}
void SweepLayer::removeEventListener()
{
    BaseLayer::removeEventListener();
}
