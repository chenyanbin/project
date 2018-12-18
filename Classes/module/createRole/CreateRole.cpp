//
//  CreateRole.cpp
//  FightPass
//
//  Created by zhangbin on 16/4/15.
//
//

#include "CreateRole.hpp"
#include "RandomNameLayer.hpp"
CreateRole::CreateRole()
{
    
}
CreateRole::~CreateRole()
{
    
}
bool CreateRole::init()
{
    this->isAnimation = false;
  
    Sprite* bg = Sprite::create(IMG_CREATEROLE_BG);
    bg->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(bg,true,true);
    this->addChild(bg, 0, TAG_BG);
    this->setContentSize(bg->getContentSize());
    setRandNameLayer();
    return true;
}

Scene* CreateRole::createScene(int fromeScene )
{
    Scene* scene = Scene::create();
    CreateRole* layer = CreateRole::create();
    layer->setFromScene(fromeScene);
    scene->addChild(layer, 0);
    return scene;
}
void CreateRole::show()
{
    Scene* scene = CreateRole::createScene();
    Director::getInstance()->replaceScene(scene);
}
void CreateRole::onEnter()
{
    BaseLayer::onEnter();
}
void CreateRole::onExit()
{
    BaseLayer::onExit();
}
void CreateRole::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void CreateRole::onEnterTransitionDidFinish()
{
     BaseLayer::onEnterTransitionDidFinish();
}
void CreateRole::addEventListener()
{
 
}
void CreateRole::removeEventListener()
{
    BaseLayer::removeEventListener();
}
void CreateRole::setRandNameLayer()
{
    RandomNameLayer* layer = RandomNameLayer::create();
    layer->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(layer);
    layer->setPosition(this->getContentSize().width/2 - 10 * GlobalInfo::getInstance()->screenScaleX , VisibleRect::bottom().y + 80 * GlobalInfo::getInstance()->screenScaleY);
    this->addChild(layer,1);
    
}
