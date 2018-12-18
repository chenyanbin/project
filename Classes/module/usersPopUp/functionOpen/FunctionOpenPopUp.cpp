//
//  FunctionOpenPopUp.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#include "FunctionOpenPopUp.hpp"
#include "../../../commonData/enum/DictFunctionEnum.h"
#include "../../../common/commonEffect/CommonEffect.h"
#include "../../../commonData/dictData/DictFunction/DictFunctionManager.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
FunctionOpenPopUp::FunctionOpenPopUp()
:m_functionID(0)
,effectName("tubiaokaiqi")
,functionEffectName("kaiqixingongneng")
{
    
}
FunctionOpenPopUp::~FunctionOpenPopUp()
{
    
}
bool FunctionOpenPopUp::init(int functionID)
{
    this->setBackground(IMG_PUBLIC_FUNCTIONOPEN);
    this->m_functionID = functionID;

    this->isAnimation = true;
    
    
    return true;
}
FunctionOpenPopUp* FunctionOpenPopUp::create(int functionID)
{
    FunctionOpenPopUp* layer = new FunctionOpenPopUp();
    if(layer && layer->init(functionID))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}
void FunctionOpenPopUp::onEnter()
{
    UserPopUp::onEnter();
}
void FunctionOpenPopUp::onExit()
{
    UserPopUp::onExit();
}
void FunctionOpenPopUp::onExitTransitionDidStart()
{
    UserPopUp::onExitTransitionDidStart();
    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, functionEffectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, effectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
}
void FunctionOpenPopUp::onEnterTransitionDidFinish()
{
    UserPopUp::onEnterTransitionDidFinish();
    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, functionEffectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    // 连接该骨骼动画的资源

    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(FunctionOpenPopUp::onDataLoaded));

    SoundManager::playEffectMusic(EFFECT_FUNCTIONOPEN);
    
    delayClickClose();
}
void FunctionOpenPopUp::onDataLoaded(float percent)
{
    if(percent < 1)
    {
        return;
    }
    Node* node = this->getChildByTag(TAG_BG);
    CommonEffect* commonEffect = CommonEffect::create(functionEffectName.c_str(),false,true);
    commonEffect->setAnchorPoint(Point(.5,0.5));
    commonEffect->setScale(1.5  * GlobalInfo::getInstance()->screenScaleX);
    commonEffect->m_onFinisedcallback = CC_CALLBACK_0(FunctionOpenPopUp::loadIconEffect, this);
    commonEffect->setPosition(node->getContentSize().width/2, node->getContentSize().height / 2  );
    this->addChild(commonEffect,-1);
    

}
void FunctionOpenPopUp::loadIconEffect()
{
    const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, effectName.c_str());
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    
    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(path, this, schedule_selector(FunctionOpenPopUp::onIconEffectLoaded));
}
void FunctionOpenPopUp::onIconEffectLoaded(float percent)
{
    if(percent < 1)
    {
        return;
    }
     Node* node = this->getChildByTag(TAG_BG);
    CommonEffect* commonEffect = CommonEffect::create(effectName.c_str(),false,true);
    commonEffect->m_onFinisedcallback = CC_CALLBACK_0(FunctionOpenPopUp::setIcon, this);
    commonEffect->setAnchorPoint(Point(.5,0));
    commonEffect->setPosition(node->getContentSize().width/2, node->getContentSize().height  );
    this->addChild(commonEffect,3);
  
}
void FunctionOpenPopUp::setIcon()
{
    DictFunction* dictFunction =  DictFunctionManager::getInstance()->getData(m_functionID);
    if(!dictFunction)
    {
        this->removeFromParent();
        return;
    }
     Node* node = this->getChildByTag(TAG_BG);
    if(dictFunction->resource.size() > 0)
    {
        const char* path = PublicShowUI::getResImgPath(IMG_ICON_FUNCTION, dictFunction->resource.c_str());
        Sprite* icon = Sprite::create(path);
        if(icon)
        {
            icon->setAnchorPoint(Point::ZERO);
            PublicShowUI::setTargetScale(icon);
            icon->setOpacity(0);
            icon->runAction(FadeIn::create(1.5));
            icon->setPosition((node->getContentSize().width - icon->getContentSize().width)/2, node->getContentSize().height + 10 * GlobalInfo::getInstance()->screenScaleX);
            this->addChild(icon,2);
            
        }
    }
    
    
    
}