//
//  FogLayer.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-10-16.
//
//

#include "FogLayer.h"
FogLayer::FogLayer()
:_delayTime(0)
,_function(NULL)
{
    
}
FogLayer::~FogLayer()
{
    _function = NULL;
}
bool FogLayer::init(float delayTime,const std::function<void()> &func)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!BaseLayer::init());
        this->_delayTime = delayTime;
        this->isAnimation = false;
        this->_function = func;
        this->isAbleGuiding = false;
        setFogLayer();
        bref = true;
    } while (false);
    return bref;
}
FogLayer* FogLayer::create(float delayTime,const std::function<void()> &func)
{
    FogLayer* layer = new FogLayer();
    if(layer && layer->init(delayTime,func))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    layer = NULL;
    return NULL;
}

void FogLayer::setFogLayer()
{
    Size size = VisibleRect::getVisibleRect().size;
    LayerColor* layer = LayerColor::create(Color4B(255,255,255,255), size.width, size.height);
    this->addChild(layer,0,TAG_BLACKBG);
}
void FogLayer::onEnter()
{
    BaseLayer::onEnter();
    this->setClickEnabled(false);
}
void FogLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void FogLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    
}
void FogLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
    DelayTime* delay = DelayTime::create(.5);
    FadeOut* fadeout =FadeOut::create(this->_delayTime);
    CallFunc* fun = CallFunc::create(CC_CALLBACK_0(FogLayer::onDelayEnd, this));
    this->runAction(Sequence::create(delay,fadeout, fun,NULL));
    

    this->setCascadeOpacityEnabled(true);

    
}
void FogLayer::onDelayEnd()
{
    this->removeFromParent();
    if(_function)
    {
        _function();
    }
}