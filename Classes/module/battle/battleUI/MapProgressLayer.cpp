//
//  MapProgressLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/7/15.
//
//

#include "MapProgressLayer.h"
#include "../../../common/ImagePath.h"
#include "../../../common/PublicShowUI.h"
MapProgressLayer* MapProgressLayer::_instance = NULL;
MapProgressLayer::MapProgressLayer()
:progressDot(NULL)
,progressTimer(NULL)

{
    Sprite* bg = Sprite::create(IMG_BATTLE_PROGRESSBG);
    bg->setAnchorPoint(Point::ZERO);
    this->addChild(bg,0);
    PublicShowUI::setTargetScale(bg);
    this->setContentSize(bg->getContentSize());
    
    Sprite* progress = Sprite::create(IMG_BATTLE_PROGRESSFRONT);
    progress->setAnchorPoint(Point::ZERO);
    
    progressTimer = ProgressTimer::create(progress);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Point(0,1));
    progressTimer->setBarChangeRate(Point(1,0));
    progressTimer->setAnchorPoint(Point(0 ,0));
    PublicShowUI::setTargetScale(progressTimer);
    this->addChild(progressTimer,1);
    progressTimer->setPosition((bg->getContentSize().width - progressTimer->getContentSize().width)/2, (bg->getContentSize().height - progressTimer->getContentSize().height)/2);
    
//    Sprite* hat = Sprite::create(IMG_BATTLE_PROGRESSHAT);
//    hat->setAnchorPoint(Point::ZERO);
//    hat->setPosition(0, this->getContentSize().height);
//    this->addChild(hat,2);
}
MapProgressLayer::~MapProgressLayer()
{
    _instance = NULL;
    progressDot = NULL;
    progressTimer = NULL;
}
MapProgressLayer* MapProgressLayer::getInstance()
{
    if(!_instance)
    {
        _instance = new MapProgressLayer();
        _instance->autorelease();
    }
    return _instance;
}
void MapProgressLayer::onEnter()
{
    Node::onEnter();
    setProgress();
}
void MapProgressLayer::onExit()
{
    Node::onExit();
}
void MapProgressLayer::setProgress()
{
    progressDot = Sprite::create(IMG_BATTLE_PROGRESSDOT);
    progressDot->setAnchorPoint(Point(.5,0));
    progressDot->setPosition(0, this->getContentSize().height);
    this->addChild(progressDot,2);
    updateProgress(0);

}
void MapProgressLayer::updateProgress(float percent)
{
    float posX = this->getContentSize().width * percent / 100;
    percent += 10;
    progressDot->setPositionX(posX);
    progressTimer->setPercentage(percent);
}