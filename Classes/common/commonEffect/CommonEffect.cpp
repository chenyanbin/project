//
//  CommonEffect.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-29.
//
//

#include "CommonEffect.h"

#include "../ImagePath.h"
#include "../PublicShowUI.h"
#include "../../protocol/UserCustomEvent.h"

CommonEffect::CommonEffect()
:m_name(NULL)
,m_isLoop(false)
,isAutoStop(false)
,onClick(NULL)
,touchListener(NULL)
,m_isRemoveCache(true)
,m_callBack(NULL)
,TAG_ARMATURE(1)
{
    
}
CommonEffect::~CommonEffect()
{

    onClick = NULL;
    m_callBack = NULL;
    CC_SAFE_RELEASE_NULL(touchListener);
    m_onFinisedcallback = NULL;
}
void CommonEffect::removeCache()
{
    if(m_name)
    {
        if (m_isRemoveCache)
        {
            pureCache(this->m_name);
        }
        m_name = NULL;
    }
}
bool CommonEffect::init(const char* name,bool isLoop,bool isRemoveCache,std::function<void()> _callBack)
{
    bool bref = false;
    do {
        CC_BREAK_IF(!Node::init());
        m_name = name;
        this->m_isLoop = isLoop;
        this->m_isRemoveCache = isRemoveCache;
        const char* path = PublicShowUI::getAvatarPath(IMG_PUBLIC_EFFECT, name);
        this->m_callBack = _callBack;
     
        // 连接该骨骼动画的资源
        if(!ArmatureDataManager::getInstance()->getAnimationData(m_name))
        {
            ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
            ArmatureDataManager::getInstance()->addArmatureFileInfo(path);
        }
        else
        {
            log("lsdjkflsdjlf");
        }
        onDataLoaded(1);
        bref = true;
    } while (false);
   
    return bref;
}
void CommonEffect::release()
{
    Node::release();
}
CommonEffect* CommonEffect::create(const char* name,bool isLoop,bool isRemoveCache,std::function<void()> _callBack)
{
    CommonEffect* effect = new CommonEffect();
    if(effect && effect->init(name,isLoop,isRemoveCache,_callBack))
    {
        effect->autorelease();
        return effect;
    }
    CC_SAFE_DELETE(effect);
    return NULL;  
}

void CommonEffect::onDataLoaded(float percent)
{
    log("CommonEffect===%s, percent=%f",this->m_name,percent);
    if(percent < 1)
    {
        return;
    }
    ArmatureData *armatureData = ArmatureDataManager::getInstance()->getArmatureData(m_name);
    if(!armatureData)
    {
        removeSelf();
        return;
    }
    Armature *pArmature = Armature::create(this->m_name);

  
    
    pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CommonEffect::onEffectMovementEvent));
   this->addChild(pArmature,1,TAG_ARMATURE);
    
    pArmature->setAnchorPoint(m_anchorPoint);
    this->setContentSize(pArmature->getContentSize());
    
    
}
void CommonEffect::rePlay()
{
    Armature *pArmature = this->getArmature();
    if(pArmature)
    {
        pArmature->getAnimation()->stop();

         pArmature->getAnimation()->playWithIndex(0);
    }
   
}
void CommonEffect::pureCache(const char* name)
{
    const char* path = PublicShowUI::getResImgPath(IMG_PUBLIC_EFFECT, name);
    ArmatureDataManager::getInstance()->removeArmatureFileInfo(path);
    ArmatureDataManager::getInstance()->removeAnimationData(name);
    path = NULL;

}
Armature* CommonEffect::getArmature()
{
    return (Armature*)this->getChildByTag(1);
}
void CommonEffect::setAnchorPoint(Point cp)
{
    m_anchorPoint = cp;
    Armature *pArmature = getArmature();
    if(pArmature)
    {
        pArmature->setAnchorPoint(cp);
    }
}
void CommonEffect::onEnter()
{
    Node::onEnter();
    
   
}
void CommonEffect::onExit()
{
    Node::onExit();
    
}
void CommonEffect::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    Armature* pArmature = ( Armature*)this->getChildByTag(TAG_ARMATURE);
    if(pArmature)
    {
        pArmature->pause();
        pArmature->getAnimation()->stop();
    }
    if(touchListener)
    {
        _eventDispatcher->removeEventListener(touchListener);
    }
  removeCache();

}
void CommonEffect::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    if(!touchListener)
    {
        touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(touchListener);
        touchListener->setSwallowTouches(false);
        touchListener->onTouchBegan = CC_CALLBACK_2(CommonEffect::ccTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(CommonEffect::ccTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(CommonEffect::ccTouchEnded, this);
    }
    _eventDispatcher->removeEventListener(touchListener);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Armature* pArmature = ( Armature*)this->getChildByTag(TAG_ARMATURE);
    if(pArmature)
    {
         pArmature->getAnimation()->playWithIndex(0);
    }
    else
    {
        removeSelf();
    }

}
bool CommonEffect::ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    return true;
}
void CommonEffect::ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
    
}
void CommonEffect::ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{
   if(isClickSprite(pTouch))
   {
       if(this->onClick)
       {
           onClick(this);
       }
   }
}
void CommonEffect::setClickOffsetRect(Rect rect)
{
    this->m_clickOffsetRect = rect;
}
bool CommonEffect::isClickSprite(cocos2d::Touch* pTouch)
{
    Rect rect = PublicShowUI::getRect(this);
    //     s_visibleRect.origin = glview->getVisibleOrigin();
//    s_visibleRect.size = glview->getVisibleSize();
    rect.origin.x += this->m_clickOffsetRect.origin.x;
    rect.origin.y += this->m_clickOffsetRect.origin.y;
    rect.size.width += this->m_clickOffsetRect.size.width;
    rect.size.height += this->m_clickOffsetRect.size.height;
    
    Point point = pTouch->getLocation();
    
    point = this->getParent()->convertToNodeSpace(point);
    if(rect.containsPoint(point))
    {
        return true;
    }
    return false;
}
void CommonEffect::onEffectMovementEvent(Armature *armature, MovementEventType type, const std::string& name)
{
    if(type != MovementEventType::COMPLETE && type != MovementEventType::LOOP_COMPLETE)
    {
        return;
    }
    if(m_onFinisedcallback)
    {
        m_onFinisedcallback(this);
    }
    if(!this->m_isLoop)
    {
        armature->getAnimation()->stop();
        armature->getAnimation()->setMovementEventCallFunc(NULL, NULL);
        if(isAutoStop == false)
        {
            DelayTime* delay = DelayTime::create(0.1);
            this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(CommonEffect::removeSelf, this)), NULL));
            
            EventDispatcher* dispatch = Director::getInstance()->getEventDispatcher();
            EventCustom event(CUSTOM_EFFECTEND_EVENT);
            dispatch->dispatchEvent(&event);
        }
        else
        {
//            EventDispatcher* dispatch = Director::getInstance()->getEventDispatcher();
//            EventCustom event(CUSTOM_EFFECTEND_EVENT);
//            dispatch->dispatchEvent(&event);
        }

    }
}
void CommonEffect::removeSelf()
{
    if(this->m_callBack)
    {
        this->m_callBack();
    }
    if(this->getParent())
    {
        this->removeFromParent();
    }
}