//
//  FamouseBossCome.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/25.
//
//

#include "FamouseBossCome.hpp"
#include "FamouseComeInfo.hpp"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/data/FunctionOpenManager.h"
FamouseBossCome::FamouseBossCome()
{
    
}
FamouseBossCome::~FamouseBossCome()
{
    
}
bool FamouseBossCome::init()
{
    this->isAnimation = false;
    Sprite* bg = Sprite::create(IMG_FAMOUSE_COMEBG);
    float last_X = ( (float)VisibleRect::getVisibleRect().size.width/ SDResource.size.width) ;
    float last_Y = ( (float)VisibleRect::getVisibleRect().size.height/SDResource.size.height);
    float sx = last_X > last_Y ? last_X : last_Y;
    bg->setPosition(VisibleRect::center());
    bg->setScale(sx);
    this->addChild(bg, 0, TAG_BG);
    
    return true;
}

void FamouseBossCome::show()
{
    if(!FunctionOpenManager::getInstance()->functionIsOpened(DictFunctionEnumLegend))
    {
        return;
    }
    FamouseBossCome* layer = FamouseBossCome::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setFromScene(SCENE_TAG_CHAPTER);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(layer,SCENE_LAYER_ZORDER + 40,SCENE_TAG_BOSSCOME);
}

void FamouseBossCome::setInfo()
{
    float sx = GlobalInfo::getInstance()->screenScaleX;
    FamouseComeInfo* info = FamouseComeInfo::create();
    info->setAnchorPoint(Point::ZERO);
    info->setPosition(VisibleRect::left().x + 100 * sx, VisibleRect::center().y - info->getContentSize().height/2);
    this->addChild(info,3);

}
void FamouseBossCome::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(true);
}
void FamouseBossCome::onExit()
{
     BaseLayer::onExit();
    this->setClickEnabled(false);
}
void FamouseBossCome::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
}
void FamouseBossCome::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
//    shuimo
    CommonEffect* effect = CommonEffect::create("shuimo",false,true);
    effect->m_onFinisedcallback = CC_CALLBACK_1(FamouseBossCome::onEffectFinished, this);
    PublicShowUI::setTargetScale(effect,true,true);
    effect->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(effect,3);
}
void FamouseBossCome::onEffectFinished(Node* pSender)
{
     setInfo();
}
void FamouseBossCome::addEventListener()
{
   
}
void FamouseBossCome::removeEventListener()
{
    BaseLayer::removeEventListener();
}