//
//  StageLayer.cpp
//  FightPass
//
//  Created by chenyanbin on 15/6/13.
//
//

#include "StageLayer.h"
#include "../homeUI/homeMainUI/userHead/UserHead.h"
#include "../userWealth/UserWealthLayer.h"
#include "StageListLayer.h"
StageLayer::StageLayer()
:TAG_USERHEAD(1)
{
    
}
StageLayer::~StageLayer()
{
    
}
bool StageLayer::init()
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        setBackGround();
        float sx = GlobalInfo::getInstance()->screenScaleX;
        this->setBackBtn(0,15*sx,true);
        this->isAbleGuiding =true;
//        setUserHead();
        setUserWealth();
        setStageListLayer();
        bref = true;
    } while (false);
    return bref;
}
StageLayer* StageLayer::create()
{
    StageLayer* layer= new StageLayer();
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return layer;
}

void StageLayer::show(int fromScene)
{
    Director::getInstance()->purgeCachedData();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    StageLayer* layer = StageLayer::create();
    layer->setFromScene(fromScene);
//    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(VisibleRect::center().x - layer->getContentSize().width/2, VisibleRect::center().y - layer->getContentSize().height/2);
    
    Scene* scene = Scene::create();
    scene->addChild(layer,0,SCENE_TAG_GOTOBATTLE);
    
    Director::getInstance()->replaceScene(scene);
    
}

void StageLayer::setBackGround()
{
    Sprite* bg = Sprite::create(IMG_PUBLIC_STAGEBG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg,true);
    addChild(bg, 0, TAG_BG);
    Size size = bg->getContentSize();
    bg->setPosition(Point::ZERO);
    this->setContentSize(bg->getContentSize());
}
void StageLayer::onEnter()
{
    BaseLayer::onEnter();
    Director::getInstance()->purgeCachedData();
}
void StageLayer::onExit()
{
    BaseLayer::onExit();
}
void StageLayer::setUserHead()
{
    UserHead* userHead = UserHead::create();
    userHead->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(userHead);
    userHead->setPositionX(VisibleRect::left().x);
    userHead->setPositionY(VisibleRect::top().y - userHead->getContentSize().height - 5 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(userHead,3);
    
}
void StageLayer::setUserWealth()
{
    UserWealthLayer* layer = UserWealthLayer::create(UserWealthLayer::STAGE);
    PublicShowUI::setTargetScale(layer);
    layer->setTitle(IMG_PUBLIC_CAMPAIGN);
    layer->setPositionX(VisibleRect::left().x);
    layer->setPositionY(VisibleRect::top().y - layer->getContentSize().height);
    this->addChild(layer,4);
}
void StageLayer::setStageListLayer()
{
    StageListLayer* layer = StageListLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPositionX(VisibleRect::center().x - layer->getContentSize().width/2);
    layer->setPositionY(VisibleRect::center().y - layer->getContentSize().height/2 - 20 * GlobalInfo::getInstance()->screenScaleX);
    
    this->addChild(layer, 5);
}